#pragma once
#ifndef XT_XTSIMPLEINI_H
#define XT_XTSIMPLEINI_H


/**
* \file XTSimpleIni.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for SimpleIni wrapper.
*
* \description
*	Designed for wrapping class SimpleIni (https://github.com/brofield/simpleini).
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>
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

#include "SimpleIni.h"

#include "StringMap.h"

namespace XT
{

	class XTSimpleIni; //forward declaration
	//////typedef for XTSimpleIni
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<XTSimpleIni> XTSimpleIniPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<XTSimpleIni> XTSimpleIniPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<XTSimpleIni> XTSimpleIniPtr;

#else

	typedef ::std::shared_ptr<XTSimpleIni> XTSimpleIniPtr;
#endif


	typedef ::sf::safe_ptr<XTSimpleIni> XTSimpleIniSafePtr;

	typedef sf::contfree_safe_ptr<XTSimpleIni> XTSimpleIniContFreePtr;
	//////end typedef for XTSimpleIni

class XT_COMMON_API XTSimpleIni
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTSimpleIni();

	/**
	* @brief constructor
	*
	* @param filename
	*/
	XTSimpleIni(const std::string& filename);


	/**
	* @brief default copy constructor
	*/
	XTSimpleIni(const XTSimpleIni& from);// = default;

	/**
	* @brief default copy assignment
	*/
	XTSimpleIni& operator=(const XTSimpleIni& from);// = default;

	/**
	* @brief destructor
	*/
	~XTSimpleIni();

	///@}
public:

	/**
	* @breif load ini file
	*
	* @param f as filename
	*/
	void loadFile(const std::string& f);

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
	* @brief get string value from two sections
	*
	* @param section0
	* @param section1
	* @param name
	* @param default_value
	*
	* @return string value
	*/
	std::string getStringBySections(const std::string& section0, const std::string& section1, const std::string& name, std::string default_value);

	/**
	* @brief get integer value from two sections
	*
	* @param section0
	* @param section1
	* @param name
	* @param default_value
	*
	* @return integer value
	*/
	int getIntegerBySections(const std::string& section0, const std::string& section1, const std::string& name, int default_value);

	/**
	* @brief get double value
	*
	* @param section0
	* @param section1
	* @param name
	* @param default_value
	*
	* @return double value
	*/
	double getRealBySections(const std::string& section0, const std::string& section1, const std::string& name, double default_value);

	/**
	* @brief get bool value
	*
	* @param section0
	* @param section1
	* @param name
	* @param default_value
	*
	* @return bool value
	*/
	bool getBooleanBySections(const std::string& section0,const std::string& section1, const std::string& name, bool default_value);

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
	* @brief has section name
	*
	* @param section
	*
	* @return if it has section
	*/
	bool hasSectionName(const std::string& section);

	/**
	* @brief has key name for section
	*
	* @param section
	* @param key
	*
	* @return if it has key for section
	*/
	bool hasKeyForSection(const std::string& section, const std::string& key);

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
	* @brief get StringMapPtr for section
	*
	* @param section0
	* @param section1
	*
	* @return StringMapPtr
	*/
	StringMapPtr getStringMapPtrForSections(const std::string& section0, const std::string& section1);

	/**
	* @brief set section by StringMapPtr
	*
	* @param section
	* @param stringmapptr
	*/
	void setSectionByStringMapPtr(const std::string& section, const StringMapPtr& smp);

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


	/**
	* @brief update from other XTSimpleIni
	*
	* @param other
	*/
	void updateFromOther(const XTSimpleIniPtr& other);

protected:
	boost::shared_ptr< CSimpleIniA > m_reader;  //CSimpleIniA m_reader;
	int m_errorCode;

};



}//namespace

#endif