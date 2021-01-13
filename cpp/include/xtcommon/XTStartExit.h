#pragma once
#ifndef XT_STARTEXIT_H
#define XT_STARTEXIT_H

/**
* \file XTStartExit.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of functions for starting and exiting.
*
* \description
*	Designed for doing something when start and exit.
*/

#define BOOST_THREAD_SOURCE
#define BOOST_THREAD_NO_LIB
#define BOOST_SYSTEM_NO_LIB

#include <iostream>
#include <string>
#include <cstdlib>

#include <thread>
#include <mutex>
//#include <boost/thread/once.hpp>
//#include <boost/shared_ptr.hpp>
#include "XTConfig.h"

 
#include "LogUtil.h"
//#include <CurlUtil.h>
#include "Util.h"
#include "TimeUtil.h"
#include <YahooUtil.h>

#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include "MongoDBMgr.h"

#include <google/protobuf/stubs/common.h>

#include "ZMQMgr.h"
#include "XTTimer.h"


//#include "InstrMgr.h"

extern XT_COMMON_API bool xt_start_init();

namespace
{
	const bool xt_init_done = xt_start_init();
}//anonymous namespace


#endif