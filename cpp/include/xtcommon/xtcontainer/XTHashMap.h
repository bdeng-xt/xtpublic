#pragma once
#ifndef XT_HASHMAP_H
#define XT_HASHMAP_H

/**
* \file XTHashMap.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for hash map.
*
* \description
*	Designed for use for hash map.
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>
#include <limits>
#include <vector>

namespace XT
{

	template <class TContainer, typename TKey, typename TValue>
	class HashMapIterator;
	template <class TContainer, typename TKey, typename TValue>
	class HashMapConstIterator;
	template <class TContainer, typename TKey, typename TValue>
	class HashMapReverseIterator;
	template <class TContainer, typename TKey, typename TValue>
	class HashMapConstReverseIterator;

	//! Hash map container
	/*!
		Hash map is an efficient  structure  for  associative  keys/value  storing  and
		accessing without keeping order. It uses hash function to  convert  string  key
		into the integer and use the index to quick access value data.

		Open  address  hash map resolves collisions of the  same  hash  values  by
		inserting new item into the next free place (probing with step 1).

		Not thread-safe.
	*/
	template <typename TKey, typename TValue, typename THash = std::hash<TKey>, typename TEqual = std::equal_to<TKey>, typename TAllocator = std::allocator<std::pair<TKey, TValue>>>
	class HashMap
	{
		friend class HashMapIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue>;
		friend class HashMapConstIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue>;
		friend class HashMapReverseIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue>;
		friend class HashMapConstReverseIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue>;

	public:
		// Standard container type definitions
		typedef TKey key_type;
		typedef TValue mapped_type;
		typedef std::pair<TKey, TValue> value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef HashMapIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue> iterator;
		typedef HashMapConstIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue> const_iterator;
		typedef HashMapReverseIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue> reverse_iterator;
		typedef HashMapConstReverseIterator<HashMap<TKey, TValue, THash, TEqual, TAllocator>, TKey, TValue> const_reverse_iterator;

		//! Initialize the hash map with a given capacity and blank key value
		/*!
			\param capacity - Hash map capacity (default is 128)
			\param blank - Blank key value (default is TKey())
			\param hash - Key hasher (default is THash())
			\param equal - Key comparator (default is THash())
			\param allocator - Allocator (default is TAllocator())
		*/
		explicit HashMap(size_t capacity = 128, const TKey& blank = TKey(), const THash& hash = THash(), const TEqual& equal = TEqual(), const TAllocator& allocator = TAllocator());
		template <class InputIterator>
		HashMap(InputIterator first, InputIterator last, bool unused, size_t capacity = 128, const TKey& blank = TKey(), const THash& hash = THash(), const TEqual& equal = TEqual(), const TAllocator& allocator = TAllocator());
		HashMap(const HashMap& hashmap);
		HashMap(const HashMap& hashmap, size_t capacity);
		HashMap(HashMap&&) = default;
		~HashMap() = default;

		HashMap& operator=(const HashMap& hashmap);
		HashMap& operator=(HashMap&&) = default;

		//! Check if the hash map is not empty
		explicit operator bool() const noexcept { return !empty(); }

		//! Access to the item with the given key or insert a new one
		mapped_type& operator[](const TKey& key) { return emplace_internal(key).first->second; }

		//! Is the hash map empty?
		bool empty() const noexcept { return _size == 0; }

		//! Get the hash map size
		size_t size() const noexcept { return _size; }
		//! Get the hash map maximum size
		size_t max_size() const noexcept { return std::numeric_limits<size_type>::max(); }
		//! Get the hash map bucket count
		size_t bucket_count() const noexcept { return _buckets.size(); }
		//! Get the hash map maximum bucket count
		size_t max_bucket_count() const noexcept { return std::numeric_limits<size_type>::max(); }

		//! Calculate hash of the given key
		size_t key_hash(const TKey& key) const noexcept { return _hash(key); }
		//! Compare two keys: if the first key equals to the second one?
		bool key_equal(const TKey& key1, const TKey& key2) const noexcept { return _equal(key1, key2); }

		//! Get the begin hash map iterator
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		//! Get the end hash map iterator
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		//! Get the reverse begin hash map iterator
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		//! Get the reverse end hash map iterator
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crend() const noexcept;

		//! Find the iterator which points to the first item with the given key in the hash map or return end iterator
		iterator find(const TKey& key) noexcept;
		const_iterator find(const TKey& key) const noexcept;

		//! Find the bounds of a range that includes all the elements in the hash map with the given key
		std::pair<iterator, iterator> equal_range(const TKey& key) noexcept;
		std::pair<const_iterator, const_iterator> equal_range(const TKey& key) const noexcept;

		//! Find the count of items with the given key
		size_t count(const TKey& key) const noexcept { return (find(key) == end()) ? 0 : 1; }

		//! Access to the item with the given key or throw std::out_of_range exception
		/*!
			\param key - Key of the item
			\return Item with the given key
		*/
		mapped_type& at(const TKey& key) noexcept;
		//! Access to the constant item with the given key or throw std::out_of_range exception
		/*!
			\param key - Key of the item
			\return Constant item with the given key
		*/
		const mapped_type& at(const TKey& key) const noexcept;

		//! Insert a new item into the hash map
		/*!
			\param item - Item to insert as a key/value pair
			\return Pair with the iterator to the given key and success flag
		*/
		std::pair<iterator, bool> insert(const value_type& item);
		//! Insert a new item into the hash map
		/*!
			\param item - Item to insert as a key/value pair
			\return Pair with the iterator to the given key and success flag
		*/
		std::pair<iterator, bool> insert(value_type&& item);

		//! Emplace a new item into the hash map
		/*!
			\param args - Arguments to emplace
			\return Pair with the iterator to the given key and success flag
		*/
		template <typename... Args>
		std::pair<iterator, bool> emplace(Args&&... args);

		//! Erase the item with the given key from the hash map
		/*!
			\param key - Key of the item to erase
			\return Number of erased elements (0 or 1 for the hash map)
		*/
		size_t erase(const TKey& key);
		//! Erase the item by its iterator from the hash map
		/*!
			\param position - Iterator position to the erased item
		*/
		void erase(const const_iterator& position);

		//! Rehash the hash map to the given capacity or more
		/*!
			\param capacity - Hash map capacity
		*/
		void rehash(size_t capacity);
		//! Reserve the hash map capacity to fit the given count of items
		/*!
			\param count - Count of items to fit
		*/
		void reserve(size_t count);

		//! Clear the hash map
		void clear() noexcept;

		//! Swap two instances
		void swap(HashMap& hashmap) noexcept;
		template <typename UKey, typename UValue, typename UHash, typename UEqual, typename UAllocator>
		friend void swap(HashMap<UKey, UValue, UHash, UEqual, UAllocator>& hashmap1, HashMap<UKey, UValue, UHash, UEqual, UAllocator>& hashmap2) noexcept;

	private:
		THash _hash;    // Hash map key hasher
		TEqual _equal;  // Hash map key comparator
		TKey _blank;    // Hash map blank key
		size_t _size;   // Hash map size
		std::vector<value_type, TAllocator> _buckets; // Hash map buckets

		template <typename... Args>
		std::pair<iterator, bool> emplace_internal(const TKey& key, Args&&... args);
		void erase_internal(size_t index);
		size_t key_to_index(const TKey& key) const noexcept;
		size_t next_index(size_t index) const noexcept;
		size_t diff(size_t index1, size_t index2) const noexcept;
	};

	//! Hash map iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename TKey, typename TValue>
	class HashMapIterator
	{
		friend HashMapConstIterator<TContainer, TKey, TValue>;
		friend TContainer;

	public:
		// Standard iterator type definitions
		typedef std::pair<TKey, TValue> value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		HashMapIterator() noexcept : _container(nullptr), _index(0) {}
		explicit HashMapIterator(TContainer* container) noexcept;
		explicit HashMapIterator(TContainer* container, size_t index) noexcept : _container(container), _index(index) {}
		HashMapIterator(const HashMapIterator& it) noexcept = default;
		HashMapIterator(HashMapIterator&& it) noexcept = default;
		~HashMapIterator() noexcept = default;

		HashMapIterator& operator=(const HashMapIterator& it) noexcept = default;
		HashMapIterator& operator=(HashMapIterator&& it) noexcept = default;

		friend bool operator==(const HashMapIterator& it1, const HashMapIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._index == it2._index);
		}
		friend bool operator!=(const HashMapIterator& it1, const HashMapIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._index != it2._index);
		}

		HashMapIterator& operator++() noexcept;
		HashMapIterator operator++(int) noexcept;

		reference operator*() noexcept;
		pointer operator->() noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _container != nullptr; }

		//! Swap two instances
		void swap(HashMapIterator& it) noexcept;
		template <class UContainer, typename UKey, typename UValue>
		friend void swap(HashMapIterator<UContainer, UKey, UValue>& it1, HashMapIterator<UContainer, UKey, UValue>& it2) noexcept;

	private:
		TContainer* _container;
		size_t _index;
	};

	//! Hash map constant iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename TKey, typename TValue>
	class HashMapConstIterator
	{
		friend TContainer;

	public:
		// Standard iterator type definitions
		typedef std::pair<TKey, TValue> value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		HashMapConstIterator() noexcept : _container(nullptr), _index(0) {}
		explicit HashMapConstIterator(const TContainer* container) noexcept;
		explicit HashMapConstIterator(const TContainer* container, size_t index) noexcept : _container(container), _index(index) {}
		HashMapConstIterator(const HashMapIterator<TContainer, TKey, TValue>& it) noexcept : _container(it._container), _index(it._index) {}
		HashMapConstIterator(const HashMapConstIterator& it) noexcept = default;
		HashMapConstIterator(HashMapConstIterator&& it) noexcept = default;
		~HashMapConstIterator() noexcept = default;

		HashMapConstIterator& operator=(const HashMapIterator<TContainer, TKey, TValue>& it) noexcept
		{
			_container = it._container; _index = it._index; return *this;
		}
		HashMapConstIterator& operator=(const HashMapConstIterator& it) noexcept = default;
		HashMapConstIterator& operator=(HashMapConstIterator&& it) noexcept = default;

		friend bool operator==(const HashMapConstIterator& it1, const HashMapConstIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._index == it2._index);
		}
		friend bool operator!=(const HashMapConstIterator& it1, const HashMapConstIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._index != it2._index);
		}

		HashMapConstIterator& operator++() noexcept;
		HashMapConstIterator operator++(int) noexcept;

		const_reference operator*() const noexcept;
		const_pointer operator->() const noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _container != nullptr; }

		//! Swap two instances
		void swap(HashMapConstIterator& it) noexcept;
		template <class UContainer, typename UKey, typename UValue>
		friend void swap(HashMapConstIterator<UContainer, UKey, UValue>& it1, HashMapConstIterator<UContainer, UKey, UValue>& it2) noexcept;

	private:
		const TContainer* _container;
		size_t _index;
	};

	//! Hash map reverse iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename TKey, typename TValue>
	class HashMapReverseIterator
	{
		friend HashMapConstReverseIterator<TContainer, TKey, TValue>;
		friend TContainer;

	public:
		// Standard iterator type definitions
		typedef std::pair<TKey, TValue> value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		HashMapReverseIterator() noexcept : _container(nullptr), _index(0) {}
		explicit HashMapReverseIterator(TContainer* container) noexcept;
		explicit HashMapReverseIterator(TContainer* container, size_t index) noexcept : _container(container), _index(index) {}
		HashMapReverseIterator(const HashMapReverseIterator& it) noexcept = default;
		HashMapReverseIterator(HashMapReverseIterator&& it) noexcept = default;
		~HashMapReverseIterator() noexcept = default;

		HashMapReverseIterator& operator=(const HashMapReverseIterator& it) noexcept = default;
		HashMapReverseIterator& operator=(HashMapReverseIterator&& it) noexcept = default;

		friend bool operator==(const HashMapReverseIterator& it1, const HashMapReverseIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._index == it2._index);
		}
		friend bool operator!=(const HashMapReverseIterator& it1, const HashMapReverseIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._index != it2._index);
		}

		HashMapReverseIterator& operator++() noexcept;
		HashMapReverseIterator operator++(int) noexcept;

		reference operator*() noexcept;
		pointer operator->() noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _container != nullptr; }

		//! Swap two instances
		void swap(HashMapReverseIterator& it) noexcept;
		template <class UContainer, typename UKey, typename UValue>
		friend void swap(HashMapReverseIterator<UContainer, UKey, UValue>& it1, HashMapReverseIterator<UContainer, UKey, UValue>& it2) noexcept;

	private:
		TContainer* _container;
		size_t _index;
	};

	//! Hash map constant reverse iterator
	/*!
		Not thread-safe.
	*/
	template <class TContainer, typename TKey, typename TValue>
	class HashMapConstReverseIterator
	{
		friend TContainer;

	public:
		// Standard iterator type definitions
		typedef std::pair<TKey, TValue> value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		HashMapConstReverseIterator() noexcept : _container(nullptr), _index(0) {}
		explicit HashMapConstReverseIterator(const TContainer* container) noexcept;
		explicit HashMapConstReverseIterator(const TContainer* container, size_t index) noexcept : _container(container), _index(index) {}
		HashMapConstReverseIterator(const HashMapReverseIterator<TContainer, TKey, TValue>& it) noexcept : _container(it._container), _index(it._index) {}
		HashMapConstReverseIterator(const HashMapConstReverseIterator& it) noexcept = default;
		HashMapConstReverseIterator(HashMapConstReverseIterator&& it) noexcept = default;
		~HashMapConstReverseIterator() noexcept = default;

		HashMapConstReverseIterator& operator=(const HashMapReverseIterator<TContainer, TKey, TValue>& it) noexcept
		{
			_container = it._container; _index = it._index; return *this;
		}
		HashMapConstReverseIterator& operator=(const HashMapConstReverseIterator& it) noexcept = default;
		HashMapConstReverseIterator& operator=(HashMapConstReverseIterator&& it) noexcept = default;

		friend bool operator==(const HashMapConstReverseIterator& it1, const HashMapConstReverseIterator& it2) noexcept
		{
			return (it1._container == it2._container) && (it1._index == it2._index);
		}
		friend bool operator!=(const HashMapConstReverseIterator& it1, const HashMapConstReverseIterator& it2) noexcept
		{
			return (it1._container != it2._container) || (it1._index != it2._index);
		}

		HashMapConstReverseIterator& operator++() noexcept;
		HashMapConstReverseIterator operator++(int) noexcept;

		const_reference operator*() const noexcept;
		const_pointer operator->() const noexcept;

		//! Check if the iterator is valid
		explicit operator bool() const noexcept { return _container != nullptr; }

		//! Swap two instances
		void swap(HashMapConstReverseIterator& it) noexcept;
		template <class UContainer, typename UKey, typename UValue>
		friend void swap(HashMapConstReverseIterator<UContainer, UKey, UValue>& it1, HashMapConstReverseIterator<UContainer, UKey, UValue>& it2) noexcept;

	private:
		const TContainer* _container;
		size_t _index;
	};
