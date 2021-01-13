#pragma once
#ifndef XT_CURL_CONNECTION_H
#define XT_CURL_CONNECTION_H

/**
* \file CurlConnection.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for CurlConnection using libcurl.
*
* \description
*	Designed for CurlConnection.
*/

#include <cstdint>
#include <set>

#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>
#include <boost/smart_ptr.hpp>
#include <curl/curl.h>

//#include "XTData.pb.h"
#include "XTConfig.h"
#include "LogUtil.h"

#include "CurlHelper.h"

namespace XT
{



////////////////////
class XT_COMMON_API CurlConnection
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor
	*
	* @param baseUrl as url address
	*/
    explicit CurlConnection(const std::string& baseUrl);

	/**
	* @brief destructor
	*/
    ~CurlConnection();

	///@}

	/**
    * @brief Instance configuration methods
    * configure basic auth
	*
	* @param username
	* @param password
	*/
    void SetBasicAuth(const std::string& username,
                      const std::string& password);

	/**
	* @brief  set connection timeout to seconds
	*
	* @param seconds as timeout seconds
    */
	void SetTimeout(int seconds);

	/**
	* @brief set to not use signals
	*
	* @no as bool
    */
	void SetNoSignal(bool no);

    /**
	* @brief set whether to follow redirects
	*
	* @param follow as bool
	*/
    void FollowRedirects(bool follow);

	/**
	* @brief  set custom user agent
    * (this will result in the UA "foo/cool restclient-cpp/VERSION")
	*
	* @param userAgent
    */
	void SetUserAgent(const std::string& userAgent);

	/**
    * @brief set the Certificate Authority (CA) Info which is the path to file holding
    * certificates to be used to verify peers. See CURLOPT_CAINFO
	*
	* @param acaInfoFilePath
    */
	void SetCAInfoFilePath(const std::string& caInfoFilePath);

	/**
    * @brief set CURLOPT_SSLCERT
	*
	* @param cert as certificate path
	*/
    void SetCertPath(const std::string& cert);

	/**
    * @brief set CURLOPT_SSLCERTTYPE
	*
	* @param type as certificate type
	*/
    void SetCertType(const std::string& type);

	/**
	* @brief set CURLOPT_SSLKEY. Default format is PEM
	*
	* @param keyPath
	*/
    void SetKeyPath(const std::string& keyPath);

	/**
	* @brief set CURLOPT_KEYPASSWD.
	*
	* @param keyPassword
	*/
    void SetKeyPassword(const std::string& keyPassword);

	/**
	* @brief set CURLOPT_PROXY
	*
	* @param uriProxy
    */
	void SetProxy(const std::string& uriProxy);

	/**
	* @brief get user agent
	*
	* @return user agent
	*/
    std::string GetUserAgent();

	/**
	* @brief get info
	*
	* @return CurlInfo pointer
	*/
    boost::shared_ptr<CurlInfo> GetInfo();

	/**
	* @brief set headers
	*
	* @param headers
	*/
    void SetHeaders(std::map<std::string,std::string> headers);

	/**
	* @brief get headers
	*
	* @retrun headers
	*/
    std::map<std::string,std::string> GetHeaders();

	/**
	* @brief append additional headers
	*
	* @param key
	* @param value
	*/
    void AppendHeader(const std::string& key,
                      const std::string& value);

	/**
	* @name Basic HTTP verb methods
	*/
    ///@{

	/**
	* @brief get method
	*
	* @param uri
	*/
	CurlResponse http_get(const std::string& uri);

	/**
	* @brief post method
	*
	* @param uri
	* @param data
	*/
	CurlResponse http_post(const std::string& uri, const std::string& data);

	/**
	* @brief put method
	*
	* @param uri
	* @param data
	*/
	CurlResponse http_put(const std::string& uri, const std::string& data);

	/**
	* @brief del method
	*
	* @param uri
	*/
	CurlResponse http_del(const std::string& uri);

	/**
	* @brief head method
	*
	* @param uri
	*/
	CurlResponse http_head(const std::string& uri);

	///@}
 private:
    CURL* curlHandle; ///< curl handle
    std::string baseUrl; ///< base url
    std::map<std::string,std::string> headerFields; ///< header fields
    int timeout; ///< timeout seconds
    bool followRedirects; ///<follow redirects
    bool noSignal; ///< no signal
	boost::shared_ptr<CurlBasicAuth> basicAuth; ///<basic authorization
    std::string customUserAgent;///<custom user agent
    std::string caInfoFilePath; ///< ca infor file path
    boost::shared_ptr<CurlRequestInfo> lastRequest; ///< last request information
    std::string certPath; ///< certificate path
    std::string certType; ///< certificate type
    std::string keyPath; ///< key path
    std::string keyPassword; ///< key password
    std::string uriProxy; ///< uri proxy
private:
	/**
	* @brief perform curl request
	*
	* @param uri
	*/
	CurlResponse performCurlRequest(const std::string& uri);

	
};//class

}//namespace

#endif