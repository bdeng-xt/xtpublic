#pragma once
#ifndef XT_CURL_MGR_H
#define XT_CURL_MGR_H

/**
* \file CurlMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for Curl Mgr using libcurl.
*
* \description
*	Designed for CurlMgr.
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

#include <curl/curl.h>

#include "CurlConnection.h"

namespace XT
{

	class XT_COMMON_API CurlMgr
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		CurlMgr();

		/**
		* @brief default copy constructor
		*/
		CurlMgr(const CurlMgr& from) {} // = delete;

		/**
		* @brief default copy assignment
		*/
		CurlMgr& operator=(const CurlMgr& from) { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~CurlMgr();

		///@}

	public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static CurlMgr* getInstance();


	public:
		/**
		* @brief get url data
		*
		* @param url
		* @param ms_timeout in milliseconds
		*/
		std::string getUrlData(const std::string& url, int ms_timeout);



	protected:
		/**
		* @brief init function. Call this before you start any threads.
		*/
		int init();
		/**
		* @brief global disable function. Call this before you terminate your program
		*/
		void release();



		/**
		* @brief HTTP GET method
		*
		* @param url to query
		*
		* @return response struct
		*/
		CurlResponse http_get(const std::string& url);


		/**
		* @brief HTTP POST method
		*
		* @param url to query
		* @param ctype content type as string
		* @param data HTTP POST body
		*
		* @return response struct
		*/
		CurlResponse http_post(const std::string& url, const std::string& content_type, const std::string& data);

		/**
		* @brief HTTP PUT method
		*
		* @param url to query
		* @param ctype content type as string
		* @param data HTTP PUT body
		*
		* @return response struct
		*/
		CurlResponse http_put(const std::string& url, const std::string& content_type, const std::string& data);

		/**
		* @brief HTTP DELETE method
		*
		* @param url to query
		*
		* @return response struct
		*/
		CurlResponse http_del(const std::string& url);


		/**
		* @brief HTTP HEAD method
		*
		* @param url to query
		*
		* @return response struct
		*/
		CurlResponse http_head(const std::string& url);



	};//class

}//namespace

#endif