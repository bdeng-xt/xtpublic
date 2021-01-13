#pragma once
#ifndef XT_CURL_HELPER_H
#define XT_CURL_HELPER_H

/**
* \file CurlHelper.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for CurlHelper using libcurl.
*
* \description
*	Designed for CurlHelper.
*/

//////https://github.com/mrtazz/restclient-cpp 

#include <cstdint>
#include <set>

#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include "XTData.pb.h"
#include "XTConfig.h"
#include "LogUtil.h"

#include <curl/curl.h>
 

#include <string>
#include <algorithm>
#include <functional>

namespace XT
{

	class XT_COMMON_API CurlResponse
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		CurlResponse();

		/**
		* @brief destructor
		*/
		~CurlResponse();
		///@}
	public:
		/**
		* @brief get code
		*
		* @return code
		*/
		int code();

		/**
		* @brief set code
		*
		* @param v as code
		*/
		void set_code(int v);

		/**
		* @brief get cody
		*
		* @return const body
		*/
		const std::string& body();

		/**
		* @brief mutable body
		*
		* @return mutable body
		*/
		std::string& mutable_body();

		/**
		* @brief set body
		*
		* @param v as body
		*/
		void set_body(const std::string& v);

		/**
		* @brief get headers
		*
		* @return headers map
		*/
		std::map<std::string, std::string>& headers();

