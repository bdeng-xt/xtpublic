#pragma once
#ifndef XT_MRSW_SET_H
#define XT_MRSW_SET_H

/**
* \file mrsw_set.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  multiple readers single writer set.
*
* \description
*	Designed for customized thread safe set for multiple readers and single writer.
*/

#include <string>
#include <map>
#include <queue>
#include <set>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

namespace XT
{

	///thread safe set
template<typename T>
class mrsw_set
{



};//class


}//namepsace XT



#endif