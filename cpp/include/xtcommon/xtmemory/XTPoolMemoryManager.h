#pragma once
#ifndef XT_POOL_MEMORY_MANAGER_H
#define XT_POOL_MEMORY_MANAGER_H

/**
* \file PoolMemoryManager.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a PoolMemoryManager class .
*
* \description
*	Designed for a PoolMemoryManager class.
*/

#include "XTMemory.h"
#include "XTAllocator.h"

namespace XT
{

	//! Memory pool manager class
	/*!
		Memory pool manager uses a pre-allocated memory buffer or several memory
		chunks in order to create an effective free-list data structure, that
		allows to allocate and free memory.

		During the allocation memory pool manager will return a first-fit memory
		block in the free list with concatenating joint blocks to avoid memory
		defragmentation.

		If the allocated block is huge and does not fit into the memory pool chunk
		then it will be allocated directly from auxiliary memory manager.

		Not thread-safe.
	*/
	template <class TAuxMemoryManager = DefaultMemoryManager>
	class PoolMemoryManager
	{
	public:
		//! Initialize memory pool manager with an auxiliary memory manager
		/*!
			Memory pool will have unlimited chunks of size 65536.

			\param auxiliary - Auxiliary memory manager
		*/
		explicit PoolMemoryManager(TAuxMemoryManager& auxiliary) : PoolMemoryManager(auxiliary, 65536, 0) {}
		//! Initialize memory pool manager with an auxiliary memory manager, single chunk size and max chunks count
		/*!
			\param auxiliary - Auxiliary memory manager
			\param chunk - Chunk size in bytes
			\param chunks - Max chunks count. Zero value means unlimited count (default is 0)
		*/
		explicit PoolMemoryManager(TAuxMemoryManager& auxiliary, size_t chunk, size_t chunks = 0);
		//! Initialize memory pool manager with an auxiliary memory manager and a given buffer
		/*!
			\param auxiliary - Auxiliary memory manager
			\param buffer - Pool buffer
			\param capacity - Pool buffer capacity
		*/
		explicit PoolMemoryManager(TAuxMemoryManager& auxiliary, void* buffer, size_t capacity);
		PoolMemoryManager(const PoolMemoryManager&) = delete;
		PoolMemoryManager(PoolMemoryManager&&) = delete;
		~PoolMemoryManager() { clear(); }

		PoolMemoryManager& operator=(const PoolMemoryManager&) = delete;
		PoolMemoryManager& operator=(PoolMemoryManager&&) = delete;

		//! Allocated memory in bytes
		size_t allocated() const noexcept { return _allocated; }
		//! Count of active memory allocations
		size_t allocations() const noexcept { return _allocations; }

		//! Chunk size in bytes
		size_t chunk() const noexcept { return _chunk; }
		//! Max chunks size
		size_t chunks() const noexcept { return _max_chunks; }

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
		//! Reset the memory manager with a given signle chunk size and max chunks count
		/*!
			\param chunk - Chunk size in bytes
			\param chunks - Max chunks count. Zero value means unlimited count (default is 0)
		*/
		void reset(size_t chunk, size_t chunks = 0);
		//! Reset the memory manager with a given buffer
		/*!
			\param buffer - Pool buffer
			\param capacity - Pool buffer capacity
		*/
		void reset(void* buffer, size_t capacity);

		//! Clear memory pool
		void clear();

	private:
		// Pool chunk contains allocated and free blocks
		struct Chunk
		{
			uint8_t* buffer;
			Chunk* prev;
			Chunk* next;
		};
		// Allocated block
		struct AllocBlock
		{
			size_t size;
			size_t adjustment;
		};
		// Free block
		struct FreeBlock
		{
			size_t size;
			FreeBlock* next;
		};

		// Allocation statistics
		size_t _allocated;
		size_t _allocations;

		// Auxiliary memory manager
		TAuxMemoryManager& _auxiliary;

		// Pool chunks
		bool _external;
		size_t _max_chunks;
		size_t _chunks;
		size_t _chunk;
		Chunk* _current;

		// Free block
		FreeBlock* _free_block;

		//! Calculate the align adjustment of the given buffer
		size_t AlignAdjustment(const void* address, size_t alignment);
		//! Calculate the align adjustment of the given buffer with header
		size_t AlignAdjustment(const void* address, size_t alignment, size_t header);

