#pragma once
#ifndef XT_UDP_MD_GATEWAY_H
#define XT_UDP_MD_GATEWAY_H

/**
* \file UDPMdGateway.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for udp gateway.
*
* \description
*	Designed for managing udp gateway.
*/

#include <string>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>

#include <thread>
#include <chrono>

#include <boost/unordered_map.hpp>
#include <boost/format.hpp>

#include <Containers.h>

#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "ThreadUtil.h"

#include "CfgMgr.h"
#include "PBUtil.h"

#include "XTConfig.h"

#if (defined(_WIN32) || defined(_WIN64) )
#include <Ws2tcpip.h>
#include <WinSock2.h>
#else
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/time.h>

#endif

namespace XT
{

class XT_COMMON_API UDPMdGateway
{

public:

	UDPMdGateway();
	virtual ~UDPMdGateway();

public:
	virtual void processBuffer();

protected:
	GatewayCfgDataPtr m_cfgData;
	GatewayDataPtr m_data;

	std::set<std::string> m_instrPrefixes;

	std::thread* m_socket_thread;

#ifdef WIN32
	char m_buffer[8196];
#else
	unsigned char m_buffer[8196];
#endif
	int m_nMsg;
	int m_nRcvBytes;
	int m_socketfd;

public:
	GatewayCfgDataPtr& cfgData();
	GatewayDataPtr& data();

public:
	virtual void init();
	virtual void release();
	virtual void start();

	virtual void updateCfgData();

public:
	

	void setInstrPrefixesStr(const std::string& s);
	bool hasValidInstrPrefix(const std::string& instrid);

	void setExchidsStr(const std::string & s);
	bool hasExchid(const std::string& exchid);

	void setProductidsStr(const std::string & s);
	bool hasProductid(const std::string& product);


protected:
	std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
	std::set<std::string> m_productidSet; ///< products
	std::set<std::string> m_exchidSet; ///< exchange ids
									   //////////////////////////
protected:
	void startUDP();
 

};//class


}//namespace XT


#endif