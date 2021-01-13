#pragma once
#ifndef XT_PROCESS_H
#define XT_PROCESS_H

/**
* \file Process.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a process class .
*
* \description
*	Designed for a process class.
*/

#include <cstdint>
#include <string>
#include <iostream> 
#include <memory>
#include <map>
#include <limits>
#include <vector>

#include "XTConfig.h"
#include "XTExceptions.h"
#include "XTPipe.h"
#include "XTTimestamp.h"

//! Current process Id macro
/*!
	Get the current process Id.
*/
#define __PROCESS__ XT::XTProcess::CurrentProcessId()

namespace XT
{

	//! Process abstraction
	/*!
		Process contains different kinds of process manipulation functionality such as
		retrive the current process Id, execute or terminate one.

		Thread-safe.
	*/
	class XT_COMMON_API XTProcess
	{
	public:
		XTProcess(const XTProcess& process);
		XTProcess(XTProcess&& process) noexcept;
		~XTProcess();

		XTProcess& operator=(const XTProcess& process);
		XTProcess& operator=(XTProcess&& process) noexcept;

		//! Get the process Id
		uint64_t pid() const noexcept;

		//! Is the process is running?
		bool IsRunning() const;

		//! Kill the process
		void Kill();

		//! Wait the process to exit
		/*!
			Will block.

			\return Process exit result
		*/
		int Wait();

		//! Wait the process to exit for the given timespan
		/*!
			Will block for the given timespan in the worst case.

			\param timespan - Timespan to wait for the process
			\return Process exit result (std::numeric_limits<int>::min() in case of timeout)
		*/
		int WaitFor(const XTTimespan& timespan);
		//! Wait the process to exit until the given timestamp
		/*!
			Will block until the given timestamp in the worst case.

			\param timestamp - Timestamp to stop wait for the process
			\return Process exit result (std::numeric_limits<int>::min() in case of timeout)
		*/
		int WaitUntil(const XTUtcTimestamp& timestamp)
		{
			return WaitFor(timestamp - XTUtcTimestamp());
		}

		//! Get the current process Id
		/*!
			\return Current process Id
		*/
		static uint64_t CurrentProcessId() noexcept;
		//! Get the parent process Id
		/*!
			\return Parent process Id
		*/
		static uint64_t ParentProcessId() noexcept;

		//! Get the current process
		/*!
			\return Current process
		*/
		static XTProcess CurrentProcess();
		//! Get the parent process
		/*!
			\return Parent process
		*/
		static XTProcess ParentProcess();

		//! Exit the current process
		/*!
			\param result - Result is returned to the parent
		*/
		static void Exit(int result);

		//! Execute a new process
		/*!
			If input/output/error communication pipe is not provided then
			new process will use equivalent standard stream of the parent
			process.

			\param command - Command to execute
			\param arguments - Pointer to arguments vector (default is nullptr)
			\param envars - Pointer to environment variables map (default is nullptr)
			\param directory - Initial working directory (default is nullptr)
			\param input - Input communication pipe (default is nullptr)
			\param output - Output communication pipe (default is nullptr)
			\param error - Error communication pipe (default is nullptr)
			\return Created process
		*/
		static XTProcess Execute(const std::string& command, const std::vector<std::string>* arguments = nullptr, const std::map<std::string, std::string>* envars = nullptr, const std::string* directory = nullptr, Pipe* input = nullptr, Pipe* output = nullptr, Pipe* error = nullptr);

		//! Swap two instances
		void swap(XTProcess& process) noexcept;
		friend void swap(XTProcess& process1, XTProcess& process2) noexcept;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;

		XTProcess();
		XTProcess(uint64_t pid);
	};

////
	inline XTProcess XTProcess::CurrentProcess()
	{
		return XTProcess(CurrentProcessId());
	}

	inline XTProcess XTProcess::ParentProcess()
	{
		return XTProcess(ParentProcessId());
	}

	inline void swap(XTProcess& process1, XTProcess& process2) noexcept
	{
		process1.swap(process2);
	}

}//namespace


#endif
