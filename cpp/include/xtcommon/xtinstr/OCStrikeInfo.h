#pragma once
#ifndef XT_OCSTRIKEINFO_H
#define XT_OCSTRIKEINFO_H

/**
* \file OCStrikeInfo.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for Strike information.
*
* \description
*	Designed for storing all information of on a strike of an option chain.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"
//#include <tbb/tbb.h>
#include "XTConfig.h"
#include "TagDataWrapper.h"

#include "EnumUtil.h"
#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "PBUtil.h"

#include "Instr.h"

namespace XT {
	class OCStrikeInfo;
	//////typedef for OCStrikeInfo
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<OCStrikeInfo> OCStrikeInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<OCStrikeInfo> OCStrikeInfoPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<OCStrikeInfo> OCStrikeInfoPtr;

#else

	typedef ::boost::shared_ptr<OCStrikeInfo> OCStrikeInfoPtr;
#endif


	typedef ::sf::safe_ptr<OCStrikeInfo> OCStrikeInfoSafePtr;

	typedef sf::contfree_safe_ptr<OCStrikeInfo> OCStrikeInfoContFreePtr;
	//////end typedef for OCStrikeInfo

class XT_COMMON_API OCStrikeInfo {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	OCStrikeInfo();

	/**
	* @brief default copy constructor
	*/
	OCStrikeInfo(const OCStrikeInfo& from);// = default;

	/**
	* @brief default copy assignment
	*/
	OCStrikeInfo& operator=(const OCStrikeInfo& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~OCStrikeInfo();
	///@}

	/**
	* @brief get double value by tag
	*
	* @param tag
	* 
	* @return double value
	*/
	double getDouble(int tag) ;

	/**
	* @brief set double value
	*
	* @param tag
	* @param d as double value
	*/
	void setDouble(int tag, double d) ;

	/**
	* @brief get integer value
	*
	* @param tag
	* 
	* @return int value
	*/
	int getInt(int tag) ;

	/**
	* @brief set integer value
	* 
	* @param tag
	* @param i as integer value
	*/
	void setInt(int tag, int i);

//	tbb::concurrent_hash_map<int,double> doubleData; ///< map for double data
//	tbb::concurrent_hash_map<int,int> intData; ///< map for integer data

/**
* @name Accessors
*/
///@{
	void setCall(InstrPtr c);
	
	InstrPtr& call();
	
	void setPut(InstrPtr p);
	InstrPtr& put();



	OCStrikeDataPtr& data();

	///@}
 

	/**
	* @brief factory function of StrikeInfo
	*
	* @return created OCStrikeInfo 
	*/
	static OCStrikeInfoPtr  create();

	/**
	* @brief string function
	*
	* @return string
	*/
	std::string str();

	/**
	* @brief json string
	*
	* @return json string
	*/
	std::string jsonStr();

	/**
	* @brief string function for volatiltiy
	*
	* @return volatility string
	*/
	std::string volStr();

	/**
	* @brief string function for snapshot
	*
	* @return snapshot string
	*/
	std::string snapStr();

protected:
//	TagDataWrapperPtr m_data; ///< data
	InstrPtr m_call;
	InstrPtr m_put;
	OCStrikeDataPtr m_data;

}; //end class StrikeInfo





} //end namespace XT

#endif