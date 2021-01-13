#pragma once
#ifndef XT_REPORTER_CONSOLE_H
#define XT_REPORTER_CONSOLE_H

/**
* \file Reporter.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a console reporter class.
*
* \description
*	Designed for console reporter.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTReporter.h"
#include "XTConfig.h"

namespace XT
{

	//! Console reporter
	/*!
		Console reporter uses console output to show benchmarks results. If it is possible results are presented in
		different colors.
	*/
	class XT_COMMON_API ReporterConsole : public Reporter
	{
	public:
		//! Default class constructor
		/*!
			Initialize reporter with an output stream. Default output stream is std::cout.

			\param stream - Output stream
		*/
		ReporterConsole(std::ostream& stream = std::cout) : _stream(stream) {}
		ReporterConsole(const ReporterConsole&) = delete;
		ReporterConsole(ReporterConsole&&) = delete;
		virtual ~ReporterConsole() = default;

		ReporterConsole& operator=(const ReporterConsole&) = delete;
		ReporterConsole& operator=(ReporterConsole&&) = delete;

		// Implementation of Reporter
		void ReportHeader() override;
		void ReportSystem() override;
		void ReportEnvironment() override;
		void ReportBenchmark(const BenchmarkBase& benchmark, const Settings& settings) override;
		void ReportPhase(const PhaseCore& phase, const PhaseMetrics& metrics) override;
		void ReportFooter() override;

		//! Generate separator string
		/*!
			Will return a string of 79 given characters.

			\param ch - Separator character
			\return String separator
		*/
		static std::string GenerateSeparator(char ch);
		//! Generate clock speed string
		/*!
			Will return a pretty string of Hz, kHz, MHz, GHz based on the given clock speed in hertz.

			\param hertz - Clock speed value in hertz
			\return String with clock speed representation
		*/
		static std::string GenerateClockSpeed(int64_t hertz);
		//! Generate data size string
		/*!
			Will return a pretty string of bytes, KiB, MiB, GiB, TiB based on the given bytes.

			\param bytes - Data size in bytes
			\return String with data size representation
		*/
		static std::string GenerateDataSize(int64_t bytes);
		//! Generate time period string
		/*!
			Will return a pretty string of ns, mcs, ms, s, m, h based on the given nanoseconds.

			\param nanoseconds - Time period in nanoseconds
			\return String with time period representation
		*/
		static std::string GenerateTimePeriod(int64_t nanoseconds);

	private:
		std::ostream& _stream;
	};


}//namespace

#endif