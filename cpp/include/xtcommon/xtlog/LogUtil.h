#pragma once
#ifndef XT_LOGUTIL_H
#define XT_LOGUTIL_H

/**
* \file LogUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for logging.
*
* \description
*	Designed for managing logging utilities.
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

#include "XTConfig.h"

#ifndef XT_DISABLE_LOG
#include <log4z.h>
#endif

namespace XT
{



class XT_COMMON_API LogUtil
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	LogUtil() {}
	/**
	* @brief disable copy constructor
	*/
	LogUtil(const LogUtil& from) {}// = delete;
	/**
	* @brief disable copy assignment
	*/
	const LogUtil& operator=(const LogUtil& from) { return *this; } // = delete;
	/**
	* @brief destructor
	*/
	virtual ~LogUtil() {}
	///@}
public:
	/**
	* @brief log information into log file
	*
	* @param logstr as string information
	*/
	static void logInfo(const std::string& logstr);

	/**
	* @brief log warning information into log file
	*
	* @param logstr as string warning
	*/
	static void logWarning(const std::string& logstr);

	/**
	* @brief log error information into log file
	*
	* @param logstr as string error
	*/
	static void logError(const std::string& logstr);

	/**
	* @brief log debug information into log file
	*
	* @param logstr as string debug information
	*/
	static void logDebug(const std::string& logstr);

/////////////////
/**
* @brief plain log information into log file
*
* @param logstr as string information
*/
	static void plogInfo(const std::string& logstr);

	/**
	* @brief plain log warning information into log file
	*
	* @param logstr as string warning
	*/
	static void plogWarning(const std::string& logstr);

	/**
	* @brief plain log error information into log file
	*
	* @param logstr as string error
	*/
	static void plogError(const std::string& logstr);

	/**
	* @brief plain log debug information into log file
	*
	* @param logstr as string debug information
	*/
	static void plogDebug(const std::string& logstr);




}; //class



 

}//namespace XT


#endif