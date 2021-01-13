#pragma once
#ifndef XT_XTUTIL_H
#define XT_XTUTIL_H

/**
* \file XTUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all xt utilities.
*
* \description
*	Designed for managing all xt utilites.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <google/protobuf/util/json_util.h>

#include "Util.h"
#include "Instr.h"
#include "InstrMgr.h"

#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "XTConfig.h"

namespace XT
{


class XT_COMMON_API XTUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTUtil() {}

	/**
	* @brief copy constructor
	*/
	XTUtil(const XTUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	XTUtil& operator=(const XTUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~XTUtil() {}

	///@}
protected:
	static const std::string s_EmptyString; ///< empty string
public:
	/**
	* @brief get empty string
	*
	* @return empty string
	*/
	static const std::string& getEmptyString(); ///< empty string
 


////////////////////////////////////////
public:


	static bool fromjsonKCBPTagQuoteInfo10(XT::KCBPTagQuoteInfo10& r, const std::string& s);
	static std::string tojsonKCBPTagQuoteInfo10(const XT::KCBPTagQuoteInfo10& r);
	static bool parseKCBPTagQuoteInfo10(XT::KCBPTagQuoteInfo10& r, const std::string& s);
	static std::string serializeKCBPTagQuoteInfo10(const XT::KCBPTagQuoteInfo10& r);

	static bool fromjsonBarData(XT::BarData& r, const std::string& s);
	static std::string tojsonBarData(const XT::BarData& r);
	static bool parseBarData(XT::BarData& r, const std::string& s);
	static std::string serializeBarData(const XT::BarData& r);

	static bool fromjsonApiPBTagMsg(XT::ApiPBTagMsg& r, const std::string& s);
	static std::string tojsonApiPBTagMsg(const XT::ApiPBTagMsg& r);
	static bool parseApiPBTagMsg(XT::ApiPBTagMsg& r, const std::string& s);
	static std::string serializeApiPBTagMsg(const XT::ApiPBTagMsg& r);

	static bool fromjsonProductInfo(XT::ProductInfo& r, const std::string& s);
	static std::string tojsonProductInfo(const XT::ProductInfo& r);
	static bool parseProductInfo(XT::ProductInfo& r, const std::string& s);
	static std::string serializeProductInfo(const XT::ProductInfo& r);

	static bool fromjsonFillInfo(XT::FillInfo& r, const std::string& s);
	static std::string tojsonFillInfo(const XT::FillInfo& r);
	static bool parseFillInfo(XT::FillInfo& r, const std::string& s);
	static std::string serializeFillInfo(const XT::FillInfo& r);

	static bool fromjsonKCBPTagQuoteInfo5(XT::KCBPTagQuoteInfo5& r, const std::string& s);
	static std::string tojsonKCBPTagQuoteInfo5(const XT::KCBPTagQuoteInfo5& r);
	static bool parseKCBPTagQuoteInfo5(XT::KCBPTagQuoteInfo5& r, const std::string& s);
	static std::string serializeKCBPTagQuoteInfo5(const XT::KCBPTagQuoteInfo5& r);

 

	static bool fromjsonInstrumentEventInfo(XT::InstrumentEventInfo& r, const std::string& s);
	static std::string tojsonInstrumentEventInfo(const XT::InstrumentEventInfo& r);
	static bool parseInstrumentEventInfo(XT::InstrumentEventInfo& r, const std::string& s);
	static std::string serializeInstrumentEventInfo(const XT::InstrumentEventInfo& r);

	static bool fromjsonTagData(XT::TagData& r, const std::string& s);
	static std::string tojsonTagData(const XT::TagData& r);
	static bool parseTagData(XT::TagData& r, const std::string& s);
	static std::string serializeTagData(const XT::TagData& r);

 

	static bool fromjsonInstrumentInfo(XT::InstrumentInfo& r, const std::string& s);
	static std::string tojsonInstrumentInfo(const XT::InstrumentInfo& r);
	static bool parseInstrumentInfo(XT::InstrumentInfo& r, const std::string& s);
	static std::string serializeInstrumentInfo(const XT::InstrumentInfo& r);

 

	static bool fromjsonTagMsg(XT::TagMsg& r, const std::string& s);
	static std::string tojsonTagMsg(const XT::TagMsg& r);
	static bool parseTagMsg(XT::TagMsg& r, const std::string& s);
	static std::string serializeTagMsg(const XT::TagMsg& r);

	static bool fromjsonOrderInfo(XT::OrderInfo& r, const std::string& s);
	static std::string tojsonOrderInfo(const XT::OrderInfo& r);
	static bool parseOrderInfo(XT::OrderInfo& r, const std::string& s);
	static std::string serializeOrderInfo(const XT::OrderInfo& r);

	static bool fromjsonPBTagMsg(XT::PBTagMsg& r, const std::string& s);
	static std::string tojsonPBTagMsg(const XT::PBTagMsg& r);
	static bool parsePBTagMsg(XT::PBTagMsg& r, const std::string& s);
	static std::string serializePBTagMsg(const XT::PBTagMsg& r);

 

	static bool fromjsonSinaQuoteData(XT::SinaQuoteData& r, const std::string& s);
	static std::string tojsonSinaQuoteData(const XT::SinaQuoteData& r);
	static bool parseSinaQuoteData(XT::SinaQuoteData& r, const std::string& s);
	static std::string serializeSinaQuoteData(const XT::SinaQuoteData& r);

	static bool fromjsonTAParams(XT::TAParams& r, const std::string& s);
	static std::string tojsonTAParams(const XT::TAParams& r);
	static bool parseTAParams(XT::TAParams& r, const std::string& s);
	static std::string serializeTAParams(const XT::TAParams& r);

	static bool fromjsonTDXDayData(XT::TDXDayData& r, const std::string& s);
	static std::string tojsonTDXDayData(const XT::TDXDayData& r);
	static bool parseTDXDayData(XT::TDXDayData& r, const std::string& s);
	static std::string serializeTDXDayData(const XT::TDXDayData& r);

	static bool fromjsonOHLCVData(XT::OHLCVData& r, const std::string& s);
	static std::string tojsonOHLCVData(const XT::OHLCVData& r);
	static bool parseOHLCVData(XT::OHLCVData& r, const std::string& s);
	static std::string serializeOHLCVData(const XT::OHLCVData& r);

	static bool fromjsonDateOHLCV(XT::DateOHLCV& r, const std::string& s);
	static std::string tojsonDateOHLCV(const XT::DateOHLCV& r);
	static bool parseDateOHLCV(XT::DateOHLCV& r, const std::string& s);
	static std::string serializeDateOHLCV(const XT::DateOHLCV& r);

	static bool fromjsonDateTimeOHLCV(XT::DateTimeOHLCV& r, const std::string& s);
	static std::string tojsonDateTimeOHLCV(const XT::DateTimeOHLCV& r);
	static bool parseDateTimeOHLCV(XT::DateTimeOHLCV& r, const std::string& s);
	static std::string serializeDateTimeOHLCV(const XT::DateTimeOHLCV& r);

	static bool fromjsonExchangeInfo(XT::ExchangeInfo& r, const std::string& s);
	static std::string tojsonExchangeInfo(const XT::ExchangeInfo& r);
	static bool parseExchangeInfo(XT::ExchangeInfo& r, const std::string& s);
	static std::string serializeExchangeInfo(const XT::ExchangeInfo& r);

	static bool fromjsonTDXMinData(XT::TDXMinData& r, const std::string& s);
	static std::string tojsonTDXMinData(const XT::TDXMinData& r);
	static bool parseTDXMinData(XT::TDXMinData& r, const std::string& s);
	static std::string serializeTDXMinData(const XT::TDXMinData& r);

	static bool fromjsonQuoteInfo(XT::QuoteInfo& r, const std::string& s);
	static std::string tojsonQuoteInfo(const XT::QuoteInfo& r);
	static bool parseQuoteInfo(XT::QuoteInfo& r, const std::string& s);
	static std::string serializeQuoteInfo(const XT::QuoteInfo& r);

 




 


};//class

}//namespace 
#endif
