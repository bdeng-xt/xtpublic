#pragma once
#ifndef XT_BENCHMARK_PC_H
#define XT_BENCHMARK_PC_H

/**
* \file BenchmarkPC.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide BenchmarkPC.
*
* \description
*	Designed for BenchmarkPC.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTBenchmarkBase.h"
#include "XTContextPC.h"
#include "XTFixturePC.h"
#include "XTSettingsPC.h"

#include <thread>

#include "XTConfig.h"

namespace XT
{

	//! Producers/Consumers benchmark base class
	/*!
		Provides interface to perform benchmark of the producers/consumers pattern in multi-thread environment.
	*/
	class XT_COMMON_API BenchmarkPC : public BenchmarkBase, public virtual FixturePC
	{
	public:
		//! BenchmarkPC settings type
		typedef SettingsPC TSettings;

		//! Default class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		template<typename... Types>
		explicit BenchmarkPC(const std::string& name, Types... settings) : BenchmarkPC(name, TSettings(settings...)) {}
		//! Alternative class constructor
		/*!
			\param name - Benchmark name
			\param settings - Benchmark settings
		*/
		explicit BenchmarkPC(const std::string& name, const TSettings& settings) : BenchmarkBase(name, settings) {}
		BenchmarkPC(const BenchmarkPC&) = delete;
		BenchmarkPC(BenchmarkPC&&) = delete;
		virtual ~BenchmarkPC() = default;

		BenchmarkPC& operator=(const BenchmarkPC&) = delete;
		BenchmarkPC& operator=(BenchmarkPC&&) = delete;

	protected:
		//! Producer run method
		/*!
			Should be implemented to provide code which produces items. This code will be executed for each producer in
			separate thread!

			\param context - Producer running context
		*/
		virtual void RunProducer(ContextPC& context) = 0;
		//! Consumer run method
		/*!
			Should be implemented to provide code which consumes items. This code will be executed for each consumer in
			separate thread!

			\param context - Consumers running context
		*/
		virtual void RunConsumer(ContextPC& context) = 0;

	private:
		std::vector<std::thread> _threads;

		int CountLaunches() const override;
		void Launch(int& current, int total, LauncherHandler& handler) override;
	};

}//namespace


#endif