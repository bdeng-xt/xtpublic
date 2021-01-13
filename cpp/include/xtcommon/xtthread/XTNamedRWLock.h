#pragma once
#ifndef XT_NAMED_RWLOCK_H
#define XT_NAMED_RWLOCK_H

/**
* \file XTNamedRWLock.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a named read-write lock class .
*
* \description
*	Designed for a named read-write lock class.
*/


#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>
#include <string>
#include "XTConfig.h"

namespace XT
{

	//! Named read/write lock synchronization primitive
	/*!
		Named read/write lock behaves as a simple read/write lock but could be shared between processes
		on the same machine.

		The fast lock is around 7% faster than the critical section when there is no contention, when
		used solely for mutual exclusion. It is also much smaller than the critical section.

		Thread-safe.

		\see RWLock
	*/
	class XT_COMMON_API NamedRWLock
	{
	public:
		//! Default class constructor
		/*!
			\param name - Read/Write lock name
		*/
		explicit NamedRWLock(const std::string& name);
		NamedRWLock(const NamedRWLock&) = delete;
		NamedRWLock(NamedRWLock&& lock) = delete;
		~NamedRWLock();

		NamedRWLock& operator=(const NamedRWLock&) = delete;
		NamedRWLock& operator=(NamedRWLock&& lock) = delete;

		//! Get the read/write lock name
		const std::string& name() const;

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
		//! Try to convert write lock to read lock without block
		/*!
			Will not block.

			\return 'true' if the write lock was successfully converted to the read one, 'false' if the write lock is busy
		*/
		bool TryConvertWriteToRead();

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
		//! Try to convert write lock to read lock for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the write lock to read lock conversion
			\return 'true' if the write lock was successfully converted to the read one, 'false' if the write lock is busy
		*/
		bool TryConvertWriteToReadFor(const XTTimespan& timespan);
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
		//! Try to convert write lock to read lock until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the write lock to read lock conversion
			\return 'true' if the write lock was successfully converted to the read one, 'false' if the write lock is busy
		*/
		bool TryConvertWriteToReadUntil(const XTUtcTimestamp& timestamp)
		{
			return TryConvertWriteToReadFor(timestamp - XTUtcTimestamp());
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

		//! Convert write lock to read lock without block
		/*!
			Exclusive acquires are not given a chance to acquire
			the lock before this function does - as a result,
			this function will never block.

			Will not block.
		*/
		void ConvertWriteToRead();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

//////

}//namespace

#endif