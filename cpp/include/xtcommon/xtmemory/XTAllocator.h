#pragma once
#ifndef XT_ALLOCATOR_H
#define XT_ALLOCATOR_H

/**
* \file XTAllocator.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide an allocator class .
*
* \description
*	Designed for an allocator class.
*/
#include <cstddef>

#include "XTMemory.h"

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4127) // C4127: conditional expression is constant
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

namespace XT
{

	//! Memory allocator class
	/*!
		Memory allocator implements standard allocator interface and
		wraps the memory manager provided as a template argument.

		Not thread-safe.
	*/
	template <typename T, class TMemoryManager, bool nothrow = false>
	class Allocator
	{
		template <typename U, class UMemoryManager, bool flag>
		friend class Allocator;

	public:
		//! Element type
		typedef T value_type;
		//! Pointer to element
		typedef T* pointer;
		//! Reference to element
		typedef T& reference;
		//! Pointer to constant element
		typedef const T* const_pointer;
		//! Reference to constant element
		typedef const T& const_reference;
		//! Quantities of elements
		typedef size_t size_type;
		//! Difference between two pointers
		typedef ptrdiff_t difference_type;

		//! Initialize allocator with a given memory manager
		/*!
			\param manager - Memory manager
		*/
		explicit Allocator(TMemoryManager& manager) noexcept : _manager(manager) {}
		template <typename U>
		Allocator(const Allocator<U, TMemoryManager, nothrow>& alloc) noexcept : _manager(alloc._manager) {}
		Allocator(const Allocator& alloc) noexcept : _manager(alloc._manager) {}
		Allocator(Allocator&&) noexcept = default;
		~Allocator() noexcept = default;

		template <typename U>
		Allocator& operator=(const Allocator<U, TMemoryManager, nothrow>& alloc) noexcept
		{
			_manager = alloc._manager; return *this;
		}
		Allocator& operator=(const Allocator& alloc) noexcept
		{
			_manager = alloc._manager; return *this;
		}
		Allocator& operator=(Allocator&&) noexcept = default;

		//! Get the address of the given reference
		/*!
			\param x - Reference to the element
			\return Pointer to the element
		*/
		pointer address(reference x) const noexcept { return std::addressof(x); }
		//! Get the constant address of the given constant reference
		/*!
			\param x - Constant reference to the element
			\return Constant pointer to the element
		*/
		const_pointer address(const_reference x) const noexcept { return std::addressof(x); }

		//! Get the maximum number of elements, that could potentially be allocated by the allocator
		/*!
			\return The number of elements that might be allocated as maximum by a call to the allocate() method
		*/
		size_type max_size() const noexcept { return _manager.max_size(); }

		//! Allocate a block of storage suitable to contain the given count of elements
		/*!
			\param num - Number of elements to be allocated
			\param hint - Allocation hint (default is 0)
			\return A pointer to the initial element in the block of storage
		*/
		pointer allocate(size_type num, const void* hint = 0);
		//! Release a block of storage previously allocated
		/*!
			\param ptr - Pointer to a block of storage
			\param num - Number of releasing elements
		*/
		void deallocate(pointer ptr, size_type num);

		//! Reset the allocator
		void reset() { _manager.reset(); }

		//! Constructs an element object on the given location pointer
		/*!
			\param ptr - Pointer to a location with enough storage space to contain an element
			\param args - Arguments to initialize the construced element with
		*/
		template <typename U, class... Args>
		void construct(U* ptr, Args&&... args);
		//! Destroys in-place the object pointed by the given location pointer
		/*!
			\param ptr - Pointer to the object to be destroyed
		*/
		template <typename U>
		void destroy(U* ptr);

		//! Create a single element object
		/*!
			\param args - Arguments to initialize the construced element with
		*/
		template <class... Args>
		T* Create(Args&&... args);
		//! Release a single element object
		/*!
			\param ptr - Pointer to the object to be released
		*/
		void Release(T* ptr);

		//! Create an array of element objects
		/*!
			\param length - Length of the array
			\param args - Arguments to initialize the construced element with
		*/
		template <class... Args>
		T* CreateArray(size_t length, Args&&... args);
		//! Release an array of element objects
		/*!
			\param ptr - Pointer to the object to be released
		*/
		void ReleaseArray(T* ptr);

