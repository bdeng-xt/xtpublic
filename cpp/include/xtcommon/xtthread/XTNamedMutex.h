#pragma once
#ifndef XT_NAMED_MUTEX_H
#define XT_NAMED_MUTEX_H

/**
* \file XTNamedMutex.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a named mutex class .
*
* \description
*	Designed for a named mutex class.
*/


#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
#include <string>
#include "XTConfig.h"

namespace XT
{

	//! Named mutex synchronization primitive
	/*!
		Named mutex behaves as a simple mutex but could be shared between processes
		on the same machine.

		Thread-safe.

		\see Mutex
	*/
	class XT_COMMON_API NamedMutex
	{
	public:
		//! Default class constructor
		/*!
			\param name - Mutex name
		*/
		explicit NamedMutex(const std::string& name);
		NamedMutex(const NamedMutex&) = delete;
		NamedMutex(NamedMutex&& mutex) = delete;
		~NamedMutex();

		NamedMutex& operator=(const NamedMutex&) = delete;
		NamedMutex& operator=(NamedMutex&& mutex) = delete;

		//! Get the mutex name
		const std::string& name() const;

		//! Try to acquire mutex without block
		/*!
			Will not block.

			\return 'true' if the mutex was successfully acquired, 'false' if the mutex is busy
		*/
		bool TryLock();

		//! Try to acquire mutex for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the mutex
			\return 'true' if the mutex was successfully acquired, 'false' if the mutex is busy
		*/
		bool TryLockFor(const XTTimespan& timespan);
		//! Try to acquire mutex until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the mutex
			\return 'true' if the mutex was successfully acquired, 'false' if the mutex is busy
		*/
		bool TryLockUntil(const XTUtcTimestamp& timestamp)
		{
			return TryLockFor(timestamp - XTUtcTimestamp());
		}

		//! Acquire mutex with block
		/*!
			Will block.
		*/
		void Lock();

		//! Release mutex
		/*!
			Will not block.
		*/
		void Unlock();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};


}//namespace XT

#endif