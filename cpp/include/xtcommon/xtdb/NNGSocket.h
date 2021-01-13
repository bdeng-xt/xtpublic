#pragma once
#ifndef XT_NNG_SOCKET_H
#define XT_NNG_SOCKET_H


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
//#include "nng.h"
#include "nng.h" 
#include "compat/nanomsg/nn.h"
#include "compat/nanomsg/nn_pubsub.h"
#include "compat/nanomsg/nn_reqrep.h"
#include "compat/nanomsg/nn_pipeline.h"
#include "compat/nanomsg/nn_bus.h"

#include "NNGUtil.h"
#include "MemDBData.h"
#include "MemDBEvent.h"
 
#include "nlohmann_json.hpp"

namespace XT
{
#define MAX_MSG_LENGTH 16 * 1024
#define DEFAULT_NOTICE_TIMEOUT 1000


	class nn_exception : public std::exception
	{
	public:
		nn_exception() : errno_(nn_errno())
		{}

		virtual const char *what() const throw();

		int num() const;

	private:
		int errno_;
	};

	///////




	class NNGSocket
	{
	public:
		NNGSocket(int protocol) : NNGSocket(AF_SP, protocol, MAX_MSG_LENGTH)
		{};

		NNGSocket(int domain, int protocol) : NNGSocket(domain, protocol, MAX_MSG_LENGTH)
		{};

		NNGSocket(int domain, int protocol, int buffer_size);

		~NNGSocket();

		void setsockopt(int level, int option, const void *optval, size_t optvallen);

		void setsockopt_str(int level, int option, std::string value);

		void setsockopt_int(int level, int option, int value);

		void getsockopt(int level, int option, void *optval, size_t *optvallen);

		int getsockopt_int(int level, int option);

		int bind(const std::string &path);

		int connect(const std::string &path);

		void shutdown(int how = 0);

		void close();

		int send(const std::string &msg, int flags = NN_DONTWAIT) const;

		int recv(int flags =  NN_DONTWAIT);

		const std::string &recv_msg(int flags = NN_DONTWAIT);

		int send_json(const nlohmann::json &msg, int flags = NN_DONTWAIT) const;

		nlohmann::json recv_json(int flags = 0);

		const std::string &request(const std::string &json_message);

		const int get_protocol() const
		{
			return protocol_;
		};

		const std::string &get_url() const
		{
			return url_;
		};

		const std::string &last_message() const
		{
			return message_;
		};

	private:
		int sock_;
		int protocol_;
		std::string url_;
		std::vector<char> buf_;
		std::string message_;
	//	size_t rcv_size;

		/*  Prevent making copies of the socket by accident. */
		NNGSocket(const NNGSocket &);

		void operator=(const NNGSocket &) {}
	};

	typedef std::shared_ptr<NNGSocket> NNGSocketPtr; //
	//////



}//namespace


#endif