		//! Rebind allocator
		template <typename TOther> struct rebind { using other = Allocator<TOther, TMemoryManager, nothrow>; };

	private:
		TMemoryManager& _manager;
	};//class Allocator

	//! Memory allocator class (void specialization)
	template <class TMemoryManager, bool nothrow>
	class Allocator<void, TMemoryManager, nothrow>
	{
	public:
		//! Element type
		typedef void value_type;
		//! Pointer to element
		typedef void* pointer;
		//! Pointer to constant element
		typedef const void* const_pointer;
		//! Quantities of elements
		typedef size_t size_type;
		//! Difference between two pointers
		typedef ptrdiff_t difference_type;

		Allocator(TMemoryManager& manager) noexcept : _manager(manager) {}
		template <typename U>
		Allocator(const Allocator<U, TMemoryManager, nothrow>& alloc) noexcept : _manager(alloc._manager) {}
		Allocator(Allocator&&) noexcept = default;
		~Allocator() noexcept = default;

		template <typename U>
		Allocator& operator=(const Allocator<U, TMemoryManager, nothrow>& alloc) noexcept
		{
			_manager = alloc._manager; return *this;
		}
		Allocator& operator=(Allocator&&) noexcept = default;

		//! Rebind allocator
		template <typename TOther> struct rebind { using other = Allocator<TOther, TMemoryManager, nothrow>; };

	private:
		TMemoryManager _manager;
	};//class Allocator

	//! Default memory manager class
	/*!
		Default memory manager uses malloc() and free() system functions
		to allocate and deallocate memory.

		Not thread-safe.
	*/
	class DefaultMemoryManager
	{
	public:
		DefaultMemoryManager() noexcept : _allocated(0), _allocations(0) {}
		DefaultMemoryManager(const DefaultMemoryManager&) noexcept = default;
		DefaultMemoryManager(DefaultMemoryManager&&) noexcept = default;
		~DefaultMemoryManager() noexcept { reset(); }

		DefaultMemoryManager& operator=(const DefaultMemoryManager&) noexcept = default;
		DefaultMemoryManager& operator=(DefaultMemoryManager&&) noexcept = default;

		//! Allocated memory in bytes
		size_t allocated() const noexcept { return _allocated; }
		//! Count of active memory allocations
		size_t allocations() const noexcept { return _allocations; }

		//! Maximum memory block size, that could be allocated by the memory manager
		size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); }

		//! Allocate a new memory block of the given size
		/*!
			\param size - Block size
			\param alignment - Block alignment (default is alignof(std::max_align_t))
			\return A pointer to the allocated memory block or nullptr in case of allocation failed
		*/
#if defined(_WIN32) || defined(_WIN64)
		void* malloc(size_t size, size_t alignment = alignof(std::max_align_t)); //alignof(std::max_align_t));
#else
		void* malloc(size_t size, size_t alignment = alignof(max_align_t));
