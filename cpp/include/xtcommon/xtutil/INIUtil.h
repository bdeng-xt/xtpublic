#pragma once
#ifndef XT_INI_UTIL_H
#define XT_INI_UTIL_H


/**
* \file INIUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for ini file utility.
*
* \description
*	Designed for utility functions of an ini file.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <boost/shared_ptr.hpp>
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
 

#include "INIReader.h"
#include "StringMap.h"
#include "XTINIReader.h"

namespace XT
{

 

class XT_COMMON_API INIUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	INIUtil() {}

	/**
	* @brief copy constructor
	*/
	INIUtil(const INIUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	INIUtil& operator=(const INIUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~INIUtil() {}

	///@}
public:
	/**
	* @brief get reader for file
	*
	* @param s as filename
	*
	* @return XTINIReader
	*/
	static XTINIReaderPtr getReaderForFile(const std::string& s);
 
}; //class 

}//namespace

#endif
