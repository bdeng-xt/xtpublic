#pragma once
#ifndef XT_STRINGMAP_H
#define XT_STRINGMAP_H

/**
* \file StringMap.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide classes for StringMap.
*
* \description
*	Designed for string map class.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
 

#include "EnumHelper.h"

namespace XT
{

	class StringMap;
	//////typedef for StringMap
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<StringMap> StringMapPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<StringMap> StringMapPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<StringMap> StringMapPtr;

#else

	typedef ::std::shared_ptr<StringMap> StringMapPtr;
#endif


	typedef ::sf::safe_ptr<StringMap> StringMapSafePtr;

	typedef sf::contfree_safe_ptr<StringMap> StringMapContFreePtr;
	//////end typedef for StringMap

	class StringMapList;
	//////typedef for StringMapList
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<StringMapList> StringMapListPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<StringMapList> StringMapListPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<StringMapList> StringMapListPtr;

#else

	typedef ::std::shared_ptr<StringMapList> StringMapListPtr;
#endif


	typedef ::sf::safe_ptr<StringMapList> StringMapListSafePtr;

	typedef sf::contfree_safe_ptr<StringMapList> StringMapListContFreePtr;
	//////end typedef for StringMapList

class XT_COMMON_API StringMap
{
public:
	/** 
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	StringMap();


	/**
	* @brief  copy constructor
	*/
	StringMap(const StringMap& from);// = default;

	/**
	* @brief  copy assignment
	*/
	StringMap& operator=(const StringMap& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~StringMap();

	///@}
public:
	/** 
	* @brief get raw data
	*
	* @return string map data
	*/
	StringMapDataPtr& data();

	/**
	* @brief has key name
	*
	* @param k as key
	*
	* @return it has key
	*/
	bool hasKey(const std::string& k);

	/**
	* @brief get double value by key
	*
	* @param k as key
	*
	* @return double value
	*/
	double getDouble(const std::string& k);

	/**
	* @brief get int value by key
	*
	* @param k key
	*
	* @return int value
	*/
	int getInt(const std::string& k);
	
	/**
	* @brief get int64_t value by key
	*
	* @param k key
	*
	* @return int64_t value
	*/
	int64_t getInt64(const std::string& k);
	
	/**
	* @brief get string value by key
	*
	* @param k key
	*
	* @return string value
	*/
	std::string getString(const std::string& k);

	/**
	* @brief get keys vector
	* 
	*/
	std::vector<std::string> getKeys();
	/**
	* @brief get keys with prefix
	*
	* @param prefix name starts with
	*
	* @return vector of keys
	*/
	std::vector<std::string> getKeysWithPrefix(const std::string& prefix);
	
	/**
	* @brief add key and value pair
	*
	* @param k key
	* @param v value
	*/
	void add(const std::string& k, const std::string& v);

	/**
	* @brief get size
	*
	* @return size
	*/
	int size();

	/**
	* @brief remove key
	*
	* @param k key
	*/
	void remove(const std::string& k);
	
	/**
	* @brief add from other stringmap
	*
	* @param other 
	*/
	void updateFromOther(const StringMapPtr & other);

	/**
	* @brief to json string
	*
	* @return json string
	*/
	std::string toJsonStr();

	/**
	* @brief to csv string
	*
	* @return comma separated key value pairs string
	*/
	std::string toCsvStr();

	/**
	* @brief construct from csv string or json string
	*
	* @param s as input string
	*/
	void fromStr(const std::string& s);

	/**
	* @brief create
	*
	* @return StringMap pointer
	*/
	static StringMapPtr create();
protected: 
	StringMapDataPtr m_data;///< data



};//class XT_COMMON_API StringMap



class XT_COMMON_API StringMapList
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	StringMapList();


	/**
	* @brief  copy constructor
	*/
	StringMapList(const StringMapList& from);// = default;

									 /**
									 * @brief  copy assignment
									 */
	StringMapList& operator=(const StringMapList& from);// = default;

												/**
												* @brief destructor
												*/
	virtual ~StringMapList();

	///@}

public:
	/**
	* @brief get ith item
	* 
	* @return ith item
	*/
	StringMapPtr& at(int i);

	/**
	* @brief get size of list
	* 
	* @retur size of list
	*/
	int size();

	/**
	* @brief add StringMapPtr
	*
	* @param smp
	*/
	void add(StringMapPtr& smp);

	/**
	* @brief clear all
	*
	*/
	void clear();


protected:
	std::vector<StringMapPtr > m_list;
	StringMapPtr m_emptyStringMap;

};


}//namespace XT

#endif