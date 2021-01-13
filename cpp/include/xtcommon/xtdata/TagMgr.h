#pragma once
#ifndef XT_TAGMGR_H
#define XT_TAGMGR_H

/**
* \file TagMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide help functions for tags.
*
* \description
*	Designed for use for all tags and their utilities.
*/

#include <assert.h>
#include <string>
#include <sstream>

#include <cstdint>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include "XTConfig.h"
//#include "FIXData.h"
#include "XTData.pb.h"
//#include "XTData.h"
#include "EnumUtil.h"

namespace XT {

class XT_COMMON_API TagMgr
{


public:
	/**
	* @name constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TagMgr();

	/**
	* @brief default copy constructor
	*/
	TagMgr(const TagMgr& from);// = default;

	/**
	* @brief default copy assignment
	*/
	TagMgr& operator=(const TagMgr& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TagMgr();

	///@}

	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static TagMgr* getInstance();
public:
	/**
	* @brief add tag name
	* 
	* @tag as integer
	* @name as string
	*/
	void addTagName(int tag, const std::string& name);
 
 
	/**
	* @brief get tag for name
	*
	* @param name as string
	*
	* @return tag integer value
	*/
	int getTagForName(const std::string & name);

	/**
	* @brief get name for tag
	*
	* @param tag as integer
	*
	* @return name for tag
	*/
	const std::string& getNameForTag(int tag);

protected:
	std::string m_EmptyString; ///< empty string
	int m_ExtraTagCutoff; ///< extra tag integer value cutoff
protected:
	boost::unordered_map<int, std::string> m_extraTagToNameMap; ///< extra tag to name map
	boost::unordered_map<std::string, int> m_extraNameToTagMap; ///< extra name to tag map


};

} //namespace XT

#endif