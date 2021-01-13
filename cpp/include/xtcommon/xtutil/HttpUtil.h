#pragma once
#ifndef HTTPUTIL_H
#define HTTPUTIL_H

/**
* \file HttpUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a util class for http.
*
* \description
*	Designed for http.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>

#include "XTConfig.h"

#include "LogUtil.h"

#include "Util.h"
//#include "CurlUtil.h"

#include <happyhttp.h>

namespace XT
{
class XT_COMMON_API HttpUtil {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	HttpUtil() {}

	/**
	* @brief copy constructor
	*/
	HttpUtil(const HttpUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	HttpUtil& operator=(const HttpUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~HttpUtil() {}

	///@}
protected:
	
	static std::string m_hostSinaMktQuote; ///< host for sina quote
	static std::string m_pathurlSinaMktQuote; ///< path url for sina quote

	static std::string m_hostSHDJT; ///< host of SHDJT
	static std::string m_pathurlSHDJTStockCodes; ///< path url for SHDJT stock codes

	static std::string m_hostLeverFun; ///< host for leverfun
	static std::string m_pathurlLeverFunTimeOrderForm; ///< path url for leverfun



public:
	/**
	* @brief get host of SHDJT
	*
	* @return host of SHDJT
	*/	 
	static const std::string& getHostSHDJT();

	/**
	* @brief get path url of SHDJT stock codes
	*
	* @return path url of SHDJT stock codes
	*/
	static const std::string& getPathurlSHDJTStockCodes();

	/**
	* @brief get host of leverfun
	*
	* @return host of leverfun
	*/
	static const std::string& getHostLeverFun();

	/**
	* @brief get path url of leverfun
	*
	* @return path url of leverfun
	*/
	static const std::string& getPathurlLeverFunTimeOrderForm();

public:
	/**
	* @brief get url data
	*
	* @param url
	* @param timeoutms as timeout in milliseconds
	* 
	* @return data
	*/
	static std::string getUrlData(const std::string& url, int timeoutms);

public:
	/**
	* @brief get SHDJT stock codes
	*
	* @return SHDJT stock codes
	*/
	static std::string getSHDJTStockCodes();

	/**
	* @brief get sina quote url
	*
	* @param instrids as instrids string separated by comma
	*
	* @return sina quote url
	*/
	static std::string getSinaMktQuoteUrl(const std::string& instrids);

	/**
	* @brief get sina quote string
	*
	* @param instrids as instrids string separated by comma
	*
	* @return sina quote string
	*/
	static std::string getSinaMktQuoteStr(const std::string& instrids);	


};//class

}//namespace

#endif