		//! Allocate memory pool
		Chunk* AllocateMemoryPool(size_t capacity, Chunk* prev);
		//! Clear memory pool
		void ClearMemoryPool();
	};

	//! Pool memory allocator class
	template <typename T, class TAuxMemoryManager = DefaultMemoryManager, bool nothrow = false>
	using PoolAllocator = Allocator<T, PoolMemoryManager<TAuxMemoryManager>, nothrow>;

////
	template <class TAuxMemoryManager>
	inline PoolMemoryManager<TAuxMemoryManager>::PoolMemoryManager(TAuxMemoryManager& auxiliary, size_t chunk, size_t chunks)
		: _allocated(0),
		_allocations(0),
		_auxiliary(auxiliary),
		_external(false),
		_max_chunks(0),
		_chunks(0),
		_chunk(0),
		_current(nullptr),
		_free_block(nullptr)
	{
		reset(chunk, chunks);
	}

	template <class TAuxMemoryManager>
	inline PoolMemoryManager<TAuxMemoryManager>::PoolMemoryManager(TAuxMemoryManager& auxiliary, void* buffer, size_t capacity)
		: _allocated(0),
		_allocations(0),
		_auxiliary(auxiliary),
		_external(false),
		_max_chunks(0),
		_chunks(0),
		_chunk(0),
		_current(nullptr),
		_free_block(nullptr)
	{
		reset(buffer, capacity);
	}

