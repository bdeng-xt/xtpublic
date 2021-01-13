#pragma once
#ifndef XT_SPSC_RINGQUEUE_H
#define XT_SPSC_RINGQUEUE_H

/**
* \file XTSPSCRingQueue.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a single producer single consumer ring queue class .
*
* \description
*	Designed for a single producer single consumer ring queue class.
*/
#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>


namespace XT
{

	//! Single producer / single consumer wait-free ring queue
	/*!
		Single producer / single consumer wait-free ring queue use only atomic operations to provide thread-safe enqueue
		and dequeue operations. Ring queue is bounded to the fixed capacity provided in the constructor.

		FIFO order is guaranteed!

		Thread-safe.

		A combination of the algorithms described by the circular buffers documentation found in the Linux kernel, and the
		bounded MPMC queue by Dmitry Vyukov. Implemented in pure C++11. Should work across most CPU architectures.
		http://www.1024cores.net/home/lock-free-algorithms/queues/bounded-mpmc-queue
	*/
	template<typename T>
	class SPSCRingQueue
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Ring queue capacity (must be a power of two)
		*/
		explicit SPSCRingQueue(size_t capacity);
		SPSCRingQueue(const SPSCRingQueue&) = delete;
		SPSCRingQueue(SPSCRingQueue&&) = delete;
		~SPSCRingQueue() { delete[] _buffer; }

		SPSCRingQueue& operator=(const SPSCRingQueue&) = delete;
		SPSCRingQueue& operator=(SPSCRingQueue&&) = delete;

		//! Check if the queue is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is ring queue empty?
		bool empty() const noexcept { return (size() == 0); }
		//! Get ring queue capacity
		size_t capacity() const noexcept { return _capacity; }
		//! Get ring queue size
		size_t size() const noexcept;

		//! Enqueue an item into the ring queue (single producer thread method)
		/*!
			The item will be copied into the ring queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the ring queue is full
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the ring queue (single producer thread method)
		/*!
			The item will be moved into the ring queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the ring queue is full
		*/
		bool Enqueue(T&& item);

		//! Dequeue an item from the ring queue (single consumer thread method)
		/*!
			The item will be moved from the ring queue.

			Will not block.

			\param item - Item to dequeue
			\return 'true' if the item was successfully dequeue, 'false' if the ring queue is empty
		*/
		bool Dequeue(T& item);

	private:
		typedef char cache_line_pad[128];

		cache_line_pad _pad0;
		const size_t _capacity;
		const size_t _mask;
		T* const _buffer;

		cache_line_pad _pad1;
		std::atomic<size_t> _head;
		cache_line_pad _pad2;
		std::atomic<size_t> _tail;
		cache_line_pad _pad3;
	};

//////
	template<typename T>
	inline SPSCRingQueue<T>::SPSCRingQueue(size_t capacity) : _capacity(capacity - 1), _mask(capacity - 1), _buffer(new T[capacity]), _head(0), _tail(0)
	{
		assert((capacity > 1) && "Ring queue capacity must be greater than one!");
		assert(((capacity & (capacity - 1)) == 0) && "Ring queue capacity must be a power of two!");

		memset(_pad0, 0, sizeof(cache_line_pad));
		memset(_pad1, 0, sizeof(cache_line_pad));
		memset(_pad2, 0, sizeof(cache_line_pad));
		memset(_pad3, 0, sizeof(cache_line_pad));
	}

	template<typename T>
	inline size_t SPSCRingQueue<T>::size() const noexcept
	{
		const size_t head = _head.load(std::memory_order_acquire);
		const size_t tail = _tail.load(std::memory_order_acquire);

		return head - tail;
	}

	template<typename T>
	inline bool SPSCRingQueue<T>::Enqueue(const T& item)
	{
		T temp = item;
		return Enqueue(std::forward<T>(temp));
	}

	template<typename T>
	inline bool SPSCRingQueue<T>::Enqueue(T&& item)
	{
		const size_t head = _head.load(std::memory_order_relaxed);
		const size_t tail = _tail.load(std::memory_order_acquire);

		// Check if the ring queue is full
		if (((head - tail + 1) & _mask) == 0)
			return false;

		// Store the item value
		_buffer[head & _mask] = std::move(item);

		// Increase the head cursor
		_head.store(head + 1, std::memory_order_release);

		return true;
	}

	template<typename T>
	inline bool SPSCRingQueue<T>::Dequeue(T& item)
	{
		const size_t tail = _tail.load(std::memory_order_relaxed);
		const size_t head = _head.load(std::memory_order_acquire);

		// Check if the ring queue is empty
		if (((head - tail) & _mask) == 0)
			return false;

		// Get the item value
		item = std::move(_buffer[tail & _mask]);

		// Increase the tail cursor
		_tail.store(tail + 1, std::memory_order_release);

		return true;
	}


}//namespace XT


#endif