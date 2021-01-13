#pragma once
#ifndef XT_BARRIER_H
#define XT_BARRIER_H

/**
* \file XTBarrier.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a barrier class .
*
* \description
*	Designed for a barrier class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "XTConfig.h"
namespace XT
{
	//! Barrier synchronization primitive
	/*!
		A barrier for a group of threads in the source code means any thread must stop at this point
		and cannot proceed until all other threads reach this barrier.

		Thread-safe.

		https://en.wikipedia.org/wiki/Barrier_(computer_science)
	*/
	class XT_COMMON_API Barrier
	{
	public:
		//! Default class constructor
		/*!
			\param threads - Count of threads to wait at the barrier
		*/
		explicit Barrier(int threads) noexcept;
		Barrier(const Barrier&) = delete;
		Barrier(Barrier&&) = delete;
		~Barrier() = default;

		Barrier& operator=(const Barrier&) = delete;
		Barrier& operator=(Barrier&&) = delete;

		//! Wait at the barrier until all other threads reach this barrier
		/*!
			Will block.

			\return 'true' for the last thread that reach barrier, 'false' for each of the remaining threads
		*/
		bool Wait() noexcept;

	private:
		std::mutex _mutex;
		std::condition_variable _cond;
		int _counter;
		int _generation;
		int _threads;
	};


}//namespace

#endif
