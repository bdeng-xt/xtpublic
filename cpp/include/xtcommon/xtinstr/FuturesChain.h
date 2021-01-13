#pragma once
#ifndef XT_FUTURESCHAIN_H
#define XT_FUTURESCHAIN_H

/**
* \file FuturesChain.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of futures for the same product.
*
* \description
*	Designed for use for futures chain of a product.
*/

#include <cstdint>
#include <iostream>
#include <sstream>

#include <map>
 
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "Util.h"
#include "PxUtil.h"
#include "TimeUtil.h"
#include "Instr.h"

#include "Curve.h"

namespace XT
{

class XT_COMMON_API FuturesChain{
public:

	/** 
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor with product name
	*/
	FuturesChain(const std::string& p);

	/**
	* @brief constructor
	*/
	FuturesChain();

	/**
	* @brief default copy constructor
	*/
	FuturesChain(const FuturesChain& from);// = default;

	/**
	* @brief default copy assignment
	*/
	FuturesChain& operator=(const FuturesChain& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~FuturesChain() {};

	///@}

	/**
	* @brief initialize with string parameters
	*
	* @param string parameters
	*/
	void updateStrParams(const StringMapPtr& smp);

	/**
	* @brief initialize product
	*
	* @param product
	*/
	void initProduct(const std::string& product);

	/**
	* @brief initialize all
	*/
	void init();

	/**
	* @brief is initialized or not
	*
	* @return if fc is initialized
	*/
	bool isInitialized();

	/** 
	* @name Add
	*/
	///@{
	/**
	* @brief add instrument
	*
	* @param instr as instrument
	*/
	void addInstr(InstrPtr& instr);

	/**
	* @brief get first instr
	*
	* @return fist InstrPtr
	*/
	InstrPtr& firstInstr();

	/**
	* @brief get last instr
	*
	* @return last InstrPtr
	*/
	InstrPtr& lastInstr();

	/**
	* @brief get instr by exipiry intdate
	*
	* @param intdate as int expiry intdate
	*
	* @return InstrPtr
	*/
	InstrPtr& getInstr(int intdate);

	/**
	* @brief get first instrid
	*
	* @return first instrid
	*/
	const std::string& getFirstInstrID();

	/**
	* @brief get last instrid
	*
	* @return last instrid
	*/
	const std::string& getLastInstrID();

	/**
	* @brief get anchor instrid
	*
	* @return anchor instrid
	*/
	const std::string& getAnchorInstrID();

	///@}


	/** 
	* @name Setters and Getters
	*/
	///@{

	/**
	* @brief get futures map
	*
	* @return futures map
	*/
	sf::contfree_safe_ptr<std::map<int, InstrPtr > >& futures();


	/**
	* @brief get cfgData
	*
	* @return   cfgData
	*/
	FCCfgDataPtr& cfgData();

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	StringMapPtr& strParams();

	/**
	* @brief data
	*
	* @return data
	*/
	FCDataPtr& data();

	/**
	* @brief get data str
	*
	* @return data str
	*/
	std::string getDataStr();

	/**
	* @brief get cfgdata str
	*
	* @return cfgdata str
	*/
	std::string getCfgDataStr();


	/**
	* @brief get str params string
	*
	* @return strParams str
	*/
	std::string getStrParamsStr();
	/////////////////////////////////////////////////////////

	/**
	* @brief prev settle curve
	*
	* @return prev settle curve
	*/
	CurvePtr& curvePrevSettle();  

	/**
	* @brief bid curve
	*
	* @return bid curve
	*/
	CurvePtr& curveBid();  

	/**
	* @brief ask curve
	*
	* @return ask curve
	*/
	CurvePtr& curveAsk();  

	/**
	* @brief mid curve
	*
	* @return mid curve
	*/
	CurvePtr& curveMid(); 



	/**
	* @brief get expiry intdates
	*
	* @return vector of intdates
	*/
	std::vector<int> getExpiryIntDates();

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string & getName();

	/**
	* @brief set name
	*
	* @param v as name
	*/
	void setName(const std::string & v);

	/**
	* @brief get product name
	*
	* @return product name
	*/
	const std::string& getProductName();

	/**
	* @brief set product name
	*
	* @param v as product name
	*/
	void setProductName(const std::string & v);


	/**
	* @brief set current date
	*
	* @param intdate as int date
	*/
	void setCurrIntDate(int intdate);

	/**
	* @brief get all future instrids
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDs();
	 
	///@}

	/**
	* @brief update time
	*
	*/
	void updateTime();


	/** 
	* @name String Functions
	*/
	///@{
	/**
	* @brief string for chain
	*
	* @return chain specification string
	*/
	std::string chainStr();

	/**
	* @brief string for data
	*
	* @param tag
	*
	* @return data string
	*/
	std::string dataStr(int tag);

	/**
	* @brief string for snapshot
	*
	* @return snap string
	*/
	std::string snapStr();

	/**
	* @brief log postion string in csv format
	* 
	* @param seq as int
	*/
	void logPosCsvStr(int seq);
	///@}
protected:
	InstrPtr m_EmptyInstr; ///null instr
	std::string m_EmptyString; ///< empty string

	sf::contfree_safe_ptr<std::map<int, InstrPtr > > m_futures; //  std::map<int, InstrPtr > m_futures; ///< futures map

	std::string m_name; ///< name of futures chain
	std::string m_product; ///< product name
protected:
	FCCfgDataPtr m_cfgData;
	FCDataPtr m_data;

	StringMapPtr m_strParams;

	CurvePtr m_curvePrevSettle; ///<  previous settle curve

	CurvePtr m_curveBid; ///<  bid curve
	CurvePtr m_curveAsk; ///<  ask curve
	CurvePtr m_curveMid; ///<  mid curve

protected:
//	mutable boost::shared_mutex m_mutex;


}; //end class FuturesChain
   //////typedef for FuturesChain
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<FuturesChain> FuturesChainPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<FuturesChain> FuturesChainPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<FuturesChain> FuturesChainPtr;

#else

typedef ::std::shared_ptr<FuturesChain> FuturesChainPtr;
#endif


typedef ::sf::safe_ptr<FuturesChain> FuturesChainSafePtr;

typedef sf::contfree_safe_ptr<FuturesChain> FuturesChainContFreePtr;
//////end typedef for FuturesChain

/////////////////////////////////////////////////////

class XT_COMMON_API FuturesChainMap {
public:

