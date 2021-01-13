#pragma once
#ifndef XT_TAGDATAWRAPPER_H
#define XT_TAGDATAWRAPPER_H

/**
* \file TagDataWrapper.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a wrapper class for TagData.
*
* \description
*	Designed for handling TagData.
*/


#include <cstdint>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <boost/smart_ptr.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"

#include "XTData.pb.h"
//#include <XTData.h>
//#include "EnumUtil.h"
#include "TagMgr.h"

#include "json_spirit/json_spirit.h"
#include "Util.h"
#include "LogUtil.h"

namespace XT {

	class TagDataWrapper;
	//////typedef for TagDataWrapper
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<TagDataWrapper> TagDataWrapperPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<TagDataWrapper> TagDataWrapperPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<TagDataWrapper> TagDataWrapperPtr;

#else

	typedef ::boost::shared_ptr<TagDataWrapper> TagDataWrapperPtr;
#endif


	typedef ::sf::safe_ptr<TagDataWrapper> TagDataWrapperSafePtr;

	typedef sf::contfree_safe_ptr<TagDataWrapper> TagDataWrapperContFreePtr;
	//////end typedef for TagDataWrapper

class XT_COMMON_API TagDataWrapper
{

protected:
	/**
	*  @name Static Variables
	*/
	///@{
	static XT::TagData s_EmptyTagData;//	static TagDataPtr s_EmptyTagData;	 
	///@}

public:
	static const XT::TagData& getEmptyTagData();
public:
	/** 
	* @name Constructor  and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*/
	TagDataWrapper();


	/**
	* @brief default copy constructor
	*/
	TagDataWrapper(const TagDataWrapper& from); // = default;

