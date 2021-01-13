#pragma once
#ifndef XT_GLOBAL_MGR_H
#define XT_GLOBAL_MGR_H

/**
* \file GlobalMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing all global data.
*
* \description
*	Designed for managing all global data.
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



#define BOOST_SYSTEM_NO_LIB
#define BOOST_FILESYSTEM_NO_LIB
#include <boost/filesystem.hpp>

#include "XTConfig.h"

#include "LogUtil.h"

#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "typedef_FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "TagDataWrapper.h"

#include "Util.h"
#include "StringMap.h"
#include "XTSimpleIni.h"
#include "CfgMgr.h"


namespace XT
{

	class XT_COMMON_API GlobalMgr {

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		GlobalMgr();

		/**
		* @brief default copy constructor
		*/
		GlobalMgr(const GlobalMgr& from) {} // = delete;

		/**
		* @brief default copy assignment
		*/
		GlobalMgr& operator=(const GlobalMgr& from) { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~GlobalMgr();

		///@}


	public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static GlobalMgr* getInstance();

		////

		/*
		* @brief get cfg data
		*
		* @return cfg data
		*/
		GlobalCfgDataPtr& cfgData();

		/*
		* @brief get data
		*
		* @return data
		*/
		GlobalDataPtr& data();

		/**
		* @brief get cfgData string parameters
		*
		* @return cfgData String Parameters
		*/
		StringMapPtr& cfgDataStrParams();

		/**
		* @brief init cfgData with string parameters
		*
		* @param smp
		*/
		void initCfgDataWithStrParams(const StringMapPtr& smp);

	protected:
		void init();

	public:

		/**
		* @brief update base directory
		*
		* @param s as base directory
		*/
		void updateBaseDir(const std::string& s);

		/**
		* @brief get base directory
		*
		* @return base directory
		*/
		const std::string& getBaseDir();

		/**
		* @brief set app directory
		*
		* @param s as app directory
		*/
		void setAppDir(const std::string& s);

		/**
		* @brief get app directory
		*
		* @return app directory
		*/
		const std::string& getAppDir();

		/**
		* @brief set log directory
		*
		* @param s as log directory
		*/
		void setLogDir(const std::string& s);

		/**
		* @brief get log directory
		*
		* @return log directory
		*/
		const std::string& getLogDir();

		/**
		* @brief set data directory
		*
		* @param s as data directory
		*/
		void setDataDir(const std::string& s);

		/**
		* @brief get data directory
		*
		* @return data directory
		*/
		const std::string& getDataDir();

		/**
		* @brief set cfg directory
		*
		* @param s as cfg directory
		*/
		void setCfgDir(const std::string& s);

		/**
		* @brief get cfg directory
		*
		* @return cfg directory
		*/
		const std::string& getCfgDir();

		/**
		* @brief set library directory
		*
		* @param s as library directory
		*/
		void setLibDir(const std::string& s);

		/**
		* @brief get library directory
		*
		* @return library directory
		*/
		const std::string& getLibDir();

		/**
		* @brief set plugin directory
		*
		* @param s as plugin directory
		*/
		void setPluginDir(const std::string& s);

		/**
		* @brief get plugin directory
		*
		* @return plugin directory
		*/
		const std::string& getPluginDir();

		/**
		* @brief get main database file
		*
		* @return main database file
		*/
		const std::string& getMainDbFile();

		/**
		* @brief get trade database file
		*
		* @return trade database file
		*/
		const std::string& getTrdDbFile();

		bool isSim();
		bool isNone();

		int getTradingDay();
		void setTradingDay(int v);

		int getPrevTradingDay();
		void setPrevTradingday( int v);
	  
	protected:
 
		GlobalCfgDataPtr m_cfgData;

		GlobalDataPtr m_data;

		StringMapPtr m_cfgDataStrParams;

		 

	};//class

}//namespace

#endif