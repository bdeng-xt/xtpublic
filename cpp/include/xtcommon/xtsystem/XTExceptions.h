#pragma once
#ifndef XT_EXCEPTIONS_H
#define XT_EXCEPTIONS_H

/**
* \file Exceptions.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for exceptions.
*
* \description
*	Designed for use for exceptions.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

#include <algorithm>
#include <cstdint>
#include <limits>

#include <exception>
#include <string>
#include <utility>

#include <cassert>
#include <functional>
#include <memory>

#include "XTConfig.h"

#include "XTErrors.h"
#include "XTSourceLocation.h"
#include "XTSingleton.h"





//! Throw extended exception macro
/*!
	Throw extended exception with the current location.
*/
#define throwex throw __LOCATION__ +

namespace XT
{

	//! Exception
	/*!
		Exception base interface.

		Not thread-safe.
	*/
	class XT_COMMON_API Exception : public std::exception
	{
	public:
		//! Default class constructor
		/*!
			\param message - Exception message (default is "")
		*/
		explicit Exception(const std::string& message = "") : _message(message), _location() {}
		Exception(const Exception&) = default;
		Exception(Exception&&) = default;
		virtual ~Exception() = default;

		Exception& operator=(const Exception&) = default;
		Exception& operator=(Exception&&) = default;

		//! Get exception message
		const std::string& message() const noexcept { return _message; }
		//! Get exception location
		const SourceLocation& location() const noexcept { return _location; }

		//! Get string identifying exception
		const char* what() const noexcept override;

		//! Get string from the current exception
		virtual std::string string() const;

		//! Output exception into the given output stream
		friend std::ostream& operator<<(std::ostream& os, const Exception& ex)
		{
			os << ex.string(); return os;
		}

		//! Link exception with source location
		template<class T>
		friend T&& operator+(const SourceLocation& location, T&& instance)
		{
			instance._location = location; return std::forward<T>(instance);
		}

	protected:
		//! Cached exception string
		mutable std::string _cache;
		//! Exception message
		std::string _message;
		//! Exception location
		SourceLocation _location;
	};

	//! Argument exception
	class ArgumentException : public Exception
	{
	public:
		using Exception::Exception;

		virtual ~ArgumentException() {}
	};

	//! Runtime exception
	class RuntimeException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~RuntimeException() {}
	};

	//! Security exception
	class SecurityException : public Exception
	{
	public:
		using Exception::Exception;
		virtual ~SecurityException() {}
	};

	//! System exception
	class SystemException : public Exception
	{
	public:
		//! Create system exception based on the last system error code
		SystemException()
			: SystemException(SystemError::GetLast())
		{}
		//! Create system exception based on the given system error code
		/*!
			\param error - System error code
		*/
		explicit SystemException(int error)
			: SystemException(SystemError::Description(error), error)
		{}
		//! Create system exception based on the given exception message
		/*!
			\param message - Exception message
		*/
		explicit SystemException(const std::string& message)
			: SystemException(message, SystemError::GetLast())
		{}
		//! Create system exception based on the given exception message and system error code
		/*!
			\param message - Exception message
			\param error - System error code
		*/
		explicit SystemException(const std::string& message, int error)
			: Exception(message),
			_system_error(error),
			_system_message(SystemError::Description(error))
		{}

		virtual ~SystemException() {}

		//! Get system error code
		int system_error() const noexcept { return _system_error; }
		//! Get system error message
		const std::string& system_message() const noexcept { return _system_message; }

		//! Get string from the current system exception
		std::string string() const override;

	protected:
		//! System error code
		int _system_error;
		//! System error message
		std::string _system_message;
	};

///////////////////
//forward
	class StackTrace;
//! Exceptions handler
/*!
	Exceptions handler allows to setup special handlers for all process and thread exceptions.
	This allows to catch different kinds of unhandled exceptions, signals, process abort and
	termination. As the result corresponding exception will be routed to the global exceptions
	handler function (default one will print the exception in std::cerr with a full stack-trace)
	and the dump file will be created.

	Not thread-safe.
*/
	class XT_COMMON_API ExceptionsHandler : public XTSingleton<ExceptionsHandler>
	{
		friend XTSingleton<ExceptionsHandler>;

	public:
		ExceptionsHandler(const ExceptionsHandler&) = delete;
		ExceptionsHandler(ExceptionsHandler&&) = delete;
		~ExceptionsHandler();

		ExceptionsHandler& operator=(const ExceptionsHandler&) = delete;
		ExceptionsHandler& operator=(ExceptionsHandler&&) = delete;

		//! Setup new global exceptions handler function
		/*!
			This method should be called once for the current process.
			It is recommended to call the method just after the current process start!

			\param handler - Exceptions handler function
		*/
		static void SetupHandler(const std::function<void(const SystemException&, const StackTrace&)>& handler);
		//! Setup exceptions handler for the current process
		/*!
			This method should be called once for the current process.
			It is recommended to call the method just after the current process start!
		*/
		static void SetupProcess();
		//! Setup exceptions handler for the current thread
		/*!
			This method should be called once for the current thread.
			It is recommended to call the method just after the current thread start!
		*/
		static void SetupThread();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;

		ExceptionsHandler();
	};

}//namespace


#endif
