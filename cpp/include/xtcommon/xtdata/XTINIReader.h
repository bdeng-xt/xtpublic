#pragma once
#ifndef XT_XTINIREADER_H
#define XT_XTINIREADER_H


/**
* \file XTINIReader.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for ini file reader wrapper.
*
* \description
*	Designed for class of an ini file.
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
 
#include "safe_ptr.h"

#include "INIReader.h"

#include "StringMap.h"

namespace XT
{

class XT_COMMON_API XTINIReader
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTINIReader();

	/**
	* @brief constructor
	*
	* @param filename
	*/
	XTINIReader(const std::string& filename);

	/**
	* @brief default copy constructor
	*/
	XTINIReader(const XTINIReader& from);// = default;

	/**
	* @brief default copy assignment
	*/
	XTINIReader& operator=(const XTINIReader& from);// = default;

	/**
	* @brief destructor
	*/
	~XTINIReader();

	///@}
public:

	/**
	* @brief get filename
	*/
	const std::string& getFileName();

	/**
	* @brief set filename
	*/
	void setFileName(const std::string& fname);

	/**
	* @brief get parse error
	*
	* @return error code
	*/
	int getParseError();

	/**
	* @brief get sections string
	*
	* @return sections string
	*/
	std::string getSectionsStr();

	/**
	* @brief get names string
	*
	* @return names string
	*/
	std::string getNamesStr(const std::string& section);

	/**
	* @brief get string value
	*
	* @param section
	* @param name
	* @param default_value
	* 
	* @return string value
	*/
	std::string getString(const std::string& section, const std::string& name, std::string default_value);

	/**
	* @brief get integer value
	*
	* @param section
	* @param name
	* @param default_value
	*
	* @return integer value
	*/
	int getInteger(const std::string& section, const std::string& name, int default_value);

	/**
	* @brief get double value
	*
	* @param section
	* @param name
	* @param default_value
	*
	* @return double value
	*/
	double getReal(const std::string& section, const std::string& name, double default_value);

	/**
	* @brief get bool value
	*
	* @param section
	* @param name
	* @param default_value
	*
	* @return bool value
	*/
	bool getBoolean(const std::string& section, const std::string& name, bool default_value);

	/**
	* @brief get sections
	*
	* @return vector of sections
	*/
	std::vector<std::string> getSections();

	/**
	* @brief get sections
	*
	* @param prefix
	*
	* @return vector of sections
	*/
	std::vector<std::string> getSectionsWithPrefix(const std::string& prefix);

	/**
	* @brief get names
	*
	* @param section
	*
	* @return vector of names
	*/
	std::vector<std::string> getNamesForSection(const std::string& section);

	/**
	* @brief get names
	*
	* @param section
	* @param prefix
	*
	* @return vector of names
	*/
	std::vector<std::string> getNamesWithPrefixForSection(const std::string& section, const std::string& prefix);

	/**
	* @brief get StringMapPtr for section
	*
	* @param section
	*
	* @return StringMapPtr
	*/
	StringMapPtr getStringMapPtrForSection(const std::string& section);

	/**
	* @brief get StringMapPtr vector for section with prefix
	*
	* @param prefix
	*
	* @return StringMapPtr vector
	*/
	std::vector<StringMapPtr > getStringMapPtrVectorForSectionWithPrefix(const std::string& prefix);


	/**
	* @brief get StringMapPtr vector for names with prefix for section
	*
	* @param section
	* @param prefix for keyname
	*
	* @return StringMapPtr vector
	*/
	std::vector<StringMapPtr > getStringMapPtrVectorForNamesWithPrefixForSection(const std::string& section, const std::string& prefix);


	/**
	* @brief write to file
	*
	* @param filename
	*
	*/
	void writeToFile(const std::string& filename);

	/**
	* @brief set value
	*
	* @param section
	* @param name
	* @param valuestr as value string
	*
	*/
	void setValue(const std::string& section, const std::string& name, const std::string& valuestr);

	

protected:
	boost::shared_ptr<INIReader> m_reader; // INIReader m_reader; ///< ini reader

};//class XT_COMMON_API XTINIReader
  //////typedef for XTINIReader
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<XTINIReader> XTINIReaderPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<XTINIReader> XTINIReaderPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<XTINIReader> XTINIReaderPtr;

#else

typedef ::boost::shared_ptr<XTINIReader> XTINIReaderPtr;
#endif


typedef ::sf::safe_ptr<XTINIReader> XTINIReaderSafePtr;

typedef sf::contfree_safe_ptr<XTINIReader> XTINIReaderContFreePtr;
//////end typedef for XTINIReader
 

}//namespace

#endif
