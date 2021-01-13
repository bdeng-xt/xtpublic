#pragma once
#ifndef XT_NAMED_SEMAPHORE_H
#define XT_NAMED_SEMAPHORE_H

/**
* \file XTNamedSemaphore.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a named semaphore class .
*
* \description
*	Designed for a named semaphore class.
*/

#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
#include <string>
#include "XTConfig.h"

namespace XT
{

	//! Named semaphore synchronization primitive
	/*!
		Named semaphore behaves as a simple semaphore but could be shared between processes
		on the same machine.

		Thread-safe.

		\see Semaphore
	*/
	class XT_COMMON_API NamedSemaphore
	{
	public:
		//! Default class constructor
		/*!
			\param name - Semaphore name
			\param resources - Semaphore resources counter
		*/
		explicit NamedSemaphore(const std::string& name, int resources);
		NamedSemaphore(const NamedSemaphore&) = delete;
		NamedSemaphore(NamedSemaphore&& semaphore) = delete;
		~NamedSemaphore();

		NamedSemaphore& operator=(const NamedSemaphore&) = delete;
		NamedSemaphore& operator=(NamedSemaphore&& semaphore) = delete;

		//! Get the semaphore name
		const std::string& name() const;
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