#pragma once
#ifndef XT_SOURCELOCATION_H
#define XT_SOURCELOCATION_H

/**
* \file SourceLocation.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for source location.
*
* \description
*	Designed for debugging source location.
*/

#include <sstream>
#include <string>

#include "XTConfig.h"
namespace XT
{

	//! Current source location macro
	/*!
		Create a new source location with a current file name and line number.
	*/
#define __LOCATION__ XT::SourceLocation(__FILE__, __LINE__)

	//! Source location
	/*!
		Source location wraps file name and line number into single object with easy-to-use interface.

		Thread-safe.
	*/
	class XT_COMMON_API SourceLocation
	{
		friend class Exception;

	public:
		//! Create a new source location with the given file name and line number
		/*!
			\param filename - File name
			\param line - Line number
		*/
		explicit SourceLocation(const char* filename, int line) noexcept : _filename(filename), _line(line) {}
		SourceLocation(const SourceLocation&) noexcept = default;
		SourceLocation(SourceLocation&&) noexcept = default;
		~SourceLocation() noexcept = default;

		SourceLocation& operator=(const SourceLocation&) = default; //noexcept = default;
		SourceLocation& operator=(SourceLocation&&) = default;// noexcept = default;

		//! Get file name
		const char* filename() const noexcept { return _filename; }
		//! Get line number
		int line() const noexcept { return _line; }

		//! Get the string from the current source location
		std::string string() const
		{
			std::stringstream ss; ss << *this; return ss.str();
		}

		//! Output source location into the given output stream
		friend std::ostream& operator<<(std::ostream& os, const SourceLocation& source_location);

	private:
		const char* _filename;
		int _line;

		SourceLocation() noexcept : SourceLocation(nullptr, 0) {}
	};


	inline std::ostream& operator<<(std::ostream& os, const SourceLocation& source_location)
	{
		if ((source_location.filename() == nullptr) || (source_location.line() == 0))
			return os;

		return os << source_location.filename() << ':' << source_location.line();
	}

}//namespace



#endif
