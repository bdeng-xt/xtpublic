#pragma once
#ifndef XT_SEQLOCK_H
#define XT_SEQLOCK_H

/**
* \file XTSeqLock.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a read-write lock class .
*
* \description
*	Designed for a read-write lock class.
*/

#include <atomic>
#include <cstring>

namespace XT
{

	//! Sequential lock synchronization primitive
	/*!
		Sequential locks are an important synchronization mechanism and
		represent a significant improvement over conventional read/write
		locks in some contexts. They avoid the need to update a synchronization
		variable during a reader critical section, and hence improve performance
		by avoiding cache coherence misses on the lock object itself.

		Thread-safe.

		https://en.wikipedia.org/wiki/Seqlock
	*/
	template <typename T>
	class SeqLock
	{
	public:
		SeqLock();
		explicit SeqLock(const T& data);
		SeqLock(const SeqLock&) = delete;
		SeqLock(SeqLock&&) = default;
		~SeqLock() = default;

		SeqLock& operator=(const T& data) noexcept;
		SeqLock& operator=(const SeqLock&) = delete;
		SeqLock& operator=(SeqLock&&) = delete;

		//! Read data under the sequential lock
		/*!
			Will block in a spin loop.

			\return Read data
		*/
		T Read() const noexcept;

		//! Write data under the sequential lock
		/*!
			Will not block.

			\param data - Data to write
		*/
		void Write(const T& data) noexcept;

	private:
		typedef char cache_line_pad[128];

		cache_line_pad _pad0;
		T _data;
		std::atomic<size_t> _seq;
		cache_line_pad _pad1;
	};

/////
	template <typename T>
	inline SeqLock<T>::SeqLock() : _seq(0)
	{
		memset(_pad0, 0, sizeof(cache_line_pad));
		memset(_pad1, 0, sizeof(cache_line_pad));
	}

	template <typename T>
	inline SeqLock<T>::SeqLock(const T& data) : SeqLock()
	{
		_data = data;
	}

	template <typename T>
	inline SeqLock<T>& SeqLock<T>::operator=(const T& data) noexcept
	{
		Write(data);
		return *this;
	}

	template <typename T>
	inline T SeqLock<T>::Read() const noexcept
	{
		T data;
		size_t seq0;
		size_t seq1;

		do
		{
			seq0 = _seq.load(std::memory_order_acquire);
			std::atomic_signal_fence(std::memory_order_acq_rel);
			data = _data;
			std::atomic_signal_fence(std::memory_order_acq_rel);
			seq1 = _seq.load(std::memory_order_acquire);
		} while ((seq0 != seq1) || (seq0 & 1));

		return data;
	}

	template <typename T>
	inline void SeqLock<T>::Write(const T& data) noexcept
	{
		size_t seq0 = _seq.load(std::memory_order_relaxed);
		_seq.store(seq0 + 1, std::memory_order_release);
		std::atomic_signal_fence(std::memory_order_acq_rel);
		_data = data;
		std::atomic_signal_fence(std::memory_order_acq_rel);
		_seq.store(seq0 + 2, std::memory_order_release);
	}

}//namespace

#endif