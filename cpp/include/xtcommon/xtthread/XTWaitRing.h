#pragma once
#ifndef XT_WAIT_RING_H
#define XT_WAIT_RING_H

/**
* \file XTWaitRing.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a wait ring class .
*
* \description
*	Designed for a wait ring class.
*/

#include "XTConditionVariable.h"

#include <cassert>
#include <vector>

namespace XT
{

	//! Multiple producers / multiple consumers wait ring
	/*!
		Multiple producers / multiple consumers wait ring provides a classic solution
		for producer-consumer problem using fixed ring and monitor synchronization
		primitive (mutex with condition variable).

		FIFO order is guaranteed!

		https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
	*/
	template<typename T>
	class WaitRing
	{
	public:
		//! Default class constructor
		/*!
			\param capacity - Ring capacity (must be a power of two)
		*/
		explicit WaitRing(size_t capacity);
		WaitRing(const WaitRing&) = delete;
		WaitRing(WaitRing&&) = delete;
		~WaitRing();

		WaitRing& operator=(const WaitRing&) = delete;
		WaitRing& operator=(WaitRing&&) = delete;

		//! Check if the wait ring is not empty
		explicit operator bool() const noexcept { return !closed() && !empty(); }

		//! Is wait ring closed?
		bool closed() const;

		//! Is wait ring empty?
		bool empty() const { return (size() == 0); }
		//! Get wait ring capacity
		size_t capacity() const { return _capacity; }
		//! Get wait ring size
		size_t size() const;

		//! Enqueue an item into the wait ring
		/*!
			The item will be copied into the wait ring.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait ring is closed
		*/
		bool Enqueue(const T& item);
		//! Enqueue an item into the wait ring
		/*!
			The item will be moved into the wait ring.

			Will block.

			\param item - Item to enqueue
			\return 'true' if the item was successfully enqueue, 'false' if the wait ring is closed
		*/
		bool Enqueue(T&& item);

		//! Dequeue an item from the wait ring
		/*!
			The item will be moved from the wait ring.

			Will block.

			\param item - Item to dequeue
			\return 'true' if the item was successfully dequeue, 'false' if the wait ring is closed
		*/
		bool Dequeue(T& item);

		//! Close the wait ring
		/*!
			Will block.
		*/
		void Close();

	private:
		bool _closed;
		mutable CriticalSection _cs;
		ConditionVariable _cv1;
		ConditionVariable _cv2;
		const size_t _capacity;
		const size_t _mask;
		size_t _head;
		size_t _tail;
		std::vector<T> _ring;
	};

//////
	template<typename T>
	inline WaitRing<T>::WaitRing(size_t capacity) : _closed(false), _capacity(capacity - 1), _mask(capacity - 1), _head(0), _tail(0), _ring(capacity)
	{
		assert((capacity > 1) && "Ring capacity must be greater than one!");
		assert(((capacity & (capacity - 1)) == 0) && "Ring capacity must be a power of two!");
	}

	template<typename T>
	inline WaitRing<T>::~WaitRing()
	{
		Close();
	}

	template<typename T>
	inline bool WaitRing<T>::closed() const
	{
		Locker<CriticalSection> locker(_cs);
		return _closed;
	}

	template<typename T>
	inline size_t WaitRing<T>::size() const
	{
		Locker<CriticalSection> locker(_cs);
		return _head - _tail;
	}

	template<typename T>
	inline bool WaitRing<T>::Enqueue(const T& item)
	{
		T temp = item;
		return Enqueue(std::forward<T>(temp));
	}

	template<typename T>
	inline bool WaitRing<T>::Enqueue(T&& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed)
			return false;

		do
		{
			if (((_head - _tail + 1) & _mask) != 0)
			{
				_ring[_head++ & _mask] = std::move(item);
				_cv1.NotifyOne();
				return true;
			}

			_cv2.Wait(_cs, [this]() { return (_closed || (((_head - _tail + 1) & _mask) != 0)); });

		} while (!_closed);

		return false;
	}

	template<typename T>
	inline bool WaitRing<T>::Dequeue(T& item)
	{
		Locker<CriticalSection> locker(_cs);

		if (_closed && (((_head - _tail) & _mask) == 0))
			return false;

		do
		{
			if (((_head - _tail) & _mask) != 0)
			{
				item = std::move(_ring[_tail++ & _mask]);
				_cv2.NotifyOne();
				return true;
			}

			_cv1.Wait(_cs, [this]() { return (_closed || (((_head - _tail) & _mask) != 0)); });

		} while (!_closed || (((_head - _tail) & _mask) != 0));

		return false;
	}

	template<typename T>
	inline void WaitRing<T>::Close()
	{
		Locker<CriticalSection> locker(_cs);
		_closed = true;
		_cv1.NotifyAll();
		_cv2.NotifyAll();
	}


}//namespace XT

#endif