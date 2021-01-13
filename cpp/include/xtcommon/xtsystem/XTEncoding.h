#pragma once
#ifndef XT_ENCODING_H
#define XT_ENCODING_H

/**
* \file Encoding.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for string encoding.
*
* \description
*	Designed for use for encoding.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

#include <algorithm>
#include <cstdint>
#include <limits>


#include <algorithm>
#include <cassert>
#include <locale> 
#include <boost/locale.hpp>//#include <codecvt> //not in gcc4.8.5
#include <vector>

#include "XTConfig.h"

namespace XT
{

	//! Encoding utilities
	/*!
		Encoding utilities contains methods for UTF-8, UTF-16, UTF-32 encoding conversions.

		Thread-safe.
	*/
	class XT_COMMON_API Encoding
	{
	public:
		Encoding() = delete;
		Encoding(const Encoding&) = delete;
		Encoding(Encoding&&) = delete;
		~Encoding() = delete;

		Encoding& operator=(const Encoding&) = delete;
		Encoding& operator=(Encoding&&) = delete;

		//! Convert system wide-string to UTF-8 encoded string
		/*!
			System wide-string could be UTF-16 (Windows) or UTF-32 (Unix).

			\param wstr - System wide-string to convert
			\return UTF-8 encoded string
		*/
		static std::string ToUTF8(const std::wstring& wstr);

		//! Convert UTF-8 encoded string to system wide-string
		/*!
			System wide-string could be UTF-16 (Windows) or UTF-32 (Unix).

			\param str - UTF-8 encoded string to convert
			\return System wide-string
		*/
		static std::wstring FromUTF8(const std::string& str);

		//! Convert UTF-8 encoded string to UTF-16 encoded string
		/*!
			\param str - UTF-8 encoded string to convert
			\return UTF-16 encoded string
		*/
		static std::u16string UTF8toUTF16(const std::string& str);
		//! Convert UTF-8 encoded string to UTF-32 encoded string
		/*!
			\param str - UTF-8 encoded string to convert
			\return UTF-32 encoded string
		*/
		static std::u32string UTF8toUTF32(const std::string& str);

		//! Convert UTF-16 encoded string to UTF-8 encoded string
		/*!
			\param str - UTF-16 encoded string to convert
			\return UTF-8 encoded string
		*/
		static std::string UTF16toUTF8(const std::u16string& str);
		//! Convert UTF-16 encoded string to UTF-32 encoded string
		/*!
			\param str - UTF-16 encoded string to convert
			\return UTF-32 encoded string
		*/
		static std::u32string UTF16toUTF32(const std::u16string& str);

		//! Convert UTF-32 encoded string to UTF-8 encoded string
		/*!
			\param str - UTF-32 encoded string to convert
			\return UTF-8 encoded string
		*/
		static std::string UTF32toUTF8(const std::u32string& str);
		//! Convert UTF-32 encoded string to UTF-16 encoded string
		/*!
			\param str - UTF-32 encoded string to convert
			\return UTF-16 encoded string
		*/
		static std::u16string UTF32toUTF16(const std::u32string& str);

		//! Base16 encode string
		/*!
			\param str - String to encode
			\return Base16 encoded string
		*/
		static std::string Base16Encode(const std::string& str);
		//! Base16 decode string
		/*!
			\param str - Base16 encoded string
			\return Decoded string
		*/
		static std::string Base16Decode(const std::string& str);

		//! Base32 encode string
		/*!
			\param str - String to encode
			\return Base32 encoded string
		*/
		static std::string Base32Encode(const std::string& str);
		//! Base32 decode string
		/*!
			\param str - Base32 encoded string
			\return Decoded string
		*/
		static std::string Base32Decode(const std::string& str);

		//! Base64 encode string
		/*!
			\param str - String to encode
			\return Base64 encoded string
		*/
		static std::string Base64Encode(const std::string& str);
		//! Base64 decode string
		/*!
			\param str - Base64 encoded string
			\return Decoded string
		*/
		static std::string Base64Decode(const std::string& str);

		//! URL encode string
		/*!
			\param str - String to encode
			\return URL encoded string
		*/
		static std::string URLEncode(const std::string& str);
		//! URL decode string
		/*!
			\param str - URL encoded string
			\return Decoded string
		*/
		static std::string URLDecode(const std::string& str);
	};

}//namespace


#endif
