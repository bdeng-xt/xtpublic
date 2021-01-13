#pragma once
#ifndef XT_NAMED_CRITICAL_SECTION_H
#define XT_NAMED_CRITICAL_SECTION_H

/**
* \file XTNamedCriticalSection.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a named critical section class .
*
* \description
*	Designed for a named critical section class.
*/

#include <cstdint>
#include <string>
#include <iostream> 


#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
 
#include "XTConfig.h"

namespace XT
{

	//! Named critical section synchronization primitive
	/*!
		Named critical section behaves as a simple critical section but could be shared
		between processes on the same machine.

		Thread-safe.

		\see CriticalSection
	*/
	class XT_COMMON_API NamedCriticalSection
	{
	public:
		//! Default class constructor
		/*!
			\param name - Critical section name
		*/
		explicit NamedCriticalSection(const std::string& name);
		NamedCriticalSection(const NamedCriticalSection&) = delete;
		NamedCriticalSection(NamedCriticalSection&& cs) = delete;
		~NamedCriticalSection();

		NamedCriticalSection& operator=(const NamedCriticalSection&) = delete;
		NamedCriticalSection& operator=(NamedCriticalSection&& cs) = delete;

		//! Get the critical section name
		const std::string& name() const;

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
	};

////


}//namespace XT

#endif