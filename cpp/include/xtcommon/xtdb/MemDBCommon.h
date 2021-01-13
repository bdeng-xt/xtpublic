#pragma once
#ifndef XT_MEMDB_COMMON_H
#define XT_MEMDB_COMMON_H


#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <csignal>
#include <utility>

#include "XTConfig.h"
#include "log4z.h"

#include "MemDBEvent.h"

#include "rx.hpp"



namespace XT
{



	namespace rx
	{
		using namespace rxcpp;
		using namespace rxcpp::operators;
		using namespace rxcpp::util;

		auto is = [](int32_t msg_type)
		{
			return filter([=](XT::MsgEventPtr e)
			{
				return e->msg_type() == msg_type;
			});
		};

		 auto from = [](uint32_t source)
		{
			return filter([=](XT::MsgEventPtr e)
			{
				return e->source() == source;
			});
		};

		auto to = [](uint32_t dest)
		{
			return filter([=](XT::MsgEventPtr e)
			{
				return e->dest() == dest;
			});
		};

		 auto trace = []()
		{
			return map([=](XT::MsgEventPtr e)
			{
				printf("coming event %d\n", e->msg_type());
				return e;
			});
		};

		 auto interrupt_on_error(std::exception_ptr e)
		{
			try
			{
				std::rethrow_exception(e);
			}
			catch (const std::exception &ex)
			{
				LOGE("Unexpected exception" + std::string(typeid(ex).name()) + ", by subscriber:" + ex.what()); // SPDLOG_ERROR("Unexpected exception {} by rx:subscriber {}", typeid(ex).name(), ex.what());
			}
			raise(SIGINT);
		}

		template<class Arg>
		inline auto $(Arg an) -> decltype(subscribe<XT::MsgEventPtr>(std::forward<Arg>(an), interrupt_on_error))
		{
			return subscribe<XT::MsgEventPtr>(std::forward<Arg>(an), interrupt_on_error);
		}

		template<class... ArgN>
		inline auto $(ArgN &&... an) -> decltype(subscribe<XT::MsgEventPtr>(std::forward<ArgN>(an)...))
		{
			return subscribe<XT::MsgEventPtr>(std::forward<ArgN>(an)...);
		}
	}



}//namespace XT


#endif //