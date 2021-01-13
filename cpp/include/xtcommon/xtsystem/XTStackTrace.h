#pragma once
#ifndef XT_STACKTRACE_H
#define XT_STACKTRACE_H

/**
* \file StackTrace.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for stack trace.
*
* \description
*	Designed for stack trace.
*/

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include <memory>

#include "XTSingleton.h"
#include "XTExceptions.h"

#include "XTConfig.h"



//! Current stack trace snapshot macro
/*!
	Capture the current stack trace snapshot.
*/
#define __STACK__ XT::StackTrace()

namespace XT
{

	//! Stack trace snapshot provider
	/*!
		Capture the current stack trace snapshot with easy-to-use interface.

		Thread-safe.
	*/
	class XT_COMMON_API StackTrace
	{
	public:
		//! Stack trace frame
		struct Frame
		{
			void* address;          //!< Frame address
			std::string module;     //!< Frame module
			std::string function;   //!< Frame function
			std::string filename;   //!< Frame file name
			int line;               //!< Frame line number

			//! Get string from the current stack trace frame
			std::string string() const
			{
				std::stringstream ss; ss << *this; return ss.str();
			}

			//! Output stack trace frame into the given output stream
			friend std::ostream& operator<<(std::ostream& os, const Frame& frame);
		};

	public:
		//! Capture the current stack trace snapshot
		/*!
			\param skip - Skip frames count (default is 0)
		*/
		explicit StackTrace(int skip = 0);
		StackTrace(const StackTrace&) = default;
		StackTrace(StackTrace&&) = default;// noexcept = default;
		~StackTrace() = default;

		StackTrace& operator=(const StackTrace&) = default;
		StackTrace& operator=(StackTrace&&) =default;//noexcept = default;

		//! Get stack trace frames
		const std::vector<Frame>& frames() const noexcept { return _frames; }

		//! Get string from the current stack trace snapshot
		std::string string() const
		{
			std::stringstream ss; ss << *this; return ss.str();
		}

		//! Output stack trace into the given output stream
		friend std::ostream& operator<<(std::ostream& os, const StackTrace& stack_trace);

	private:
		std::vector<Frame> _frames;
	};



/////////////////////
//! Stack trace manager
/*!
	Provides interface to initialize and cleanup stack trace snapshots capturing.

	Not thread-safe.
*/
	class XT_COMMON_API StackTraceManager : public XTSingleton<StackTraceManager>
	{
		friend XTSingleton<StackTraceManager>;

	public:
		StackTraceManager(const StackTraceManager&) = delete;
		StackTraceManager(StackTraceManager&&) = delete;
		~StackTraceManager();

		StackTraceManager& operator=(const StackTraceManager&) = delete;
		StackTraceManager& operator=(StackTraceManager&&) = delete;

		//! Initialize stack trace manager
		/*!
			This method should be called before you start capture any stack trace snapshots.
			It is recommended to call the method just after the current process start!
		*/
		static void Initialize();
		//! Cleanup stack trace manager
		/*!
			This method should be called just before the current process exits!
		*/
		static void Cleanup();

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;

		StackTraceManager();
	};




}//namespace



#endif
