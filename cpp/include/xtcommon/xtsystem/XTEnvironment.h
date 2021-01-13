#pragma once
#ifndef XT_ENVIRONMENT_H
#define XT_ENVIRONMENT_H

/**
* \file Enviroment.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for enviroment.
*
* \description
*	Designed for use for environment.
*/

#include <cstdint>
#include <cstring>

#include <map>
#include <string>

#include "XTConfig.h"

#include "XTExceptions.h"

namespace XT
{
	//! Environment management static class
	/*!
		Provides environment management functionality to get OS bit version, process bit version,
		debug/release mode.

		Thread-safe.
	*/
	class XT_COMMON_API Environment
	{
	public:
		Environment() = delete;
		Environment(const Environment&) = delete;
		Environment(Environment&&) = delete;
		~Environment() = delete;

		Environment& operator=(const Environment&) = delete;
		Environment& operator=(Environment&&) = delete;

		//! Is 32-bit OS?
		static bool Is32BitOS();
		//! Is 64-bit OS?
		static bool Is64BitOS();

		//! Is 32-bit running process?
		static bool Is32BitProcess();
		//! Is 64-bit running process?
		static bool Is64BitProcess();

		//! Is compiled in debug mode?
		static bool IsDebug();
		//! Is compiled in release mode?
		static bool IsRelease();

		//! Is big-endian system?
		static bool IsBigEndian();
		//! Is little-endian system?
		static bool IsLittleEndian();

		//! Get OS version string
		static std::string OSVersion();

		//! Get text end line separator
		static std::string EndLine();

		//! Get Unix text end line separator
		static std::string UnixEndLine();
		//! Get Windows text end line separator
		static std::string WindowsEndLine();

		//! Get all environment variables
		/*!
			\return Environment variables collection
		*/
		static std::map<std::string, std::string> envars();

		//! Get environment variable value by the given name
		/*!
			\param name - Environment variable name
			\return Environment variable value
		*/
		static std::string GetEnvar(const std::string name);
		//! Set environment variable value by the given name
		/*!
			\param name - Environment variable name
			\param value - Environment variable value
		*/
		static void SetEnvar(const std::string name, const std::string value);
		//! Clear environment variable by the given name
		/*!
			\param name - Environment variable name
		*/
		static void ClearEnvar(const std::string name);

		//! Get the current time in seconds
		static time_t Timestamp();
	};

}//namespace
#endif