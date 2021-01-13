#pragma once
#ifndef XT_SHAREDTYPE_H
#define XT_SHAREDTYPE_H

/**
* \file SharedType.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a SharedType class .
*
* \description
*	Designed for a SharedType class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <memory>

#include "XTExceptions.h"
#include "XTSharedMemory.h"

namespace XT
{

	//! Shared memory type
	/*!
		Shared memory type allows to create an instance of the given type in a shared memory and access
		to the instance from multiple processes using the given name.

		Not thread-safe.
	*/
	template <typename T>
	class SharedType
	{
	public:
		//! Create a new or open existing shared memory type with a given name
		/*!
			\param name - Shared memory type name
		*/
		explicit SharedType(const std::string& name);
		SharedType(const SharedType<T>&) = delete;
		SharedType(SharedType<T>&&) = delete;
		~SharedType() = default;

		SharedType<T>& operator=(const SharedType<T>&) = delete;
		SharedType<T>& operator=(SharedType<T>&&) = delete;

		//! Check if the shared memory type is valid
		explicit operator bool() const { return (_shared.ptr() != nullptr); }

		//! Dereference shared memory type
		T& operator*() { return ref(); }
		//! Dereference constant shared memory type
		const T& operator*() const { return ref(); }

		//! Dereference shared memory type member
		T* operator->() { return ptr(); }
		//! Dereference constant shared memory type member
		const T* operator->() const { return ptr(); }

		//! Get the shared memory type name
		const std::string& name() const noexcept { return _shared.name(); }
		//! Get the shared memory type size
		size_t size() const noexcept { return _shared.size(); }

		//! Get the shared memory type pointer
		T* ptr() { return (T*)_shared.ptr(); }
		//! Get the constant shared memory type pointer
		const T* ptr() const { return (const T*)_shared.ptr(); }

		//! Get the shared memory type reference
		T& ref() { return *ptr(); }
		//! Get the constant shared memory type reference
		const T& ref() const { return *ptr(); }

		//! Get the shared memory type owner flag (true if the new one was created, false if the existing one was opened)
		bool owner() const { return _shared.owner(); }

	private:
		SharedMemory _shared;
	};

////
	template <typename T>
	inline SharedType<T>::SharedType(const std::string& name) : _shared(name, sizeof(T))
	{
		// Check for the owner flag
		if (_shared.owner())
		{
			// Call in place constructor
			new (_shared.ptr()) T();
		}
	}


}//namespace


#endif