#pragma once
#ifndef XT_SEMAPHORE_H
#define XT_SEMAPHORE_H

/**
* \file XTSemaphore.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a semaphore class .
*
* \description
*	Designed for a semaphore class.
*/

#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
#include "XTConfig.h"

namespace XT
{

	//! Semaphore synchronization primitive
	/*!
		Semaphore synchronization primitive allows fixed count of threads to access some resource
		while other threads are waiting for it. When some thread unlocks the semaphore then one of
		waiting threads will lock it.

		Thread-safe.

		https://en.wikipedia.org/wiki/Semaphore_(programming)
	*/
	class XT_COMMON_API Semaphore
	{
	public:
		//! Default class constructor
		/*!
			\param resources - Semaphore resources counter
		*/
		explicit Semaphore(int resources);
		Semaphore(const Semaphore&) = delete;
		Semaphore(Semaphore&& semaphore) = delete;
		~Semaphore();

		Semaphore& operator=(const Semaphore&) = delete;
		Semaphore& operator=(Semaphore&& semaphore) = delete;

		//! Get the semaphore resources counter
		int resources() const noexcept;

		//! Try to acquire semaphore without block
		/*!
			Will not block.

			\return 'true' if the semaphore was successfully acquired, 'false' if the semaphore is busy
		*/
		bool TryLock();

		//! Try to acquire semaphore for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the semaphore
			\return 'true' if the semaphore was successfully acquired, 'false' if the semaphore is busy
		*/
		bool TryLockFor(const XTTimespan& timespan);
		//! Try to acquire semaphore until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the semaphore
			\return 'true' if the semaphore was successfully acquired, 'false' if the semaphore is busy
		*/
		bool TryLockUntil(const XTUtcTimestamp& timestamp)
		{
			return TryLockFor(timestamp - XTUtcTimestamp());
		}

		//! Acquire semaphore with block
		/*!
			Will block.
		*/
		void Lock();

		//! Release semaphore
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
