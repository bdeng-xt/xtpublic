#pragma once
#ifndef XT_BENCHMARK_H
#define XT_BENCHMARK_H

/**
* \file Benchmark.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide Benchmark.
*
* \description
*	Designed for Benchmark.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTBenchmarkBase.h"
#include "XTFixture.h"

#include <thread>
#include "XTConfig.h"

namespace XT
{

	//! Benchmark class
	/*!
		Provides interface to perform single thread benchmark.
	*/
	class XT_COMMON_API Benchmark : public BenchmarkBase, public virtual Fixture
	{
	public:
		//! Benchmark settings type
		typedef Settings TSettings;

		//! Default class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		template<typename... Types>
		explicit Benchmark(const std::string& name, Types... settings) : Benchmark(name, TSettings(settings...)) {}
		//! Alternative class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		explicit Benchmark(const std::string& name, const TSettings& settings) : BenchmarkBase(name, settings) {}
		Benchmark(const Benchmark&) = delete;
		Benchmark(Benchmark&&) = delete;
		virtual ~Benchmark() = default;

		Benchmark& operator=(const Benchmark&) = delete;
		Benchmark& operator=(Benchmark&&) = delete;

	protected:
		//! Benchmark run method
		/*!
			Should be implemented to provide code fragment to measure.

			\param context - Benchmark running context
		*/
		virtual void Run(Context& context) = 0;

	private:
		int CountLaunches() const override;
		void Launch(int& current, int total, LauncherHandler& handler) override;
	};


}//namespace

#endif