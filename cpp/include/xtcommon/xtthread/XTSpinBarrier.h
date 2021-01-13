#pragma once
#ifndef XT_SPIN_BARRIER_H
#define XT_SPIN_BARRIER_H

/**
* \file XTSpinBarrier.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a spin barrier class .
*
* \description
*	Designed for a spin barrier class.
*/

#include <atomic>
#include <cassert>

namespace XT
{

	//! Spin barrier synchronization primitive
	/*!
		A barrier for a group of threads in the source code means any thread must stop at this point and cannot
		proceed until all other threads reach this barrier.

		Spin version: threads will busy-wait and waste CPU cycles instead of yielding the CPU to another thread.
		Do not use spinlocks unless you are certain that you understand the consequences!

		Thread-safe.

		https://en.wikipedia.org/wiki/Barrier_(computer_science)
		https://en.wikipedia.org/wiki/Spinlock
	*/
	class SpinBarrier
	{
	public:
		//! Default class constructor
		/*!
			\param threads - Count of threads to wait at the barrier
		*/
		explicit SpinBarrier(int threads) noexcept;
		SpinBarrier(const SpinBarrier&) = delete;
		SpinBarrier(SpinBarrier&&) = delete;
		~SpinBarrier() = default;

		SpinBarrier& operator=(const SpinBarrier&) = delete;
		SpinBarrier& operator=(SpinBarrier&&) = delete;

		//! Get the count of threads to wait at the barrier
		int threads() const noexcept { return _threads; }

		//! Wait at the barrier until all other threads reach this barrier
		/*!
			Will block.

			\return 'true' for the last thread that reach barrier, 'false' for each of the remaining threads
		*/
		bool Wait() noexcept;

	private:
		std::atomic<int> _counter;
		std::atomic<int> _generation;
		int _threads;
	};

/////
	inline SpinBarrier::SpinBarrier(int threads) noexcept : _counter(threads), _generation(0), _threads(threads)
	{
		assert((threads > 0) && "Count of barrier threads must be greater than zero!");
	}

	inline bool SpinBarrier::Wait() noexcept
	{
		// Remember the current barrier generation
		int generation = _generation;

		// Decrease the count of waiting threads
		if (--_counter == 0)
		{
			// Increase the current barrier generation
			++_generation;

			// Reset waiting threads counter
			_counter = _threads;

			// Notify the last thread that reached the barrier
			return true;
		}
		else
		{
			// Spin-wait for the next barrier generation
			while ((generation == _generation) || (_counter == 0));

			// Notify each of remaining threads
			return false;
		}
	}


}//namespace

#endif