#pragma once
#ifndef XT_REPORTER_H
#define XT_REPORTER_H

/**
* \file Reporter.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a reporter class.
*
* \description
*	Designed for reporter.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTBenchmarkBase.h"

#include "XTConfig.h"

namespace XT
{

	//! Reporter base class
	/*!
		Provides interface to report benchmark results.
	*/
	class Reporter
	{
	public:
		Reporter() = default;
		Reporter(const Reporter&) = delete;
		Reporter(Reporter&&) = delete;
		virtual ~Reporter() = default;

		Reporter& operator=(const Reporter&) = delete;
		Reporter& operator=(Reporter&&) = delete;

		//! Report header
		virtual void ReportHeader() {}
		//! Report system information
		virtual void ReportSystem() {}
		//! Report environment information
		virtual void ReportEnvironment() {}
		//! Report all benchmarks header
		virtual void ReportBenchmarksHeader() {}
		//! Report all benchmarks footer
		virtual void ReportBenchmarksFooter() {}
		//! Report current benchmark header
		virtual void ReportBenchmarkHeader() {}
		//! Report current benchmark footer
		virtual void ReportBenchmarkFooter() {}
		//! Report current benchmark information
		/*!
			\param benchmark - Current benchmark
			\param settings - Current benchmark settings
		*/
		virtual void ReportBenchmark(const BenchmarkBase& benchmark, const Settings& settings) {}
		//! Report all phases header
		virtual void ReportPhasesHeader() {}
		//! Report all phases footer
		virtual void ReportPhasesFooter() {}
		//! Report current phase header
		virtual void ReportPhaseHeader() {}
		//! Report current phase footer
		virtual void ReportPhaseFooter() {}
		//! Report current phase information
		/*!
			\param phase - Current phase
			\param metrics - Current phase metrics
		*/
		virtual void ReportPhase(const PhaseCore& phase, const PhaseMetrics& metrics) = 0;
		//! Report footer
		virtual void ReportFooter() {}
	};




}//namespace

#endif