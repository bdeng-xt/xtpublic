#pragma once
#ifndef XT_PTR_UTIL_H
#define XT_PTR_UTIL_H

/**
* \file PtrUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide utility functions for pointer.
*
* //https://stackoverflow.com/questions/12314967/cohabitation-of-boostshared-ptr-and-stdshared-ptr
*
* \description
*	This component provides common used functions for pointer.
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <limits>

#include <memory>

#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>

template<typename T>
void release_boost_shared_ptr(typename boost::shared_ptr<T> const &, T*)
{

}

template<typename T>
typename std::shared_ptr<T> boost_to_std_ptr(typename boost::shared_ptr<T> const & bsp)
{
	return std::shared_ptr<T>(bsp.get(), boost::bind(&release_boost_shared_ptr<T>, bsp, _1)  );
}

#endif