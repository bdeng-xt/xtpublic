#pragma once
#ifndef XT_FILE_CACHE_H
#define XT_FILE_CACHE_H

/**
* \file FileCache.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide file cache classes .
*
* \description
*	Designed for file cache classes .
*/

#include <cstdint>
#include <string>
#include <iostream>


#include "XTDirectory.h"
#include "XTFile.h"
#include "XTPath.h"
#include "XTTimespan.h"
#include "XTTimestamp.h"

#include <functional>
#include <map>

#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp> //#include <shared_mutex>
#include <string>
//#include <string_view>
#include <tuple>
#include <unordered_map>
#include "XTConfig.h"

namespace XT
{

	//! File cache
	/*!
		File cache is used to cache files in memory with optional
		timeouts.

		Thread-safe.
	*/
	class XT_COMMON_API FileCache
	{
	public:
		//! File cache insert hanlder type
		typedef std::function<bool(FileCache& cache, const std::string& key, const std::string& value, const XTTimespan& timeout)> InsertHandler;

		FileCache() = default;
		FileCache(const FileCache&) = delete;
		FileCache(FileCache&&) = delete;
		~FileCache() = default;

		FileCache& operator=(const FileCache&) = delete;
		FileCache& operator=(FileCache&&) = delete;

		//! Check if the file cache is not empty
		explicit operator bool() const { return !empty(); }

		//! Is the file cache empty?
		bool empty() const;

		//! Get the file cache size
		size_t size() const;

		//! Emplace a new cache value with the given timeout into the file cache
		/*!
			\param key - Key to emplace
			\param value - Value to emplace
			\param timeout - Cache timeout (default is 0 - no timeout)
			\return 'true' if the cache value was emplaced, 'false' if the given key was not emplaced
		*/
		bool emplace(std::string&& key, std::string&& value, const XTTimespan& timeout = XTTimespan(0));

		//! Insert a new cache value with the given timeout into the file cache
		/*!
			\param key - Key to insert
			\param value - Value to insert
			\param timeout - Cache timeout (default is 0 - no timeout)
			\return 'true' if the cache value was inserted, 'false' if the given key was not inserted
		*/
		bool insert(const std::string& key, const std::string& value, const XTTimespan& timeout = XTTimespan(0));

		//! Try to find the cache value by the given key
		/*!
			\param key - Key to find
			\return 'true' if the cache value was found, 'false' if the given key was not found
		*/
		std::pair<bool, std::string> find(const std::string& key);
		//! Try to find the cache value with timeout by the given key
		/*!
			\param key - Key to find
			\param timeout - Cache timeout value
			\return 'true' if the cache value was found, 'false' if the given key was not found
		*/
		std::pair<bool, std::string> find(const std::string& key, XTTimestamp& timeout);

		//! Remove the cache value with the given key from the file cache
		/*!
			\param key - Key to remove
			\return 'true' if the cache value was removed, 'false' if the given key was not found
		*/
		bool remove(const std::string& key);

		//! Insert a new cache path with the given timeout into the file cache
		/*!
			\param path - Path to insert
			\param prefix - Cache prefix (default is "/")
			\param timeout - Cache timeout (default is 0 - no timeout)
			\param handler - Cache insert handler (default is 'return cache.insert(key, value, timeout)')
			\return 'true' if the cache path was setup, 'false' if failed to setup the cache path
		*/
		bool insert_path(const XT::Path& path, const std::string& prefix = "/", const XTTimespan& timeout = XTTimespan(0), const InsertHandler& handler = [](FileCache& cache, const std::string& key, const std::string& value, const XTTimespan& timeout) 
		{ return cache.insert(key, value, timeout); });

		//! Try to find the cache path
		/*!
			\param path - Path to find
			\return 'true' if the cache path was found, 'false' if the given path was not found
		*/
		bool find_path(const XT::Path& path);
		//! Try to find the cache path with timeout
		/*!
			\param path - Path to find
			\param timeout - Cache timeout value
			\return 'true' if the cache path was found, 'false' if the given path was not found
		*/
		bool find_path(const XT::Path& path, XTTimestamp& timeout);

		//! Remove the cache path from the file cache
		/*!
			\param path - Path to remove
			\return 'true' if the cache path was removed, 'false' if the given path was not found
		*/
		bool remove_path(const XT::Path& path);

		//! Clear the memory cache
		void clear();

		//! Watchdog the file cache
		void watchdog(const XTUtcTimestamp& utc = XTUtcTimestamp());

		//! Swap two instances
		void swap(FileCache& cache) noexcept;
		friend void swap(FileCache& cache1, FileCache& cache2) noexcept;

	private:
		mutable boost::shared_mutex _lock;// mutable std::shared_mutex _lock;
		XTTimestamp _timestamp;

		struct MemCacheEntry
		{
			std::string value;
			XTTimestamp timestamp;
			XTTimespan timespan;

			MemCacheEntry() = default;
			MemCacheEntry(const std::string& v, const XTTimestamp& ts = XTTimestamp(), const XTTimespan& tp = XTTimespan()) : value(v), timestamp(ts), timespan(tp) {}
			MemCacheEntry(std::string&& v, const XTTimestamp& ts = XTTimestamp(), const XTTimespan& tp = XTTimespan()) : value(v), timestamp(ts), timespan(tp) {}
		};

		struct FileCacheEntry
		{
			std::string prefix;
			InsertHandler handler;
			XTTimestamp timestamp;
			XTTimespan timespan;

			FileCacheEntry() = default;
			FileCacheEntry(const std::string& pfx, const InsertHandler& h, const XTTimestamp& ts = XTTimestamp(), const XTTimespan& tp = XTTimespan()) : prefix(pfx), handler(h), timestamp(ts), timespan(tp) {}
		};

		std::unordered_map<std::string, MemCacheEntry> _entries_by_key;
		std::map<XTTimestamp, std::string> _entries_by_timestamp;
		std::map<XT::Path, FileCacheEntry> _paths_by_key;
		std::map<XTTimestamp, XT::Path> _paths_by_timestamp;

		bool remove_internal(const std::string& key);
		bool insert_path_internal(const XT::Path& path, const std::string& prefix, const XTTimespan& timeout, const InsertHandler& handler);
		bool remove_path_internal(const XT::Path& path);
	};
//////
	inline bool FileCache::empty() const
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);// std::shared_lock<std::shared_mutex> locker(_lock);
		return _entries_by_key.empty();
	}

	inline size_t FileCache::size() const
	{
		boost::shared_lock<boost::shared_mutex> locker(_lock);// std::shared_lock<std::shared_mutex> locker(_lock);
		return _entries_by_key.size();
	}

	inline void swap(FileCache& cache1, FileCache& cache2) noexcept
	{
		cache1.swap(cache2);
	}



}//namespace XT


#endif