#pragma once
#ifndef XT_MUTEX_H
#define XT_MUTEX_H

/**
* \file XTMutex.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a mutex class .
*
* \description
*	Designed for a mutex class.
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

	//! Mutex synchronization primitive
	/*!
		A mutex object facilitates protection against data races and allows thread-safe synchronization
		of data between threads. A thread obtains ownership of a mutex object by calling one of the lock
		functions and relinquishes ownership by calling the corresponding unlock function.

		Thread-safe.

		https://en.wikipedia.org/wiki/Mutual_exclusion
	*/
	class XT_COMMON_API Mutex
	{
	public:
		Mutex();
		Mutex(const Mutex&) = delete;
		Mutex(Mutex&& mutex) = delete;
		~Mutex();

		Mutex& operator=(const Mutex&) = delete;
		Mutex& operator=(Mutex&& mutex) = delete;

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

}//namespace


#endif