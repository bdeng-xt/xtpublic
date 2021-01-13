#pragma once
#ifndef YAHOO_UTIL_H
#define YAHOO_UTIL_H

/**
* \file YahooUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a util class for Yahoo.
*
* \description
*	Designed for Yahoo.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>

#include "XTConfig.h"
#include <happyhttp.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "LogUtil.h"

#include "Util.h"
#include "EnumUtil.h"

#include "happyhttp.h"
#include "HttpUtil.h"


namespace XT
{

class XT_COMMON_API YahooUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	YahooUtil() {}

	/**
	* @brief copy constructor
	*/
	YahooUtil(const YahooUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	YahooUtil& operator=(const YahooUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~YahooUtil() {}

	///@}
protected:
	static int m_bytesCount;///< bytes count
	static std::stringstream m_dataSS;///< data string stream
	static bool m_isCompleted;///< is completed

	static std::string m_hostYahooQuote;///< host of yahoo market quote
	static std::string m_pathurlYahooQuote;///< path url of yahoo market quote

	static std::string m_hostYahooHist; ///< host of yahoo hist quote
	static std::string m_pathurlYahooHist;///< path url of yahoo hist quote

public:
	/**
	* @brief get bytes count
	*
	* @return bytes count
	*/
	static int getBytesCount();

	/**
	* @brief get data string
	*
	* @return data string
	*/
	static std::string getDataStr();

	/**
	* @brief check if it is completed
	*
	* @return if it is completed
	*/
	static bool isCompleted();

	/**
	* @brief get host of yahoo market quote
	*
	* @return host of yahoo market quote
	*/
	static const std::string& getHostYahooQuote();

	/**
	* @brief get path url of yahoo market quote
	*
	* @return path url of yahoo market quote
	*/
	static const std::string& getPathurlYahooQuote();

	/**
	* @brief get host of yahoo hist quote
	*
	* @return host of yahoo hist quote
	*/
	static const std::string& getHostYahooHist();
	/**
	* @brief get path url of yahoo hist quote
	*
	* @return path url of yahoo hist quote
	*/
	static const std::string& getPathurlYahooHist();

protected:
	/**
	* @brief on begin event
	*/
	static void onBegin(const Response* r, void* userdata);

	/**
	* @brief on data event
	*/
	static void onData(const Response* r, void* userdata, const unsigned char* data, int n);

	/**
	* @brief on complete event
	*/
	static void onComplete(const Response* r, void* userdata);	

public:
	/**
	* @brief get yahoo market quote url
	*
	* @param instrs as instrids string separated by comma
	* @param quoteTypes
	*
	* @return yahoo market quote url
	*/
	static std::string getYahooQuoteUrl(const std::string& instrs, const std::string& quoteTypes);

	/**
	* @brief get yahoo market quote string
	*
	* @param instrs as instrids string separated by comma
	* @param quoteTypes
	*
	* @return yahoo market quote string
	*/
	static std::string getYahooQuote(const std::string& instrs, const std::string& quoteTypes);

	/**
	* @brief get yahoo hist data url
	*
	* @param instrs as instrids string separated by comma
	* @param startIntdate
	* @param endIntdate
	* @param rangeType
	*
	* @return yahoo hist data url
	*/
	static std::string getYahooHistUrl(const std::string& instr, int startIntdate, int endIntdate, const std::string& rangeType);

	/**
	* @brief get yahoo hist data string
	*
	* @param instrs as instrids string separated by comma
	* @param startIntdate
	* @param endIntdate
	* @param rangeType
	*
	* @return yahoo hist data string
	*/
	static std::string getYahooHist(const std::string& instr, int startIntdate, int endIntdate, const std::string& rangeType);

///////
public:
	/**
	* @brief get yahoo quote type string
	* 
	* @param yqType as yahoo quote type
	*
	* @retrun yahoo quote type string
	*/
	static std::string getYahooQuoteTypeStr(YahooQuoteType::enumtype yqType);
	/**
	* @brief get yahoo range type string
	*
	* @param yqType as yahoo range type
	*
	* @retrun yahoo range type string
	*/
	static std::string getYahooRangeTypeStr(YahooRangeType::enumtype yrType);

	/**
	* @brief get yahoo quote type string
	*
	* @param yqTypes as vector of yahoo quote types
	*
	* @retrun yahoo quote type string
	*/
	static std::string getYahooQuoteTypesStr(std::vector<YahooQuoteType::enumtype> yqTypes);

	/**
	* @brief get all yahoo quote types
	*
	* @return vector of all yahoo quote types
	*/
	static std::vector<YahooQuoteType::enumtype> getAllYahooQuoteTypes();

	/**
	* @brief get all yahoo quote types string
	*
	* @return string of all yahoo quote types separated by comma
	*/
	static std::string getAllYahooQuoteTypesStr();

};//class

}//namespace


#endif