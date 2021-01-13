#pragma once
#ifndef XT_WAIT_BATCHER_H
#define XT_WAIT_BATCHER_H

/**
* \file XTWaitBatcher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a wait batcher class .
*
* \description
*	Designed for a wait batcher class.
*/

#include "XTConditionVariable.h"

#include <cassert>
#include <vector>

namespace XT
{

	//! Multiple producers / multiple consumers wait batcher
	/*!
		Multiple producers / multiple consumers wait batcher provides a classic solution
		for producer-consumer problem using two vectors and hot-swap technique with monitor
		synchronization primitive (mutex with condition variable). It allows a consumer thread
		to process all items in queue in a batch mode.

		FIFO order is guaranteed!

		https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
	*/
	template<typename T>
	class WaitBatcher
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Wait batcher capacity (0 for unlimited capacity, default is 0)
			\param initial - Initial wait batcher capacity (default is 0)
		*/
		explicit WaitBatcher(size_t capacity = 0, size_t initial = 0);
		WaitBatcher(const WaitBatcher&) = delete;
		WaitBatcher(WaitBatcher&&) = delete;
		~WaitBatcher();

		WaitBatcher& operator=(const WaitBatcher&) = delete;
		WaitBatcher& operator=(WaitBatcher&&) = delete;

		//! Check if the wait batcher is not empty
		explicit operator bool() const noexcept { return !closed() && !empty(); }

		//! Is wait batcher closed?
		bool closed() const;

		//! Is wait batcher empty?
		bool empty() const { return (size() == 0); }
		//! Get wait batcher capacity
		size_t capacity() const;
		//! Get wait batcher size
		size_t size() const;

		//! Enqueue an item into the wait batcher
		/*!
			The item will be copied into the wait batcher.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait batcher is closed
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the wait batcher
		/*!
			The item will be moved into the wait batcher.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait batcher is closed
		*/
		bool Enqueue(T&& item);
		//! Enqueue all items into the wait batcher
		/*!
			All items will be copied into the wait batcher.

			Will block.

			\param first - Iterator to the first item
			\param last - Iterator to the last item
			\return 'true' if all items were successfully enqueue, 'false' if the wait batcher is closed
		*/
		template <class InputIterator>
		bool Enqueue(InputIterator first, InputIterator last);

		//! Dequeue all items from the wait batcher
		/*!
			Will block.

			\param items - Items to dequeue
			\return 'true' if all items was successfully dequeue, 'false' if the wait batcher is closed
		*/
		bool Dequeue(std::vector<T>& items);

		//! Close the wait batcher
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
		std::vector<T> _batch;
	};

//////
	template<typename T>
	inline WaitBatcher<T>::WaitBatcher(size_t capacity, size_t initial) : _closed(false), _capacity(capacity)
	{
		_batch.reserve(initial);
	}

	template<typename T>
	inline WaitBatcher<T>::~WaitBatcher()
	{
		Close();
	}

	template<typename T>
	inline bool WaitBatcher<T>::closed() const
	{
		Locker<CriticalSection> locker(_cs);
		return _closed;
	}

	template<typename T>
	inline size_t WaitBatcher<T>::capacity() const
	{
		if (_capacity > 0)
			return _capacity;

		Locker<CriticalSection> locker(_cs);
		return _batch.capacity();
	}

	template<typename T>
	inline size_t WaitBatcher<T>::size() const
	{
		Locker<CriticalSection> locker(_cs);
		return _batch.size();
	}

	template<typename T>
	inline bool WaitBatcher<T>::Enqueue(const T& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if ((_capacity == 0) || (_batch.size() < _capacity))
			{
				_batch.push_back(item);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (_capacity == 0) || (_batch.size() < _capacity)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	inline bool WaitBatcher<T>::Enqueue(T&& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if ((_capacity == 0) || (_batch.size() < _capacity))
			{
				_batch.emplace_back(item);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (_capacity == 0) || (_batch.size() < _capacity)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	template <class InputIterator>
	inline bool WaitBatcher<T>::Enqueue(InputIterator first, InputIterator last)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if ((_capacity == 0) || (_batch.size() < _capacity))
			{
				_batch.insert(_batch.end(), first, last);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (_capacity == 0) || (_batch.size() < _capacity)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	inline bool WaitBatcher<T>::Dequeue(std::vector<T>& items)
	{
		// Clear the result items vector
		items.clear();

		Locker<CriticalSection> locker(_cs);

		if (_closed && _batch.empty())
			return false;

		do
		{
			if (!_batch.empty())
			{
				// Swap batch items
				std::swap(_batch, items);
				_cv2.NotifyOne();
				return true;
			}

			_cv1.Wait(_cs, [this]() { return (_closed || !_batch.empty()); });

		} while (!_closed || !_batch.empty());

		return false;
	}

	template<typename T>
	inline void WaitBatcher<T>::Close()
	{
		Locker<CriticalSection> locker(_cs);
		_closed = true;
		_cv1.NotifyAll();
		_cv2.NotifyAll();
	}

}//namespace XT

#endif