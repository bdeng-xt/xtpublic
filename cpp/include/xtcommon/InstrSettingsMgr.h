#pragma once
#ifndef XT_INSTRSETTINGSMGR_H
#define XT_INSTRSETTINGSMGR_H

/**
* \file InstrSettingsMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all instrument settings.
*
* \description
*	Designed for managing all instrument settings.
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

 

class XT_COMMON_API InstrSettingsMgr {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	InstrSettingsMgr();

	/**
	* @brief default copy constructor
	*/
	InstrSettingsMgr(const InstrSettingsMgr& from) {} // = delete;

	/**
	* @brief default copy assignment
	*/
	InstrSettingsMgr& operator=(const InstrSettingsMgr& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~InstrSettingsMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static InstrSettingsMgr* getInstance();

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
	* @brief get indicator path
	*
	* @return path string
	*/
	const std::string& getTAIndicatorsPath();

	/**
	* @brief create a default template servers file
	*/
	void createDefaultFile();

	/**
	* @brief check if there is a string value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return if string value exists
	*/
	bool hasString(const std::string& instrid, int tag);
	
	/**
	* @brief get string value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	* @param v as string value
	*/
	void setString(const std::string& instrid, int tag, const std::string& v);

	/**
	* @brief get string value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return string value
	*/
	std::string getString(const std::string& instrid, int tag);

	/**
	* @brief check if there is a int value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return if int value exists
	*/
	bool hasInt32(const std::string& instrid, int tag);

	/**
	* @brief get int value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	* @param v as int value
	*/
	void setInt32(const std::string& instrid, int tag, int v);

	/**
	* @brief get int value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return int value
	*/
	int getInt32(const std::string& instrid, int tag);

	/**
	* @brief check if there is a double value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return if double value exists
	*/
	bool hasDouble(const std::string& instrid, int tag);

	/**
	* @brief set string value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	* @param v as double value
	*/
	void setDouble(const std::string& instrid, int tag, double v);

	/**
	* @brief get double value with tag for instrument
	*
	* @param instrid as instrid
	* @param tag
	*
	* @return double value
	*/
	double getDouble(const std::string& instrid, int tag);

	/**
	* @brief get TagData for instrid
	*
	* @param instrid as instrid
	*
	* @return tagdata
	*/
	const TagData& getTagData(const std::string& instrid);

	/**
	* @brief check if has instrid or not
	*
	* @return if has instrid or not
	*/
	bool hasInstrID(const std::string& instrid);

	/**
	* @brief get instrids
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDs();

public:

	/////////////////////////////////////////
	/**
	* @brief get all bar seconds for instrid
	*
	* @param instrid as instrid
	*
	* @return vector of indicator names
	*/
	std::vector<std::string> getTAIndicatorNames(const std::string& instrid);

	/**
	* get int32 value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	*
	* @return int value
	*/
	int getInt32ForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag);

	/**
	* @brief set int32 value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	* @param v as int value
	*/
	void setInt32ForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag, int v);

	/**
	* @brief get double value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	*
	* @return double value
	*/
	double getDoubleForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag);

	/**
	* @brief set double value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	* @param v as double value
	*/
	void setDoubleForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag, double v);

	/**
	* @brief get string value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	*/
	std::string getStringForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag);

	/**
	* @brief set string value for instrid and bar
	*
	* @param instrid as instrid
	* @param taindicatorname
	* @param tag
	* @param v as string value
	*
	* @return string value
	*/
	void setStringForTAIndicator(const std::string& instrid, const std::string& taindicatorname, int tag, const std::string& v);


	/**
	* @brief add ATR for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultATR(const std::string& instrid);

	/**
	* @brief add SMA for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultSMA(const std::string& instrid);

	/**
	* @brief add RSI for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultRSI(const std::string& instrid);

	/**
	* @brief add MACD for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultMACD(const std::string& instrid);

	/**
	* @brief add SAR for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultSAR(const std::string& instrid);

	/**
	* @brief add ADX for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultADX(const std::string& instrid);

	/**
	* @brief add BBands for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultBBands(const std::string& instrid);

	/**
	* @brief add VolBB for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultVolBB(const std::string& instrid);

	/**
	* @brief add BSVDBB for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultBSVDBB(const std::string& instrid);

	/**
	* @brief add OIChgBB for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultOIChgBB(const std::string& instrid);

	/**
	* @brief add CCI for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultCCI(const std::string& instrid);

	/**
	* @brief add MFI for instrid in cfg
	*
	* @param instrid as instrid
	*/
	void addDefaultMFI(const std::string& instrid);
 
protected:
	std::string m_fileName;///< filename
	TagDataWrapperPtr m_data; ///< data
	std::string m_TAIndicatorsPath; ///< ta indicator path


	 


};//class InstrSettingsMgr

}//namespace

#endif