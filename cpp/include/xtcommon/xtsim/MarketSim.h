#pragma once
#ifndef XT_MARKET_SIM_H
#define XT_MARKET_SIM_H

/**
* \file MarketSim.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for market simulation.
*
* \description
*	Designed for use for market simulation.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "StringMap.h"
#include "XTConfig.h"

#include "TimeUtil.h"
#include "Util.h"

#include "GlobalMgr.h"
#include "InstrMgr.h"
#include "StratMgr.h"

#include "RequestMgr.h"

#include "MarketHandler.h"
#include "MarketManager.h"
#include "MarketHandlerSim.h"
#include "SimMd.h"
#include "SimTrader.h"
#include "SimUtil.h"

#include "LineFiles.h"
#include "LineFilesGroup.h"

#include "InstrUtil.h"

namespace XT
{



////////////////////

class XT_COMMON_API MarketSim
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	MarketSim();

	/**
	* @brief default copy constructor
	*/
	MarketSim(const MarketSim& from);// = default;

	/**
	* @brief default copy assignment
	*/
	MarketSim& operator=(const MarketSim& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~MarketSim();
	///@}




	//SimMdPtr& md();

	//SimTraderPtr& trd();

protected:
	StringMapPtr m_cfgStrMap;

//	MarketManagerPtr m_mktMgr;

	SimMdPtr m_md;
	SimTraderPtr m_trd;

	std::vector<std::string> m_csvItems;
	std::string m_csvDelimiter;
	int m_csvSkipCols;
	int m_csvType;


	MktQuoteDataPtr m_mktQuoteData;

	LineFilesGroupPtr m_mktFilesGroup;
	LineFilesPtr m_instrFiles;

public:
	StringMapPtr& cfgStrMap();

	void setCfgStrMap(StringMapPtr p);
public:
	void init();

	void start();

	void processMktDataCsvStr(const std::string& csvstr);

protected:
	void processCTPMktDataCsvStr(const std::string& csvstr);

	void processMktQuoteDataCsvStr(const std::string& csvstr);

protected:
//	void processCTPInstrumentFile(const std::string& filename);

};//class

	  //////typedef for MarketSim

#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<MarketSim> MarketSimPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<MarketSim> MarketSimPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<MarketSim> MarketSimPtr;

#else

typedef ::boost::shared_ptr<MarketSim> MarketSimPtr;
#endif


typedef ::sf::safe_ptr<MarketSim> MarketSimSafePtr;

typedef sf::contfree_safe_ptr<MarketSim> MarketSimContFreePtr;
//////end typedef for MarketSim


}//namespace XT


#endif