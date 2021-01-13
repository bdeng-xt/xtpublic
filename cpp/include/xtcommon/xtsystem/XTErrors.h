#pragma once
#ifndef XT_ERRORS_H
#define XT_ERRORS_H

/**
* \file XTErrors.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for errors.
*
* \description
*	Designed for use for erros.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

#include <algorithm>
#include <cstdint>
#include <limits>

#include "XTConfig.h"

namespace XT
{

	//! System error
	/*!
		System exception provides interface to get, set and clear the last system error.

		Thread-safe.
	*/
	class XT_COMMON_API SystemError
	{
	public:
		SystemError() = delete;
		SystemError(const SystemError&) = delete;
		SystemError(SystemError&&) = delete;
		~SystemError() = delete;

		SystemError& operator=(const SystemError&) = delete;
		SystemError& operator=(SystemError&&) = delete;

		//! Get the last system error code
		/*!
			\return Last system error code
		*/
		static int GetLast() noexcept;

		//! Set the last system error code
		/*!
			\param error - Last system error code to set
		*/
		static void SetLast(int error) noexcept;

		//! Clear the last system error code
		static void ClearLast() noexcept;

		//! Convert the last system error code to the system error description
		/*!
			\return Last system error description
		*/
		static std::string Description() { return Description(GetLast()); }
		//! Convert the given system error code to the system error description
		/*!
			\param error - System error code
			\return System error description
		*/
		static std::string Description(int error);
	};


}//namespace

#endif