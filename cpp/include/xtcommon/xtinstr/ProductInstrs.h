#pragma once
#ifndef HT_PRODUCTINSTRS_H
#define HT_PRODUCTINSTRS_H
/**
* \file ProductInstrs.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of both futures chains and options chains.
*
* \description
*	Designed for use for all instruments for a underlying product.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include <iomanip>
#include "XTConfig.h"
#include "FIXData.pb.h"
#include "typedef_FIXData.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
#include "TagDataWrapper.h"

#include "FuturesChain.h"
#include "OptionsChain.h"

namespace XT {

class XT_COMMON_API ProductInstrs {
public:

	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ProductInstrs() ;
	/**
	* @brief constructor with procut name
	*
	* @param product as product id
	*/
	ProductInstrs(const std::string& product);

	/**
	* @brief default copy constructor
	*/
	ProductInstrs(const ProductInstrs& from);// = default;

	/**
	* @brief default copy assignment
	*/
	ProductInstrs& operator=(const ProductInstrs& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~ProductInstrs();

	///@}

	/**
	* @brief initialization
	*
	* @param undlySym as underlying symbol
	*/
	void init(const std::string& undlySym);

	/**
	* @brief initialization of underlying curves
	*/
	void initUndlyCurves();

	 /**
	 * @brief initialize with string parameters
	 *
	 * @param string parameters
	 */
	void updateStrParams(const StringMapPtr& smp);

	/**
	* @brief add instrument
	*
	* @param instr
	*/
	void addInstr(InstrPtr instr);

	/**
	* @brief calculate previous implied volatilities
	*/
	void calcPrevVols();
	
	/**
	* @brief calculate total options chains' positions and greeks
	*/
	void calcTotOCPosGreeks();

	/**
	* @brief get total value with tag on all strikes
	*
	* @param tag
	*
	* @return double value
	*/
	double getTotOnOCStrikes(int tag);

	/**
	* @brief get total value with tag on all options chains
	*
	* @param tag
	*
	* @return double value
	*/
	double getTotOnOptionsChains(int tag);

	/**
	* @brief set double with tag
	*
	* @param tag
	* @param d as double value
	*/
	void setDouble(int tag, double d);

	/**
	* @brief get double with tag
	*
	* @param tag
	*
	* @return double value
	*/
	double getDouble(int tag) ;

	/**
	* @brief string information for instruments
	*
	* @return instrument information
	*/
	std::string instrInfo();

	/**
	* @brief string for positions
	*
	* @return position information
	*/
	std::string posStr();

	/**
	* @brief write positions string to log file in csv format
	*
	* @param seq
	*/
	void logPosCsvStr(int seq);

	/**
	* @brief write positions string to log file
	*/
	void logPosStr();
protected:
//	InstrPtr m_stock;

	InstrPtr m_underlying; ///< underlying
	ExchangeType::enumtype m_exchangeType; ///< exchange type

	FuturesChainPtr m_fc; ///< futures chain
	std::map<int,OptionsChainPtr > m_ocMap; ///<  map for options chains

	InstrPtr m_deltaHedgingInstr; ///< delta hedgin instrument

	CurvePtr m_undlyCurvePrevSettle; ///< underlying previous settle curve

	CurvePtr m_undlyCurveBid; ///< underlfying bid curve
	CurvePtr m_undlyCurveAsk; ///< underlying ask curve
	CurvePtr m_undlyCurveMid; ///< underlying mid curve

	TagDataWrapperPtr m_tagData; ///< pid data

	std::string m_undlySymbol; ///< underlying symbol

	 

public:
//	InstrPtr& stock();
	/**
	* @brief get underlying
	*
	* @return underlying
	*/
	InstrPtr& underlying();

	/**
	* @brief get exchange type
	*
	* @return exchange type
	*/
	ExchangeType::enumtype getExchangeType();

	/**
	* @brief has security type
	*
	* @return if it has security type st
	*/
	bool hasSecurityType(SecurityType::enumtype st);

	/**
	* @brief get futures chain
	*
	* @return futures chain
	*/
	FuturesChainPtr& futuresChain();

	/**
	* @brief get options chain map
	*
	* @return options chain map
	*/
	std::map<int,OptionsChainPtr >& optionsChainMap();

	/**
	* @brief get delta hedging instrument
	*
	* @return detla hedgin instrument
	*/
	InstrPtr& deltaHedgingInstr();

	/**
	* @brief get data
	*
	* @return data
	*/
	TagDataWrapperPtr& tagData();

	/**
	* @brief get underlying symbol
	*
	* @return underlying symbol
	*/
	const std::string& getUndlySymbol();

	/**
	* @brief get option expire int dates
	*
	* @return vector of option expire int dates
	*/
	std::vector<int> getOptionExpireIntDates();

	/**
	* @brief get cfgData
	*
	* @return   cfgData
	*/
	PICfgDataPtr& cfgData();

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
	PIDataPtr& data();

protected:
	PICfgDataPtr m_cfgData;
	PIDataPtr m_data;

	StringMapPtr m_strParams;

protected:
	mutable boost::shared_mutex m_mutex;

}; //end class ProductInstrs

   //////typedef for ProductInstrs
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<ProductInstrs> ProductInstrsPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<ProductInstrs> ProductInstrsPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<ProductInstrs> ProductInstrsPtr;

#else

typedef ::boost::shared_ptr<ProductInstrs> ProductInstrsPtr;
#endif


typedef ::sf::safe_ptr<ProductInstrs> ProductInstrsSafePtr;

typedef sf::contfree_safe_ptr<ProductInstrs> ProductInstrsContFreePtr;
//////end typedef for ProductInstrs


} //end namespace XT





#endif
