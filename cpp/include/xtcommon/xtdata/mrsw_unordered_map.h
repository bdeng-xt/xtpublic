#pragma once
#ifndef XT_MRSW_UNORDERED_MAP_H
#define XT_MRSW_UNORDERED_MAP_H

/**
* \file mrsw_map.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  multiple readers single writer unordered map.
*
* \description
*	Designed for customized thread safe unordered map for multiple readers and single writer.
*/

#include <string>
#include <map>
#include <queue>

#include <unordered_map>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

namespace XT
{

	///thread safe unordered map
template<typename T>
class mrsw_unordered_map
{



};//class


}//namepsace XT



#endif