#pragma once
#ifndef XT_XTSINGLETON_H
#define XT_XTSINGLETON_H

/**
* \file XTSingleton.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a template class for singleton.
*
* \description
*	Designed for an impletation for singleton pattern.
*/


#include <iostream>
#include <string>
#include <cstdlib>

#include <thread>
#include <mutex>

//#include <CurlUtil.h>

namespace XT
{

//https://stackoverflow.com/questions/41328038/singleton-template-as-base-class-in-c


template <typename T>
class XTSingleton
{
	friend T;
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static T& getInstance()
	{
		static T instance;
		return instance;
	}

protected:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	XTSingleton() {}

 

	/**
	* @brief destructor
	*/
	~XTSingleton() {}
	///@}
public:
	/**
	* @brief copy constructor
	*/
	XTSingleton(const XTSingleton &) {} //= delete;

	XTSingleton(XTSingleton&&) {} //=delete;

	/**
	* @brief assignment operator
	*/
	XTSingleton& operator=(const XTSingleton &) { return *this; } //= delete;
	XTSingleton& operator=(XTSingleton&&) { return *this; } //=delete;


};//class



}//namespace 




#endif
