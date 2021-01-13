#pragma once
#ifndef XT_MPSC_LINKED_BATCHER_H
#define XT_MPSC_LINKED_BATCHER_H

/**
* \file XTMPSCLinkedBatcher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a multi producers single consumers linked batcher class .
*
* \description
*	Designed for a multi producers single consumers linked batcher class.
*/

#include <cstdint>
#include <string>
#include <iostream>

#include <atomic>
#include <cassert>
#include <functional>
#include <utility>

namespace XT
{

	//! Multiple producers / single consumer wait-free linked batcher
	/*!
		Multiple producers / single consumer wait-free linked batcher use only atomic operations to provide thread-safe
		enqueue and batch dequeue operations. Linked batcher is a dynamically grows queue which allocates memory for each
		new node. It allows a consumer thread to process all items in queue in a batch mode.

		FIFO order is guaranteed!

		Thread-safe.

		Based on Boost Wait-free multi-producer queue
		http://www.boost.org/doc/libs/1_60_0/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.mp_queue
	*/
	template<typename T>
	class MPSCLinkedBatcher
	{
	public:
		MPSCLinkedBatcher();
		MPSCLinkedBatcher(const MPSCLinkedBatcher&) = delete;
		MPSCLinkedBatcher(MPSCLinkedBatcher&&) = delete;
		~MPSCLinkedBatcher();

		MPSCLinkedBatcher& operator=(const MPSCLinkedBatcher&) = delete;
		MPSCLinkedBatcher& operator=(MPSCLinkedBatcher&&) = delete;

		//! Enqueue an item into the linked batcher (multiple producers threads method)
		/*!
			The item will be copied into the linked batcher.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if there is no enough memory for the batcher node
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the linked batcher (multiple producers threads method)
		/*!
			The item will be moved into the linked batcher.

			Will not block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if there is no enough memory for the batcher node
		*/
		bool Enqueue(T&& item);

		//! Dequeue all items from the linked queue (single consumer thread method)
		/*!
			All items in the batcher will be processed by the given handler.

			Will not block.

			\param handler - Batch handler (default is empty handler)
			\return 'true' if all items were successfully handled, 'false' if the linked batcher is empty
		*/
		bool Dequeue(const std::function<void(const T&)>& handler = [](const int&) {});

	private:
		struct Node
		{
			Node* next;
			T value;
		};

		std::atomic<Node*> _head;
	};
//////
	template<typename T>
	inline MPSCLinkedBatcher<T>::MPSCLinkedBatcher() : _head(nullptr)
	{
	}

	template<typename T>
	inline MPSCLinkedBatcher<T>::~MPSCLinkedBatcher()
	{
		// Remove all nodes from the linked batcher
		Dequeue([](const T&) {});
	}

	template<typename T>
	inline bool MPSCLinkedBatcher<T>::Enqueue(const T& item)
	{
		T temp = item;
		return Enqueue(std::forward<T>(temp));
	}

	template<typename T>
	inline bool MPSCLinkedBatcher<T>::Enqueue(T&& item)
	{
		// Create new head node
		Node* node = new Node;
		if (node == nullptr)
			return false;

		// Fill new head node with the given value
		node->value = std::move(item);

		// Insert new head node into the batcher and linked it with the previous one
		Node* prev_head = _head.load(std::memory_order_relaxed);
		do
		{
			node->next = prev_head;
		} while (!_head.compare_exchange_weak(prev_head, node, std::memory_order_release));

		return true;
	}

	template<typename T>
	inline bool MPSCLinkedBatcher<T>::Dequeue(const std::function<void(const T&)>& handler)
	{
		assert((handler) && "Batch handler must be valid!");

		Node* last = _head.exchange(nullptr, std::memory_order_acq_rel);
		Node* first = nullptr;

		// Check if the linked batcher is empty
		if (last == nullptr)
			return false;

		// Reverse the order to get nodes in FIFO order
		do
		{
			Node* temp = last;
			last = last->next;
			temp->next = first;
			first = temp;
		} while (last != nullptr);

		// Process all items in a batch mode
		do
		{
			Node* temp = first;
			first = first->next;
			// Process the item with the given handler
			handler(temp->value);
			delete temp;
		} while (first != nullptr);

		return true;
	}

}//namespace XT

#endif