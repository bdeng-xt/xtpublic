#pragma once
#ifndef XT_SYSMISC_H
#define XT_SYSMISC_H

/**
* \file SysMisc.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide miscellaneous functions .
*
* \description
*	Designed for miscellaneous functions .
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include <exception>

#include "XTConfig.h"

#include "XTErrors.h"
#include "XTExceptions.h"
#include "XTSourceLocation.h"
#include "XTStackTrace.h"


#include "fmt/format.h"
#include "fmt/ostream.h"

//! Fatal abort execution extended macro
/*!
	Fatal abort execution with the current location.
*/
#define fatality(...) XT::fatal(__LOCATION__, __STACK__, __VA_ARGS__)

namespace XT
{

	//! Count of elements in static array
	template <typename T, size_t N>
	constexpr size_t countof(const T(&)[N]) noexcept { return N; }

	//! Count of elements in any other STL container
	template <typename T>
	size_t countof(const T& container) noexcept { return container.size(); }

	//! Fatal abort execution
	/*!
		Fatal aborts execution. It will print fatal message into the std::cerr stream,
		get and print the last system error code and message, stack trace if available.
		Finally abort() function will be called!

		Thread-safe.

		\param location - Source location
		\param trace - Stack trace
		\param message - Fatal message
		\param error - System error code
	*/
	void fatal(const SourceLocation& location, const StackTrace& trace, const std::string& message, int error = SystemError::GetLast()) noexcept;
	//! Fatal abort execution
	/*!
		Fatal aborts execution. It will print fatal exception into the std::cerr stream,
		get and print the last system error code and message, stack trace if available.
		Finally abort() function will be called!

		Thread-safe.

		\param location - Source location
		\param trace - Stack trace
		\param fatal - Fatal exception
	*/
	void fatal(const SourceLocation& location, const StackTrace& trace, const std::exception& fatal) noexcept;

//////
//! Format string
/*!
	Format string with the help of {fmt} library (http://fmtlib.net)

	Thread-safe.

	\param pattern - Format string pattern
	\param args - Format arguments
	\return Formatted string
*/
	template <typename... Args>
	std::string format(const std::string& pattern, const Args&... args);

	//! Format wide string
	/*!
		Format wide string with the help of {fmt} library (http://fmtlib.net)

		Thread-safe.

		\param pattern - Format wide string pattern
		\param args - Format arguments
		\return Formatted wide string
	*/
	template <typename... Args>
	std::wstring format(const std::wstring& pattern, const Args&... args);

	//! Format string and print it into the std::cout
	/*!
		Format string with the help of {fmt} library (http://fmtlib.net)

		Thread-safe.

		\param pattern - Format string pattern
		\param args - Format arguments
	*/
	template <typename... Args>
	void print(const std::string& pattern, const Args&... args);

	//! Format wide string and print it into the std::wcout
	/*!
		Format wide string with the help of {fmt} library (http://fmtlib.net)

		Thread-safe.

		\param pattern - Format wide string pattern
		\param args - Format arguments
	*/
	template <typename... Args>
	void print(const std::wstring& pattern, const Args&... args);

	//! Format string and print it into the given std::ostream
	/*!
		Format string with the help of {fmt} library (http://fmtlib.net)

		Thread-safe.

		\param stream - Output stream
		\param pattern - Format string pattern
		\param args - Format arguments
	*/
	template <typename... Args>
	void print(std::ostream& stream, const std::string& pattern, const Args&... args);

	//! Format wide string and print it into the given std::wostream
	/*!
		Format wide string with the help of {fmt} library (http://fmtlib.net)

		Thread-safe.

		\param stream - Output wide stream
		\param pattern - Format wide string pattern
		\param args - Format arguments
	*/
	template <typename... Args>
	void print(std::wostream& stream, const std::wstring& pattern, const Args&... args);


	template <typename... Args>
	inline std::string format(const std::string& pattern, const Args&... args)
	{
		return fmt::format(pattern, args...);
	}

	template <typename... Args>
	inline std::wstring format(const std::wstring& pattern, const Args&... args)
	{
		return fmt::format(pattern, args...);
	}

	template <typename... Args>
	inline void print(const std::string& pattern, const Args&... args)
	{
		return fmt::print(pattern, args...);
	}

	template <typename... Args>
	inline void print(const std::wstring& pattern, const Args&... args)
	{
		return fmt::print(pattern, args...);
	}

	template <typename... Args>
	inline void print(std::ostream& stream, const std::string& pattern, const Args&... args)
	{
		return fmt::print(stream, pattern, args...);
	}

	template <typename... Args>
	inline void print(std::wostream& stream, const std::wstring& pattern, const Args&... args)
	{
		return fmt::print(stream, pattern, args...);
	}

}//namespace


#endif