	protected:
		int m_code;///< code
		std::string m_body; ///< body
		std::map<std::string, std::string> m_headers; ///< headers map
	};

	////////////////////////////
	class XT_COMMON_API CurlRequestInfo
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		CurlRequestInfo();

		/**
		* @brief destructor
		*/
		~CurlRequestInfo();

		///@}
	public:
		/**
		* @brief get total time
		*
		* @return total time
		*/
		double totaltime();

		/**
		* @brief set total time
		*
		* @param value as total time
		*/
		void set_totaltime(double value);

		/**
		* @brief get name lookup time
		*
		* @return name lookup time
		*/
		double namelookuptime();

		/**
		* @brief set name lookup time
		*
		* @param value as name lookup time
		*/
		void set_namelookuptime(double value);

		/**
		* @brief set connect time
		*
		* @param value as connect time
		*/
		double connecttime();

		/**
		* @brief set connect time
		*
		* @param value as connect time
		*/
		void set_connecttime(double value);

		/**
		* @brief set app connect time
		*
		* @param value as app connect time
		*/
		double appconnecttime();

		/**
		* @brief set app connect time
		*
		* @param value as app connect time
		*/
		void set_appconnecttime(double value);

		/**
		* @brief set pre transfer time
		*
		* @param value as pre transfer time
		*/
		double pretransfertime();

		/**
		* @brief set pre transfer time
		*
		* @param value as pre transfer time
		*/
		void set_pretransfertime(double value);

		/**
		* @brief set start transfer time
		*
		* @param value as start transfer time
		*/
		double starttransfertime();

		/**
		* @brief set start transfer time
		*
		* @param value as start transfer time
		*/
		void set_starttransfertime(double value);

		/**
		* @brief set redirect time
		*
		* @param value as redirect time
		*/
		double redirecttime();

		/**
		* @brief set redirect time
		*
		* @param value as redirect time
		*/
		void set_redirecttime(double value);

		/**
		* @brief set redirect count
		*
		* @param value as redirect count
		*/
		int redirectcount();

		/**
		* @brief set redirect count
		*
		* @param value as redirect count
		*/
		void set_redirectcount(int value);

	protected:
		double m_totalTime; ///< total time
		double m_nameLookupTime; ///< name look up time
		double m_connectTime; ///< connect time
		double m_appConnectTime; ///< app connect time
		double m_preTransferTime; ///< pre transfer time
		double m_startTransferTime; ///< start transfer time
		double m_redirectTime; ///< redirect time
		int m_redirectCount; ///< redirect count
	}; //CurlRequestInfo

	   ////////////////////////////////////////////////

	class XT_COMMON_API CurlBasicAuth
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		CurlBasicAuth();

		/**
		* @brief destructor
		*/
		~CurlBasicAuth();

		///@}

		/**
		* @brief get username
		*
		* @return username
		*/
		const std::string& username();

		/**
		* @brief set username
		*
		* @param v as username
		*/
		void set_username(const std::string& v);

		/**
		* @brief get password
		*
		* @return password
		*/
		const std::string& password();

		/**
		* @brief set password
		*
		* @param v as password
		*/
		void set_password(const std::string& v);


	protected:
		std::string m_username; ///< username
		std::string m_password; ///< password
	};// CurlBasicAuth

	  /////////////////////////////////
	class XT_COMMON_API CurlInfo
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		CurlInfo();

		/**
		* @brief destructor
		*/
		virtual ~CurlInfo();

		///@}
	public:
		/**
		* @brief get base url
		*
		* @return base url
		*/
		const ::std::string& baseurl();

		/**
		* @brief set base url
		*
		* @param value as base url
		*/
		void set_baseurl(const ::std::string& value);

		/**
		* @brief get headers
		*
		* @return headers map
		*/
		std::map<std::string, std::string>& headers();

		/**
		* @brief get timeout
		*
		* @return timeout
		*/
		int timeout();

		/**
		* @brief set timeout
		*
		* @param value as timeout
		*/
		void set_timeout(int value);

		/**
		* @brief get follow redirects
		*
		* @return follow redirects
		*/
		bool followredirects();

		/**
		* @brief set follow redirects
		*
		* @param value as follow redirects
		*/
		void set_followredirects(bool value);

		/**
		* @brief get no signal
		*
		* @return no signal
		*/
		bool nosignal();

		/**
		* @brief set nosignal
		*
		* @param value as nosignal
		*/
		void set_nosignal(bool value);

		/**
		* @brief get basic authorization
		*
		* @return CurlBasicAuth pointer
		*/
		boost::shared_ptr<CurlBasicAuth>& basicauth();

		/**
		* @brief get certificate path
		*
		* @return certificate path
		*/
		const ::std::string& certpath();

		/**
		* @brief set certificate path
		*
		* @param value as certificate path
		*/
		void set_certpath(const ::std::string& value);

		/**
		* @brief get certificate type
		*
		* @return certificate type
		*/
		const ::std::string& certtype();

		/**
		* @brief set certificate type
		*
		* @param value as certificate type
		*/
		void set_certtype(const ::std::string& value);

		/**
		* @brief get key path
		*
		* @return key path
		*/
		const ::std::string& keypath();

		/**
		* @brief set key path
		*
		* @param value as key path
		*/
		void set_keypath(const ::std::string& value);

		/**
		* @brief get key password
		*
		* @return key password
		*/
		const ::std::string& keypassword();

		/**
		* @brief set key password
		*
		* @param value as key password
		*/
		void set_keypassword(const ::std::string& value);

		/**
		* @brief get custom user agent
		*
		* @return custom user agent
		*/
		const ::std::string& customuseragent();

		/**
		* @brief set custom user agent
		*
		* @param value as custom user agent
		*/
		void set_customuseragent(const ::std::string& value);

		/**
		* @brief get proxy uri
		*
		* @return proxy uri
		*/
		const ::std::string& uriproxy();

		/**
		* @brief set proxy uri
		*
		* @param value as proxy uri
		*/
		void set_uriproxy(const ::std::string& value);

		/**
		* @brief get last request
		*
		* @return last request information
		*/
		boost::shared_ptr<CurlRequestInfo>& lastrequest();

		/**
		* @brief set last request
		*
		* @param info as CurlRequestInfo pointer
		*/
		void set_lastrequest(boost::shared_ptr<CurlRequestInfo> info);
	protected:
		std::string m_baseUrl; ///< base url
		std::map<std::string, std::string> m_headers; ///<headers map
		int m_timeout; ///< timeout seconds
		bool m_followRedirects; ///< follow redirects or not
		bool m_noSignal; ///< no signal
		boost::shared_ptr<CurlBasicAuth> m_basicAuth; ///< basic authorization

		std::string m_certPath; ///< certificate path
		std::string m_certType; ///< certificate type
		std::string m_keyPath; ///< key path
		std::string m_keyPassword; ///< key password
		std::string m_customUserAgent; ///< custom user agent
		std::string m_uriProxy; ///< uri proxy
		boost::shared_ptr<CurlRequestInfo> m_lastRequest; ///< last request information
	}; //CurlInfo



  /** 
  * @struct UploadObject
    *  @brief This structure represents the payload to upload on POST
    *  requests
    *  @var UploadObject::data
    *  Member 'data' contains the data to upload
    *  @var UploadObject::length
    *  Member 'length' contains the length of the data to upload
    */
 typedef struct {
    const char* data; ///< data
    size_t length; ///< length
} CurlUploadObject;


namespace CurlHelper
{
 
 
/**
* @brief writedata callback function
*/
 size_t write_callback(void *ptr, size_t size, size_t nmemb,
                              void *userdata);

  /**
  * @brief header callback function
  */
size_t header_callback(void *ptr, size_t size, size_t nmemb,
                                void *userdata);
  /**
  * @brief read callback function
  */
 size_t read_callback(void *ptr, size_t size, size_t nmemb,
                              void *userdata);

  /**
  * @brief trim from start
  */
  static inline std::string &ltrim(std::string &s) {  // NOLINT
    //s.erase(s.begin(), std::find_if(s.begin(), s.end(),
    //      std::not1(std::ptr_fun<int, int>(std::isspace))));
	  boost::algorithm::trim_left(s);
    return s;
  }

  /**
  * @brief trim from end
  */
  static inline std::string &rtrim(std::string &s) { // NOLINT
    //s.erase(std::find_if(s.rbegin(), s.rend(),
    //      std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	  boost::algorithm::trim_right(s);
    return s;
  }

  /**
  * @brief trim from both ends
  */
  static inline std::string &trim(std::string &s) {  // NOLINT
 //   return ltrim(rtrim(s));
	  boost::algorithm::trim(s);
	  return s;
} 

};//namespace CurlHelper

}//namespace

#endif