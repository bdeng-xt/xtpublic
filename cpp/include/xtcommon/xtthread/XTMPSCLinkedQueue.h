#pragma once
#ifndef XT_MPMC_LINKED_QUEUE_H
#define XT_MPMC_LINKED_QUEUE_H

/**
* \file XTMPMCLinkedQueue.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a multi producers multi consumers linked queue class .
*
* \description
*	Designed for a multi producers multi consumers linked queue class.
*/

#include <cstdint>
#include <string>
#include <iostream>

#include <atomic>
#include <cstring>
#include <utility>

namespace XT
{

	//! Multiple producers / single consumer wait-free linked queue
	/*!
		Multiple producers / single consumer wait-free linked queue use only atomic operations to provide thread-safe
		enqueue and dequeue operations. Linked queue is a dynamically grows queue which allocates memory for each
		new node.

		FIFO order is guaranteed!

		Thread-safe.

		C++ implementation of Dmitry Vyukov's non-intrusive lock free unbound MPSC queue
		http://www.1024cores.net/home/lock-free-algorithms/queues/non-intrusive-mpsc-node-based-queue
	*/
	template<typename T>
	class MPSCLinkedQueue
	{
	public:
		MPSCLinkedQueue();
		MPSCLinkedQueue(const MPSCLinkedQueue&) = delete;
		MPSCLinkedQueue(MPSCLinkedQueue&&) = delete;
		~MPSCLinkedQueue();

		MPSCLinkedQueue& operator=(const MPSCLinkedQueue&) = delete;
		MPSCLinkedQueue& operator=(MPSCLinkedQueue&&) = delete;

		//! Enqueue an item into the linked queue (multiple producers threads method)
		/*!
			The item will be copied into the linked queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if there is no enough memory for the queue node
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the linked queue (multiple producers threads method)
		/*!
			The item will be moved into the linked queue.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if there is no enough memory for the queue node
		*/
		bool Enqueue(T&& item);

		//! Dequeue an item from the linked queue (single consumer thread method)
		/*!
			The item will be moved from the linked queue.

			Will not block.

			\param item - Item to dequeue
			\return 'true' if the item was successfully dequeue, 'false' if the linked queue is empty
		*/
		bool Dequeue(T& item);

	private:
		struct Node
		{
			std::atomic<Node*> next;
			T value;
		};

		typedef char cache_line_pad[128];

		cache_line_pad _pad0;
		std::atomic<Node*> _head;
		cache_line_pad _pad1;
		std::atomic<Node*> _tail;
		cache_line_pad _pad2;
	};
//////
	template<typename T>
	inline MPSCLinkedQueue<T>::MPSCLinkedQueue() : _head(new Node), _tail(_head.load(std::memory_order_relaxed))
	{
		memset(_pad0, 0, sizeof(cache_line_pad));
		memset(_pad1, 0, sizeof(cache_line_pad));
		memset(_pad2, 0, sizeof(cache_line_pad));

		// Linked queue is initialized with a fake node as a head node
		Node* front = _head.load(std::memory_order_relaxed);
		front->next.store(nullptr, std::memory_order_relaxed);
	}

	template<typename T>
	inline MPSCLinkedQueue<T>::~MPSCLinkedQueue()
	{
		// Remove all nodes from the linked queue
		T item;
		while (Dequeue(item)) {}

		// Remove the last fake node
		Node* front = _head.load(std::memory_order_relaxed);
		delete front;
	}

	template<typename T>
	inline bool MPSCLinkedQueue<T>::Enqueue(const T& item)
	{
		T temp = item;
		return Enqueue(std::forward<T>(temp));
	}

	template<typename T>
	inline bool MPSCLinkedQueue<T>::Enqueue(T&& item)
	{
		// Create new head node
		Node* node = new Node;
		if (node == nullptr)
			return false;

		// Fill new head node with the given value
		node->value = std::move(item);
		node->next.store(nullptr, std::memory_order_relaxed);

		// Insert new head node into the queue and linked it with the previous one
		Node* prev_head = _head.exchange(node, std::memory_order_acq_rel);
		prev_head->next.store(node, std::memory_order_release);

		return true;
	}

	template<typename T>
	inline bool MPSCLinkedQueue<T>::Dequeue(T& item)
	{
		Node* tail = _tail.load(std::memory_order_relaxed);
		Node* next = tail->next.load(std::memory_order_acquire);

		// Check if the linked queue is empty
		if (next == nullptr)
			return false;

		// Get the item value
		item = std::move(next->value);

		// Update tail node with a next one
		_tail.store(next, std::memory_order_release);

		// Remove the previous tail node
		delete tail;

		return true;
	}

}//namespace XT

#endif