	template <class TAuxMemoryManager>
	inline void* PoolMemoryManager<TAuxMemoryManager>::malloc(size_t size, size_t alignment)
	{
		assert((size > 0) && "Allocated block size must be greater than zero!");
		assert(Memory::IsValidAlignment(alignment) && "Alignment must be valid!");

		// Allocate huge blocks using the auxiliary memory manager
		if (size > _chunk)
		{
			void* result = _auxiliary.malloc(size, alignment);
			if (result != nullptr)
			{
				// Update allocation statistics
				_allocated += size;
				++_allocations;
			}
			return result;
		}

		bool allocate = true;
		FreeBlock* prev_free_block = nullptr;
		FreeBlock* current_free_block = _free_block;

		while ((current_free_block != nullptr) || allocate)
		{
			// Try to allocate a new memory pool chunk
			if ((current_free_block == nullptr) && allocate)
			{
				if ((_current != nullptr) && (_current->next != nullptr))
				{
					// Use the next memory pool chunk
					_current = _current->next;

					// Update the current free block
					current_free_block = (FreeBlock*)_current->buffer;
					current_free_block->size = _chunk;
					current_free_block->next = nullptr;

					// Update the free blocks list
					if (prev_free_block != nullptr)
						prev_free_block->next = current_free_block;
					else
						_free_block = current_free_block;
				}
				else
				{
					// Check if there is enough chunks to create
					if (_chunks > 0)
					{
						// Allocate a new memory pool chunk
						Chunk* current = AllocateMemoryPool(_chunk, _current);
						if (current != nullptr)
						{
							// Use the new memory pool chunk
							_current = current;

							// Update the current free block
							current_free_block = (FreeBlock*)_current->buffer;
							current_free_block->size = _chunk;
							current_free_block->next = nullptr;

							// Update the free blocks list
							if (prev_free_block != nullptr)
								prev_free_block->next = current_free_block;
							else
								_free_block = current_free_block;

							// Update created memory pool chunks count
							--_chunks;
						}
					}
				}

				// Stop the allocation attempts
				allocate = false;
				continue;
			}

			// Reset the allocation attempts
			allocate = true;

			// Calculate memory adjustment including the allocation header
			size_t adjustment = AlignAdjustment(current_free_block, alignment, sizeof(AllocBlock));

			// Calculate aligned block size
			size_t aligned_size = size + adjustment;

			// Concatenate joint free blocks
			while (current_free_block->next != nullptr)
			{
				FreeBlock* base_free_block = current_free_block;
				FreeBlock* next_free_block = current_free_block->next;

				// Right joint
				if (((uint8_t*)base_free_block + base_free_block->size) == (uint8_t*)next_free_block)
				{
					current_free_block->size += next_free_block->size;
					current_free_block->next = next_free_block->next;
				}
				else
					break;
			}

			// If there is no enough free space in the current free block use the next one
			if (current_free_block->size < aligned_size)
			{
				// Optimization: Skip the last too small peace of memory in chunk
				if (current_free_block->next != nullptr)
					prev_free_block = current_free_block;
				current_free_block = current_free_block->next;
				continue;
			}

			static_assert(sizeof(AllocBlock) >= sizeof(FreeBlock), "Allocated block structure size must not be less than free block structure size!");

			// Allocate from the remaining memory in the current free block
			if ((current_free_block->size - aligned_size) <= sizeof(AllocBlock))
			{
				//Increase allocation size instead of creating a new free block
				aligned_size = current_free_block->size;

				// Update the free blocks list
				if (prev_free_block != nullptr)
					prev_free_block->next = current_free_block->next;
				else
					_free_block = current_free_block->next;
			}
			else
			{
				// Create a new free block containing remaining memory
				FreeBlock* next_free_block = (FreeBlock*)((uint8_t*)current_free_block + aligned_size);
				next_free_block->size = current_free_block->size - aligned_size;
				next_free_block->next = current_free_block->next;

				// Update the free blocks list
				if (prev_free_block != nullptr)
					prev_free_block->next = next_free_block;
				else
					_free_block = next_free_block;
			}

			// Calculate the aligned address
			uint8_t* aligned = (uint8_t*)current_free_block + adjustment;

			// Create a new allocated block
			AllocBlock* alloc_block = (AllocBlock*)(aligned - sizeof(AllocBlock));
			alloc_block->size = aligned_size;
			alloc_block->adjustment = adjustment;

			// Update allocation statistics
			_allocated += size;
			++_allocations;

			return aligned;
		}

		// Out of memory...
		return nullptr;
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::free(void* ptr, size_t size)
	{
		assert((ptr != nullptr) && "Deallocated block must be valid!");

		// Deallocate huge blocks using the auxiliary memory manager
		if (size > _chunk)
		{
			_auxiliary.free(ptr, size);

			// Update allocation statistics
			_allocated -= size;
			--_allocations;

			return;
		}

		AllocBlock* alloc_block = (AllocBlock*)((uint8_t*)ptr - sizeof(AllocBlock));

		uint8_t* block_start = (uint8_t*)ptr - alloc_block->adjustment;
		size_t   block_size = alloc_block->size;
		uint8_t* block_end = block_start + block_size;

		// Insert a new free block in the begin of the list
		FreeBlock* old_free_block = _free_block;
		FreeBlock* new_free_block = (FreeBlock*)block_start;
		new_free_block->size = block_size;
		new_free_block->next = old_free_block;
		_free_block = new_free_block;

		// Concatenate two joint free blocks
		if (old_free_block != nullptr)
		{
			// Left joint
			if (((uint8_t*)old_free_block + old_free_block->size) == block_start)
			{
				old_free_block->size += new_free_block->size;
				_free_block = old_free_block;
			}
			// Right joint
			else if ((uint8_t*)old_free_block == block_end)
			{
				new_free_block->size += old_free_block->size;
				new_free_block->next = old_free_block->next;
				_free_block = new_free_block;
			}
		}

		// Update allocation statistics
		_allocated -= size;
		--_allocations;
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::reset()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		if (_current != nullptr)
		{
			// Reset the current memory pool chunk
			while (_current->prev != nullptr)
				_current = _current->prev;

			// Reset the free block pointer
			_free_block = (FreeBlock*)_current->buffer;
			_free_block->size = _chunk;
			_free_block->next = nullptr;
		}
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::reset(size_t chunk, size_t chunks)
	{
		assert((chunk >= (sizeof(Chunk) + sizeof(AllocBlock))) && "Memory pool chunk must be big enough to fit at least one allocation block!");

		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear previous allocations
		clear();

		// Initialize the memory pool
		_external = false;
		_max_chunks = (chunks > 0) ? chunks : std::numeric_limits<size_t>::max();
		_chunks = _max_chunks;
		_chunk = chunk;

		// Allocate a new memory pool chunk
		Chunk* current = AllocateMemoryPool(chunk, _current);
		if (current != nullptr)
		{
			// Use the new memory pool chunk
			_current = current;

			// Initialize the free block pointer
			_free_block = (FreeBlock*)_current->buffer;
			_free_block->size = chunk;
			_free_block->next = nullptr;

			// Update created memory pool chunks count
			--_chunks;
		}
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::reset(void* buffer, size_t capacity)
	{
		assert((buffer != nullptr) && "Memory pool buffer must be valid!");
		assert((capacity >= (sizeof(Chunk) + sizeof(AllocBlock))) && "Memory pool buffer capacity must be big enough to fit at least one allocation block!");

		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear previous allocations
		clear();

		// Initialize the external memory pool
		_external = true;
		_max_chunks = 1;
		_chunks = 0;
		_chunk = capacity;
		_current = (Chunk*)buffer;
		_current->buffer = (uint8_t*)buffer + sizeof(Chunk);
		_current->prev = nullptr;
		_current->next = nullptr;

		// Initialize the free block pointer
		_free_block = (FreeBlock*)_current->buffer;
		_free_block->size = capacity - sizeof(Chunk);
		_free_block->next = nullptr;
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::clear()
	{
		assert((_allocated == 0) && "Memory leak detected! Allocated memory size must be zero!");
		assert((_allocations == 0) && "Memory leak detected! Count of active memory allocations must be zero!");

		// Clear memory pool
		ClearMemoryPool();

		// Clear memory pool buffer
		_external = false;
		_max_chunks = 0;
		_chunks = 0;
		_chunk = 0;
		_current = nullptr;

		// Reset the free block pointer
		_free_block = nullptr;
	}

	template <class TAuxMemoryManager>
	inline size_t PoolMemoryManager<TAuxMemoryManager>::AlignAdjustment(const void* address, size_t alignment)
	{
		return (uint8_t*)Memory::Align(address, alignment) - (uint8_t*)address;
	}

	template <class TAuxMemoryManager>
	inline size_t PoolMemoryManager<TAuxMemoryManager>::AlignAdjustment(const void* address, size_t alignment, size_t header)
	{
		size_t adjustment = AlignAdjustment(address, alignment);

		size_t required = header;
		if (adjustment < required)
		{
			required -= adjustment;
			adjustment += alignment * (required / alignment);
			if ((required % alignment) > 0)
				adjustment += alignment;
		}

		return adjustment;
	}

	template <class TAuxMemoryManager>
	inline typename PoolMemoryManager<TAuxMemoryManager>::Chunk* PoolMemoryManager<TAuxMemoryManager>::AllocateMemoryPool(size_t capacity, Chunk* prev)
	{
		// Allocate a new memory pool chunk
#if defined(_WIN32) || defined(_WIN64)	
		uint8_t* buffer = (uint8_t*)_auxiliary.malloc(sizeof(Chunk) + capacity + alignof(std::max_align_t));//(std::max_align_t));
#else
		uint8_t* buffer = (uint8_t*)_auxiliary.malloc(sizeof(Chunk) + capacity + alignof(max_align_t));
#endif
		Chunk* chunk = (Chunk*)buffer;
		if (chunk != nullptr)
		{
			// Prepare and return a new memory pool chunk
			chunk->buffer = buffer + sizeof(Chunk);
			chunk->prev = prev;
			chunk->next = nullptr;
			if (prev != nullptr)
				prev->next = chunk;
			return chunk;
		}

		// Out of memory...
		return nullptr;
	}

	template <class TAuxMemoryManager>
	inline void PoolMemoryManager<TAuxMemoryManager>::ClearMemoryPool()
	{
		if (!_external)
		{
			// Clear all memory pool chunks
			while (_current != nullptr)
			{
				Chunk* prev = _current->prev;
				Chunk* next = _current->next;
#if defined(_WIN32) || defined(_WIN64)
				_auxiliary.free(_current, sizeof(Chunk) + _chunk + alignof(std::max_align_t));//(std::max_align_t));
#else
				_auxiliary.free(_current, sizeof(Chunk) + _chunk + alignof(max_align_t));
#endif
				if (prev != nullptr)
				{
					prev->next = next;
					_current = prev;
				}
				else if (next != nullptr)
				{
					next->prev = prev;
					_current = next;
				}
				else
					_current = nullptr;
			}

			// Reset the free block pointer
			_free_block = nullptr;
		}
	}


}//namespace


#endif
