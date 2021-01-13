#pragma once
#ifndef XT_EXECUTOR_H
#define XT_EXECUTOR_H

/**
* \file Executor.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide an executor class.
*
* \description
*	Designed for executor.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include <mutex>

#include "XTPhaseCore.h"
#include "XTReporter.h"

#include "XTConfig.h"

namespace XT
{

	//! Dynamic benchmarks executor class
	/*!
		Provides interface to register dynamic benchmarks and report results with external reporters.
	*/
	class XT_COMMON_API Executor
	{
	public:
		Executor(const Executor&) = delete;
		Executor(Executor&&) = delete;
		~Executor() = default;

		Executor& operator=(const Executor&) = delete;
		Executor& operator=(Executor&&) = delete;

		//! Start a new dynamic benchmark with a given name
		/*!
			This method will create or get existent dynamic benchmark with a given name, start benchmark measurement
			and return it as a shared pointer. Please note the method is thread-safe and might be called in multi-thread
			environment!

			\param benchmark - Dynamic benchmark name
			\return Shared pointer to the required dynamic benchmark
		*/
		static std::shared_ptr<Phase> StartBenchmark(const std::string& benchmark);

		//! Stop dynamic benchmark with a given name
		/*!
			This method will try to find existent dynamic benchmark with a given name and stop benchmark measurement for it.
			Please note the method is thread-safe and might be called in multi-thread environment!

			\param benchmark - Dynamic benchmark name
		*/
		static void StopBenchmark(const std::string& benchmark);

		//! Start a new dynamic benchmark with a given name and wrap it in a PhaseScope
		/*!
			Please note the method is thread-safe and might be called in multi-thread environment!

			\param benchmark - Dynamic benchmark name
			\return Shared pointer to the required dynamic benchmark scope wrapper
		*/
		static std::shared_ptr<PhaseScope> ScopeBenchmark(const std::string& benchmark)
		{
			return std::make_shared<PhaseScope>(StartBenchmark(benchmark));
		}

		//! Report benchmarks results using the given reporter
		/*!
			Please note the method is thread-safe and might be called in multi-thread environment!

			\param reporter - Reporter interface
		*/
		static void Report(Reporter& reporter);

	protected:
		//! Synchronization mutex
		std::mutex _mutex;
		//! Registered benchmarks collection
		std::vector<std::shared_ptr<PhaseCore>> _benchmarks;

	private:
		Executor() = default;

		void ReportPhase(Reporter& reporter, const PhaseCore& phase, const std::string& name) const;

		//! Get singleton instance
		static Executor& GetInstance()
		{
			static Executor instance; return instance;
		}
	};

}//namespace XT

namespace XT
{

}//namespace XT

#endif