	/**
	* @brief default copy assignment
	*/
	TagDataWrapper& operator=(const TagDataWrapper& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TagDataWrapper() {};

	///@}

	/** 
	* @name Getters and Setters for Top Level  
	*/
	///@{

	/**
	* @brief has data
	*
	* @return if it has data
	*/
	bool hasData();

	/**
	* @brief get String by tag
	*
	* @param tag
	*
	* @return value with tag
	*/
	const std::string& getString(int32_t tag);

	/**
	* @brief has String with tag
	*
	* @param tag
	*
	* @return if it has string value with tag
	*/
	bool hasString(int32_t tag);

	/**
	* @brief set String with tag
	*
	* @param tag
	* @param v as string value
	*/
	void setString(int32_t tag, const std::string& v);

	/**
	* @brief get named string by name
	*
	* @param name as key name
	*
	* @return value string with key name
	*/
	const std::string& getNamedString(const std::string& name);

	/**
	* @brief has named string with name
	*
	* @param name as key name
	*
	* @return if it has string name with name
	*/
	bool hasNamedString(const std::string& name);

	/**
	* @brief set named string
	*
	* @name as key name
	* @param v as value string
	*/
	void setNamedString(const std::string& name, const std::string& v);

	
	/**
	* @brief get named double by name
	*
	* @param name as key name
	*
	* @return double value
	*/
	double getNamedDouble(const std::string& name);

	/**
	* @brief set named double
	*
	* @param name
	* @param v as double value
	*/
	void setNamedDouble(const std::string& name, double v);

	
	/**
	* @brief get named int by name
	* 
	* @param name
	* 
	* @return named string value
	*/
	int getNamedInt32(const std::string& name);

	/**
	* @brief set named int
	*
	* @param name
	* @param named integer value
	*/
	void setNamedInt32(const std::string& name, int v);


	/**
	* @brief get named int64_t by name
	*
	* @param name
	*
	* @return integer value
	*/
	int64_t getNamedInt64(const std::string& name);

	/**
	* @brief set named int64_t
	*
	* @param name
	* @param v as int64_t value
	*/
	void setNamedInt64(const std::string& name, int64_t v);


	/**
	* @brief get Double with tag
	*
	* @param tag
	*
	* @return double value
	*/
	double getDouble(int32_t tag);

	/**
	* @brief has Double with tag
	*
	* @param tag
	*
	* @return if it has tagged double 
	*/
	bool hasDouble(int32_t tag);

	/**
	* @brief set Double with tag
	*
	* @param tag
	* @param v as double value
	*/
	void setDouble(int32_t tag, double v);

	/**
	* @brief get int32_t value with tag
	*
	* @param tag
	*
	* @return int value
	*/
	int32_t getInt32(int32_t tag);

	/**
	* @brief has int32_t value with tag
	*
	* @param tag
	*
	* @return if it has tagged int
	*/
	bool hasInt32(int32_t tag);

	/**
	* @brief set int32_t value with tag
	*
	* @param tag
	* @param v as int value
	*/
	void setInt32(int32_t tag, int32_t v);

	/**
	* @brief get int64_t value with tag
	* 
	* @param tag
	*
	* @return int64_t value
	*/
	int64_t getInt64(int32_t tag);

	/**
	* @brief has int64_t value with tag
	* 
	* @param tag
	*
	* @return if it has tagged int64_t
	*/
	bool hasInt64(int32_t tag);

	/**
	* @brief set int64_t value with tag
	*
	* @param tag
	* @param v as int64_t value
	*/
	void setInt64(int32_t tag, int64_t v);


	/**
	* @brief get TagData by name
	* 
	* @param s as object name
	*
	* @return tagdata
	*/
	TagData& getTagDataByName(const std::string& s);

	/**
	* @brief has TagData with name
	* 
	* @param s as name
	*
	* @return if it has tagged object
	*/
	bool hasTagDataWithName(const std::string& s);

	/**
	* @brief set TagData with name
	* 
	* @param s as name
	* @param v as object data
	*/
	void setTagDataWithName(const std::string& s, const TagData& v);

	///@}

	/** @name Getters and Setters for a path  
	*
	*/
	///@{

	/**
	* @brief has int32_t value by path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return if it has tagged int under path
	*/
	bool hasInt32ByPath(const std::string& p, int32_t tag);

	/**
	* @brief get int32_ t value by path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return int value
	*/
	int32_t getInt32ByPath(const std::string& p, int32_t tag);

	/**
	* @brief set int32_t value with path and tag
	*
	* @param p as path
	* @param tag
	* @param v as integer value
	*/
	void setInt32ByPath(const std::string& p, int32_t tag, int32_t v);


	/**
	* @brief has int64_t value by path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return if int64_t value exists
	*/
	bool hasInt64ByPath(const std::string& p, int32_t tag);

	/**
	* @brief get int64_t value by path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return int64_t value
	*/
	int64_t getInt64ByPath(const std::string& p, int32_t tag);

	/**
	* @brief set int64_t value with path and tag
	*
	* @param p as path
	* @param tag
	* @param v as int64_t value
	*/
	void setInt64ByPath(const std::string& p, int32_t tag, int64_t v);

	/**
	* @brief has double value with path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return if double value exists
	*/
	bool hasDoubleByPath(const std::string& p, int32_t tag);

	/**
	* @brief get double value with path and tag
	*
	* @param p as path
	* @param tag
	* 
	* @return double value
	*/
	double getDoubleByPath(const std::string& p, int32_t tag);

	/**
	* @brief set double value with path and tag
	*
	* @param p as path
	* @param tag
	* @param v as double value
	*/
	void setDoubleByPath(const std::string& p, int32_t tag, double v);

	/**
	* @brief has string value with path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return if string value exists
	*/
	bool hasStringByPath(const std::string& p, int32_t tag);

	/**
	* @brief get string value with path and tag
	*
	* @param p as path
	* @param tag
	*
	* @return string value
	*/
	const std::string& getStringByPath(const std::string& p, int32_t tag);

	/**
	* @brief set string value with tag and tag
	*
	* @param p as path
	* @param tag
	* @param v as string value
	*/
	void setStringByPath(const std::string& p, int32_t tag, const std::string& v);


	/**
	* @brief has named string value with path and name
	*
	* @param p as path
	* @param name
	*
	* @return if named string value exists
	*/
	bool hasNamedStringByPath(const std::string& p, const std::string& name);

	/**
	* @brief get named string value with path and name
	*
	* @param p as path
	* @param name
	*
	* @return named string value
	*/
	const std::string& getNamedStringByPath(const std::string& p, const std::string& name);

	/**
	* @brief set named string value with tag and name
	* 
	* @param p as path
	* @param name
	* @param v as string value
	*/
	void setNamedStringByPath(const std::string& p, const std::string& name, const std::string& v);

	/**
	* @brief get subdirs under path
	*
	* @param p as path
	*
	* @return vector of subdirectories
	*/
	std::vector<std::string> getSubdirsUnderPath(const std::string& p);

	///@}


	/**
	*  @name Update Functions
	*/
	///@{

	/**
	* @brief add other TagDataWrapper
	*/
	void addOther(const TagDataWrapperPtr& other);

	/**
	* @brief update from another tag data wrapper
	*
	* @param other as other TagDataWrapper pointer
	*/
	void updateFromOther(const TagDataWrapperPtr& other);

	/**
	* @brief update from TagData
	*
	* @param td as TagData
	*/
	void updateFromOtherTagData(const XT::TagData& td);

	/**
	* @brief clone
	*
	* @return cloned TagDataWrapper pointer
	*/
	TagDataWrapperPtr clone();

	///@}


	/** 
	* @name String Functions
	*/
	///@{

	/**
	* @brief get json str
	*
	* @return json string
	*/
	std::string toJsonStr();

	/**
	* @brief get pretty json str
	*
	* @return pretty json string
	*/
	std::string toPrettyJsonStr();

	///@}

	/** 
	* @name Static Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @return TagDataWrapper pointer
	*/
	static TagDataWrapperPtr create();

	///@}

	/**
	*  @name Static Functions for Converting between TagData and JsonSpirit
	*/
	///@{

	/**
	* @brief test if TagData has data
	*
	* @param d as tagdata
	*/
	static bool TagDataHasData(const TagData& d);

	/**
	* @brief convert TagData to json spirit object
	* 
	* @param d as tagdata
	* @param doc as json_spirit document
	*/
	static void TagData2JsonSpiritObject(const TagData& d, json_spirit::mObject & doc);

	/**
	* @brief convert json spirit object to TagData
	*
	* @param doc as json_spirit document
	* @param d as tagdata
	*/
	static void JsonSpiritObject2TagData(const json_spirit::mObject & doc, TagData& d);
	///@}


	/** 
	* @name Static Functions for Converting between TagDataWrapper and String
	*/
	///@{
	/**
	* @brief print TagDataWrapper to json string
	*
	* @param tdw as TagDataWrapper pointer
	*
	* @return json string
	*/
	static std::string toJsonStrForTDW(const TagDataWrapperPtr & tdw);

	/**
	* @brief print TagDataWrapper to pretty json string
	*
	* @param tdw as TagDataWrapper pointer
	*
	* @return pretty json string
	*/
	static std::string toPrettyJsonStrForTDW(const TagDataWrapperPtr & tdw);

	/**
	* @brief convert json string to TagDataWrapper
	* 
	* @param s as input json string
	*
	* @return TagDataWrapper pointer
	*/
	static TagDataWrapperPtr fromJsonStr(const std::string& s);

	///@}

	/** 
	* @name Static Functions for Converting between TagDataWrapper and File
	*/
	///@{

	/**
	* @brief print TagDataWrapper to json file
	*
	* @param tdw as TagDataWrapper pointer
	* @param filename
	*/
	static void toJsonFile(const TagDataWrapperPtr& tdw, const std::string& filename);

	 
	/**
	* @brief read json from filename
	* 
	* @filename
	*
	* @return TagDataWrapper pointer
	*/
	static TagDataWrapperPtr fromJsonFile(const std::string& filename);
	///@}

	/** 
	* @name Static Getting and Setting Functions
	*/
	///@{

	/**
	* @brief has int32_t value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return if int value exists
	*/
	static bool hasInt32ByPathForTagData(const TagData& tagData, const std::string& p, int32_t tag);

	/**
	* @brief get int32_t value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return int value
	*/
	static int32_t getInt32ByPathForTagData(const TagData& tagData,const std::string& p, int32_t tag);

	/**
	* @brief has int64_t value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return if int64_t value exists
	*/
	static bool hasInt64ByPathForTagData(const TagData& tagData, const std::string& p, int32_t tag);

	/**
	* @brief get int64_t value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return int64_t value
	*/
	static int64_t getInt64ByPathForTagData(const TagData& tagData,const std::string& p, int32_t tag);
	
	
	/**
	* @brief has double value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return if double value exists
	*/
	static bool hasDoubleByPathForTagData(const TagData& tagData, const std::string& p, int32_t tag);

	/**
	* @brief get double value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return double value
	*/
	static double getDoubleByPathForTagData(const TagData& tagData,const std::string& p, int32_t tag);


	/**
	* @brief has string value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	*
	* @return if string value exists
	*/
	static bool hasStringByPathForTagData(const TagData& tagData, const std::string& p, int32_t tag);

	/**
	* @brief get string value by path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param name
	*
	* @return string value
	*/
	static const std::string& getStringByPathForTagData(const TagData& tagData,const std::string& p, int32_t tag);


	/**
	* @brief has named string by path and name from TagData
	*
	* @param tagData
	* @param p as path
	* @param name
	*
	* @return string value exists
	*/
	static bool hasNamedStringByPathForTagData(const TagData& tagData, const std::string& p, const std::string& name);

	/**
	* @brief get named string by path and name from TagData
	*
	* @param tagData
	* @param p as path
	* @param name
	*
	* @return string value
	*/
	static const std::string& getNamedStringByPathForTagData(const TagData& tagData, const std::string& p, const std::string& name);

	/**
	* @brief get nested TagData by path
	*
	* @param td as tagdata
	* @param p as path
	* @param name
	* 
	* @return tagdata
	*/
	static const TagData& getNestedTagDataByPathForTagData(const TagData& td, const std::string& p, const std::string& name);

	/**
	* @brief set int32_t value with path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	* @param v as int value
	*/
	static void setInt32ByPathForTagData(TagData& tagData, const std::string& p, int32_t tag, int32_t v);

	/**
	* @brief set int64_t value with path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	* @param v as int64_t value
	*/
	static void setInt64ByPathForTagData(TagData& tagData, const std::string& p, int32_t tag, int64_t v);

	/**
	* @brief set double value with path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	* @param v as double value
	*/
	static void setDoubleByPathForTagData(TagData& tagData, const std::string& p, int32_t tag, double v);

	/**
	* @brief set string value with path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param tag
	* @param v as string value
	*/
	static void setStringByPathForTagData(TagData& tagData, const std::string& p, int32_t tag, const std::string& v);

	/**
	* @brief set named string value with path and tag from TagData
	*
	* @param tagData
	* @param p as path
	* @param name
	* @param v as string value
	*/
	static void setNamedStringByPathForTagData(TagData& tagData, const std::string& p, const std::string& name, const std::string& v);

	/**
	* @brief set nested TagData with path and name from TagData
	*
	* @param td as tagdata
	* @param p as path
	* @param name for key name
	* @param tdNested as nested object
	*/
	static void setNestedTagDataByPathForTagData(TagData& td, const std::string& p, const std::string& name, const TagData& tdNested);

	/**
	* @brief get all keys with path from TagData
	*
	* @param tagData
	* @param p as path
	*
	* @return vector of subdirectories
	*/
	static std::vector<std::string> getSubdirsUnderPathForTagData(const TagData& tagData, const std::string& p);

	///@}

	/** 
	* @name Static Updating Functions
	*/
	///@{

	/**
	* @brief update data from other TagDataPtr
	*/
//	void updateFromOther(TagDataWrapperPtr other);

	/**
	* @brief add TagData from other TagDataPtr
	*
	* @tagData 
	* @other as other tagdata
	*/
	static void addTagDataFromOther(TagData& tagData, const TagData& other);

	///@}


	/** 
	* @name TagData Pointer
	*/
	///@{
	/**
	* @brief get tag data ptr
	*
	* @return tagdata
	*/
	TagData& data();

	///@}

protected:
	TagData m_data; ///< tag data



}; //end class TagDataWrapper


} //end namespace XT


#endif
