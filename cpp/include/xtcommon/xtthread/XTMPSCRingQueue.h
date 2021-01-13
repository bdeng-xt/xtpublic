#pragma once
#ifndef XT_MPSC_RING_QUEUE_H
#define XT_MPSC_RING_QUEUE_H

/**
* \file XTMPSCRingQueue.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a multi producers single consumers ring queue class .
*
* \description
*	Designed for a multi producers single consumers ring queue class.
*/

#include "XTSpinLock.h"
#include "XTSPSCRingQueue.h"
#include "XTTimestamp.h"

#include <cassert>
#include <cstdio>
#include <functional>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

namespace XT
{

	//! Multiple producers / single consumer wait-free ring queue
	/*!
		Multiple producers / single consumer wait-free ring queue use only atomic operations to provide thread-safe
		enqueue and dequeue operations. This data structure consist of several SPSC ring queues which count is
		provided as a hardware concurrency in the constructor. All of them are randomly accessed with a RDTS
		distribution index. All the items available in sesequential or batch mode. All ring queue sizes are
		limited to the capacity provided in the constructor.

		FIFO order is not guaranteed!

		Thread-safe.
	*/
	template<typename T>
	class MPSCRingQueue
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Ring queue capacity (must be a power of two)
			\param concurrency - Hardware concurrency (default is std::thread::hardware_concurrency)
		*/
		explicit MPSCRingQueue(size_t capacity, size_t concurrency = std::thread::hardware_concurrency());
		MPSCRingQueue(const MPSCRingQueue&) = delete;
		MPSCRingQueue(MPSCRingQueue&&) = delete;
		~MPSCRingQueue() = default;

		MPSCRingQueue& operator=(const MPSCRingQueue&) = delete;
		MPSCRingQueue& operator=(MPSCRingQueue&&) = delete;

		//! Check if the queue is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Is ring queue empty?
		bool empty() const noexcept { return (size() == 0); }
		//! Get ring queue capacity
		size_t capacity() const noexcept { return _capacity; }
		//! Get ring queue concurrency
		size_t concurrency() const noexcept { return _concurrency; }
		//! Get ring queue size
		size_t size() const noexcept;

		//! Enqueue an item into the ring queue (multiple producers threads method)
		/*!
			The item will be copied into the ring queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the ring queue is full
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the ring queue (multiple producers threads method)
		/*!
			The item will be moved into the ring queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the ring queue is full
		*/
		bool Enqueue(T&& item);

		//! Dequeue an item from the ring queue (single consumer threads method)
		/*!
			The item will be moved from the ring queue.

			Will not block.

			\param item - Item to dequeue
			\return 'true' if the item was successfully dequeue, 'false' if the ring queue is empty
		*/
		bool Dequeue(T& item);

		//! Dequeue all items from the linked queue (single consumer thread method)
		/*!
			All items in the batcher will be processed by the given handler.

			Will not block.

			\param handler - Batch handler (default is empty handler)
			\return 'true' if all items were successfully handled, 'false' if the linked batcher is empty
		*/
		bool Dequeue(const std::function<void(const T&)>& handler = [](const int&) {});

	private:
		struct Producer
		{
			SpinLock lock;
			SPSCRingQueue<T> queue;

			Producer(size_t capacity) : queue(capacity) {}
		};

		size_t _capacity;
		size_t _concurrency;
		std::vector<std::shared_ptr<Producer>> _producers;
		size_t _consumer;
	};
//////
	template<typename T>
	inline MPSCRingQueue<T>::MPSCRingQueue(size_t capacity, size_t concurrency) : _capacity(capacity - 1), _concurrency(concurrency), _consumer(0)
	{
		// Initialize producers' ring queue
		for (size_t i = 0; i < concurrency; ++i)
			_producers.push_back(std::make_shared<Producer>(capacity));
	}

	template<typename T>
	inline size_t MPSCRingQueue<T>::size() const noexcept
	{
		size_t size = 0;
		for (const auto& producer : _producers)
			size += producer->queue.size();
		return size;
	}

	template<typename T>
	inline bool MPSCRingQueue<T>::Enqueue(const T& item)
	{
		T temp = item;
		return Enqueue(std::forward<T>(temp));
	}

	template<typename T>
	inline bool MPSCRingQueue<T>::Enqueue(T&& item)
	{
		// Get producer index for the current thread based on RDTS value
		size_t index = XTTimestamp::rdts() % _concurrency;

		// Lock the chosen producer using its spin-lock
		Locker<SpinLock> lock(_producers[index]->lock);

		// Enqueue the item into the producer's ring queue
		return _producers[index]->queue.Enqueue(std::forward<T>(item));
	}

	template<typename T>
	inline bool MPSCRingQueue<T>::Dequeue(T& item)
	{
		// Try to dequeue one item from the one of producer's ring queue
		for (size_t i = 0; i < _concurrency; ++i)
		{
			if (_producers[_consumer++ % _concurrency]->queue.Dequeue(item))
				return true;
		}

		return false;
	}

	template<typename T>
	inline bool MPSCRingQueue<T>::Dequeue(const std::function<void(const T&)>& handler)
	{
		assert((handler) && "Batch handler must be valid!");

		bool result = false;

		// Consume all available items from producers' ring queues
		for (auto& producer : _producers)
		{
			T item;
			while (producer->queue.Dequeue(item))
			{
				handler(item);
				result = true;
			}
		}

		return result;
	}

}//namespace 

#endif