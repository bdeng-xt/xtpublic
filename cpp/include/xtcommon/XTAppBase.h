#pragma once
#ifndef XT_XTAPPBASE_H
#define XT_XTAPPBASE_H

/**
* \file XTAppBase.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a base class for application.
*
* \description
*	Designed for application base.
*/


#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>	

//#include <signal.h>
#include <csignal>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "log4z.h"//  #include "LogUtil.h"

#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "CfgMgr.h" //#include "SettingsMgr.h"
#include "ZMQMgr.h"
#include "XTTimer.h"
#include "XTApiMgr.h"
#include "XTMgr.h"

namespace XT
{

class XT_COMMON_API XTAppBase
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTAppBase();

	/**
	* @brief default copy constructor
	*/
	XTAppBase(const XTAppBase& from) = default;

	/**
	* @brief default copy assignment
	*/
	XTAppBase& operator=(const XTAppBase& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~XTAppBase();

	///@}


	/**
	* @brief virtual function run
	*
	* @param argc as count or arguments
	* @param argv as arguments
	*/
	virtual void run(int argc, const char* argv[]);

	/**
	* @brief main function
	*
	* @param argc as count or arguments
	* @param argv as arguments
	*/
	int main(int argc, const char* argv[]);
public:
	/**
	* @brief check if it is running or not
	*
	* @return if it is running or not
	*/
	bool isRunning();

public:

	/**
	* @brief catch interrupt singals such as CTRL-C
	*/
	static void catchInterruptSignals();

protected:
	/**
	* @brief handle interrupt singals such as CTRL-C
	*/
	static void handleInterruptSignal(int signal_value);
 
};//class


}//namespace 

#endif