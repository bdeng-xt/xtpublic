#pragma once
#ifndef XT_WEB_MGR_H
#define XT_WEB_MGR_H

/**
* \file WebMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for sina data Mgr using libcurl.
*
* \description
*	Designed for WebMgr.
*/

//////https://github.com/mrtazz/restclient-cpp 

#include <cstdint>
#include <set>

#include <string>
#include <map>
#include <cstdlib>

#include <boost/shared_ptr.hpp>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"

#include "CurlMgr.h"

namespace XT
{

	class XT_COMMON_API WebMgr
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		WebMgr();

		/**
		* @brief default copy constructor
		*/
		WebMgr(const WebMgr& from) {} // = delete;

		/**
		* @brief default copy assignment
		*/
		WebMgr& operator=(const WebMgr& from) { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~WebMgr();

		///@}

	public:

		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static WebMgr* getInstance();


	public:
		 /**
		 * @brief get host for sina market quote
		 *
		 * @return host
		 */
		const std::string&  getHostSinaMktQuote();

		/**
		* @brief get path url of sina market quote
		*
		* @return path url
		*/
		const std::string& getPathurlSinaMktQuote();

		/**
		* @brief get sina market quote url
		*
		* @param instrs as comma separated instrids
		*
		* @return url
		*/
		std::string getSinaMktQuoteUrl(const std::string& instrs);

		/**
		* @brief get sina market quote string
		*
		* @param instrs as comma separated instrids
		*
		* @return quote string
		*/
		std::string getSinaMktQuoteStr(const std::string& instrs);

		/**
		* @brief get sina market quote string
		*
		* @param instrid as instrid
		*
		* @return quote string
		*/
		std::string getSinaMktQuoteStrForInstrID(const std::string& instrid);

		/**
		* @brief get host from SHDJT
		* 
		* @return host
		*/
		const std::string& getHostSHDJT();

		/**
		* @brief get path url from SHDJT
		*
		* @return path url
		*/
		const std::string& getPathurlSHDJTStockCodes();

		/**
		* @brief get stock codes from SHDJT
		*
		* @return stock codes as comma separated string
		*/
		std::string getSHDJTStockCodes();

		/**
		* @brief get host for leverfun
		* 
		* @return host
		*/
		const std::string& getHostLeverFun();

		/**
		* @brief get path url for leverfun
		*
		* @return path url
		*/
		const std::string& getPathurlLeverFunTimeOrderForm();

	protected:
		std::string m_hostSinaMktQuote; ///< host for sina market quote
		std::string m_pathurlSinaMktQuote; ///< path url for sina market quote
	 
		std::string m_hostSHDJT; ///< host for SHDJT
		std::string m_pathurlSHDJTStockCodes; ///< path url for SHDJT

		std::string m_hostLeverFun; ///< host for leverfun
		std::string m_pathurlLeverFunTimeOrderForm; ///< path url for leverfun


	};//class

}//namespace

#endif