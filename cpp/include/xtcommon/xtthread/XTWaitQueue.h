#pragma once
#ifndef XT_WAIT_QUEUE_H
#define XT_WAIT_QUEUE_H

/**
* \file XTWaitQueue.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a wait queue class .
*
* \description
*	Designed for a wait queue class.
*/


#include "XTConditionVariable.h"

#include <queue>

namespace XT
{

	//! Multiple producers / multiple consumers wait queue
	/*!
		Multiple producers / multiple consumers wait queue provides a classic solution
		for producer-consumer problem using queue and monitor synchronization primitive
		(mutex with condition variable).

		FIFO order is guaranteed!

		https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
	*/
	template<typename T>
	class WaitQueue
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Wait queue capacity (default is 0 for unlimited capacity)
		*/
		explicit WaitQueue(size_t capacity = 0);
		WaitQueue(const WaitQueue&) = delete;
		WaitQueue(WaitQueue&&) = default;
		~WaitQueue();

		WaitQueue& operator=(const WaitQueue&) = delete;
		WaitQueue& operator=(WaitQueue&&) = default;

		//! Check if the wait queue is not empty
		explicit operator bool() const noexcept { return !closed() && !empty(); }

		//! Is wait queue closed?
		bool closed() const;

		//! Is wait queue empty?
		bool empty() const { return (size() == 0); }
		//! Get wait queue capacity
		size_t capacity() const;
		//! Get wait queue size
		size_t size() const;

		//! Enqueue an item into the wait queue
		/*!
			The item will be copied into the wait queue.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait queue is closed
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the wait queue
		/*!
			The item will be moved into the wait queue.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait queue is closed
		*/
		bool Enqueue(T&& item);

		//! Dequeue an item from the wait queue
		/*!
			The item will be moved from the wait queue.

			Will block.

			\param item - Item to dequeue
			\return 'true' if the item was successfully dequeue, 'false' if the wait queue is closed
		*/
		bool Dequeue(T& item);

		//! Close the wait queue
		/*!
			Will block.
		*/
		void Close();

	private:
		bool _closed;
		const size_t _capacity;
		mutable CriticalSection _cs;
		ConditionVariable _cv1;
		ConditionVariable _cv2;
		std::queue<T> _queue;
	};

//////
	template<typename T>
	inline WaitQueue<T>::WaitQueue(size_t capacity) : _closed(false), _capacity(capacity)
	{
	}

	template<typename T>
	inline WaitQueue<T>::~WaitQueue()
	{
		Close();
	}

	template<typename T>
	inline bool WaitQueue<T>::closed() const
	{
		Locker<CriticalSection> locker(_cs);
		return _closed;
	}

	template<typename T>
	inline size_t WaitQueue<T>::capacity() const
	{
		if (_capacity > 0)
			return _capacity;

		Locker<CriticalSection> locker(_cs);
		return _queue.size();
	}

	template<typename T>
	inline size_t WaitQueue<T>::size() const
	{
		Locker<CriticalSection> locker(_cs);
		return _queue.size();
	}

	template<typename T>
	inline bool WaitQueue<T>::Enqueue(const T& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if ((_capacity == 0) || (_queue.size() < _capacity))
			{
				_queue.push(item);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (_capacity == 0) || (_queue.size() < _capacity)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	inline bool WaitQueue<T>::Enqueue(T&& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if ((_capacity == 0) || (_queue.size() < _capacity))
			{
				_queue.emplace(item);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (_capacity == 0) || (_queue.size() < _capacity)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	inline bool WaitQueue<T>::Dequeue(T& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed && _queue.empty())
			return false;

		do
		{
			if (!_queue.empty())
			{
				item = _queue.front();
				_queue.pop();
				_cv2.NotifyOne();
				return true;
			}

			_cv1.Wait(_cs, [this]() { return (_closed || !_queue.empty()); });

		} while (!_closed || !_queue.empty());

		return false;
	}

	template<typename T>
	inline void WaitQueue<T>::Close()
	{
		Locker<CriticalSection> locker(_cs);
		_closed = true;
		_cv1.NotifyAll();
		_cv2.NotifyAll();
	}


}//namespace XT

#endif