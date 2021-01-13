#pragma once
#ifndef XT_FILE_LOCK_H
#define XT_FILE_LOCK_H

/**
* \file XTFileLock.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a file lock class .
*
* \description
*	Designed for a file lock class.
*/


#include <cstdint>
#include <string>
#include <iostream> 

#include "XTFile.h"
#include "XTLocker.h"
#include "XTTimestamp.h"

#include <memory>

#include "XTConfig.h"

namespace XT
{

	//! File-lock synchronization primitive
	/*!
		A file-lock provide shared and exclusive access to some resource based
		on the file locking functionality provided by OS. This means that multiple
		threads or processes can read the data in parallel but an exclusive lock
		is needed for writing or modifying data. When a writer is writing the data,
		all other writers or readers will be blocked until the writer is finished
		writing.

		Thread-safe.

		https://en.wikipedia.org/wiki/File_locking
	*/
	class XT_COMMON_API FileLock
	{
	public:
		FileLock();
		explicit FileLock(const Path& path);
		FileLock(const FileLock&) = delete;
		FileLock(FileLock&& lock) = delete;
		~FileLock();

		FileLock& operator=(const Path& path);
		FileLock& operator=(const FileLock&) = delete;
		FileLock& operator=(FileLock&& lock) = delete;

		//! Get the file-lock path
		const Path& path() const noexcept;

		//! Assign a new file-lock path
		/*!
			\param path - File-lock path
		*/
		void Assign(const Path& path);

		//! Reset file-lock
		void Reset();

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