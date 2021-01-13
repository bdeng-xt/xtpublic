#pragma once
#ifndef XT_MEM_CACHE_H
#define XT_MEM_CACHE_H

/**
* \file MemCache.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide memory cache classes .
*
* \description
*	Designed for memory cache classes .
*/

#include <cstdint>
#include <string>
#include <iostream>



#include "XTTimespan.h"
#include "XTTimestamp.h"

#include <map>
#include <memory>
#include <boost/thread.hpp>
#include <boost/thread/shared_mutex.hpp> //<shared_mutex>
#include <unordered_map>

namespace XT
{

	//! Memory cache
	/*!
		Memory cache is used to cache data in memory with optional
		timeouts.

		Thread-safe.
	*/
	template <typename TKey, typename TValue>
	class MemCache
	{
	public:
		MemCache() = default;
		MemCache(const MemCache&) = delete;
		MemCache(MemCache&&) = delete;
		~MemCache() = default;

		MemCache& operator=(const MemCache&) = delete;
		MemCache& operator=(MemCache&&) = delete;

		//! Check if the memory cache is not empty
		explicit operator bool() const { return !empty(); }

		//! Is the memory cache empty?
		bool empty() const;

		//! Get the memory cache size
		size_t size() const;

		//! Emplace a new cache value with the given timeout into the memory cache
		/*!
			\param key - Key to emplace
			\param value - Value to emplace
			\param timeout - Cache timeout (default is 0 - no timeout)
			\return 'true' if the cache value was emplaced, 'false' if the given key was not emplaced
		*/
		bool emplace(TKey&& key, TValue&& value, const XTTimespan& timeout = XTTimespan(0));

		//! Insert a new cache value with the given timeout into the memory cache
		/*!
			\param key - Key to insert
			\param value - Value to insert
			\param timeout - Cache timeout (default is 0 - no timeout)
			\return 'true' if the cache value was inserted, 'false' if the given key was not inserted
		*/
		bool insert(const TKey& key, const TValue& value, const XTTimespan& timeout = XTTimespan(0));

		//! Try to find the cache value by the given key
		/*!
			\param key - Key to find
			\return 'true' if the cache value was found, 'false' if the given key was not found
		*/
		bool find(const TKey& key);
		//! Try to find the cache value by the given key
		/*!
			\param key - Key to find
			\param value - Value to find
			\return 'true' if the cache value was found, 'false' if the given key was not found
		*/
		bool find(const TKey& key, TValue& value);
		//! Try to find the cache value with timeout by the given key
		/*!
			\param key - Key to find
			\param value - Value to find
			\param timeout - Cache timeout value
			\return 'true' if the cache value was found, 'false' if the given key was not found
		*/
		bool find(const TKey& key, TValue& value, XTTimestamp& timeout);

		//! Remove the cache value with the given key from the memory cache
		/*!
			\param key - Key to remove
			\return 'true' if the cache value was removed, 'false' if the given key was not found
		*/
		bool remove(const TKey& key);

		//! Clear the memory cache
		void clear();

		//! Watchdog the memory cache
		void watchdog(const XTUtcTimestamp& utc = XTUtcTimestamp());

		//! Swap two instances
		void swap(MemCache& cache) noexcept;
		template <typename UKey, typename UValue>
		friend void swap(MemCache<UKey, UValue>& cache1, MemCache<UKey, UValue>& cache2) noexcept;

	private:
		mutable boost::shared_mutex _lock;// mutable std::shared_mutex _lock;
		XTTimestamp _timestamp;

		struct MemCacheEntry
		{
			TValue value;
			XTTimestamp timestamp;
			XTTimespan timespan;

			MemCacheEntry() = default;
			MemCacheEntry(const TValue& v, const XTTimestamp& ts = XTTimestamp(), const XTTimespan& tp = XTTimespan()) : value(v), timestamp(ts), timespan(tp) {}
			MemCacheEntry(TValue&& v, const XTTimestamp& ts = XTTimestamp(), const XTTimespan& tp = XTTimespan()) : value(v), timestamp(ts), timespan(tp) {}
		};

		std::unordered_map<TKey, MemCacheEntry> _entries_by_key;
		std::map<XTTimestamp, TKey> _entries_by_timestamp;

