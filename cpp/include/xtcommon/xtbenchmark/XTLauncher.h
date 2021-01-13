#pragma once
#ifndef XT_LAUNCHER_H
#define XT_LAUNCHER_H

/**
* \file Launcher.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a launcher class.
*
* \description
*	Designed for launcher.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>


#include "XTBenchmark.h"
#include "XTBenchmarkPC.h"
#include "XTBenchmarkThreads.h"
#include "XTLauncherHandler.h"

#include "XTReporter.h"

#include "XTConfig.h"

namespace XT
{

	//! Launcher base class
	/*!
		Provides interface to register benchmarks, launch them and report results with external reporters.
	*/
	class XT_COMMON_API Launcher : public LauncherHandler
	{
	public:
		Launcher() = default;
		Launcher(const Launcher&) = delete;
		Launcher(Launcher&&) = delete;
		virtual ~Launcher() = default;

		Launcher& operator=(const Launcher&) = delete;
		Launcher& operator=(Launcher&&) = delete;

		//! Add the given benchmark to the benchmarks collection
		/*!
			\param benchmark - Benchmark to register
		*/
		void AddBenchmark(const std::shared_ptr<BenchmarkBase>& benchmark) { _benchmarks.emplace_back(benchmark); }
		//! Clear benchmarks collection
		void ClearAllBenchmarks() { _benchmarks.clear(); }

		//! Add the given benchmark builder function to the benchmark builders collection
		/*!
			\param builder - Benchmark builder function
		*/
		void AddBenchmarkBuilder(const std::function<std::shared_ptr<BenchmarkBase>()>& builder) { if (builder) _builders.emplace_back(builder); }
		//! Clear benchmark builders collection
		void ClearAllBenchmarksBuilders() { _builders.clear(); }

		//! Launch registered benchmarks
		/*!
			Launch benchmarks from the benchmarks collection which names are matched to the given string pattern. String
			pattern is represented with a regular expression.

			\param pattern - Pattern to match with benchmark names
		*/
		virtual void Launch(const std::string& pattern = "");

		//! Report benchmarks results using the given reporter
		/*!
			\param reporter - Reporter interface
		*/
		void Report(Reporter& reporter) const;
		//! Report benchmarks High Dynamic Range (HDR) Histograms
		/*!
			\param resolution - Histogram resolution
		*/
		void ReportHistograms(int32_t resolution) const;

	protected:
		//! Registered benchmarks collection
		std::vector<std::shared_ptr<BenchmarkBase>> _benchmarks;
		//! Benchmark builders collection
		std::vector<std::function<std::shared_ptr<BenchmarkBase>()>> _builders;

	private:
		void ReportPhase(Reporter& reporter, const PhaseCore& phase, const std::string& name) const;
		void ReportPhaseHistograms(int32_t resolution, const PhaseCore& phase, const std::string& name) const;
		void ReportPhaseHistogram(int32_t resolution, const PhaseCore& phase, const std::string& name) const;
	};

}//namespace

#endif