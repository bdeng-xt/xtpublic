#pragma once
#ifndef XT_SHAREDMEMORY_H
#define XT_SHAREDMEMORY_H

/**
* \file SharedMemory.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a SharedMemory class .
*
* \description
*	Designed for a SharedMemory class.
*/

#include <cstdint>
#include <string>
#include <iostream> 

#include <memory>

#include "XTExceptions.h"

namespace XT
{

	//! Shared memory manager
	/*!
		Shared memory manager allows to create named memory buffers shared between multiple processes.
		This is one of the common ways to organize different kinds of IPC (inter-process communication).

		Not thread-safe.

		https://en.wikipedia.org/wiki/Shared_memory_(interprocess_communication)
	*/
	class XT_COMMON_API SharedMemory
	{
	public:
		//! Create a new or open existing block of shared memory with a given name and size
		/*!
			\param name - Shared memory block name
			\param size - Shared memory block size
		*/
		explicit SharedMemory(const std::string& name, size_t size);
		SharedMemory(const SharedMemory&) = delete;
		SharedMemory(SharedMemory&& shmem) = delete;
		~SharedMemory();

		SharedMemory& operator=(const SharedMemory&) = delete;
		SharedMemory& operator=(SharedMemory&& shmem) = delete;

		//! Check if the shared memory block is valid
		explicit operator bool() const { return (ptr() != nullptr); }

		//! Get the shared memory block name
		const std::string& name() const noexcept { return _name; }
		//! Get the shared memory block size
		size_t size() const noexcept { return _size; }

		//! Get the shared memory block pointer
		void* ptr();
		//! Get the constant shared memory block pointer
		const void* ptr() const;

		//! Get the shared memory owner flag (true if the new one was created, false if the existing one was opened)
		bool owner() const;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
		std::string _name;
		size_t _size;
	};

}//namespace


#endif