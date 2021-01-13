#pragma once
#ifndef XT_ENUMHELPER_H
#define XT_ENUMHELPER_H

/**
* \file EnumHelper.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide help functions for enums.
*
* \description
*	Designed for use for all enums and their utilities.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>

#include "XTConfig.h"

#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"


namespace XT {

class XT_COMMON_API BuySellTypeHelper {

public:
	BuySellTypeHelper() {}
	BuySellTypeHelper(const BuySellTypeHelper& from) {}// = delete;
	const BuySellTypeHelper& operator=(const BuySellTypeHelper& from) { return *this; }// = delete;
	virtual ~BuySellTypeHelper() {}

public:
		/**
		* @brief get string name for enum integer
		*
		* @param i integer value
		*
		* @return name
		*/
		static std::string getName(int i) ;

		/**
		* @brief get integer value for enum name
		*
		* @param s name
		*
		* @return enum value
		*/
		static int getValue(std::string s) ;

		/**
		* @brief get type for integer value
		*
		* @param i integer value
		*
		* @return buysell type
		*/
		static XT::BuySellType::enumtype getType(int i) ;

		/** 
		* @brief get sign of Buy(1) or Sell(-1)
		* sign of Buy is 1
		* sign of Sell is -1
		*
		* @param bsType Buy or Sell type
		*
		* @return sign value
		*/
		static int signOf(XT::BuySellType::enumtype bsType) ;

		/** 
		* @brief flip side
		* Buy will be flipped to Sell
		* Sell will be flipped to Buy
		*
		* @param bsType, Buy or Sell type
		*
		* @return buy sell type
		*/
		static XT::BuySellType::enumtype flip(BuySellType::enumtype bsType) ;

		/** 
		* @brief parse 0 or 1 to BuySellType::type
		* 0: Buy
		* 1: Sell
		*
		* @param i integer value 0 or 1
		*
		* @return buy sell type
		*/
		static XT::BuySellType::enumtype parse01(int i) ;

		/** 
		* @brief parse 1 or -1 to BuySellType::type
		* 1: Buy
		* -1: Sell
		*
		* @param i integer value 1 or -1
		*
		* @return buy sell type
		*/
		static XT::BuySellType::enumtype parseSign(int i) ;

		/** 
		* @brief cast BuySellType::type to 0 or 1
		* Buy: 0
		* Sell: -1
		*
		* @param bsType Buy or Sell
		*
		* @return 0(buy) or 1 (sell)
		*/
		static int cast01(XT::BuySellType::enumtype bsType) ;

}; //class


 
} //end namespace XT

#endif