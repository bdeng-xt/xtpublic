#pragma once
#ifndef XT_MRSW_VECTOR_H
#define XT_MRSW_VECTOR_H

/**
* \file mrsw_vector.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  multiple readers single writer vector.
*
* \description
*	Designed for customized thread safe vector for multiple readers and single writer.
*/

#include <string>
#include <map>
#include <queue>

#include <vector>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>	 

namespace XT
{

	///thread safe vector
template<typename T>
class mrsw_vector
{



};//class


}//namepsace XT



#endif