#pragma once
#ifndef XT_PORTFOLIO_H
#define XT_PORTFOLIO_H

/**
* \file Portfolio.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of instrs.
*
* \description
*	Designed for use for portfolio.
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

#include "Rolling.h"
#include "RollingXY.h"


#include "CfgMgr.h"
#include "ExchMgr.h"

#include "OptionsChain.h"
#include "OptionsChains.h"
#include "FuturesChain.h"

namespace XT {

class XT_COMMON_API Portfolio {
public:

	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	Portfolio();
 
	/**
	* @brief default copy constructor
	*/
	Portfolio(const Portfolio& from);// = default;

	/**
	* @brief default copy assignment
	*/
	Portfolio& operator=(const Portfolio& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~Portfolio();

	///@}

	/**
	* @brief get cfg data
	*
	* @return cfg data
	*/
	PortfolioCfgDataPtr& cfgData();

	/**
	* @brief get data
	*
	* @return data
	*/
	PortfolioDataPtr& data();

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	StringMapPtr& strParams();

	sf::contfree_safe_ptr<std::map<std::string, InstrPtr > >& instrMap(); ///< map for id to Instr

	sf::contfree_safe_ptr<std::map<std::string, InstrPtr > >& undlyMap(); ///< map for id to undly
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > >& ocsMap(); ///< map for name to OptionsChains
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > >& fcMap(); ///< map for name to FuturesChain


	/**
	* @brief add instr
	*/
	void addInstr(InstrPtr& instr);

	/**
	* @brief update pnl
	*/
	void updatePnL();

protected:
	PortfolioCfgDataPtr m_cfgData;
	PortfolioDataPtr m_data;

	StringMapPtr m_strParams;

	sf::contfree_safe_ptr<std::map<std::string, InstrPtr > > m_instrMap; ///< map for id to Instr

	sf::contfree_safe_ptr<std::map<std::string, InstrPtr > > m_undlyMap; ///< map for id to undly
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > > m_ocsMap; ///< map for name to OptionsChains
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > > m_fcMap; ///< map for name to FuturesChain
	


};//class

  //////typedef for Portfolio
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<Portfolio> PortfolioPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<Portfolio> PortfolioPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<Portfolio> PortfolioPtr;

#else

typedef ::std::shared_ptr<Portfolio> PortfolioPtr;
#endif


typedef ::sf::safe_ptr<Portfolio> PortfolioSafePtr;

typedef sf::contfree_safe_ptr<Portfolio> PortfolioContFreePtr;
//////end typedef for Portfolio

}//namespace XT


#endif