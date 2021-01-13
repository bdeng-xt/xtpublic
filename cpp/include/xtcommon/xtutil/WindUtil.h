#pragma once
#ifndef XT_WINDUTIL_H
#define XT_WINDUTIL_H

/**
* \file WindUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all wind utilities.
*
* \description
*	Designed for managing all wind utilities.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <google/protobuf/util/json_util.h>

#include "Util.h"
#include "Instr.h"
#include "InstrMgr.h"

#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "XTConfig.h"

namespace XT
{


	class XT_COMMON_API WindUtil
	{
	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		WindUtil() {}

		/**
		* @brief copy constructor
		*/
		WindUtil(const WindUtil& from) {} // = delete;

		/**
		* @brief copy assignment
		*/
		WindUtil& operator=(const WindUtil& from) { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~WindUtil() {}

		///@}
	protected:
		static const std::string s_EmptyString; ///< empty string
	public:
		/**
		* @brief get empty string
		*
		* @return empty string
		*/
		static const std::string& getEmptyString(); ///< empty string

	};//class

}//namespace 
#endif