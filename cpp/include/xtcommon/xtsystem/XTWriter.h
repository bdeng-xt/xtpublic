#pragma once
#ifndef XT_WRITER_H
#define XT_WRITER_H

/**
* \file Writer.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for writer.
*
* \description
*	Designed for use for writer.
*/

#include <cstdint>
#include <string>
#include <vector>
#include "XTConfig.h"

namespace XT
{

	//! Writer interface
	/*!
		Writer interface is based on a write byte buffer method and provides
		functionality to write bytes buffer, text or text lines.
	*/
	class XT_COMMON_API Writer
	{
	public:
		Writer() noexcept = default;
		Writer(const Writer&) noexcept = default;
		Writer(Writer&&) noexcept = default;
		virtual ~Writer() noexcept = default;

		Writer& operator=(const Writer&) noexcept = default;
		Writer& operator=(Writer&&) noexcept = default;

		//! Write a byte buffer base method
		/*!
			\param buffer - Buffer to write
			\param size - Buffer size
			\return Count of written bytes
		*/
		virtual size_t Write(const void* buffer, size_t size) = 0;

		//! Write a text string
		/*!
			\param text - Text string
			\return Count of written characters
		*/
		size_t Write(const std::string& text);
		//! Write text lines
		/*!
			\param lines - Text lines
			\return Count of written lines
		*/
		size_t Write(const std::vector<std::string>& lines);

		//! Flush the writer
		virtual void Flush() {}
	};

}//namespace

#endif