#pragma once
#ifndef XT_HEAP_MEMORY_MANAGER_H
#define XT_HEAP_MEMORY_MANAGER_H

/**
* \file HeapMemoryManager.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a HeapMemoryManager class .
*
* \description
*	Designed for a HeapMemoryManager class.
*/

#include "XTMemory.h"
#include "XTAllocator.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#undef DELETE
#undef ERROR
#undef Yield
#undef min
#undef max
#undef uuid_t
#endif

namespace XT
{

	//! Heap memory manager class
	/*!
		Heap memory manager will allocate memory in system heap.
		Windows: HeapAlloc()/HeapFree()
		Unix: malloc()/free()

		Not thread-safe.
	*/
	class HeapMemoryManager
	{
	public:
		HeapMemoryManager() noexcept : _allocated(0), _allocations(0) {}
		HeapMemoryManager(const HeapMemoryManager&) = delete;
		HeapMemoryManager(HeapMemoryManager&&) = delete;
		~HeapMemoryManager() noexcept { reset(); }

		HeapMemoryManager& operator=(const HeapMemoryManager&) = delete;
		HeapMemoryManager& operator=(HeapMemoryManager&&) = delete;

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
		void* malloc(size_t size, size_t alignment = alignof(std::max_align_t));//  (std::max_align_t));
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
	};

	//! Heap memory allocator class
	template <typename T, bool nothrow = false>
	using HeapAllocator = Allocator<T, HeapMemoryManager, nothrow>;

////
	inline void* HeapMemoryManager::malloc(size_t size, size_t alignment)
	{
		assert((size > 0) && "Allocated block size must be greater than zero!");
		assert(Memory::IsValidAlignment(alignment) && "Alignment must be valid!");

#if defined(_WIN32) || defined(_WIN64)
		void* result = HeapAlloc(GetProcessHeap(), 0, size);
#else
		void* result = std::malloc(size);
#endif
		if (result != nullptr)
		{
			// Update allocation statistics
			_allocated += size;
			++_allocations;
		}
		return result;
	}

	inline void HeapMemoryManager::free(void* ptr, size_t size)
	{
		assert((ptr != nullptr) && "Deallocated block must be valid!");

		if (ptr != nullptr)
		{
#if defined(_WIN32) || defined(_WIN64)
			HeapFree(GetProcessHeap(), 0, (LPVOID)ptr);
#else
			std::free(ptr);
#endif

			// Update allocation statistics
			_allocated -= size;
			--_allocations;
		}
	}

	inline void HeapMemoryManager::reset()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");
	}

}//namespace

#endif
