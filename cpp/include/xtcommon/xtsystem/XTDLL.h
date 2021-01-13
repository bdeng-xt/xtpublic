#pragma once
#ifndef XT_DLL_H
#define XT_DLL_H

/**
* \file DLL.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a DLL class .
*
* \description
*	Designed for a DLL class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <memory>

#include "XTExceptions.h"
#include "XTPath.h"

#include "XTConfig.h"

//! DLL API macro
/*!
	DLL API is used to mark exported API functions:

	\code{.cpp}
	API int PluginFunction();
	\endcode
*/
#define API extern "C" EXPORT

namespace XT
{

	//! Dynamic link library
	/*!
		Dynamic link library wraps dll operations (load, resolve, unload).

		Not thread-safe.
	*/
	class XT_COMMON_API DLL
	{
	public:
		//! Initialize the dynamic link library with an empty path
		DLL();
		//! Initialize the dynamic link library with a given path and optionally load it
		/*!
			\param path - Dynamic link library path
			\param load - Load library flag (default is true)
		*/
		DLL(const Path& path, bool load = true);
		DLL(const DLL& dll);
		DLL(DLL&& dll) noexcept;
		~DLL();

		DLL& operator=(const Path& path);
		DLL& operator=(const DLL& dll);
		DLL& operator=(DLL&& dll) noexcept;

		//! Check if the dynamic link library is loaded
		explicit operator bool() const { return IsLoaded(); }

		//! Get the dynamic link library path
		const Path path() const;

		//! Is dynamic link library loaded?
		bool IsLoaded() const;

		//! Is dynamic link library resolve the given symbol?
		bool IsResolve(const std::string& name) const;

		//! Load dynamic link library
		/*!
			\return 'true' if the library was successfully loaded, 'false' if the library was not loaded
		*/
		bool Load();
		//! Load dynamic link library with a given path
		/*!
			\param path - Dynamic link library path
			\return 'true' if the library was successfully loaded, 'false' if the library was not loaded
		*/
		bool Load(const Path& path);

		//! Unload dynamic link library
		/*!
			If the dynamic link library cannot be unloaded the method will raise
			a dynamic link library exception!
		*/
		void Unload();

		//! Resolve dynamic link library symbol by the given name
		/*!
			\param name - Symbol name
			\return A pointer to the resolved symbol or nullptr in case of symbol resolution failed
		*/
		template <typename T>
		T* Resolve(const std::string& name) const;

		//! Get the dynamic link library prefix
		/*!
			Cygwin: cyg
			MinGW: lib
			Linux: lib
			OSX: lib
			Windows:

			\return Dynamic link library prefix
		*/
		static std::string prefix();
		//! Get the dynamic link library extension
		/*!
			Linux: .so
			OSX: .dylib
			Windows: .dll

			\return Dynamic link library extension
		*/
		static std::string extension();

		//! Swap two instances
		void swap(DLL& dll) noexcept;
		friend void swap(DLL& dll1, DLL& dll2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;

		//! Resolve dynamic link library symbol by the given name
		/*!
			\param name - Symbol name
			\return A pointer to the resolved symbol or nullptr in case of symbol resolution failed
		*/
		void* ResolveAddress(const std::string& name) const;
	};

////
	template <typename T>
	inline T* DLL::Resolve(const std::string& name) const
	{
		return (T*)ResolveAddress(name);
	}

	inline std::string DLL::prefix()
	{
#if defined(__CYGWIN__)
		return "cyg";
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MINGW32__) || defined(__MINGW64__)
		return "lib";
#else
		return "";
#endif
	}

	inline std::string DLL::extension()
	{
#if defined(__APPLE__)
		return ".dylib";
#elif (defined(unix) || defined(__unix) || defined(__unix__)) && !defined(__CYGWIN__)
		return ".so";
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
		return ".dll";
#else
		return "";
#endif
	}

	inline void swap(DLL& dll1, DLL& dll2) noexcept
	{
		dll1.swap(dll2);
	}


}//namespace


#endif