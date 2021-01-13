#pragma once
#ifndef XT_ARENA_MEMORY_MANAGER_H
#define XT_ARENA_MEMORY_MANAGER_H

/**
* \file ArenaMemoryManager.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide an ArenaMemoryManager class .
*
* \description
*	Designed for an ArenaMemoryManager class.
*/

#include "XTMemory.h"
#include "XTAllocator.h"

namespace XT
{

	//! Arena memory manager class
	/*!
		Arena memory manager uses pre-allocated memory buffer (arena) as a first
		source of memory during the allocation. If arena buffer has insufficient
		space to allocate the required block then an auxiliary memory manager will
		be used.

		Arena memory manager is suitable for multiple allocations during long
		operations with a single reset at the end (e.g. HTTP request processing).

		Not thread-safe.
	*/
	template <class TAuxMemoryManager = DefaultMemoryManager>
	class ArenaMemoryManager
	{
	public:
		//! Initialize arena memory manager with an auxiliary memory manager
		/*!
			Arena chunk capacity will be 65536.

			\param auxiliary - Auxiliary memory manager
		*/
		explicit ArenaMemoryManager(TAuxMemoryManager& auxiliary) : ArenaMemoryManager(auxiliary, 65536) {}
		//! Initialize arena memory manager with an auxiliary memory manager and a given chunk capacity
		/*!
			\param auxiliary - Auxiliary memory manager
			\param capacity - Arena chunk capacity in bytes
		*/
		explicit ArenaMemoryManager(TAuxMemoryManager& auxiliary, size_t capacity);
		//! Initialize arena memory manager with an auxiliary memory manager and a given buffer
		/*!
			\param auxiliary - Auxiliary memory manager
			\param buffer - Arena buffer
			\param capacity - Arena buffer capacity
		*/
		explicit ArenaMemoryManager(TAuxMemoryManager& auxiliary, void* buffer, size_t capacity);
		ArenaMemoryManager(const ArenaMemoryManager&) = delete;
		ArenaMemoryManager(ArenaMemoryManager&&) = delete;
		~ArenaMemoryManager() { clear(); }

		ArenaMemoryManager& operator=(const ArenaMemoryManager&) = delete;
		ArenaMemoryManager& operator=(ArenaMemoryManager&&) = delete;

		//! Allocated memory in bytes
		size_t allocated() const noexcept { return _allocated; }
		//! Count of active memory allocations
		size_t allocations() const noexcept { return _allocations; }

		//! Arena buffer
		const uint8_t* buffer() const noexcept { return _buffer; }
		//! Arena capacity
		size_t capacity() const noexcept { return _capacity; }
		//! Arena allocated size
		size_t size() const noexcept { return _size; }

		//! Maximum memory block size, that could be allocated by the memory manager
		size_t max_size() const noexcept { return _auxiliary.max_size(); }

		//! Auxiliary memory manager
		TAuxMemoryManager& auxiliary() noexcept { return _auxiliary; }

		//! Allocate a new memory block of the given size
		/*!
			\param size - Block size
			\param alignment - Block alignment (default is alignof(std::max_align_t))
			\return A pointer to the allocated memory block or nullptr in case of allocation failed
		*/
#if defined(_WIN32) || defined(_WIN64)
		void* malloc(size_t size, size_t alignment = alignof(std::max_align_t));// alignof(std::max_align_t));
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
		//! Reset the memory manager with a given chunk capacity
		/*!
			\param capacity - Arena chunk capacity in bytes
		*/
		void reset(size_t capacity);
		//! Reset the memory manager with a given buffer
		/*!
			\param buffer - Arena buffer
			\param capacity - Arena buffer capacity
		*/
		void reset(void* buffer, size_t capacity);

		//! Clear arena memory allocator
		void clear();

	private:
		// Arena chunk
		struct Chunk
		{
			uint8_t* buffer;
			size_t capacity;
			size_t size;
			Chunk* prev;
		};

		// Allocation statistics
		size_t _allocated;
		size_t _allocations;

		// Auxiliary memory manager
		TAuxMemoryManager& _auxiliary;

		// Arena chunks
		Chunk* _current;
		size_t _reserved;

		// External buffer
		bool _external;
		uint8_t* _buffer;
		size_t _capacity;
		size_t _size;

		//! Allocate arena
		Chunk* AllocateArena(size_t capacity, Chunk* prev);
		//! Clear arena
		void ClearArena();
	};

	//! Arena memory allocator class
	template <typename T, class TAuxMemoryManager = DefaultMemoryManager, bool nothrow = false>
	using ArenaAllocator = Allocator<T, ArenaMemoryManager<TAuxMemoryManager>, nothrow>;

////
	template <class TAuxMemoryManager>
	inline ArenaMemoryManager<TAuxMemoryManager>::ArenaMemoryManager(TAuxMemoryManager& auxiliary, size_t capacity)
		: _allocated(0),
		_allocations(0),
		_auxiliary(auxiliary),
		_current(nullptr),
		_reserved(0),
		_external(false),
		_buffer(nullptr),
		_capacity(0),
		_size(0)
	{
		reset(capacity);
	}

	template <class TAuxMemoryManager>
	inline ArenaMemoryManager<TAuxMemoryManager>::ArenaMemoryManager(TAuxMemoryManager& auxiliary, void* buffer, size_t capacity)
		: _allocated(0),
		_allocations(0),
		_auxiliary(auxiliary),
		_current(nullptr),
		_reserved(0),
		_external(true),
		_buffer(nullptr),
		_capacity(0),
		_size(0)
	{
		reset(buffer, capacity);
	}

