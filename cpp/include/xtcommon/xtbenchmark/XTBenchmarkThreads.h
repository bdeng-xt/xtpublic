#pragma once
#ifndef XT_BENCHMARK_THREADS_H
#define XT_BENCHMARK_THREADS_H

/**
* \file BenchmarkThreads.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide BenchmarkThreads.
*
* \description
*	Designed for BenchmarkThreads.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTBenchmarkBase.h"
#include "XTContextThreads.h"
#include "XTFixtureThreads.h"
#include "XTSettingsThreads.h"

#include <thread>
#include "XTConfig.h"

namespace XT
{

	//! Threads benchmark base class
	/*!
		Provides interface to perform benchmark in multi-thread environment.
	*/
	class XT_COMMON_API BenchmarkThreads : public BenchmarkBase, public virtual FixtureThreads
	{
	public:
		//! BenchmarkThreads settings type
		typedef SettingsThreads TSettings;

		//! Default class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		template<typename... Types>
		explicit BenchmarkThreads(const std::string& name, Types... settings) : BenchmarkThreads(name, TSettings(settings...)) {}
		//! Alternative class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		explicit BenchmarkThreads(const std::string& name, const TSettings& settings) : BenchmarkBase(name, settings) {}
		BenchmarkThreads(const BenchmarkThreads&) = delete;
		BenchmarkThreads(BenchmarkThreads&&) = delete;
		virtual ~BenchmarkThreads() = default;

		BenchmarkThreads& operator=(const BenchmarkThreads&) = delete;
		BenchmarkThreads& operator=(BenchmarkThreads&&) = delete;

	protected:
		//! Thread run method
		/*!
			Should be implemented to provide code which will be executed in separate thread!

			\param context - Threads running context
		*/
		virtual void RunThread(ContextThreads& context) = 0;

	private:
		std::vector<std::thread> _threads;

		int CountLaunches() const override;
		void Launch(int& current, int total, LauncherHandler& handler) override;
	};


}//namespace


#endif