#pragma once
#ifndef XT_CPU_H
#define XT_CPU_H

/**
* \file CPU.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for cpu.
*
* \description
*	Designed for use for cpu.
*/

#include <cassert>
#include <string>
#include <sstream>
#include <ostream> 

#include "XTConfig.h"

namespace XT
{

	//! CPU management static class
	/*!
		Provides CPU management functionality such as architecture, cores count,
		clock speed, Hyper-Threading feature.

		Thread-safe.
	*/
	class XT_COMMON_API CPU
	{
	public:
		CPU() = delete;
		CPU(const CPU&) = delete;
		CPU(CPU&&) = delete;
		~CPU() = delete;

		CPU& operator=(const CPU&) = delete;
		CPU& operator=(CPU&&) = delete;

		//! CPU architecture string
		static std::string Architecture();
		//! CPU affinity count
		static int Affinity();
		//! CPU logical cores count
		static int LogicalCores();
		//! CPU physical cores count
		static int PhysicalCores();
		//! CPU total cores count
		static std::pair<int, int> TotalCores();
		//! CPU clock speed in Hz
		static int64_t ClockSpeed();
		//! Is CPU Hyper-Threading enabled?
		static bool HyperThreading();
	};

}//namespace


#endif