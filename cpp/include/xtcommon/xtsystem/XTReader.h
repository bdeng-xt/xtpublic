#pragma once
#ifndef XT_READER_H
#define XT_READER_H

/**
* \file Reader.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for reader.
*
* \description
*	Designed for use for reader.
*/

#include <cstdint>
#include <string>
#include <vector>
#include "XTConfig.h"

namespace XT
{

	//! Reader interface
	/*!
		Reader interface is based on a read byte buffer method and provides
		functionality to read all bytes, text or text lines.
	*/
	class XT_COMMON_API Reader
	{
	public:
		Reader() noexcept = default;
		Reader(const Reader&) noexcept = default;
		Reader(Reader&&) noexcept = default;
		virtual ~Reader() noexcept = default;

		Reader& operator=(const Reader&) noexcept = default;
		Reader& operator=(Reader&&) noexcept = default;

		//! Read a bytes buffer base method
		/*!
			\param buffer - Buffer to read
			\param size - Buffer size
			\return Count of read bytes
		*/
		virtual size_t Read(void* buffer, size_t size) = 0;

		//! Read all bytes
		/*!
			\return Bytes buffer
		*/
		std::vector<uint8_t> ReadAllBytes();
		//! Read all text
		/*!
			\return Text string
		*/
		std::string ReadAllText();
		//! Read all text lines
		/*!
			\return Text lines
		*/
		std::vector<std::string> ReadAllLines();
	};

}//namespace


#endif