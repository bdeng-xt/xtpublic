#pragma once
#ifndef XT_NNG_MSG_PUBSUB_H
#define XT_NNG_MSG_PUBSUB_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <memory>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "XTSocket.h"

#include "nlohmann_json.hpp"

#include "nng.h" 
#include "compat/nanomsg/nn.h"
#include "compat/nanomsg/nn_pubsub.h"
#include "compat/nanomsg/nn_reqrep.h"
#include "compat/nanomsg/nn_pipeline.h"
#include "compat/nanomsg/nn_bus.h"

#include "NNGUtil.h"
#include "MemDBData.h"
#include "MemDBEvent.h"
#include "NNGUtil.h"
#include "NNGSocket.h"

namespace XT
{

	class JsonMsgEvent : public MsgEvent
	{
	public:
		JsonMsgEvent(const std::string &msg)
			//: binding_(nlohmann::json::parse(msg.c_str() ), msg_(msg)
		{
			msg_ = msg;
			binding_ = nlohmann::json::parse(msg.c_str());
		};

		int64_t gen_time() const override
		{
			return get_meta<int64_t>("gen_time", 0);
		}

		int64_t trigger_time() const override
		{
			return get_meta<int64_t>("trigger_time", 0);
		}

		int32_t msg_type() const override
		{
			return get_meta<int32_t>("msg_type", 0);
		}

		uint32_t source() const override
		{
			return get_meta<uint32_t>("source", 0);
		}

		uint32_t dest() const override
		{
			return get_meta<uint32_t>("dest", 0);
		}

		uint32_t data_length() const override
		{
			return binding_.size();
		}

		const char *data_as_bytes() const override
		{
			return msg_.c_str();
		}

		const std::string data_as_string() const override
		{
			return binding_["data"].dump();
		}

		const std::string to_string() const override
		{
			return msg_;
		}

	protected:
		const void *data_address() const override
		{
			return &binding_["data"];
		}

	private:
		nlohmann::json binding_;
		std::string msg_;

		template<typename T>
		T get_meta(const std::string &name, T default_value) const
		{
			if (binding_.find(name) == binding_.end())
			{
				return default_value;
			}
			else
			{
				T value = binding_[name];
				return value;
			}
		}
	};
	typedef std::shared_ptr<JsonMsgEvent> JsonMsgEventPtr;
	//////

	class NNGMsgPublisher : public MsgPublisher
	{
	public:
		NNGMsgPublisher(bool low_latency, int protocol) : socket_(protocol), low_latency_(low_latency)
		{}

		~NNGMsgPublisher() override
		{
			socket_.close();
		}

		void init(const MemDBIODevice &io)
		{
			auto location = std::make_shared<MemDBLocation>((int)EventModeType::Live, (int)EventCategoryType::System, "master", "master",
				io.get_home()->locator);
			init_socket(socket_, location, io.get_url_factory());
		}

		int notify() override
		{
			return low_latency_ ? 0 : publish("{}");
		}

		int publish(const std::string &json_message) override
		{
			return socket_.send(json_message);
		}

	protected:
		virtual void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory)
		{}

	private:
		const bool low_latency_;
		NNGSocket socket_;
	};

	class NNGMsgPublisherMaster : public NNGMsgPublisher
	{
	public:
		NNGMsgPublisherMaster(bool low_latency) : NNGMsgPublisher(low_latency, (int)NN_PUB)
		{}

	protected:
		void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory) override
		{
			s.bind(url_factory->make_path_bind(location, s.get_protocol()));
		}
	};

	class NNGMsgPublisherClient : public NNGMsgPublisher
	{
	public:
		NNGMsgPublisherClient(bool low_latency) : NNGMsgPublisher(low_latency, (int)NN_PUSH)
		{}

	protected:
		void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory) override
		{
			s.connect(url_factory->make_path_connect(location, s.get_protocol()));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	};

	class NNGMsgSubscriber : public MsgSubscriber
	{
	public:
		NNGMsgSubscriber(bool low_latency, int protocol) : low_latency_(low_latency), socket_(protocol), recv_flags_(low_latency ? NN_DONTWAIT : 0)
		{}

		void init(const MemDBIODevice &iodevice)
		{
			auto location = std::make_shared<MemDBLocation>((int)EventModeType::Live, (int)EventCategoryType::System, "master", "master",
				iodevice.get_home()->locator);
			init_socket(socket_, location, iodevice.get_url_factory());
			if (not low_latency_)
			{
				socket_.setsockopt_int(NN_SOL_SOCKET, NN_RCVTIMEO, DEFAULT_NOTICE_TIMEOUT);
			}
		}

		virtual ~NNGMsgSubscriber()
		{
			socket_.close();
		}

		bool wait() override
		{
			return socket_.recv(recv_flags_) > 0;
		}

		const std::string &get_notice() override
		{
			return socket_.last_message();
		}

	protected:

		virtual void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory)
		{}

	private:
		const bool low_latency_;
		NNGSocket socket_;
		int recv_flags_;
	};

	class NNGMsgSubscriberMaster : public NNGMsgSubscriber
	{
	public:
		NNGMsgSubscriberMaster(bool low_latency) : NNGMsgSubscriber(low_latency, (int)NN_PULL)
		{}

	protected:
		void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory) override
		{
			s.bind(url_factory->make_path_bind(location, s.get_protocol()));
		}
	};

	class NNGMsgSubscriberClient : public NNGMsgSubscriber
	{
	public:
		NNGMsgSubscriberClient(bool low_latency) : NNGMsgSubscriber(low_latency, (int)NN_SUB)
		{}

	protected:
		void init_socket(NNGSocket &s, MemDBLocationPtr location, URLFactoryPtr url_factory) override
		{
			s.connect(url_factory->make_path_connect(location, s.get_protocol()));
			s.setsockopt_str(NN_SUB, NN_SUB_SUBSCRIBE, "");
		}
	};



}//namespace 


#endif