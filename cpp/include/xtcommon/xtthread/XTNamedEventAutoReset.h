#pragma once
#ifndef XT_NAMED_EVENT_AUTO_RESET_H
#define XT_NAMED_EVENT_AUTO_RESET_H

/**
* \file XTNamedEventAutoReset.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a named auto reset event class .
*
* \description
*	Designed for a named auto reset event class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include "XTTimestamp.h"

#include <memory>
#include "XTConfig.h"

namespace XT
{

	//! Named auto-reset event synchronization primitive
	/*!
		Named auto-reset event behaves as a simple auto-reset event but could be shared
		between processes on the same machine.

		Thread-safe.

		\see EventAutoReset
	*/
	class XT_COMMON_API NamedEventAutoReset
	{
	public:
		//! Default class constructor
		/*!
			\param name - Event name
			\param signaled - Signaled event initial state (default is false)
		*/
		explicit NamedEventAutoReset(const std::string& name, bool signaled = false);
		NamedEventAutoReset(const NamedEventAutoReset&) = delete;
		NamedEventAutoReset(NamedEventAutoReset&& event) = delete;
		~NamedEventAutoReset();

		NamedEventAutoReset& operator=(const NamedEventAutoReset&) = delete;
		NamedEventAutoReset& operator=(NamedEventAutoReset&& event) = delete;

		//! Get the event name
		const std::string& name() const;

		//! Signal one of waiting thread about event occurred
		/*!
			If some threads are waiting for the event one will be chosen, signaled and continued.
			The order of thread signalization by auto-reset event is not guaranteed.

			Will not block.
		*/
		void Signal();

		//! Try to wait the event without block
		/*!
			Will not block.

			\return 'true' if the event was occurred before and no other threads were signaled, 'false' if the event was not occurred before
		*/
		bool TryWait();

		//! Try to wait the event for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the event
			\return 'true' if the event was occurred, 'false' if the event was not occurred
		*/
		bool TryWaitFor(const XTTimespan& timespan);
		//! Try to wait the event until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the event
			\return 'true' if the event was occurred, 'false' if the event was not occurred
		*/
		bool TryWaitUntil(const XTUtcTimestamp& timestamp)
		{
			return TryWaitFor(timestamp - XTUtcTimestamp());
		}

		//! Try to wait the event with block
		/*!
			Will block.
		*/
		void Wait();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};
//////

}//namespace XT

#endif