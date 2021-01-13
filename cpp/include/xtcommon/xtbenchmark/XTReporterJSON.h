#pragma once
#ifndef XT_REPORTER_JSON_H
#define XT_REPORTER_JSON_H

/**
* \file ReporterJSON.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a json reporter class.
*
* \description
*	Designed for json reporter.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTReporter.h"
#include "XTConfig.h"

namespace XT
{

	//! JSON reporter
	/*!
		Reports benchmarks results in JSON format.

		More information about JSON format you can find here: https://en.wikipedia.org/wiki/Comma-separated_values
	*/
	class XT_COMMON_API ReporterJSON : public Reporter
	{
	public:
		//! Default class constructor
		/*!
			Initialize reporter with an output stream. Default output stream is std::cout.

			\param stream - Output stream
		*/
		ReporterJSON(std::ostream& stream = std::cout) : _stream(stream), _benchmark_comma(false), _phase_comma(false) {}
		ReporterJSON(const ReporterJSON&) = delete;
		ReporterJSON(ReporterJSON&&) = delete;
		virtual ~ReporterJSON() = default;

		ReporterJSON& operator=(const ReporterJSON&) = delete;
		ReporterJSON& operator=(ReporterJSON&&) = delete;

		// Implementation of Reporter
		void ReportHeader() override;
		void ReportSystem() override;
		void ReportEnvironment() override;
		void ReportBenchmarksHeader() override;
		void ReportBenchmarksFooter() override;
		void ReportBenchmarkHeader() override;
		void ReportBenchmarkFooter() override;
		void ReportBenchmark(const BenchmarkBase& benchmark, const Settings& settings) override;
		void ReportPhasesHeader() override;
		void ReportPhasesFooter() override;
		void ReportPhaseHeader() override;
		void ReportPhaseFooter() override;
		void ReportPhase(const PhaseCore& phase, const PhaseMetrics& metrics) override;
		void ReportFooter() override;

	private:
		std::ostream& _stream;
		bool _benchmark_comma;
		bool _phase_comma;
	};


}//namespace

#endif