//////
	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline HashMap<TKey, TValue, THash, TEqual, TAllocator>::HashMap(size_t capacity, const TKey& blank, const THash& hash, const TEqual& equal, const TAllocator& allocator)
		: _hash(hash), _equal(equal), _blank(blank), _size(0), _buckets(allocator)
	{
		size_t reserve = 1;
		while (reserve < capacity)
			reserve <<= 1;
		_buckets.resize(reserve, std::make_pair(_blank, TValue()));
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	template <class InputIterator>
	inline HashMap<TKey, TValue, THash, TEqual, TAllocator>::HashMap(InputIterator first, InputIterator last, bool unused, size_t capacity, const TKey& blank, const THash& hash, const TEqual& equal, const TAllocator& allocator)
		: HashMap(capacity, blank, hash, equal, allocator)
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline HashMap<TKey, TValue, THash, TEqual, TAllocator>::HashMap(const HashMap& hashmap)
		: HashMap(hashmap.bucket_count(), hashmap._blank, hashmap._hash, hashmap._equal, hashmap._buckets.get_allocator())
	{
		for (const auto& item : hashmap)
			insert(item);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline HashMap<TKey, TValue, THash, TEqual, TAllocator>::HashMap(const HashMap& hashmap, size_t capacity)
		: HashMap(capacity, hashmap._blank, hashmap._hash, hashmap._equal, hashmap._buckets.get_allocator())
	{
		for (const auto& item : hashmap)
			insert(item);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline HashMap<TKey, TValue, THash, TEqual, TAllocator>& HashMap<TKey, TValue, THash, TEqual, TAllocator>::operator=(const HashMap& hashmap)
	{
		clear();
		reserve(hashmap.size());
		for (const auto& item : hashmap)
			insert(item);
		return *this;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::begin() noexcept
	{
		return iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::begin() const noexcept
	{
		return const_iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::cbegin() const noexcept
	{
		return const_iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::end() noexcept
	{
		return iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::end() const noexcept
	{
		return const_iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::cend() const noexcept
	{
		return const_iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::rbegin() noexcept
	{
		return reverse_iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::rbegin() const noexcept
	{
		return const_reverse_iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::crbegin() const noexcept
	{
		return const_reverse_iterator(this);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::rend() noexcept
	{
		return reverse_iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::rend() const noexcept
	{
		return const_reverse_iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_reverse_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::crend() const noexcept
	{
		return const_reverse_iterator(nullptr);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::find(const TKey& key) noexcept
	{
		assert(!key_equal(key, _blank) && "Cannot find a blank key!");

		for (size_t index = key_to_index(key);; index = next_index(index))
		{
			if (key_equal(_buckets[index].first, key))
				return iterator(this, index);
			if (key_equal(_buckets[index].first, _blank))
				return end();
		}
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator HashMap<TKey, TValue, THash, TEqual, TAllocator>::find(const TKey& key) const noexcept
	{
		assert(!key_equal(key, _blank) && "Cannot find a blank key!");

		for (size_t index = key_to_index(key);; index = next_index(index))
		{
			if (key_equal(_buckets[index].first, key))
				return const_iterator(this, index);
			if (key_equal(_buckets[index].first, _blank))
				return end();
		}
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator, typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator> HashMap<TKey, TValue, THash, TEqual, TAllocator>::equal_range(const TKey& key) noexcept
	{
		return std::make_pair(find(key), end());
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator, typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::const_iterator> HashMap<TKey, TValue, THash, TEqual, TAllocator>::equal_range(const TKey& key) const noexcept
	{
		return std::make_pair(find(key), end());
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::mapped_type& HashMap<TKey, TValue, THash, TEqual, TAllocator>::at(const TKey& key) noexcept
	{
		auto it = find(key);
		if (it == end())
			throw std::out_of_range("Item with the given key was not found in the hash map!");

		return it->second;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline const typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::mapped_type& HashMap<TKey, TValue, THash, TEqual, TAllocator>::at(const TKey& key) const noexcept
	{
		auto it = find(key);
		if (it == end())
			throw std::out_of_range("Item with the given key was not found in the hash map!");

		return it->second;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator, bool> HashMap<TKey, TValue, THash, TEqual, TAllocator>::insert(const value_type& item)
	{
		return emplace_internal(item.first, item.second);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator, bool> HashMap<TKey, TValue, THash, TEqual, TAllocator>::insert(value_type&& item)
	{
		return emplace_internal(item.first, std::move(item.second));
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	template <typename... Args>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator, bool> HashMap<TKey, TValue, THash, TEqual, TAllocator>::emplace(Args&&... args)
	{
		return emplace_internal(std::forward<Args>(args)...);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline size_t HashMap<TKey, TValue, THash, TEqual, TAllocator>::erase(const TKey& key)
	{
		auto it = find(key);
		if (it == end())
			return 0;

		erase_internal(it._index);
		return 1;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::erase(const const_iterator& position)
	{
		erase_internal(position._index);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	template <typename... Args>
	inline std::pair<typename HashMap<TKey, TValue, THash, TEqual, TAllocator>::iterator, bool> HashMap<TKey, TValue, THash, TEqual, TAllocator>::emplace_internal(const TKey& key, Args&&... args)
	{
		assert(!key_equal(key, _blank) && "Cannot emplace a blank key!");

		reserve(_size + 1);

		for (size_t index = key_to_index(key);; index = next_index(index))
		{
			if (key_equal(_buckets[index].first, key))
				return std::make_pair(iterator(this, index), false);
			if (key_equal(_buckets[index].first, _blank))
			{
				_buckets[index].first = key;
				_buckets[index].second = TValue(std::forward<Args>(args)...);
				++_size;
				return std::make_pair(iterator(this, index), true);
			}
		}
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::erase_internal(size_t index)
	{
		size_t current = index;
		for (index = next_index(current);; index = next_index(index))
		{
			if (key_equal(_buckets[index].first, _blank))
			{
				_buckets[current].first = _blank;
				--_size;
				return;
			}

			// Move buckets with the same key hash closer to the first suitable position in the hash map
			size_t base = key_to_index(_buckets[index].first);
			if (diff(current, base) < diff(index, base))
			{
				_buckets[current] = _buckets[index];
				current = index;
			}
		}
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline size_t HashMap<TKey, TValue, THash, TEqual, TAllocator>::key_to_index(const TKey& key) const noexcept
	{
		size_t mask = _buckets.size() - 1;
		return _hash(key) & mask;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline size_t HashMap<TKey, TValue, THash, TEqual, TAllocator>::next_index(size_t index) const noexcept
	{
		size_t mask = _buckets.size() - 1;
		return (index + 1) & mask;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline size_t HashMap<TKey, TValue, THash, TEqual, TAllocator>::diff(size_t index1, size_t index2) const noexcept
	{
		size_t mask = _buckets.size() - 1;
		return (_buckets.size() + (index1 - index2)) & mask;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::rehash(size_t capacity)
	{
		capacity = std::max(capacity, 2 * size());
		HashMap<TKey, TValue, THash, TEqual, TAllocator> temp(*this, capacity);
		swap(temp);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::reserve(size_t count)
	{
		if (_buckets.size() < 2 * count)
			rehash(2 * count);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::clear() noexcept
	{
		_size = 0;
		for (auto& bucket : _buckets)
			bucket.first = _blank;
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void HashMap<TKey, TValue, THash, TEqual, TAllocator>::swap(HashMap& hashmap) noexcept
	{
		using std::swap;
		swap(_hash, hashmap._hash);
		swap(_equal, hashmap._equal);
		swap(_blank, hashmap._blank);
		swap(_size, hashmap._size);
		swap(_buckets, hashmap._buckets);
	}

	template <typename TKey, typename TValue, typename THash, typename TEqual, typename TAllocator>
	inline void swap(HashMap<TKey, TValue, THash, TEqual, TAllocator>& hashmap1, HashMap<TKey, TValue, THash, TEqual, TAllocator>& hashmap2) noexcept
	{
		hashmap1.swap(hashmap2);
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapIterator<TContainer, TKey, TValue>::HashMapIterator(TContainer* container) noexcept : _container(container), _index(0)
	{
		if (_container != nullptr)
		{
			if (_container->size() == 0)
			{
				// Hash map is empty
				_container = nullptr;
				_index = 0;
				return;
			}
			else
			{
				for (size_t i = 0; i < _container->_buckets.size(); ++i)
				{
					if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
					{
						_index = i;
						return;
					}
				}

				assert(false && "Non empty hash map has no valid items!");
			}
		}
	}

	template <class TContainer, typename TKey, typename TValue>
	HashMapIterator<TContainer, TKey, TValue>& HashMapIterator<TContainer, TKey, TValue>::operator++() noexcept
	{
		if (_container != nullptr)
		{
			for (size_t i = _index + 1; i < _container->_buckets.size(); ++i)
			{
				if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
				{
					_index = i;
					return *this;
				}
			}

			// End of the hash map
			_container = nullptr;
			_index = 0;
		}

		return *this;
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapIterator<TContainer, TKey, TValue> HashMapIterator<TContainer, TKey, TValue>::operator++(int) noexcept
	{
		HashMapIterator<TContainer, TKey, TValue> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapIterator<TContainer, TKey, TValue>::reference HashMapIterator<TContainer, TKey, TValue>::operator*() noexcept
	{
		assert(((_container != nullptr) && (_index < _container->_buckets.size())) && "Iterator must be valid!");

		return _container->_buckets[_index];
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapIterator<TContainer, TKey, TValue>::pointer HashMapIterator<TContainer, TKey, TValue>::operator->() noexcept
	{
		return ((_container != nullptr) && (_index < _container->_buckets.size())) ? &_container->_buckets[_index] : nullptr;
	}

	template <class TContainer, typename TKey, typename TValue>
	void HashMapIterator<TContainer, TKey, TValue>::swap(HashMapIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_index, it._index);
	}

	template <class TContainer, typename TKey, typename TValue>
	void swap(HashMapIterator<TContainer, TKey, TValue>& it1, HashMapIterator<TContainer, TKey, TValue>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapConstIterator<TContainer, TKey, TValue>::HashMapConstIterator(const TContainer* container) noexcept : _container(container), _index(0)
	{
		if (_container != nullptr)
		{
			if (_container->size() == 0)
			{
				// Hash map is empty
				_container = nullptr;
				_index = 0;
				return;
			}
			else
			{
				for (size_t i = 0; i < _container->_buckets.size(); ++i)
				{
					if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
					{
						_index = i;
						return;
					}
				}

				assert(false && "Non empty hash map has no valid items!");
			}
		}
	}

	template <class TContainer, typename TKey, typename TValue>
	HashMapConstIterator<TContainer, TKey, TValue>& HashMapConstIterator<TContainer, TKey, TValue>::operator++() noexcept
	{
		if (_container != nullptr)
		{
			for (size_t i = _index + 1; i < _container->_buckets.size(); ++i)
			{
				if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
				{
					_index = i;
					return *this;
				}
			}

			// End of the hash map
			_container = nullptr;
			_index = 0;
		}

		return *this;
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapConstIterator<TContainer, TKey, TValue> HashMapConstIterator<TContainer, TKey, TValue>::operator++(int) noexcept
	{
		HashMapConstIterator<TContainer, TKey, TValue> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapConstIterator<TContainer, TKey, TValue>::const_reference HashMapConstIterator<TContainer, TKey, TValue>::operator*() const noexcept
	{
		assert(((_container != nullptr) && (_index < _container->_buckets.size())) && "Iterator must be valid!");

		return _container->_buckets[_index];
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapConstIterator<TContainer, TKey, TValue>::const_pointer HashMapConstIterator<TContainer, TKey, TValue>::operator->() const noexcept
	{
		return ((_container != nullptr) && (_index < _container->_buckets.size())) ? &_container->_buckets[_index] : nullptr;
	}

	template <class TContainer, typename TKey, typename TValue>
	void HashMapConstIterator<TContainer, TKey, TValue>::swap(HashMapConstIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_index, it._index);
	}

	template <class TContainer, typename TKey, typename TValue>
	void swap(HashMapConstIterator<TContainer, TKey, TValue>& it1, HashMapConstIterator<TContainer, TKey, TValue>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapReverseIterator<TContainer, TKey, TValue>::HashMapReverseIterator(TContainer* container) noexcept : _container(container), _index(0)
	{
		if (_container != nullptr)
		{
			if (_container->size() == 0)
			{
				// Hash map is empty
				_container = nullptr;
				_index = 0;
				return;
			}
			else
			{
				for (size_t i = _container->_buckets.size(); i-- > 0;)
				{
					if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
					{
						_index = i;
						return;
					}
				}

				assert(false && "Non empty hash map has no valid items!");
			}
		}
	}

	template <class TContainer, typename TKey, typename TValue>
	HashMapReverseIterator<TContainer, TKey, TValue>& HashMapReverseIterator<TContainer, TKey, TValue>::operator++() noexcept
	{
		if (_container != nullptr)
		{
			for (size_t i = _index; i-- > 0;)
			{
				if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
				{
					_index = i;
					return *this;
				}
			}

			// End of the hash map
			_container = nullptr;
			_index = 0;
		}

		return *this;
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapReverseIterator<TContainer, TKey, TValue> HashMapReverseIterator<TContainer, TKey, TValue>::operator++(int) noexcept
	{
		HashMapReverseIterator<TContainer, TKey, TValue> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapReverseIterator<TContainer, TKey, TValue>::reference HashMapReverseIterator<TContainer, TKey, TValue>::operator*() noexcept
	{
		assert(((_container != nullptr) && (_index < _container->_buckets.size())) && "Iterator must be valid!");

		return _container->_buckets[_index];
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapReverseIterator<TContainer, TKey, TValue>::pointer HashMapReverseIterator<TContainer, TKey, TValue>::operator->() noexcept
	{
		return ((_container != nullptr) && (_index < _container->_buckets.size())) ? &_container->_buckets[_index] : nullptr;
	}

	template <class TContainer, typename TKey, typename TValue>
	void HashMapReverseIterator<TContainer, TKey, TValue>::swap(HashMapReverseIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_index, it._index);
	}

	template <class TContainer, typename TKey, typename TValue>
	void swap(HashMapReverseIterator<TContainer, TKey, TValue>& it1, HashMapReverseIterator<TContainer, TKey, TValue>& it2) noexcept
	{
		it1.swap(it2);
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapConstReverseIterator<TContainer, TKey, TValue>::HashMapConstReverseIterator(const TContainer* container) noexcept : _container(container), _index(0)
	{
		if (_container != nullptr)
		{
			if (_container->size() == 0)
			{
				// Hash map is empty
				_container = nullptr;
				_index = 0;
				return;
			}
			else
			{
				for (size_t i = _container->_buckets.size(); i-- > 0;)
				{
					if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
					{
						_index = i;
						return;
					}
				}

				assert(false && "Non empty hash map has no valid items!");
			}
		}
	}

	template <class TContainer, typename TKey, typename TValue>
	HashMapConstReverseIterator<TContainer, TKey, TValue>& HashMapConstReverseIterator<TContainer, TKey, TValue>::operator++() noexcept
	{
		if (_container != nullptr)
		{
			for (size_t i = _index; i-- > 0;)
			{
				if (!_container->key_equal(_container->_buckets[i].first, _container->_blank))
				{
					_index = i;
					return *this;
				}
			}

			// End of the hash map
			_container = nullptr;
			_index = 0;
		}

		return *this;
	}

	template <class TContainer, typename TKey, typename TValue>
	inline HashMapConstReverseIterator<TContainer, TKey, TValue> HashMapConstReverseIterator<TContainer, TKey, TValue>::operator++(int) noexcept
	{
		HashMapConstReverseIterator<TContainer, TKey, TValue> result(*this);
		operator++();
		return result;
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapConstReverseIterator<TContainer, TKey, TValue>::const_reference HashMapConstReverseIterator<TContainer, TKey, TValue>::operator*() const noexcept
	{
		assert(((_container != nullptr) && (_index < _container->_buckets.size())) && "Iterator must be valid!");

		return _container->_buckets[_index];
	}

	template <class TContainer, typename TKey, typename TValue>
	typename HashMapConstReverseIterator<TContainer, TKey, TValue>::const_pointer HashMapConstReverseIterator<TContainer, TKey, TValue>::operator->() const noexcept
	{
		return ((_container != nullptr) && (_index < _container->_buckets.size())) ? &_container->_buckets[_index] : nullptr;
	}

	template <class TContainer, typename TKey, typename TValue>
	void HashMapConstReverseIterator<TContainer, TKey, TValue>::swap(HashMapConstReverseIterator& it) noexcept
	{
		using std::swap;
		swap(_container, it._container);
		swap(_index, it._index);
	}

	template <class TContainer, typename TKey, typename TValue>
	void swap(HashMapConstReverseIterator<TContainer, TKey, TValue>& it1, HashMapConstReverseIterator<TContainer, TKey, TValue>& it2) noexcept
	{
		it1.swap(it2);
	}

}//namespace

#endif