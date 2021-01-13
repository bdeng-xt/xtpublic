#pragma once
#ifndef XT_THREAD_UTIL_H
#define XT_THREAD_UTIL_H

#include <string>
#include <iostream>
 
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <thread>

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#endif

#include "XTConfig.h"

namespace XT {

class XT_COMMON_API ThreadUtil {
public:
	/**
	* @brief get current thread id
	*
	* @return current thread id
	*/
	static  unsigned int getCurrThreadId();

	/**
	* @brief get current thread process id
	*
	* @return current thread process id
	*/
	static int getCurrThreadPid();

	/**
	* @brief set name for current thread
	*
	* @param name
	*/
	static void setCurrThreadName(const std::string & name);

 

};//class 

}//namespace



#endif
