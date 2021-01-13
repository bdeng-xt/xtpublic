#pragma once
#ifndef XT_THREAD_H
#define XT_THREAD_H

/**
* \file XTThread.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a thread class .
*
* \description
*	Designed for a thread class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include "XTExceptions.h"
#include "XTTimestamp.h"

#include <bitset>
#include <thread>
#include "XTConfig.h"

//! Current thread Id macro
/*!
	Get the current thread Id.
*/
#define __THREAD__ XT::XTThread::CurrentThreadId()

namespace XT
{

	//! Thread abstraction
	/*!
		Thread contains different kinds of thread manipulation  functionality  such  as
		retrive the current thread Id, sleep for the given time period in  nanoseconds,
		etc.

		Thread-safe.
	*/
	class XT_COMMON_API XTThread
	{
	public:
		//! Supported thread priorities
		enum class Priority : uint8_t
		{
			IDLE = 0x00,    //!< Idle thread priority
			LOWEST = 0x1F,    //!< Lowest thread priority
			LOW = 0x3F,    //!< Low thread priority
			NORMAL = 0x7F,    //!< Normal thread priority
			HIGH = 0x9F,    //!< High thread priority
			HIGHEST = 0xBF,    //!< Highest thread priority
			REALTIME = 0xFF     //!< Realtime thread priority
		};

		XTThread() = delete;
		XTThread(const XTThread&) = delete;
		XTThread(XTThread&&) = delete;
		~XTThread() = delete;

		XTThread& operator=(const XTThread&) = delete;
		XTThread& operator=(XTThread&&) = delete;

		//! Get the current thread Id
		/*!
			\return Current thread Id
		*/
		static uint64_t CurrentThreadId() noexcept;

		//! Get the current thread CPU affinity
		/*!
			\return Current thread CPU affinity
		*/
		static uint32_t CurrentThreadAffinity() noexcept;

		//! Start a new thread with an exception handler registered
		/*!
			Works the same way as std::thread() does but also register an exception handler
			with ExceptionsHandler.SetupThread() call.

			\param fn - Thread function
			\param args - Thread function arguments
			\return Instance of a new thread
		*/
		template <class Fn, class... Args>
		static std::thread Start(Fn&& fn, Args&&... args);

		//! Sleep the current thread for the given milliseconds
		/*!
			\param milliseconds - Milliseconds to sleep
		*/
		static void Sleep(int64_t milliseconds) noexcept
		{
			SleepFor(XTTimespan::milliseconds(milliseconds));
		}
		//! Sleep the current thread for the given timespan
		/*!
			\param timespan - Timespan to sleep
		*/
		static void SleepFor(const XTTimespan& timespan) noexcept;
		//! Sleep the current thread until the given timestamp
		/*!
			\param timestamp - Timestamp to stop sleeping
		*/
		static void SleepUntil(const XTUtcTimestamp& timestamp) noexcept
		{
			SleepFor(timestamp - XTUtcTimestamp());
		}

		//! Yield to other threads
		static void YieldToOther() noexcept;

		//! Get the current thread CPU affinity bitset
		/*!
			\return CPU affinity bitset of the current thread
		*/
		static std::bitset<64> GetAffinity();
		//! Get the given thread CPU affinity bitset
		/*!
			\param thread - Thread
			\return CPU affinity bitset of the given thread
		*/
		static std::bitset<64> GetAffinity(std::thread& thread);

		//! Set the current thread CPU affinity bitset
		/*!
			\param affinity - Thread CPU affinity bitset
		*/
		static void SetAffinity(const std::bitset<64>& affinity);
		//! Set the given thread CPU affinity bitset
		/*!
			\param thread - Thread
			\param affinity - Thread CPU affinity bitset
		*/
		static void SetAffinity(std::thread& thread, const std::bitset<64>& affinity);

		//! Get the current thread priority
		/*!
			\return Priority of the current thread
		*/
		static Priority GetPriority();
		//! Get the given thread priority
		/*!
			\param thread - Thread
			\return Priority of the given thread
		*/
		static Priority GetPriority(std::thread& thread);

		//! Set the current thread priority
		/*!
			\param priority - Thread priority
		*/
		static void SetPriority(Priority priority);
		//! Set the given thread priority
		/*!
			\param thread - Thread
			\param priority - Thread priority
		*/
		static void SetPriority(std::thread& thread, Priority priority);
	};//class

	template <class Fn, class... Args>
	inline std::thread XTThread::Start(Fn&& fn, Args&&... args)
	{
//		return std::thread(
//		[fn = fn, args...]()
//		{
//			// Setup exception handler for the new thread
//			ExceptionsHandler::SetupThread();
//
//			// Call the base thread function
//			fn(std::move(args)...);
//		}
//		);

//		auto thfunc =[&fn,&args...]() {
//			// Setup exception handler for the new thread
//			ExceptionsHandler::SetupThread();
//			fn(args...);
//		};
//		return std::thread(thfunc);
		std::cout<<"Thread::Start, TODO, not implemented in c++11 yet!" << std::endl;
		return std::thread(
			[]() {}
			);
	}

}//namespace

#endif