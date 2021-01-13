#pragma once
#ifndef XT_OPTIONSCHAINS_H
#define XT_OPTIONSCHAINS_H

/**
* \file OptionsChains.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of options chains for the same product.
*
* \description
*	Designed for use for options chains of a product.
*/


#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include <map>

#include <unordered_map>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

//#include <boost/lexical_cast.hpp>
#include "XTConfig.h"
#include "log4z.h"

#include "Util.h"
#include "PxUtil.h"
#include "Instr.h"
#include "OCStrikeInfo.h"
#include "Curve.h"
#include "DoubleWingCurve.h"
#include "FlatCurve.h"
#include "LineCurve.h"

#include "DataUtil.h"
#include "Rolling.h"
#include "RollingXY.h"


#include "CfgMgr.h"
#include "ExchMgr.h"

#include "OptionsChain.h"

namespace XT {

class XT_COMMON_API OptionsChains {

public:

	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	OptionsChains();
	/**
	* @brief constructor with procut name
	*
	* @param product as product id
	*/
	OptionsChains(const std::string& product);

	/**
	* @brief default copy constructor
	*/
	OptionsChains(const OptionsChains& from);// = default;

	/**
	* @brief default copy assignment
	*/
	OptionsChains& operator=(const OptionsChains& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~OptionsChains();

	///@}

	/**
	* @brief get cfg data
	*
	* @return cfg data
	*/
	OCSCfgDataPtr& cfgData();

	/**
	* @brief get data
	*
	* @return data
	*/
	OCSDataPtr& data();

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	StringMapPtr& strParams();

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
	///////////////

	/**
	* @brief oc map
	*
	* @return oc map
	*/
	sf::contfree_safe_ptr<std::map<int, OptionsChainPtr > >& ocMap(); 

	/**
	* @brief undly prev settle curve
	*
	* @return undly prev settle curve
	*/
	CurvePtr& undlyCurvePrevSettle();  

	/**
	* @brief undly bid curve
	*
	* @return undly bid curve
	*/
	CurvePtr& undlyCurveBid(); 
	/**
	* @brief undly ask curve
	*
	* @return undly ask curve
	*/
	CurvePtr& undlyCurveAsk();  
	/**
	* @brief undly mid curve
	*
	* @return undly mid curve
	*/
	CurvePtr& undlyCurveMid();  

	/**
	* @brief undly instr
	*
	* @brief unldy instr
	*/
	InstrPtr& undlyInstr(); 
	/**
	* @brief hedging instr
	*
	* @brief hedging instr
	*/
	InstrPtr& hedgingInstr();
	/**
	* @brief price hedging instr
	*
	* @brief price hedging instr
	*/
	InstrPtr& pxUndlyInstr();  

protected:
	OCSCfgDataPtr m_cfgData;
	OCSDataPtr m_data;

	StringMapPtr m_strParams;

	sf::contfree_safe_ptr<std::map<int, OptionsChainPtr > > m_ocMap; //
	OptionsChainPtr m_emptyOC;

	CurvePtr m_undlyCurvePrevSettle; ///< underlying previous settle curve

	CurvePtr m_undlyCurveBid; ///< underlfying bid curve
	CurvePtr m_undlyCurveAsk; ///< underlying ask curve
	CurvePtr m_undlyCurveMid; ///< underlying mid curve

	InstrPtr m_undlyInstr; ///< underlying instrument
	InstrPtr m_hedgingInstr; ///< hedging instrument
	InstrPtr m_pxUndlyInstr; ///< pricing underlying instrument

public:
	/**
	* @brief initialization with productid
	*
	* @param product
	*/
	void initProduct(const std::string& product);

	/**
	* @brief initialize with string parameters
	*
	* @param string parameters
	*/
	void updateStrParams(const StringMapPtr& smp);

	/**
	* @brief initialize all
	*/
	void init();

	/**
	* @brief is initialized or not
	*
	* @return if oc is initialized
	*/
	bool isInitialized();

public:
	/**
	* @brief add instrument
	*
	* @param instr
	*/
	void addInstr(InstrPtr& instr);

	/**
	* @brief has OptionsChain with ExpireIntDate
	*
	* @param expireintdate
	*/
	bool hasExpireIntDate(int expireintdate);

	/**
	* @brief get OptionsChain with ExpireIntDate
	*
	* @param expireintdate
	*
	* @return OptionsChain
	*/
	OptionsChainPtr& ocByExpireIntDate(int expireintdate);

	/**
	* @brief get expireintdate vector
	*
	* @return expireintdate vector
	*/
	std::vector<int> getExpireIntDates();

	/**
	* @brief get call instrids for expireintdate
	*
	* @param expireintdate
	*
	* @return call instrids
	*/
	std::vector<std::string> getCallInstrIDsForExpireIntDate(int expireintdate);

	/**
	* @brief get put instrids for expireintdate
	*
	* @param expireintdate
	*
	* @return put instrids
	*/
	std::vector<std::string> getPutInstrIDsForExpireIntDate(int expireintdate);

};//class

  //////typedef for OptionsChains
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OptionsChains> OptionsChainsPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OptionsChains> OptionsChainsPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OptionsChains> OptionsChainsPtr;

#else

typedef ::std::shared_ptr<OptionsChains> OptionsChainsPtr;
#endif


typedef ::sf::safe_ptr<OptionsChains> OptionsChainsSafePtr;

typedef sf::contfree_safe_ptr<OptionsChains> OptionsChainsContFreePtr;
//////end typedef for OptionsChains

//////////////////////////
/////////////////////////////////////////////////////

class XT_COMMON_API OptionsChainsMap {
public:

	/**
	* @name Constructor and Initialization
	*/
	///@{


	/**
	* @brief constructor
	*/
	OptionsChainsMap();

	/**
	* @brief default copy constructor
	*/
	OptionsChainsMap(const OptionsChainsMap& from);// = default;

												 /**
												 * @brief default copy assignment
												 */
	OptionsChainsMap& operator=(const OptionsChainsMap& from);// = default;

															/**
															* @brief destructor
															*/
	virtual ~OptionsChainsMap() {};

	///@}



public:
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > >& ocsMap();

	void add(OptionsChainsPtr& ocs);

	void removeByOCSName(const std::string& name);
	void removeByOCSProductID(const std::string& product);

	bool hasOCSName(const std::string& name);
	bool hasOCSProductID(const std::string& product);

	std::vector<std::string> getOCSNames();
	std::vector<std::string> getOCSProductIDs();

	OptionsChainsPtr& getOptionsChainsByName(const std::string& name);

	OptionsChainsPtr& getOptionsChainsByProductID(const std::string& product);



protected:
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > > m_ocsMap;
	OptionsChainsPtr m_EmptyOptionsChains; ///< null OptionsChains


}; //class XT_COMMON_API OptionsChainsMap {
   //////typedef for OptionsChainsMap
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OptionsChainsMap> OptionsChainsMapPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OptionsChainsMap> OptionsChainsMapPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OptionsChainsMap> OptionsChainsMapPtr;

#else

typedef ::std::shared_ptr<OptionsChainsMap> OptionsChainsMapPtr;
#endif


typedef ::sf::safe_ptr<OptionsChainsMap> OptionsChainsMapSafePtr;

typedef sf::contfree_safe_ptr<OptionsChainsMap> OptionsChainsMapContFreePtr;
//////end typedef for OptionsChainsMap


}//namespace XT


#endif
