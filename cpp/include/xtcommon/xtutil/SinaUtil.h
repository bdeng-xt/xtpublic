#pragma once
#ifndef SINA_UTIL_H
#define SINA_UTIL_H

/**
* \file SinaUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a util class for sina data.
*
* \description
*	Designed for sina.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>

#include "XTConfig.h"
#include "happyhttp.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"

#include "LogUtil.h"

#include "Util.h"

#include "HttpUtil.h"


namespace XT
{

class XT_COMMON_API SinaUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	SinaUtil() {}

	/**
	* @brief copy constructor
	*/
	SinaUtil(const SinaUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	SinaUtil& operator=(const SinaUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~SinaUtil() {}

	///@}
protected:
	static int m_bytesCount;///< bytes count
	static std::stringstream m_dataSS; ///< data string stream
	static bool m_isCompleted; ///< is completed

	static std::string m_hostSinaMktQuote;///< host of sina market quote
	static std::string m_pathurlSinaMktQuote; ///< path url of sina market quote
	static const char* m_headerSinaMktQuote[]; ///< header of sina market quote

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
	* @brief get host of sina market quote
	*
	* @return host of sina market quote
	*/
	static const std::string&  getHostSinaMktQuote();

	/**
	* @brief get path url of sina market quote
	*
	* @return path url of sina market quote
	*/
	static const std::string& getPathurlSinaMktQuote();

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
	* @brief get sina market quote url
	*
	* @param instrs as instrids string separated by comma
	*
	* @return sina market quote url
	*/
	static std::string getSinaMktQuoteUrl(const std::string& instrs);

	/**
	* @brief get sina market quote string
	*
	* @param instrs as instrids string separated by comma
	*
	* @return sina market quote string
	*/
	static std::string getSinaMktQuoteStr(const std::string& instrs);

	
};//class

}//namespace

#endif