		bool remove_internal(const TKey& key);
	};

//////
	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::empty() const
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);// std::shared_lock<std::shared_mutex> locker(_lock);
		return _entries_by_key.empty();
	}

	template <typename TKey, typename TValue>
	inline size_t MemCache<TKey, TValue>::size() const
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);//std::shared_lock<std::shared_mutex> locker(_lock);
		return _entries_by_key.size();
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::emplace(TKey&& key, TValue&& value, const XTTimespan& timeout)
	{
		std::unique_lock<boost::shared_mutex> locker(_lock);// std::unique_lock<std::shared_mutex> locker(_lock);

		// Try to find and remove the previous key
		remove_internal(key);

		// Update the cache entry
		if (timeout.total() > 0)
		{
			XTTimestamp current = XTUtcTimestamp();
			_timestamp = (current <= _timestamp) ? _timestamp + 1 : current;
			_entries_by_key.insert(std::make_pair(key, MemCacheEntry(std::move(value), _timestamp, timeout)));
			_entries_by_timestamp.insert(std::make_pair(_timestamp, key));
		}
		else
			_entries_by_key.emplace(std::make_pair(std::move(key), MemCacheEntry(std::move(value))));

		return true;
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::insert(const TKey& key, const TValue& value, const XTTimespan& timeout)
	{
		std::unique_lock<boost::shared_mutex> locker(_lock);//std::unique_lock<std::shared_mutex> locker(_lock);

		// Try to find and remove the previous key
		remove_internal(key);

		// Update the cache entry
		if (timeout.total() > 0)
		{
			XTTimestamp current = XTUtcTimestamp();
			_timestamp = (current <= _timestamp) ? _timestamp + 1 : current;
			_entries_by_key.insert(std::make_pair(key, MemCacheEntry(value, _timestamp, timeout)));
			_entries_by_timestamp.insert(std::make_pair(_timestamp, key));
		}
		else
			_entries_by_key.insert(std::make_pair(key, MemCacheEntry(value)));

		return true;
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::find(const TKey& key)
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);// std::shared_lock<std::shared_mutex> locker(_lock);

		// Try to find the given key
		auto it = _entries_by_key.find(key);
		if (it == _entries_by_key.end())
			return false;

		return true;
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::find(const TKey& key, TValue& value)
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);//std::shared_lock<std::shared_mutex> locker(_lock);

		// Try to find the given key
		auto it = _entries_by_key.find(key);
		if (it == _entries_by_key.end())
			return false;

		value = it->second.value;
		return true;
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::find(const TKey& key, TValue& value, XTTimestamp& timeout)
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);//std::shared_lock<std::shared_mutex> locker(_lock);

		// Try to find the given key
		auto it = _entries_by_key.find(key);
		if (it == _entries_by_key.end())
			return false;

		value = it->second.value;
		timeout = it->second.timestamp + it->second.timespan;
		return true;
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::remove(const TKey& key)
	{
		std::unique_lock<boost::shared_mutex> locker(_lock);// std::unique_lock<std::shared_mutex> locker(_lock);

		return remove_internal(key);
	}

	template <typename TKey, typename TValue>
	inline bool MemCache<TKey, TValue>::remove_internal(const TKey& key)
	{
		// Try to find the given key
		auto it = _entries_by_key.find(key);
		if (it == _entries_by_key.end())
			return false;

		// Try to erase cache entry by timestamp
		if (it->second.timestamp.total() > 0)
			_entries_by_timestamp.erase(it->second.timestamp);

		// Erase cache entry
		_entries_by_key.erase(it);

		return true;
	}

	template <typename TKey, typename TValue>
	inline void MemCache<TKey, TValue>::clear()
	{
		std::unique_lock<boost::shared_mutex> locker(_lock);// std::unique_lock<std::shared_mutex> locker(_lock);

		// Clear all cache entries
		_entries_by_key.clear();
		_entries_by_timestamp.clear();
	}

	template <typename TKey, typename TValue>
	inline void MemCache<TKey, TValue>::watchdog(const XTUtcTimestamp& utc)
	{
		std::unique_lock<boost::shared_mutex> locker(_lock);//std::unique_lock<std::shared_mutex> locker(_lock);

		// Watchdog for cache entries
		auto it_entry_by_timestamp = _entries_by_timestamp.begin();
		while (it_entry_by_timestamp != _entries_by_timestamp.end())
		{
			// Check for the cache entry timeout
			auto it_entry_by_key = _entries_by_key.find(it_entry_by_timestamp->second);
			if ((it_entry_by_key->second.timestamp + it_entry_by_key->second.timespan) <= utc)
			{
				// Erase the cache entry with timeout
				_entries_by_key.erase(it_entry_by_key);
				_entries_by_timestamp.erase(it_entry_by_timestamp);
				it_entry_by_timestamp = _entries_by_timestamp.begin();
				continue;
			}
			else
				break;
		}
	}

	template <typename TKey, typename TValue>
	inline void MemCache<TKey, TValue>::swap(MemCache& cache) noexcept
	{
		std::unique_lock<boost::shared_mutex> locker1(_lock);// std::unique_lock<std::shared_mutex> locker1(_lock);
		std::unique_lock<boost::shared_mutex> locker2(cache._lock);// std::unique_lock<std::shared_mutex> locker2(cache._lock);

		using std::swap;
		swap(_timestamp, cache._timestamp);
		swap(_entries_by_key, cache._entries_by_key);
		swap(_entries_by_timestamp, cache._entries_by_timestamp);
	}

	template <typename TKey, typename TValue>
	inline void swap(MemCache<TKey, TValue>& cache1, MemCache<TKey, TValue>& cache2) noexcept
	{
		cache1.swap(cache2);
	}


}//namespace


#endif