	/**
	* @name Constructor and Initialization
	*/
	///@{
 

	/**
	* @brief constructor
	*/
	FuturesChainMap();

	/**
	* @brief default copy constructor
	*/
	FuturesChainMap(const FuturesChainMap& from);// = default;

										   /**
										   * @brief default copy assignment
										   */
	FuturesChainMap& operator=(const FuturesChainMap& from);// = default;

													  /**
													  * @brief destructor
													  */
	virtual ~FuturesChainMap() {};

	///@}



public:
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > >& fcMap();

	void add(FuturesChainPtr& fc);

	void removeByFCName(const std::string& name);
	void removeByFCProductID(const std::string& product);

	bool hasFCName(const std::string& name);
	bool hasFCProductID(const std::string& product);

	std::vector<std::string> getFCNames();
	std::vector<std::string> getFCProductIDs();

	FuturesChainPtr& getFuturesChainByName(const std::string& name);

	FuturesChainPtr& getFuturesChainByProductID(const std::string& product);



protected:
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > > m_fcMap;
	FuturesChainPtr m_EmptyFuturesChain; ///< null FuturesChain


}; //class XT_COMMON_API FuturesChainMap {
   //////typedef for FuturesChainMap
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<FuturesChainMap> FuturesChainMapPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<FuturesChainMap> FuturesChainMapPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<FuturesChainMap> FuturesChainMapPtr;

#else

typedef ::std::shared_ptr<FuturesChainMap> FuturesChainMapPtr;
#endif


typedef ::sf::safe_ptr<FuturesChainMap> FuturesChainMapSafePtr;

typedef sf::contfree_safe_ptr<FuturesChainMap> FuturesChainMapContFreePtr;
//////end typedef for FuturesChainMap


} //end namespace XT

#endif