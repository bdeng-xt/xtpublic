#pragma once
#ifndef XT_MPMC_RING_BUFFER_H
#define XT_MPMC_RING_BUFFER_H

/**
* \file XTMPMCRingBuffer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a multi producers multi consumers ring buffer class .
*
* \description
*	Designed for a multi producers multi consumers ring buffer class.
*/

#include <cstdint>
#include <string>
#include <iostream>

#include "XTSpinLock.h"
#include "XTSPSCRingBuffer.h"
#include "XTTimestamp.h"

#include <cstdio>
#include <memory>
#include <thread>
#include <vector>

namespace XT
{

	//! Multiple producers / single consumer wait-free ring buffer
	/*!
		Multiple producers / single consumer wait-free ring buffer use only atomic operations to provide thread-safe
		enqueue and dequeue operations. This data structure consist of several SPSC ring buffers which count is
		provided as a hardware concurrency in the constructor. All of them are randomly accessed with a RDTS
		distribution index. All the items available in sesequential or batch mode. All ring buffer sizes are
		limited to the capacity provided in the constructor.

		FIFO order is not guaranteed!

		Thread-safe.
	*/
	class MPSCRingBuffer
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Ring buffer capacity (must be a power of two)
			\param concurrency - Hardware concurrency (default is std::thread::hardware_concurrency)
		*/
		explicit MPSCRingBuffer(size_t capacity, size_t concurrency = std::thread::hardware_concurrency());
		MPSCRingBuffer(const MPSCRingBuffer&) = delete;
		MPSCRingBuffer(MPSCRingBuffer&&) = delete;
		~MPSCRingBuffer() = default;

		MPSCRingBuffer& operator=(const MPSCRingBuffer&) = delete;
		MPSCRingBuffer& operator=(MPSCRingBuffer&&) = delete;

		//! Check if the buffer is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is ring buffer empty?
		bool empty() const noexcept { return (size() == 0); }
		//! Get ring buffer capacity
		size_t capacity() const noexcept { return _capacity; }
		//! Get ring buffer concurrency
		size_t concurrency() const noexcept { return _concurrency; }
		//! Get ring buffer size
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
		struct Producer
		{
			SpinLock lock;
			SPSCRingBuffer buffer;

			Producer(size_t capacity) : buffer(capacity) {}
		};

		size_t _capacity;
		size_t _concurrency;
		std::vector<std::shared_ptr<Producer>> _producers;
		size_t _consumer;
	};

//////
	inline MPSCRingBuffer::MPSCRingBuffer(size_t capacity, size_t concurrency) : _capacity(capacity - 1), _concurrency(concurrency), _consumer(0)
	{
		// Initialize producers' ring buffer
		for (size_t i = 0; i < concurrency; ++i)
			_producers.push_back(std::make_shared<Producer>(capacity));
	}

	inline size_t MPSCRingBuffer::size() const noexcept
	{
		size_t size = 0;
		for (const auto& producer : _producers)
			size += producer->buffer.size();
		return size;
	}

	inline bool MPSCRingBuffer::Enqueue(const void* chunk, size_t size)
	{
		// Get producer index for the current thread based on RDTS value
		size_t index = XTTimestamp::rdts() % _concurrency;

		// Lock the chosen producer using its spin-lock
		Locker<SpinLock> lock(_producers[index]->lock);

		// Enqueue the item into the producer's ring buffer
		return _producers[index]->buffer.Enqueue(chunk, size);
	}

	inline bool MPSCRingBuffer::Dequeue(void* chunk, size_t& size)
	{
		// Try to dequeue one item from the one of producer's ring buffers
		for (size_t i = 0; i < _concurrency; ++i)
		{
			size_t temp = size;
			if (_producers[_consumer++ % _concurrency]->buffer.Dequeue(chunk, temp))
			{
				size = temp;
				return true;
			}
		}

		size = 0;
		return false;
	}

}//namespace XT


#endif