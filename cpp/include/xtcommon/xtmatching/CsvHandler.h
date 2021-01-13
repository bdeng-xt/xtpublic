#pragma once
#ifndef XT_CSV_HANDLER_H
#define XT_CSV_HANDLER_H

/**
* \file CsvHandler.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for csv handler.
*
* \description
*	Designed for use for csv handler.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "XTConfig.h"

#include "Util.h"
#include "StringUtil.h"

namespace XT
{

class XT_COMMON_API CsvHandler
{

public:
	CsvHandler():
		m_count(0),
//		m_datastr(""),
		m_delimiter(",")
	{
		m_headers = std::vector<std::string>();
		m_dataitems = std::vector<std::string>();
	}
	CsvHandler(const CsvHandler&) {} // = delete;
	CsvHandler(CsvHandler&&) {} // = delete;
	virtual ~CsvHandler() {} // = default;

	CsvHandler& operator=(const CsvHandler&) { return *this; } // = delete;
	CsvHandler& operator=(CsvHandler&&) { return *this; } // = delete;

 
	virtual bool processCsvStr(const std::string& s);

	std::vector<std::string>& items();

	int count();

	const std::string& delimiter();
	void setDelimiter(const std::string& s);

protected:
	int m_count;
//	std::string m_datastr;
	std::vector<std::string> m_headers;
	std::vector<std::string> m_dataitems;
	std::string m_delimiter;

//	std::string m_datastr;

};//class CsvHandler

}//namespace XT

#endif