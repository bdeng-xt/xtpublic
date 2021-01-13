#pragma once
#ifndef XT_CRITICAL_SECTION_H
#define XT_CRITICAL_SECTION_H

/**
* \file XTCriticalSection.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a critical section class .
*
* \description
*	Designed for a critical section class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include <memory>

#include "XTExceptions.h"
#include "XTTimestamp.h"
#include "XTLocker.h"

#include "XTConfig.h"
namespace XT
{

	//! Critical section synchronization primitive
	/*!
		Critical sections prevents code fragments from access by multiple threads simultaneously. Only one thread can
		access the code inside the critical section. Other threads must wait for the lock! Critical sections are usually
		more lightweight than mutexes and don't enter kernel mode.

		Thread-safe.

		https://en.wikipedia.org/wiki/Critical_section
	*/
	class XT_COMMON_API CriticalSection
	{
		friend class ConditionVariable;

	public:
		CriticalSection();
		CriticalSection(const CriticalSection&) = delete;
		CriticalSection(CriticalSection&& cs) = delete;
		~CriticalSection();

		CriticalSection& operator=(const CriticalSection&) = delete;
		CriticalSection& operator=(CriticalSection&& cs) = delete;

		//! Try to acquire critical section without block
		/*!
			Will not block.

			\return 'true' if the critical section was successfully acquired, 'false' if the critical section is busy
		*/
		bool TryLock();

		//! Try to acquire critical section for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the critical section
			\return 'true' if the critical section was successfully acquired, 'false' if the critical section is busy
		*/
		bool TryLockFor(const XTTimespan& timespan);
		//! Try to acquire critical section until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the critical section
			\return 'true' if the critical section was successfully acquired, 'false' if the critical section is busy
		*/
		bool TryLockUntil(const XTUtcTimestamp& timestamp)
		{
			return TryLockFor(timestamp - XTUtcTimestamp());
		}

		//! Acquire critical section with block
		/*!
			Will block.
		*/
		void Lock();

		//! Release critical section
		/*!
			Will not block.
		*/
		void Unlock();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;

		//! Get the native critical section handler
		void* native() noexcept;
	};

}


#endif