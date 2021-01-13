#pragma once
#ifndef XT_EXCH_UTIL_H
#define XT_EXCH_UTIL_H


/**
* \file ExchUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for instrument utility.
*
* \description
*	Designed for utility functions of exchanges and products.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <boost/unordered_set.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/sliced.hpp>

//#include <boost/regex.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include "XTConfig.h"
 
#include "XTData.pb.h"
#include "XTEnum.pb.h"
#include "Util.h"
#include "StringUtil.h"
#include "StringMap.h"

namespace XT
{

class XT_COMMON_API ExchUtil
{

protected:
	static std::string m_EmptyString; ///< empty string

public:
	ExchUtil() {}
	ExchUtil(const ExchUtil& from) {} // = delete;
	ExchUtil& operator=(const ExchUtil& from) { return *this; } // = delete;
	virtual ~ExchUtil() {}

public:
	static std::string getSuffixForExchangeType(XT::ExchangeType::enumtype exchtype);

	static XT::ExchangeType::enumtype getExchangeTypeForSuffix(const std::string& suffix);

	static std::string getSuffixForExchID(const std::string& exchid);

	static std::string getExchIDForSuffix(const std::string& suffix);

public:
	static int readCalendarCsv(const std::string& filename, std::shared_ptr<std::map<int, int> > & tradingdays);

	static int getTradingDaysBetweenFromCalendarCsv(const std::string& exchid, const std::string& productid, int tradingday, int expiredate);
	static int getPrevTradingDayFromCalendarCsv(const std::string& exchid, const std::string& productid, int intdate);



};//class

}//namespace XT

#endif