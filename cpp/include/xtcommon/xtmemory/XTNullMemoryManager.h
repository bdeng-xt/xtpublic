#pragma once
#ifndef XT_NULL_MEMORY_MANAGER_H
#define XT_NULL_MEMORY_MANAGER_H

/**
* \file NullMemoryManager.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a NullMemoryManager class .
*
* \description
*	Designed for a NullMemoryManager class.
*/

#include "XTMemory.h"
#include "XTAllocator.h"

namespace XT
{

	//! Null memory manager class
	/*!
		Null memory manager will always return nullptr for any attempt
		to allocate a memory buffer of the given size.

		Not thread-safe.
	*/
	class NullMemoryManager
	{
	public:
		NullMemoryManager() noexcept : _allocated(0), _allocations(0) {}
		NullMemoryManager(const NullMemoryManager&) = delete;
		NullMemoryManager(NullMemoryManager&&) = delete;
		~NullMemoryManager() noexcept { reset(); }

		NullMemoryManager& operator=(const NullMemoryManager&) = delete;
		NullMemoryManager& operator=(NullMemoryManager&&) = delete;

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
		void* malloc(size_t size, size_t alignment = alignof(std::max_align_t));//(std::max_align_t));
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

	//! Null memory allocator class
	template <typename T, bool nothrow = false>
	using NullAllocator = Allocator<T, NullMemoryManager, nothrow>;

////
	inline void* NullMemoryManager::malloc(size_t size, size_t alignment)
	{
		assert((size > 0) && "Allocated block size must be greater than zero!");
		assert(Memory::IsValidAlignment(alignment) && "Alignment must be valid!");

		// Not enough memory...
		return nullptr;
	}

	inline void NullMemoryManager::free(void* ptr, size_t size)
	{
		assert((ptr != nullptr) && "Deallocated block must be valid!");

		if (ptr != nullptr)
		{
			// Update allocation statistics
			_allocated -= size;
			--_allocations;
		}
	}

	inline void NullMemoryManager::reset()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");
	}


}//namespace


#endif
