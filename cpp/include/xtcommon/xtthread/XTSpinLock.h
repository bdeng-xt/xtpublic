#pragma once
#ifndef XT_SPIN_LOCK_H
#define XT_SPIN_LOCK_H

/**
* \file XTSpinLock.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a spin lock class .
*
* \description
*	Designed for a spin lock class.
*/

#include "XTLocker.h"
#include "XTTimestamp.h"

#include <atomic>

namespace XT
{

	//! Spin-lock synchronization primitive
	/*!
		The purpose of a spin lock is to prevent multiple threads from concurrently accessing a shared data structure.
		In contrast to a mutex, threads will busy-wait and waste CPU cycles instead of yielding the CPU to another thread.
		Do not use spinlocks unless you are certain that you understand the consequences!

		Thread-safe.

		https://en.wikipedia.org/wiki/Spinlock
	*/
	class SpinLock
	{
	public:
		SpinLock() noexcept : _lock(false) {}
		SpinLock(const SpinLock&) = delete;
		SpinLock(SpinLock&&) = delete;
		~SpinLock() = default;

		SpinLock& operator=(const SpinLock&) = delete;
		SpinLock& operator=(SpinLock&&) = delete;

		//! Is already locked?
		/*!
			Will not block.

			\return 'true' if the spin-lock is already locked, 'false' if the spin-lock is released
		*/
		bool IsLocked() noexcept;

		//! Try to acquire spin-lock without block
		/*!
			Will not block.

			\return 'true' if the spin-lock was successfully acquired, 'false' if the spin-lock is busy
		*/
		bool TryLock() noexcept;

		//! Try to acquire spin-lock for the given spin count
		/*!
			Will block for the given spin count in the worst case.

			\param spin - Spin count
			\return 'true' if the spin-lock was successfully acquired, 'false' if the spin-lock is busy
		*/
		bool TryLockSpin(int64_t spin) noexcept;

		//! Try to acquire spin-lock for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the spin-lock
			\return 'true' if the spin-lock was successfully acquired, 'false' if the spin-lock is busy
		*/
		bool TryLockFor(const XTTimespan& timespan) noexcept;
		//! Try to acquire spin-lock until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the spin-lock
			\return 'true' if the spin-lock was successfully acquired, 'false' if the spin-lock is busy
		*/
		bool TryLockUntil(const XTUtcTimestamp& timestamp) noexcept
		{
			return TryLockFor(timestamp - XTUtcTimestamp());
		}

		//! Acquire spin-lock with block
		/*!
			Will block in a spin loop.
		*/
		void Lock() noexcept;

		//! Release spin-lock
		/*!
			Will not block.
		*/
		void Unlock() noexcept;

	private:
		std::atomic<bool> _lock;
	};
//////
	inline bool SpinLock::IsLocked() noexcept
	{
		return _lock.load(std::memory_order_acquire);
	}

	inline bool SpinLock::TryLock() noexcept
	{
		return !_lock.exchange(true, std::memory_order_acquire);
	}

	inline bool SpinLock::TryLockSpin(int64_t spin) noexcept
	{
		// Try to acquire spin-lock at least one time
		do
		{
			if (TryLock())
				return true;
		} while (spin-- > 0);

		// Failed to acquire spin-lock
		return false;
	}

	inline bool SpinLock::TryLockFor(const XTTimespan& timespan) noexcept
	{
		// Calculate a finish timestamp
		XTTimestamp finish = XTNanoTimestamp() + timespan;

		// Try to acquire spin-lock at least one time
		do
		{
			if (TryLock())
				return true;
		} while (XTNanoTimestamp() < finish);

		// Failed to acquire spin-lock
		return false;
	}

	inline void SpinLock::Lock() noexcept
	{
		while (_lock.exchange(true, std::memory_order_acquire));
	}

	inline void SpinLock::Unlock() noexcept
	{
		_lock.store(false, std::memory_order_release);
	}


}//namespace XT


#endif