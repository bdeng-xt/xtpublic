#pragma once
#ifndef XT_CONSOLE_H
#define XT_CONSOLE_H

/**
* \file Console.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for console.
*
* \description
*	Designed for use for console.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 

#include "XTConfig.h"

namespace XT
{

	//! Supported console colors
class ConsoleColor
{
public:
	enum enumtype
	{
		BLACK,          //!< Black color
		BLUE,           //!< Blue color
		GREEN,          //!< Green color
		CYAN,           //!< Cyan color
		RED,            //!< Red color
		MAGENTA,        //!< Magenta color
		BROWN,          //!< Brown color
		GREY,           //!< Grey color
		DARKGREY,       //!< Dark grey color
		LIGHTBLUE,      //!< Light blue color
		LIGHTGREEN,     //!< Light green color
		LIGHTCYAN,      //!< Light cyan color
		LIGHTRED,       //!< Light red color
		LIGHTMAGENTA,   //!< Light magenta color
		YELLOW,         //!< Yellow color
		WHITE           //!< White color
	};
};

	//! Stream manipulator: change console text color
	/*!
		\param stream - Output stream
		\param color - Console text color
		\return Output stream
	*/
	template <class TOutputStream>
	TOutputStream& operator<<(TOutputStream& stream, ConsoleColor::enumtype color);

	//! Stream manipulator: change console text and background colors
	/*!
		\param stream - Output stream
		\param colors - Console text and background colors
		\return Output stream
	*/
	template <class TOutputStream>
	TOutputStream& operator<<(TOutputStream& stream, std::pair<ConsoleColor::enumtype, ConsoleColor::enumtype> colors);

	//! Console management static class
	/*!
		Provides console management functionality such as setting
		text and background colors.

		Thread-safe.
	*/
	class XT_COMMON_API Console
	{
	public:
		Console() = delete;
		Console(const Console&) = delete;
		Console(Console&&) = delete;
		~Console() = delete;

		Console& operator=(const Console&) = delete;
		Console& operator=(Console&&) = delete;

		//! Set console text color
		/*!
			\param color - Console text color
			\param background - Console background color (default is Color::BLACK)
		*/
		static void SetColor(ConsoleColor::enumtype color, ConsoleColor::enumtype background = ConsoleColor::BLACK);
	};

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, ConsoleColor::enumtype color)
	{
		Console::SetColor(color);
		return stream;
	}

	template <class TOutputStream>
	inline TOutputStream& operator<<(TOutputStream& stream, std::pair<ConsoleColor::enumtype, ConsoleColor::enumtype> colors)
	{
		Console::SetColor(colors.first, colors.second);
		return stream;
	}

}//namespace

#endif