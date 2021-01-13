#pragma once
#ifndef XT_RWLOCK_H
#define XT_RWLOCK_H

/**
* \file XTRWLock.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a read-write lock class .
*
* \description
*	Designed for a read-write lock class.
*/

#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
#include "XTConfig.h"

namespace XT
{

	//! Read/Write lock synchronization primitive
	/*!
		An read/write lock allows concurrent access for read-only operations, while write operations
		require exclusive access. This means that multiple threads can read the data in parallel but
		an exclusive lock is needed for writing or modifying data. When a writer is writing the data,
		all other writers or readers will be blocked until the writer is finished writing.

		Thread-safe.

		https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
	*/
	class XT_COMMON_API RWLock
	{
	public:
		RWLock();
		RWLock(const RWLock&) = delete;
		RWLock(RWLock&& lock) = delete;
		~RWLock();

		RWLock& operator=(const RWLock&) = delete;
		RWLock& operator=(RWLock&& lock) = delete;

		//! Try to acquire read lock without block
		/*!
			Will not block.

			\return 'true' if the read lock was successfully acquired, 'false' if the read lock is busy
		*/
		bool TryLockRead();
		//! Try to acquire write lock without block
		/*!
			Will not block.

			\return 'true' if the write lock was successfully acquired, 'false' if the write lock is busy
		*/
		bool TryLockWrite();

		//! Try to acquire read lock for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the read lock
			\return 'true' if the read lock was successfully acquired, 'false' if the read lock is busy
		*/
		bool TryLockReadFor(const XTTimespan& timespan);
		//! Try to acquire write lock for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the write lock
			\return 'true' if the write lock was successfully acquired, 'false' if the write lock is busy
		*/
		bool TryLockWriteFor(const XTTimespan& timespan);
		//! Try to acquire read lock until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the read lock
			\return 'true' if the read lock was successfully acquired, 'false' if the read lock is busy
		*/
		bool TryLockReadUntil(const XTUtcTimestamp& timestamp)
		{
			return TryLockReadFor(timestamp - XTUtcTimestamp());
		}
		//! Try to acquire write lock until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the write lock
			\return 'true' if the write lock was successfully acquired, 'false' if the write lock is busy
		*/
		bool TryLockWriteUntil(const XTUtcTimestamp& timestamp)
		{
			return TryLockWriteFor(timestamp - XTUtcTimestamp());
		}

		//! Acquire read lock with block
		/*!
			Will block.
		*/
		void LockRead();
		//! Acquire write lock with block
		/*!
			Will block.
		*/
		void LockWrite();

		//! Release read lock
		/*!
			Will not block.
		*/
		void UnlockRead();
		//! Release write lock
		/*!
			Will not block.
		*/
		void UnlockWrite();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

}//namespace XT

#endif