#endif
		//! Free the previously allocated memory block
		/*!
			\param ptr - Pointer to the memory block
			\param size - Block size
		*/
		void free(void* ptr, size_t size);

		//! Reset the memory manager
		void reset();

	private:
		// Allocation statistics
		size_t _allocated;
		size_t _allocations;
	};//class DefaultMemoryManager

	//! Default memory allocator class
	template <typename T, bool nothrow = false>
	using DefaultAllocator = Allocator<T, DefaultMemoryManager, nothrow>;

	template <typename T, typename U, class TMemoryManager, bool nothrow>
	inline bool operator==(const Allocator<T, TMemoryManager, nothrow>& alloc1, const Allocator<U, TMemoryManager, nothrow>& alloc2) noexcept
	{
		return true;
	}

	template <typename T, typename U, class TMemoryManager, bool nothrow>
	inline bool operator!=(const Allocator<T, TMemoryManager, nothrow>& alloc1, const Allocator<U, TMemoryManager, nothrow>& alloc2) noexcept
	{
		return false;
	}

	template <typename T, class TMemoryManager, bool nothrow>
	inline T* Allocator<T, TMemoryManager, nothrow>::allocate(size_t num, const void* hint)
	{
		pointer result = (pointer)_manager.malloc(num * sizeof(T), alignof(T));
		if (result != nullptr)
			return result;

		// Not enough memory...
		if (nothrow)
			return nullptr;
		else
			throw std::bad_alloc();
	}

	template <typename T, class TMemoryManager, bool nothrow>
	inline void Allocator<T, TMemoryManager, nothrow>::deallocate(T* ptr, size_t num)
	{
		_manager.free(ptr, num * sizeof(T));
	}

	template <typename T, class TMemoryManager, bool nothrow>
	template <typename U, class... Args>
	inline void Allocator<T, TMemoryManager, nothrow>::construct(U* ptr, Args&&... args)
	{
		assert((ptr != nullptr) && "Constructed element must be valid!");

		// Construct the element
		if (ptr != nullptr)
			new ((void*)ptr) U(std::forward<Args>(args)...);
	}

	template <typename T, class TMemoryManager, bool nothrow>
	template <typename U>
	inline void Allocator<T, TMemoryManager, nothrow>::destroy(U* ptr)
	{
		assert((ptr != nullptr) && "Destroyed element must be valid!");

		// Destroy the element
		if (ptr != nullptr)
			ptr->~U();
	}

	template <typename T, class TMemoryManager, bool nothrow>
	template <class... Args>
	inline T* Allocator<T, TMemoryManager, nothrow>::Create(Args&&... args)
	{
		// Allocate memory for the element
		void* ptr = _manager.malloc(sizeof(T));

		// Construct the element
		if (ptr != nullptr)
			new (ptr) T(std::forward<Args>(args)...);

		return (T*)ptr;
	}

	template <typename T, class TMemoryManager, bool nothrow>
	inline void Allocator<T, TMemoryManager, nothrow>::Release(T* ptr)
	{
		assert((ptr != nullptr) && "Released element must be valid!");

		// Release the element
		if (ptr != nullptr)
		{
			// Destroy the element
			ptr->~T();

			// Free element memory
			_manager.free(ptr, sizeof(T));
		}
	}

	template <typename T, class TMemoryManager, bool nothrow>
	template <class... Args>
	inline T* Allocator<T, TMemoryManager, nothrow>::CreateArray(size_t length, Args&&... args)
	{
		assert((length > 0) && "Array length must be greater than zero!");

		size_t header = sizeof(size_t) / sizeof(T);
		if ((sizeof(size_t) % sizeof(T)) > 0)
			header += 1;

		// Allocate extra space to store array length in the bytes before the array
		T* ptr = ((T*)_manager.malloc(sizeof(T) * (length + header), alignof(T))) + header;

		// Store the array length value
		*(((size_t*)ptr) - 1) = length;

		// Construct array elements
		for (size_t i = 0; i < length; ++i)
			new (&ptr[i]) T(std::forward<Args>(args)...);

		return ptr;
	}

	template <typename T, class TMemoryManager, bool nothrow>
	inline void Allocator<T, TMemoryManager, nothrow>::ReleaseArray(T* ptr)
	{
		assert((ptr != nullptr) && "Released array must be valid!");

		// Release the array
		if (ptr != nullptr)
		{
			// Get the length of the array
			size_t length = *(((size_t*)ptr) - 1);

			// Destroy array elements
			for (size_t i = 0; i < length; ++i)
				ptr[i].~T();

			// Calculate how much extra memory was allocated to store the length before the array
			size_t header = sizeof(size_t) / sizeof(T);
			if ((sizeof(size_t) % sizeof(T)) > 0)
				header += 1;

			// Free array memory
			_manager.free(ptr - header, sizeof(T) * (length + header));
		}
	}

	inline void* DefaultMemoryManager::malloc(size_t size, size_t alignment)
	{
		assert((size > 0) && "Allocated block size must be greater than zero!");
		assert(Memory::IsValidAlignment(alignment) && "Alignment must be valid!");

		void* result = std::malloc(size);
		if (result != nullptr)
		{
			// Update allocation statistics
			_allocated += size;
			++_allocations;
		}
		return result;
	}

	inline void DefaultMemoryManager::free(void* ptr, size_t size)
	{
		assert((ptr != nullptr) && "Deallocated block must be valid!");

		if (ptr != nullptr)
		{
			std::free(ptr);

			// Update allocation statistics
			_allocated -= size;
			--_allocations;
		}
	}

	inline void DefaultMemoryManager::reset()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");
	}

}//namespace

#endif
