#pragma once
#ifndef XT_SYSTEM_UTIL_H
#define XT_SYSTEM_UTIL_H

/**
* \file SystemUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide system utility functions.
*
* \description
*	This component provides utility functions for system.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>

#include <ctime>
#include <chrono>

#include "XTConfig.h"

namespace XT
{

class XT_COMMON_API SystemUtil {
public:
	SystemUtil() {} // = delete;
	SystemUtil(const SystemUtil&) {} // = delete;
//	SystemUtil(SystemUtil&&) {} // = delete;
	~SystemUtil() {} // = delete;

	SystemUtil& operator=(const SystemUtil&) { return *this; } // = delete;
//	SystemUtil& operator=(SystemUtil&&) { return *this; } // = delete;
	//////

public:

	//! CPU architecture string
	static std::string getCpuArchitecture();
	//! CPU logical cores count
	static int getCpuLogicalCores();
	//! CPU physical cores count
	static int getCpuPhysicalCores();

	//! CPU clock speed in Hz
	static int64_t getCpuClockSpeed();
	//! Is CPU Hyper-Threading enabled?
	static bool getCpuHyperThreading();

	//! Total RAM in bytes
	static int64_t getRamTotal();
	//! Free RAM in bytes
	static int64_t getRamFree();

	//! Current thread Id
	static uint64_t getCurrThreadId();

	//! Get the current timestamp in nanoseconds
	static uint64_t getCurrTimestamp();

protected:
	//! CPU total cores count
	static std::pair<int, int> getCpuTotalCores();

	//! Calculate (operant * multiplier / divider) with 64-bit unsigned integer values
	static uint64_t MulDiv64(uint64_t operant, uint64_t multiplier, uint64_t divider);

};//class

}//namespace


#endif