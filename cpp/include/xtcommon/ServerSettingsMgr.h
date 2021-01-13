#pragma once
#ifndef XT_SERVERSETTINGSMGR_H
#define XT_SERVERSETTINGSMGR_H

/**
* \file ServerSettingsMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all server settings.
*
* \description
*	Designed for managing all server settings.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>


#include "XTConfig.h"

#include "LogUtil.h"


#include "TagDataWrapper.h"

#include "INIUtil.h"

#include "Util.h"
#include "FileUtil.h"
//#include "SqliteUtil.h"
//#include "MongoUtil.h"

namespace XT {

 

class XT_COMMON_API ServerSettingsMgr {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ServerSettingsMgr();

	/**
	* @brief default copy constructor
	*/
	ServerSettingsMgr(const ServerSettingsMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	ServerSettingsMgr& operator=(const ServerSettingsMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~ServerSettingsMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static ServerSettingsMgr* getInstance();

public:
	/**
	* @brief get data
	* 
	* @return data
	*/
	TagDataWrapperPtr& data();

	/**
	* @brief get file name
	*
	* @return file name
	*/
	const std::string& getFileName();

	/**
	* @brief set file name
	*
	* @param s as file name
	*/
	void setFileName(const std::string& s);

	/**
	* @brief load data from file name
	*
	* @param s as file name
	*/
	void loadFromFile(const std::string& s);

	/**
	* @brief save data to file name
	*
	* @param s as file name
	*/
	void saveToFile(const std::string& s);

	/**
	* @brief create a default template servers file
	*/
	void createDefaultFile();

	/**
	* @brief add default settings
	*/
	void addDefaultSettings();

	/**
	* @brief check if it has string value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return if string value exists
	*/
	bool hasString(const std::string& settingname, int tag);

	/**
	* @brief set string value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	* @param v as string value
	*/
	void setString(const std::string& settingname, int tag, const std::string& v);

	/**
	* @brief get string value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return string value
	*/
	std::string getString(const std::string& settingname, int tag);

	/**
	* @brief check if it has int value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return if int value exists
	*/
	bool hasInt32(const std::string& settingname, int tag);

	/**
	* @brief set int value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	* @param v as int value
	*/
	void setInt32(const std::string& settingname, int tag, int v);

	/**
	* @brief get int value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return int value
	*/
	int getInt32(const std::string& settingname, int tag);

	/**
	* @brief check if it has double value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return if double value exists
	*/
	bool hasDouble(const std::string& settingname, int tag);

	/**
	* @brief set double value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	* @param v as double value
	*/
	void setDouble(const std::string& settingname, int tag, double v);

	/**
	* @brief get double value with tag for instrument
	*
	* @param settingname as setting name
	* @param tag
	*
	* @return double value
	*/
	double getDouble(const std::string& settingname, int tag);

	/**
	* @brief check if it has setting name or not
	*
	* @param s as setting name
	*
	* @return if setting name exists
	*/
	bool hasSettingName(const std::string& s);

	/**
	* @brief remove settings with name
	*
	* @param s as setting name
	*/
	void removeSettingByName(const std::string& s);

	/**
	* @brief get setting names
	*
	* @param apitypename as api type name
	* @param mdtrdtype as type mask
	*
	* @return vector of setting names
	*/
	std::vector<std::string> getSettingNames(const std::string& apitypename, int mdtrdtype);

	/**
	* @brief get setting names by account type
	*
	* @param mask as api type mask
	* @param mdtrdtype as type mask
	*
	* @return vector of settng names
	*/
	std::vector<std::string> getSettingNamesByAccountTypeMask(int mask, int mdtrdtype);

public:
	
protected:
	std::string m_fileName; ///< file name
	TagDataWrapperPtr m_data; ///< data



	 


};//class ServerSettingsMgr

}//namespace

#endif