#pragma once
#ifndef XT_LAUNCHER_HANDLER_H
#define XT_LAUNCHER_HANDLER_H

/**
* \file LauncherHandler.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a console handler class.
*
* \description
*	Designed for console handler.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTBenchmarkBase.h"
#include "XTBenchmarkThreads.h"

namespace XT
{

	//! Launcher handler
	/*!
		Provides interface to handle progress notifications from benchmark launcher.
	*/
	class LauncherHandler
	{
		friend class Benchmark;
		friend class BenchmarkPC;
		friend class BenchmarkThreads;

	public:
		LauncherHandler() = default;
		LauncherHandler(const LauncherHandler&) = default;
		LauncherHandler(LauncherHandler&&) noexcept = default;
		virtual ~LauncherHandler() = default;

		LauncherHandler& operator=(const LauncherHandler&) = default;
		LauncherHandler& operator=(LauncherHandler&&) noexcept = default;

	protected:
		//! Handle benchmark launching notification
		/*!
			This method is called before launching the given benchmark.

			\param current - Current benchmark number
			\param total - Total benchmarks
			\param benchmark - Benchmark
			\param context - Benchmark running context
			\param attempt - Benchmark attempt
		*/
		virtual void onLaunching(int current, int total, const BenchmarkBase& benchmark, const Context& context, int attempt) {}
		//! Handle benchmark launched notification
		/*!
			This method is called after launched the given benchmark.

			\param current - Current benchmark number
			\param total - Total benchmarks
			\param benchmark - Benchmark
			\param context - Benchmark running context
			\param attempt - Benchmark attempt
		*/
		virtual void onLaunched(int current, int total, const BenchmarkBase& benchmark, const Context& context, int attempt) {}
	};

}//namespace


#endif