#pragma once
#ifndef XT_REPORTER_CSV_H
#define XT_REPORTER_CSV_H

/**
* \file ReporterCSV.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a csv reporter class.
*
* \description
*	Designed for csv reporter.
*/

#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>

#include "XTReporter.h"
#include "XTConfig.h"

namespace XT
{

	//! Comma-separated values (CSV) reporter
	/*!
		Reports benchmarks results in comma-separated values (CSV) format.

		More information about comma-separated values format you can find here: https://en.wikipedia.org/wiki/Comma-separated_values
	*/
	class XT_COMMON_API ReporterCSV : public Reporter
	{
	public:
		//! Default class constructor
		/*!
			Initialize reporter with an output stream. Default output stream is std::cout.

			\param stream - Output stream
		*/
		ReporterCSV(std::ostream& stream = std::cout) : _stream(stream) {}
		ReporterCSV(const ReporterCSV&) = delete;
		ReporterCSV(ReporterCSV&&) = delete;
		virtual ~ReporterCSV() = default;

		ReporterCSV& operator=(const ReporterCSV&) = delete;
		ReporterCSV& operator=(ReporterCSV&&) = delete;

		// Implementation of Reporter
		void ReportHeader() override;
		void ReportPhase(const PhaseCore& phase, const PhaseMetrics& metrics) override;

	private:
		std::ostream& _stream;
	};

}//namespace

#endif