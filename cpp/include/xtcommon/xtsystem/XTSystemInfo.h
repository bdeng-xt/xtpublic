#pragma once
#ifndef XT_SYSTEM_INFO_H
#define XT_SYSTEM_INFO_H

/**
* \file SystemInfo.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide system information .
*
* \description
*	Designed for system information.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>
#include "XTConfig.h"
namespace XT
{

	//! System management static class
	/*!
		Provides system management functionality to get CPU properties, RAM properties, current thread Id, etc.
	*/
	class XT_COMMON_API SystemInfo
	{
	public:
		SystemInfo() {} // = delete;
		SystemInfo(const SystemInfo&) {} // = delete;
		SystemInfo(SystemInfo&&) {} // = delete;
		~SystemInfo() {} // = delete;

		SystemInfo& operator=(const SystemInfo&) { return *this; } // = delete;
		SystemInfo& operator=(SystemInfo&&) { return *this; } // = delete;

		//! CPU architecture string
		static std::string CpuArchitecture();
		//! CPU logical cores count
		static int CpuLogicalCores();
		//! CPU physical cores count
		static int CpuPhysicalCores();
		//! CPU total cores count
		static std::pair<int, int> CpuTotalCores();
		//! CPU clock speed in Hz
		static int64_t CpuClockSpeed();
		//! Is CPU Hyper-Threading enabled?
		static bool CpuHyperThreading();

		//! Total RAM in bytes
		static int64_t RamTotal();
		//! Free RAM in bytes
		static int64_t RamFree();

		//! Current thread Id
		static uint64_t CurrentThreadId();

		//! Get the current timestamp in nanoseconds
		static uint64_t Timestamp();

		//! Calculate (operant * multiplier / divider) with 64-bit unsigned integer values
		static uint64_t MulDiv64(uint64_t operant, uint64_t multiplier, uint64_t divider);
	};

}//namespace XT

#endif