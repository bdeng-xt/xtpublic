#pragma once
#ifndef XT_SPSC_RINGBUFFER_H
#define XT_SPSC_RINGBUFFER_H

/**
* \file XTSPSCRingBuffer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a single producer single consumer ring buffer class .
*
* \description
*	Designed for a single producer single consumer ring buffer class.
*/

#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstring>


namespace XT
{

	//! Single producer / single consumer wait-free ring buffer
	/*!
		Single producer / single consumer wait-free ring buffer use only atomic operations to provide thread-safe enqueue
		and dequeue operations. Ring buffer is bounded to the fixed capacity provided in the constructor.

		FIFO order is guaranteed!

		Thread-safe.

		A combination of the algorithms described by the circular buffers documentation found in the Linux kernel, and the
		bounded MPMC queue by Dmitry Vyukov. Implemented in pure C++11. Should work across most CPU architectures.
		http://www.1024cores.net/home/lock-free-algorithms/queues/bounded-mpmc-queue
	*/
	class SPSCRingBuffer
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Ring buffer capacity (must be a power of two)
		*/
		explicit SPSCRingBuffer(size_t capacity);
		SPSCRingBuffer(const SPSCRingBuffer&) = delete;
		SPSCRingBuffer(SPSCRingBuffer&&) = delete;
		~SPSCRingBuffer() { delete[] _buffer; }

		SPSCRingBuffer& operator=(const SPSCRingBuffer&) = delete;
		SPSCRingBuffer& operator=(SPSCRingBuffer&&) = delete;

		//! Check if the buffer is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is ring buffer empty?
		bool empty() const noexcept { return (size() == 0); }
		//! Get ring buffer capacity in bytes
		size_t capacity() const noexcept { return _capacity; }
		//! Get ring buffer size in bytes
		size_t size() const noexcept;

		//! Enqueue a chunk of bytes into the ring buffer (single producer thread method)
		/*!
			The chunk of bytes will be copied into the ring buffer using 'memcpy()' function.
			Chunk size should not be greater than ring buffer capacity!

			Will not block.

			\param chunk - Chunk buffer to enqueue
			\param size - Chunk buffer size
			\return 'true' if the chunk of bytes was successfully enqueue, 'false' if the ring buffer is full
		*/
		bool Enqueue(const void* chunk, size_t size);

		//! Dequeue a chunk of bytes from the ring buffer (single consumer thread method)
		/*!
			The chunk of bytes will be copied from the ring buffer using 'memcpy()' function.

			Will not block.

			\param chunk - Chunk buffer to dequeue
			\param size - Chunk buffer size
			\return 'true' if the chunk of bytes was successfully dequeue, 'false' if the ring buffer is empty
		*/
		bool Dequeue(void* chunk, size_t& size);

	private:
		typedef char cache_line_pad[128];

		cache_line_pad _pad0;
		const size_t _capacity;
		const size_t _mask;
		uint8_t* const _buffer;

		cache_line_pad _pad1;
		std::atomic<size_t> _head;
		cache_line_pad _pad2;
		std::atomic<size_t> _tail;
		cache_line_pad _pad3;
	};
//////
	inline SPSCRingBuffer::SPSCRingBuffer(size_t capacity) : _capacity(capacity), _mask(capacity - 1), _buffer(new uint8_t[capacity]), _head(0), _tail(0)
	{
		assert((capacity > 1) && "Ring buffer capacity must be greater than one!");
		assert(((capacity & (capacity - 1)) == 0) && "Ring buffer capacity must be a power of two!");

		memset(_pad0, 0, sizeof(cache_line_pad));
		memset(_pad1, 0, sizeof(cache_line_pad));
		memset(_pad2, 0, sizeof(cache_line_pad));
		memset(_pad3, 0, sizeof(cache_line_pad));
	}

	inline size_t SPSCRingBuffer::size() const noexcept
	{
		const size_t head = _head.load(std::memory_order_acquire);
		const size_t tail = _tail.load(std::memory_order_acquire);

		return head - tail;
	}

	inline bool SPSCRingBuffer::Enqueue(const void* chunk, size_t size)
	{
		assert((size <= _capacity) && "Chunk size should not be greater than ring buffer capacity!");
		if (size > _capacity)
			return false;

		if (size == 0)
			return true;

		assert((chunk != nullptr) && "Pointer to the chunk should not be null!");
		if (chunk == nullptr)
			return false;

		const size_t head = _head.load(std::memory_order_relaxed);
		const size_t tail = _tail.load(std::memory_order_acquire);

		// Check if there is required free space in the ring buffer
		if ((size + head - tail) > _capacity)
			return false;

		// Copy chunk of bytes into the ring buffer
		size_t head_index = head & _mask;
		size_t tail_index = tail & _mask;
		size_t remain = (tail_index > head_index) ? (tail_index - head_index) : (_capacity - head_index);
		size_t first = (size > remain) ? remain : size;
		size_t last = (size > remain) ? size - remain : 0;
		memcpy(&_buffer[head_index], (uint8_t*)chunk, first);
		memcpy(_buffer, (uint8_t*)chunk + first, last);

		// Increase the head cursor
		_head.store(head + size, std::memory_order_release);

		return true;
	}

	inline bool SPSCRingBuffer::Dequeue(void* chunk, size_t& size)
	{
		if (size == 0)
			return true;

		assert((chunk != nullptr) && "Pointer to the chunk should not be null!");
		if (chunk == nullptr)
			return false;

		const size_t tail = _tail.load(std::memory_order_relaxed);
		const size_t head = _head.load(std::memory_order_acquire);

		// Get the ring buffer size
		size_t available = head - tail;
		if (size > available)
			size = available;

		// Check if the ring buffer is empty
		if (size == 0)
			return false;

		// Copy chunk of bytes from the ring buffer
		size_t head_index = head & _mask;
		size_t tail_index = tail & _mask;
		size_t remain = (head_index > tail_index) ? (head_index - tail_index) : (_capacity - tail_index);
		size_t first = (size > remain) ? remain : size;
		size_t last = (size > remain) ? size - remain : 0;
		memcpy((uint8_t*)chunk, &_buffer[tail_index], first);
		memcpy((uint8_t*)chunk + first, _buffer, last);

		// Increase the tail cursor
		_tail.store(tail + size, std::memory_order_release);

		return true;
	}



}//namespace XT
 


#endif