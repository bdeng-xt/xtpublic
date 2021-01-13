#pragma once
#ifndef XT_MEMORY_H
#define XT_MEMORY_H

/**
* \file Memory.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a memory class .
*
* \description
*	Designed for a memory class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>

#include "XTConfig.h"
#include "XTExceptions.h"

namespace XT
{

	//! Memory management static class
	/*!
		Provides memory management functionality such as total and free RAM available.

		Thread-safe.
	*/
	class XT_COMMON_API Memory
	{
	public:
		Memory() = delete;
		Memory(const Memory&) = delete;
		Memory(Memory&&) = delete;
		~Memory() = delete;

		Memory& operator=(const Memory&) = delete;
		Memory& operator=(Memory&&) = delete;

		//! Total RAM in bytes
		static int64_t RamTotal();
		//! Free RAM in bytes
		static int64_t RamFree();

		//! Is the given memory buffer filled with zeros?
		/*!
			\param buffer - Memory buffer
			\param size - Size of memory buffer in bytes
			\return 'true' if the given memory buffer is filled with zeros, 'false' if the memory buffer is not filled with zeros
		*/
		static bool IsZero(const void* buffer, size_t size) noexcept;

		//! Is the given alignment valid?
		/*!
			\param alignment - Alignment value. Must be a power of two.
			\return 'true' if the given alignment is valid, 'false' if the given alignment is not valid
		*/
		static bool IsValidAlignment(size_t alignment) noexcept;

		//! Is the given pointer aligned?
		/*!
			\param address - Address
			\param alignment - Alignment value. Must be a pointer of two (default is alignof(T))
			\return 'true' if the given address is aligned, 'false' if the given address is not aligned
		*/
		template <typename T>
		static bool IsAligned(const T* address, size_t alignment = alignof(T)) noexcept;

		//! Align pointer (upwards or downwards)
		/*!
			\param address - Address
			\param alignment - Alignment value. Must be a pointer of two (default is alignof(T))
			\param upwards - Upwards flag (default is true)
			\return Aligned address
		*/
		template <typename T>
		static T* Align(const T* address, size_t alignment = alignof(T), bool upwards = true) noexcept;

		//! Fill the given memory buffer with zeros
		/*!
			\param buffer - Memory buffer to fill
			\param size - Size of memory buffer in bytes
		*/
		static void ZeroFill(void* buffer, size_t size);
		//! Fill the given memory buffer with random bytes
		/*!
			\param buffer - Memory buffer to fill
			\param size - Size of memory buffer in bytes
		*/
		static void RandomFill(void* buffer, size_t size);
		//! Fill the given memory buffer with cryptographic strong random bytes
		/*!
			\param buffer - Memory buffer to fill
			\param size - Size of memory buffer in bytes
		*/
		static void CryptoFill(void* buffer, size_t size);
	};
////
	inline bool Memory::IsValidAlignment(size_t alignment) noexcept
	{
		return ((alignment > 0) && ((alignment & (alignment - 1)) == 0));
	}

	template <typename T>
	inline bool Memory::IsAligned(const T* address, size_t alignment) noexcept
	{
		assert((address != nullptr) && "Address must be valid!");
		assert(IsValidAlignment(alignment) && "Alignment must be valid!");

		uintptr_t ptr = (uintptr_t)address;
		return (ptr & (alignment - 1)) == 0;
	}

	template <typename T>
	inline T* Memory::Align(const T* address, size_t alignment, bool upwards) noexcept
	{
		assert((address != nullptr) && "Address must be valid!");
		assert(IsValidAlignment(alignment) && "Alignment must be valid!");

		uintptr_t ptr = (uintptr_t)address;

		if (upwards)
			return (T*)((ptr + (alignment - 1)) & -((int)alignment));
		else
			return (T*)(ptr & -((int)alignment));
	}

}//namespace 


#endif
