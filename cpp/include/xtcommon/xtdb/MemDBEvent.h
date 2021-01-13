#pragma once
#ifndef XT_MEMDB_EVENT_H
#define XT_MEMDB_EVENT_H


#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "log4z.h"



namespace XT
{

	class MsgEvent
	{
	public:

		virtual ~MsgEvent() = default;

		virtual int64_t gen_time() const = 0;

		virtual int64_t trigger_time() const = 0;

		virtual int32_t msg_type() const = 0;

		virtual uint32_t source() const = 0;

		virtual uint32_t dest() const = 0;

		virtual uint32_t data_length() const = 0;

		virtual const char *data_as_bytes() const = 0;

		virtual const std::string data_as_string() const = 0;

		virtual const std::string to_string() const = 0;

		/**
		* Using auto with the return mess up the reference with the undlerying memory address, DO NOT USE it.
		* @tparam T
		* @return a casted reference to the underlying memory address
		*/
		template<typename T>
		inline const T &data() const
		{
			return *(reinterpret_cast<const T *>(data_address()));
		}

	protected:
		virtual const void *data_address() const = 0;
	};

	typedef std::shared_ptr<MsgEvent> MsgEventPtr; //

	class MsgPublisher
	{
	public:

		virtual ~MsgPublisher() = default;

		virtual int notify() = 0;

		virtual int publish(const std::string &json_message) = 0;
	};

	typedef std::shared_ptr<MsgPublisher> MsgPublisherPtr; //

	class MsgSubscriber
	{
	public:

		virtual ~MsgSubscriber() = default;

		virtual bool wait() = 0;

		virtual const std::string &get_notice() = 0;
	};

	typedef std::shared_ptr<MsgSubscriber> MsgSubscriberPtr; //

}//namespace



#endif