	template <class TAuxMemoryManager>
	inline void* ArenaMemoryManager<TAuxMemoryManager>::malloc(size_t size, size_t alignment)
	{
		assert((size > 0) && "Allocated block size must be greater than zero!");
		assert(Memory::IsValidAlignment(alignment) && "Alignment must be valid!");

		if (_external)
		{
			// Allocate memory from the external memory block
			uint8_t* buffer = _buffer + _size;
			uint8_t* aligned = Memory::Align(buffer, alignment);
			size_t aligned_size = size + (aligned - buffer);

			// Check if there is enough free space to allocate the block
			if (aligned_size <= (_capacity - _size))
			{
				// Memory allocated
				_size += aligned_size;

				// Update allocation statistics
				_allocated += size;
				++_allocations;

				return aligned;
			}

			// Not enough memory... use auxiliary memory manager
			void* result = _auxiliary.malloc(size, alignment);
			if (result != nullptr)
			{
				// Update allocation statistics
				_allocated += size;
				++_allocations;

				// Increase the required reserved memory size
				_reserved += size;
			}
			return result;
		}
		else
		{
			if (_current != nullptr)
			{
				// Allocate memory from the current arena chunk
				uint8_t* buffer = _current->buffer + _current->size;
				uint8_t* aligned = Memory::Align(buffer, alignment);
				size_t aligned_size = size + (aligned - buffer);

				// Check if there is enough free space to allocate the block
				if (aligned_size <= (_current->capacity - _current->size))
				{
					// Memory allocated
					_current->size += aligned_size;

					// Update allocation statistics
					_allocated += size;
					++_allocations;

					return aligned;
				}
			}

			// Increase the required reserved memory size
			size_t next_reserved = 2 * _reserved;
			while (next_reserved < size)
				next_reserved *= 2;

			// Allocate a new arena chunk
			Chunk* current = AllocateArena(next_reserved, _current);
			if (current != nullptr)
			{
				// Update the current arena chunk
				_current = current;

				// Increase the required reserved memory size
				_reserved = next_reserved;

				// Allocate memory from the current arena chunk
				uint8_t* buffer = _current->buffer + _current->size;
				uint8_t* aligned = Memory::Align(buffer, alignment);
				size_t aligned_size = size + (aligned - buffer);

				// Memory allocated
				_current->size += aligned_size;

				// Update allocation statistics
				_allocated += size;
				++_allocations;

				return aligned;
			}

			// Not enough memory...
			return nullptr;
		}
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::free(void* ptr, size_t size)
	{
		assert((ptr != nullptr) && "Deallocated block must be valid!");

		if (_external)
		{
			// Free memory block in auxiliary memory manager
			if ((ptr < _buffer) || (ptr >= (_buffer + _size)))
				_auxiliary.free(ptr, size);
		}
		else
		{
			// Free memory block in auxiliary memory manager
			if (_current == nullptr)
				_auxiliary.free(ptr, size);
		}

		// Update allocation statistics
		_allocated -= size;
		--_allocations;
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::reset()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Expand internal arena buffer to fit auxiliary allocated storage
		if (!_external)
			reset(_reserved);

		_size = 0;
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::reset(size_t capacity)
	{
		assert((capacity > 0) && "Arena capacity must be greater than zero!");

		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear previous allocations
		clear();

		// Allocate a new arena chunk
		Chunk* current = AllocateArena(capacity, _current);
		if (current != nullptr)
			_current = current;

		// Set initial reserved memory size
		_reserved = capacity;
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::reset(void* buffer, size_t capacity)
	{
		assert((buffer != nullptr) && "Arena buffer must be valid!");
		assert((capacity > 0) && "Arena buffer capacity must be greater than zero!");

		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear previous allocations
		clear();

		// Initialize an external arena buffer
		_external = true;
		_buffer = (uint8_t*)buffer;
		_capacity = capacity;
		_size = 0;

		// Set initial reserved memory size
		_reserved = capacity;
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::clear()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear arena
		ClearArena();

		// Clear external buffer
		_external = false;
		_buffer = nullptr;
		_capacity = 0;
		_size = 0;
	}

	template <class TAuxMemoryManager>
	inline typename ArenaMemoryManager<TAuxMemoryManager>::Chunk* ArenaMemoryManager<TAuxMemoryManager>::AllocateArena(size_t capacity, Chunk* prev)
	{
		// Allocate a new arena chunk
#if defined(_WIN32) || defined(_WIN64)
		uint8_t* buffer = (uint8_t*)_auxiliary.malloc(sizeof(Chunk) + capacity + alignof(std::max_align_t));//  (std::max_align_t));
#else
		uint8_t* buffer = (uint8_t*)_auxiliary.malloc(sizeof(Chunk) + capacity + alignof(max_align_t));
#endif
		Chunk* chunk = (Chunk*)buffer;
		if (chunk != nullptr)
		{
			// Prepare and return a new arena chunk
			chunk->buffer = buffer + sizeof(Chunk);
			chunk->capacity = capacity;
			chunk->size = 0;
			chunk->prev = prev;
			return chunk;
		}

		// Out of memory...
		return nullptr;
	}

	template <class TAuxMemoryManager>
	inline void ArenaMemoryManager<TAuxMemoryManager>::ClearArena()
	{
		if (!_external)
		{
			// Clear all arena chunks
			while (_current != nullptr)
			{
				Chunk* prev = _current->prev;
#if defined(_WIN32) || defined(_WIN64)				
				_auxiliary.free(_current, sizeof(Chunk) + _current->capacity + alignof(std::max_align_t));// ( std::max_align_t));
#else
				_auxiliary.free(_current, sizeof(Chunk) + _current->capacity + alignof(max_align_t));
#endif
				_current = prev;
			}
		}
	}

}//namespace


#endif
