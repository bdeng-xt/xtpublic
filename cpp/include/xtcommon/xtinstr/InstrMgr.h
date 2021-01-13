#pragma once
#ifndef XT_INSTRMGR_H
#define XT_INSTRMGR_H


/**
* \file InstrMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for instruments.
*
* \description
*	Designed for managing all instruments.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>

//#include <unordered_map>
//#include <atomic>
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

//#include "tbb/concurrent_unordered_map.h"
//#include "tbb/concurrent_unordered_set.h"
//#include "tbb/concurrent_vector.h"

#include "XTConfig.h"

//#include "mrsw_map.h"
//#include "mrsw_unordered_map.h"
#include "safe_ptr.h"


#include "LogUtil.h"
#include "TimeUtil.h"
#include "StringUtil.h"

#include "FIXData.pb.h"
#include "XTData.pb.h"

#include "SettingsMgr.h"

#include "ExchMgr.h"
#include "InstrSpec.h"
#include "Instr.h"
//#include "InstrEvent.h"
#include "InstrLeg.h"
#include "InstrCombo.h"

//#include "InstrIndicator.h"

#include "FuturesChain.h"
#include "OptionsChain.h"
#include "OptionsChains.h"
#include "ProductInstrs.h"

//#include "SqliteUtil.h"
//#include "MongoUtil.h"
#include "MongoDBMgr.h"
#include "SQLiteMgr.h"
#include "GlobalMgr.h"

#include "CurveSurfaceMgr.h"

#include "PBUtil.h"
#include "ZMQMgr.h"
#include "XTTimer.h"
 
#include "WebMgr.h"

#include "XTRapidCsv.h"

#include "StringMap.h"

#include "StringUtil.h"


namespace XT {

class XT_COMMON_API InstrMgr {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	InstrMgr();

	/**
	* @brief default copy constructor
	*/
	InstrMgr(const InstrMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	InstrMgr& operator=(const InstrMgr& from) { return *this; }// = delete;

	/**
	* @brief destructor
	*/
	virtual ~InstrMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static InstrMgr* getInstance();

public:

	/**
	* @brief clear all instrs
	*/
	void clearAll();


protected:
	std::string m_EmptyString; ///< empty string

	InstrPtr m_EmptyInstr; ///< null instrument
	ProductInstrsPtr m_EmptyProductInstrs; ///< null ProductInstrs
	std::map<int,OptionsChainPtr > m_EmptyOptionsChainMap; ///< empty OptionsChain map
	OptionsChainPtr m_EmptyOptionsChain; ///< null OptionsChain
	OptionsChainsPtr m_EmptyOptionsChains; ///< null OptionsChains
	FuturesChainPtr m_EmptyFuturesChain; ///< null FuturesChain


	InstrComboPtr m_EmptyInstrCombo; ///< null InstrCombo
protected:

	int m_instrCount; ///< count for instruments

	int m_initFlag; ///< if initialized

	int m_instrComboCount; ///< count for instrcombos
	int m_instrComboCountStart; ///< start count for instrcombos

public:
	/** 
	* @name Variables
	*/
	///@{


	/**
	* @brief get null instr
	*
	* @return null instr
	*/
	InstrPtr& getEmptyInstr();

	/**
	* @brief get null productinstrs
	*
	* @return null productinstrs
	*/
	ProductInstrsPtr& getEmptyProductInstrs();

	/**
	* @brief get empty optionschain map
	*
	* @return empty optionschain map
	*/
	std::map<int, OptionsChainPtr >& getEmptyOptionsChainMap();

	/**
	* @brief get null optionschain
	*
	* @return null optionschain
	*/
	OptionsChainPtr& getEmptyOptionsChain();

	/**
	* @brief get empty OptionsChains
	*
	* @return empty OptionsChains
	*/
	OptionsChainsPtr& getEmptyOptionsChains();

	/**
	* @brief get null futureschain
	*
	* @return null futureschain
	*/
	FuturesChainPtr& getEmptyFuturesChain();
 
	/**
	* @brief get instr count
	*
	* @return instr count
	*/
	int getInstrCount();
	/**
	* @brief get instr count
	*
	* @param v as instr count
	*/
	void setInstrCount(int v);
	/**
	* @brief increase instr count
	*/
	void increaseInstrCount();

	/**
	* @brief get instrcombo count
	*
	* @return instrcombo count
	*/
	int getInstrComboCount();
	/**
	* @brief get instrcombo count
	*
	* @param v as instrcombo count
	*/
	void setInstrComboCount(int v);
	/**
	* @brief increase instrcombo count
	*/
	void increaseInstrComboCount();
	/**
	* @brief get instrcombo count start
	*
	* @return instrcombo count start
	*/
	int getInstrComboCountStart();


	/**
	* @brief get init flag
	*
	* @return init flag
	*/
	int getInitFlag();
	/**
	* @brief get init flag
	*
	* @param v as init flag
	*/
	void setInitFlag(int v);


	///@}

protected:


	sf::contfree_safe_ptr<std::unordered_map<std::string,InstrPtr > > m_idToInstrMap;///< map for string instrument ID to instrument
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > > m_iidToInstrMap; ///< map for integer id to instrument
	


	sf::contfree_safe_ptr<std::unordered_map<std::string,int> > m_idToIidMap; ///< map for integer id to string id for instruments
	sf::contfree_safe_ptr<std::unordered_map<int, std::string> > m_iidToInstrIDMap; ///< map for integer id to string id for instruments

	sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> > m_localinstridMap;///< localinstrid to instrid map

	sf::contfree_safe_ptr<std::unordered_map<std::string, InstrComboPtr > >m_nameToInstrComboMap; ///< map for string name to InstrCombo
	sf::contfree_safe_ptr<std::unordered_map<int, InstrComboPtr > >m_iidToInstrComboMap; ///< map for integer id to instrcombo


	sf::contfree_safe_ptr<std::set<std::string> > m_exchanges; ///< exchanges
	sf::contfree_safe_ptr<std::set<ExchangeType::enumtype> > m_exchangeTypes; ///< exchange types

	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > > m_iidToStocks; ///< stocks
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > > m_iidToFutures; ///< futures
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > > m_iidToOptions; ///< options
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > > m_iidToETFs; ///< etfs
	sf::contfree_safe_ptr<std::unordered_map<int, InstrPtr > > m_iidToIdxs; ///< idxs

//	sf::contfree_safe_ptr<std::unordered_map<std::string,ProductInstrsPtr > > m_productInstrsMap; ///< map for product anme to ProductInstruments
//	sf::contfree_safe_ptr<std::unordered_map<int, ProductInstrsPtr > > m_iidToProductInstrsMap; ///< map for integer id to ProductInstruments

	sf::contfree_safe_ptr<std::unordered_map<int,OptionsChainPtr > > m_optionIidToChainMap; ///< map for instrument integer id to OptionsChain
	sf::contfree_safe_ptr<std::unordered_map<int, OptionsChainsPtr > > m_optionIidToOCSMap; ///< map for instrument integer id to OptionsChains
	sf::contfree_safe_ptr<std::unordered_map<int,FuturesChainPtr > > m_futureIidToChainMap; ///< map for instrument integer id to FuturesChain

	sf::contfree_safe_ptr<std::map<std::string, OptionsChainPtr > > m_ocMap; ///< map for name to OptionsChain
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > > m_ocsMap; ///< map for name to OptionsChains
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > > m_fcMap; ///< map for name to FuturesChain

//	boost::unordered_map<std::string, boost::shared_ptr<InstrIndicator> > m_instrIndicatorMap; ///< map for instrument to InstrumentIndicator


	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_undlyIidToOCNamesMap; ///< map for undly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_undlyIidToOCSNamesMap; ///< map for undly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_undlyIidToFCNamesMap; ///< map for undly iid to FuturesChain

	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_pxUndlyIidToOCNamesMap; ///< map for pxundly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_pxUndlyIidToOCSNamesMap; ///< map for pxundly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_pxUndlyIidToFCNamesMap; ///< map for pxundly iid to FuturesChain


	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_hedgingIidToOCNamesMap; ///< map for pxundly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_hedgingIidToOCSNamesMap; ///< map for pxundly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > > m_hedgingIidToFCNamesMap; ///< map for pxundly iid to FuturesChain

 
	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > > m_undlyIidToOCMap; ///< map for undly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > > m_undlyIidToOCSMap; ///< map for undly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > > m_undlyIidToFCMap; ///< map for undly iid to FuturesChain

	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > > m_pxUndlyIidToOCMap; ///< map for pxundly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > > m_pxUndlyIidToOCSMap; ///< map for pxundly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > > m_pxUndlyIidToFCMap; ///< map for pxundly iid to FuturesChain


	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > > m_hedgingIidToOCMap; ///< map for pxundly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > > m_hedgingIidToOCSMap; ///< map for pxundly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > > m_hedgingIidToFCMap; ///< map for pxundly iid to FuturesChain

	OptionsChainMapPtr m_EmptyOCMap;
	OptionsChainsMapPtr m_EmptyOCSMap;
	FuturesChainMapPtr m_EmptyFCMap;

	sf::contfree_safe_ptr<std::unordered_set<std::string> > m_invalidSpecInstrIDSet; ///< set for instrid which has invalid instrspec 


public:
	/** 
	* @name Map and Accessors
	*/
	///@{
	/**
	* @brief instrid to instr map
	*
	* @return instrid to instr map
	*/
    sf::contfree_safe_ptr<std::unordered_map<std::string,InstrPtr > >& idToInstrMap();

	/**
	* @brief integer id to instr map
	*
	* @return integer id to instr map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > >& iidToInstrMap();

	/**
	* @brief instrid to integer id map
	*
	* @return instrid to integer id map
	*/
	sf::contfree_safe_ptr<std::unordered_map<std::string,int> >& idToIidMap();

	/**
	* @brief integer id to instrid map
	*
	* @return integer id to instrid map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int, std::string> >& iidToIdMap();

	/**
	* @brief localinstrid to instrid map
	*
	* @return localinstrid map
	*/
	sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> >& localinstridMap();

	/**
	* @brief get set of exchange ids
	*
	* @return set of exchange ids
	*/
	sf::contfree_safe_ptr<std::set<std::string> >& exchanges();

	/**
	* @brief get set of exchange types
	*
	* @return set of exchange types
	*/
	sf::contfree_safe_ptr<std::set<ExchangeType::enumtype> >& exchangeTypes();

	/**
	* @brief get integer id to stocks map
	*
	* @return integer id to stocks map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > >& iidToStocksMap();

	/**
	* @brief get integer id to futures map
	*
	* @return integer id to futures map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > >& iidToFuturesMap();

	/**
	* @brief get integer id to options map
	*
	* @return integer id to options map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,InstrPtr > >& iidToOptionsMap();

	///**
	//* @brief get name to productinstrs map, TO_BE_DEPRECATED
	//*
	//* @return name to productinstrs map
	//*/
	//sf::contfree_safe_ptr<std::unordered_map<std::string,ProductInstrsPtr > >& productInstrsMap();

	///**
	//* @brief get integer id to productinstrs map
	//*
	//* @return integer id to productinstrs map
	//*/
	//sf::contfree_safe_ptr<std::unordered_map<int, ProductInstrsPtr > >& iidToProductInstrsMap();

	/**
	* @brief get integer id to optionschain map
	*
	* @return integer id to optionschain map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,OptionsChainPtr > >& optionIidToChainMap();

	/**
	* @brief integer id to optionschains map
	*
	* @return integer id to optionschains map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int, OptionsChainsPtr > >& optionIidToOCSMap();


	/**
	* @brief get integer id to futureschain map
	*
	* @return integer id to futureschain map
	*/
	sf::contfree_safe_ptr<std::unordered_map<int,FuturesChainPtr > >& futureIidToChainMap();

	/**
	* @brief OptionsChain map
	*
	* @return OptionsChain map
	*/
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainPtr > >& ocMap();  

	/**
	* @brief OptionsChains map
	*
	* @return OptioinsChains map
	*/
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainsPtr > >& ocsMap();  

	/**
	* @brief FuturesChain map
	*
	* @return FuturesChain map
	*/
	sf::contfree_safe_ptr<std::map<std::string, FuturesChainPtr > >& fcMap(); 

 //   boost::unordered_map<std::string, boost::shared_ptr<InstrIndicator> >& instrIndicatorMap();


	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& undlyIidToOCNamesMap(); ///< map for undly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& undlyIidToOCSNamesMap(); ///< map for undly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& undlyIidToFCNamesMap(); ///< map for undly iid to FuturesChain

	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& pxUndlyIidToOCNamesMap(); ///< map for pxundly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& pxUndlyIidToOCSNamesMap(); ///< map for pxundly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& pxUndlyIidToFCNamesMap(); ///< map for pxundly iid to FuturesChain


	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& hedgingIidToOCNamesMap(); ///< map for pxundly iid to OptionsChain
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& hedgingIidToOCSNamesMap(); ///< map for pxundly iid to OptionsChains
	//sf::contfree_safe_ptr<std::map<int, std::set<std::string> > >& hedgingIidToFCNamesMap(); ///< map for pxundly iid to FuturesChain



	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > >& undlyIidToOCMap(); ///< map for undly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > >& undlyIidToOCSMap(); ///< map for undly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > >& undlyIidToFCMap(); ///< map for undly iid to FuturesChain

	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > >& pxUndlyIidToOCMap(); ///< map for pxundly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > >& pxUndlyIidToOCSMap(); ///< map for pxundly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > >& pxUndlyIidToFCMap(); ///< map for pxundly iid to FuturesChain


	sf::contfree_safe_ptr<std::map<int, OptionsChainMapPtr > >& hedgingIidToOCMap(); ///< map for pxundly iid to OptionsChain
	sf::contfree_safe_ptr<std::map<int, OptionsChainsMapPtr > >& hedgingIidToOCSMap(); ///< map for pxundly iid to OptionsChains
	sf::contfree_safe_ptr<std::map<int, FuturesChainMapPtr > >& hedgingIidToFCMap(); ///< map for pxundly iid to FuturesChain

	//////
	OptionsChainMapPtr& getOCMapForUndlyIid(int iid);
	OptionsChainMapPtr& getOCMapForUndlyInstrID(const std::string& instrid);

	OptionsChainsMapPtr& getOCSMapForUndlyIid(int iid);
	OptionsChainsMapPtr& getOCSMapForUndlyInstrID(const std::string& instrid);

	FuturesChainMapPtr& getFCMapForUndlyIid(int iid);
	FuturesChainMapPtr& getFCMapForUndlyInstrID(const std::string& instrid);
	//
	OptionsChainMapPtr& getOCMapForPxUndlyIid(int iid);
	OptionsChainMapPtr& getOCMapForPxUndlyInstrID(const std::string& instrid);

	OptionsChainsMapPtr& getOCSMapForPxUndlyIid(int iid);
	OptionsChainsMapPtr& getOCSMapForPxUndlyInstrID(const std::string& instrid);

	FuturesChainMapPtr& getFCMapForPxUndlyIid(int iid);
	FuturesChainMapPtr& getFCMapForPxUndlyInstrID(const std::string& instrid);
	//
	OptionsChainMapPtr& getOCMapForHedgingIid(int iid);
	OptionsChainMapPtr& getOCMapForHedgingInstrID(const std::string& instrid);

	OptionsChainsMapPtr& getOCSMapForHedgingIid(int iid);
	OptionsChainsMapPtr& getOCSMapForHedgingInstrID(const std::string& instrid);

	FuturesChainMapPtr& getFCMapForHedgingIid(int iid);
	FuturesChainMapPtr& getFCMapForHedgingInstrID(const std::string& instrid);



	bool hasUndlyIidForOC(int iid);
	bool hasUndlyIidForOCS(int iid);
	bool hasUndlyIidForFC(int iid);

	bool hasPxUndlyIidForOC(int iid);
	bool hasPxUndlyIidForOCS(int iid);
	bool hasPxUndlyIidForFC(int iid);
	
	bool hasHedgingIidForOC(int iid);
	bool hasHedgingIidForOCS(int iid);
	bool hasHedgingIidForFC(int iid);

	std::vector<int> getUndlyIidsForOC();
	std::vector<int> getUndlyIidsForOCS();
	std::vector<int> getUndlyIidsForFC();


	std::vector<int> getPxUndlyIidsForOC();
	std::vector<int> getPxUndlyIidsForOCS();
	std::vector<int> getPxUndlyIidsForFC();


	std::vector<int> getHedgingIidsForOC();
	std::vector<int> getHedgingIidsForOCS();
	std::vector<int> getHedgingIidsForFC();

	std::vector<std::string> getUndlyInstrIDsForOC();
	std::vector<std::string> getUndlyInstrIDsForOCS();
	std::vector<std::string> getUndlyInstrIDsForFC();

	std::vector<std::string> getPxUndlyInstrIDsForOC();
	std::vector<std::string> getPxUndlyInstrIDsForOCS();
	std::vector<std::string> getPxUndlyInstrIDsForFC();

	std::vector<std::string> getHedgingInstrIDsForOC();
	std::vector<std::string> getHedgingInstrIDsForOCS();
	std::vector<std::string> getHedgingInstrIDsForFC();

	bool hasUndlyInstrIDForOC(const std::string& instrid);
	bool hasUndlyInstrIDForOCS(const std::string& instrid);
	bool hasUndlyInstrIDForFC(const std::string& instrid);

	bool hasPxUndlyInstrIDForOC(const std::string& instrid);
	bool hasPxUndlyInstrIDForOCS(const std::string& instrid);
	bool hasPxUndlyInstrIDForFC(const std::string& instrid);

	bool hasHedgingInstrIDForOC(const std::string& instrid);
	bool hasHedgingInstrIDForOCS(const std::string& instrid);
	bool hasHedgingInstrIDForFC(const std::string& instrid);

	std::vector<std::string> getOCNamesForUndlyIid(int iid);
	std::vector<std::string> getOCNamesForUndlyInstrID(const std::string& instrid);
	std::vector<std::string> getOCSNamesForUndlyIid(int iid);
	std::vector<std::string> getOCSNamesForUndlyInstrID(const std::string& instrid);
	std::vector<std::string> getFCNamesForUndlyIid(int iid);
	std::vector<std::string> getFCNamesForUndlyInstrID(const std::string& instrid);

	std::vector<std::string> getOCNamesForPxUndlyIid(int iid);
	std::vector<std::string> getOCNamesForPxUndlyInstrID(const std::string& instrid);
	std::vector<std::string> getOCSNamesForPxUndlyIid(int iid);
	std::vector<std::string> getOCSNamesForPxUndlyInstrID(const std::string& instrid);
	std::vector<std::string> getFCNamesForPxUndlyIid(int iid);
	std::vector<std::string> getFCNamesForPxUndlyInstrID(const std::string& instrid);

	std::vector<std::string> getOCNamesForHedgingIid(int iid);
	std::vector<std::string> getOCNamesForHedgingInstrID(const std::string& instrid);
	std::vector<std::string> getOCSNamesForHedgingIid(int iid);
	std::vector<std::string> getOCSNamesForHedgingInstrID(const std::string& instrid);
	std::vector<std::string> getFCNamesForHedgingIid(int iid);
	std::vector<std::string> getFCNamesForHedgingInstrID(const std::string& instrid);
/////////////////////
	/**
	* @brief has instrument with ID
	*
	* @param instrid as instrid
	*
	* @return if instrid exists
	*/
	bool hasInstr(const std::string& instrid);

	/**
	* @brief has iid
	*
	* @param iid as integer id
	*
	* @return if integer id exists
	*/
	bool hasIidForInstr(int iid);

	/**
	* @brief get instrument by ID
	*
	* @param instrid as instrid
	*
	* @return instr
	*/
	InstrPtr& getInstr(const std::string& instrid) ;

	/**
	* @brief get instrument by iid
	*
	* @param iid as integer id
	*
	* @return instr
	*/
	InstrPtr& getInstrByIid(int iid);

	/**
	* @brief get instrument by localinstrid
	*
	* @param localinstrid
	*
	* @return instr
	*/
	InstrPtr& getInstrByLocalInstrID(const std::string& localinstrid);

	/**
	* @brief get instrid for localinstrid
	*
	* @param localinstrid
	*
	* @return instrid
	*/
	const std::string& getInstrIDForLocalInstrID(const std::string& localinstrid);

	/**
	* @brief get localinstrid for instrid
	*
	* @param instrid
	*
	* @return localinstrid
	*/
	const std::string& getLocalInstrIDForInstrID(const std::string& instrid);

	/**
	* @brief add (localinstrid, instrid) pair
	*
	* @param instrid
	* @param localinstrid
	*/
	void addInstrIDForLocalInstrID(const std::string& instrid, const std::string& localinstrid);

	/**
	* @brief has localinstrid
	*
	* @param localinstrid
	*/
	bool hasLocalInstrID(const std::string& localinstrid);


	/**
	* @brief get integer id by string instrument ID
	*
	* @param instrid as instrid
	*
	* @return integer id
	*/
	int getIidForInstr(const std::string& instrid);

	/**
	* @brief get all instrument ids
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDs();



 
	/**
	* @brief has product
	*
	* @param product
	*/
	bool hasProductID(const std::string& product);



	/**
	* @brief get product name list
	* 
	* @return vector of product ids
	*/
	std::vector<std::string> getProductIDs();

	/**
	* @brief get futures chain name list
	*
	* @return vector of futures chain names
	*/
	std::vector<std::string> getFuturesChainNames();

	/**
	* @brief get options chain name list
	*
	* @return vector of options chain names
	*/
	std::vector<std::string> getOptionsChainNames();

	/**
	* @brief get futures chain product names by exchid
	*
	* @param s as exchange id
	*
	* @return vector of product ids
	*/
	std::vector<std::string> getFuturesChainProductIDsByExchID(const std::string& s);

	/**
	* @brief get options chain product names by exchid
	*
	* @param s as exchange id
	*
	* @return vector of product ids
	*/
	std::vector<std::string> getOptionsChainProductIDsByExchID(const std::string& s);


	///**
	//* @brief get productInstrs by product name, TO_BE_DEPRECATED
	//*
	//* @param product as product id
	//*
	//* @return productinstrs
	//*/
	//ProductInstrsPtr& getProductInstrs(const std::string& product);

	///**
	//* @brief get OptionsChain map by product name, TO_BE_DEPRECATED
	//*
	//* @param product as product id
	//*
	//* @return map of optionschain
	//*/
	//std::map<int,OptionsChainPtr >& getOptionsChainMap(const std::string& product);

	/**
	* @brief has product for OptionsChains
	*
	* @param product
	*
	* @return if there is product for OptionsChains
	*/
	bool hasProductIDForOCS(const std::string& product);

	/**
	* @brief get option products
	*
	* @return vector of option products
	*/
	std::vector<std::string> getOptionProductIDs();


	/**
	* @brief get ocs names
	*
	* @return vector of ocs names
	*/
	std::vector<std::string> getOCSNames();

	/**
	* @brief get OptionsChains by product
	*
	* @param product
	*
	* @return OptionsChains
	*/
	OptionsChainsPtr& getOCS(const std::string& product);

	/**
	* @brief has ocs name or not
	*
	* @return if ocs_name exists or not
	*/
	bool hasOCSName(const std::string& ocsname);

	/**
	* @brief get OptionsChains by name
	*
	* @return OptionsChains
	*/
	OptionsChainsPtr& getOCSByName(const std::string& ocsname);
	

	/**
	* @brief get OptionsChain by product name and expiry date
	*
	* @param product as product id
	* @param expireIntDate as expire int date
	*
	* @return optionschain
	*/
	OptionsChainPtr& getOptionsChain(const std::string& product, int expireIntDate);

	/**
	* @brief has optionschain for iid
	*
	* @param iid
	*
	* @return true or false
	*/
	bool hasOptionIid(int iid);

	/**
	* @brief get OptionsChain by option instr iid
	*
	* @param iid
	*
	* @return optionschain
	*/
	OptionsChainPtr& getOptionsChainByIid(int iid);

	/**
	* @brief has oc name or not
	*
	* @return if oc_name exists or not
	*/
	bool hasOptionsChainName(const std::string& ocname);

	/**
	* @brief get OptionsChain by name
	*
	* @return OptionsChain
	*/
	OptionsChainPtr& getOptionsChainByName(const std::string& ocname);

	/**
	* @brief has product for FuturesChain
	*
	* @param product
	*
	* @return if there is FturesChains with product
	*/
	bool hasProudctIDForFuturesChain(const std::string& product);

	/**
	* @brief get products for futures
	*
	* @return vector of future products
	*/
	std::vector<std::string> getFutureProductIDs();

	/**
	* @brief get futures chain by product name
	*
	* @param product as product id
	*
	* @return futureschain
	*/
	FuturesChainPtr& getFuturesChain(const std::string& product);

	/**
	* @brief has future iid
	*
	* @param iid
	*
	* @return if iid is for future instr
	*/
	bool hasFutureIid(int iid);

	/**
	* @brief get FuturesChain by option instr iid
	*
	* @param iid
	*
	* @return futureschain
	*/
	FuturesChainPtr& getFuturesChainByIid(int iid);

	/**
	* @brief has fc name or not
	* 
	* @return if fc_name exists or not
	*/
	bool hasFuturesChainName(const std::string& fcname);

	/**
	* @brief get FuturesChain by name
	*
	* @return FuturesChain
	*/
	FuturesChainPtr& getFuturesChainByName(const std::string& fcname);

/////parse ocname ocsname, fcname
	StringMapPtr parseFCName(const std::string& name);

	std::string getFCName(const std::string& productid);
	
	StringMapPtr parseOCSName(const std::string& name);

	std::string getOCSName(const std::string& productid);

	StringMapPtr parseOCName(const std::string& name);

	std::string getOCName(const std::string& name, int expireintdate);





///////////////////////////////////
	/**
	* @brief has iid for instrcombo
	*
	* @param iid as integer id
	*
	* @return integer id exists
	*/
	bool hasIidForInstrCombo(int iid);

	/**
	* @brief get instrcombo by integer id
	*
	* @param iid as integer id
	*
	* @return instrcombo
	*/
	InstrComboPtr& getInstrComboByIid(int iid);


	/**
	* @brief has name for instrcombo
	*
	* @param name as combo name
	*
	* @return if name exists
	*/
	bool hasNameForInstrCombo(const std::string& name);

	/**
	* @brief get instrcombo by name
	* 
	* @param name as combo name
	*
	* @return instrcombo
	*/
	InstrComboPtr& getInstrComboByName(const std::string& name);



	///@}


 

public:
	/** 
	* @name Init
	*/
	///@{

	/**
	* @brief initialize FuturesChain
	*
	* @param fc
	*/
	void initFuturesChain(FuturesChainPtr& fc);


	/**
	* @brief initialize OptionsChain
	*
	* @param oc
	*/
	void initOptionsChain(OptionsChainPtr& oc);


	/**
	* @brief initialize OptionsChains
	*
	* @param ocs
	*/
	void initOptionsChains(OptionsChainsPtr& ocs);

	///**
	//* @brief initialize ProductInstr, TO_BE_DEPRECATED
	//*
	//* @param pi
	//*/
	//void initProductInstrs(ProductInstrsPtr& pi);   


	/**
	* @brief initialization with trading intdate
	*
	* @param intdate as int date
	*/
	void init();

	///@}

public:

	/**
	* @name InstrSpec
	*/
	///@{

	/**
	* @brief create InstrSpec from string definition map
	*
	* @param strmap
	*
	* @return InstrSpec pointer
	*/
	InstrSpecPtr createInstrSpecFromStrMap(const std::map<std::string, std::string>& nameValueMap);


	/**
	* @brief create InstrSpec from name vector and value vector
	*
	* @param nameVec as name vector
	* @param valueVec as value vector
	*
	* @return InstrSpec pointer
	*/
	InstrSpecPtr createInstrSpecFromNameValueVectors(const std::vector<std::string>& nameVec, const std::vector<std::string>& valueVec);


	/**
	* @brief get InstrSpec from data
	*
	* @param instrspecdata
	*
	* @return instrspec
	*/
	InstrSpecPtr createInstrSpecFromData(InstrSpecDataPtr& instrspecdata);

	/**
	* @brief factory function with parameters
	*
	* @param exchangeID
	* @param instrumentID
	* @param securityType
	* @param symbol
	* @param expireintdate
	* @param callputtype
	* @param strikeprice
	* @param pricetick
	* @param contractmultiplier
	*
	* @return InstrSpec
	*/
	InstrSpecPtr createInstrSpecFromParams(const std::string& exchangeID, const std::string& instrumentID, const std::string& securityType,
		const std::string& productid, int expireintdate, int callputtype, double strikeprice, double pricetick, double contractmultiplier);

	/**
	* @brief create instr from instrspec
	*
	* @param instrspec
	*
	* @return instr
	*/
	InstrPtr createInstr(InstrSpecPtr& instrspec);

	/**
	* @brief create instr from params
	* @param exchangeID
	* @param instrumentID
	* @param securityType
	* @param symbol
	* @param expireintdate
	* @param callputtype
	* @param strikeprice
	* @param pricetick
	* @param contractmultiplier
	* @param booklevels
	*
	* @return instr
	*/
	InstrPtr createInstrFromParams(const std::string& exchid, const std::string& instrid, const std::string& securitytype,
		const std::string& productid, int expireintdate, int callputtype, double strikeprice, double pricetick, double contractmultiplier,
		int booklevels);


	///@}

	/** 
	* @name Add
	*/
	///@{

	 /**
	 * @brief add instrument
	 *
	 * @param instr
	 */
	void addInstr(InstrPtr& instr);

	///**
	//* @brief add instrs by sql
	//*
	//* @param sql as query string
	//* @param booklevels
	//*/
	//void addInstrsBySql(const std::string& sql, int booklevels);

	/**
	* @brief add instrs by sql from maindb
	*
	* @param sql as query string
	*/
	void addInstrsFromMainDB(const std::string& sql, int booklevels=5);

	/**
	* @brief has instrid in maindb
	*/
	bool hasInstrIDInMainDB(const std::string& instrid);

	/**
	* @brief add instr to maindb
	*/
	void addInstrToMainDB(InstrPtr& instr);

	/**
	* @brief add instrs from csv file
	* @param csv file
	* @booklevels
	* @instr prefix
	*
	*/
	void addInstrsFromCsvFile(const std::string& csvfile, int booklevels, const std::string& prefix);

	/**
	* @brief add instrs in settings
	*/
	void addInstrsInCfg();

	/**
	* @brief add SSE stocks from maindb
	*
	* @param booklevels
	*/
	void addSSEStockInstrsFromMainDb(int booklevels);

	/**
	* @brief add SSE funds from maindb
	*
	* @param booklevels
	*/
	void addSSEFundInstrsFromMainDb(int booklevels);

	/**
	* @brief add SZSE stocks from maindb
	*
	* @param booklevels
	*/
	void addSZSEStockInstrsFromMainDb(int booklevels);

	/**
	* @brief add SZSE funds from maindb
	*
	* @param booklevels
	*/
	void addSZSEFundInstrsFromMainDb(int booklevels);

	/**
	* @brief add futures from maindb
	*
	* @param intdate as int date
	* @param maxday as max span for expire intdates
	* @param booklevels
	* @param exch as exchange id
	*/
	void addFuturesFromMainDb(int intdate, int maxdays, int booklevels, const std::string& exch);

	/**
	* @brief add options from maindb
	*
	* @param intdate as int date
	* @param maxday as max span for expire intdates
	* @param booklevels
	* @param exch as exchange id
	*/
	void addOptionsFromMainDb(int intdate, int maxdays, int booklevels, const std::string& exch);

	/**
	* @brief add instrs from mongodb db_ts
	*
	* @param intdate as intdate
	* @param query string
	* @param collection name
	*	//add stock instrs for SSE querystr: {"exchange":"SSE"}    colname="stock_basic"
	* //add etf instrs for SSE querystr: {"exchange":"SSE"} colname = "fund_basic"
	* //add future instrs for SHFE querystr: {"exchange":"SHFE"} colname="fut_basic"
	* //add option instrs for SSE querystr: {"exchange":"SSE"} colname="opt_basic"
	* //add index for SSE querystr: {"exchange":"SSE"} colname="index_basic"
	*
	*/
	void addInstrsFromMongoDbTs(int intdate, const std::string& query_str, const std::string& colname);

	/**
	* @brief update daily data from mongodb db_ts
	*
	* @param intdate as intdate
	* @param query string
	* @param collection name
	*
	*/
	void updateDailyDataFromMongoDbTs(int intdate, const std::string& query_str, const std::string& colname);


	/**
	* @brief update previous daily data from mongodb db_ts
	*
	* @param previntdate as previous intdate
	* @param query string
	* @param collection name
	*
	*/
	void updatePrevDailyDataFromMongoDbTs(int previntdate, const std::string& query_str, const std::string& colname);

	/**
	* @brief add instrument by InstrID
	*
	* @param instrid as instrid
	* @param booklevels as book levels
	*/
	void addInstrByInstrID(const std::string& instrid, int booklevels );

	/**
	* @brief add instrid for invalid instrspec 
	*
	* @param instrid as instrid
	*/
	void addInstrIDForInvalidInstrSpec(const std::string& instrid);

	/**
	* @brief has invalid instrspec
	*
	* @param instrid as instrid
	*
	* @return if instr has invalid specification
	*/
	bool hasInvalidInstrSpec(const std::string& instrid);

	/**
	* @brief get all instrids which have invalid instrspec
	*
	* @return vector of all instrids which have invalid instrspec
	*/
	std::vector<std::string> getInvalidInstrSpecInstrIDs();

	/**
	* @brief get string for all instrids which have invalid instrspec
	*
	* @return string for all instrids which have invalid instrspec
	*/
	std::string getInvalidInstrSpecInstrIDsStr();

	/**
	* @brief add instrcombo
	*
	* @param instrcombo
	*/
	void addInstrCombo(InstrComboPtr& instrcombo);

	/**
	* @brief add instrcombo by specstr
	*
	* @param s as specification string
	*/
	void addInstrComboBySpecStr(const std::string& s);

	/**
	* @brief add instrcombos in settings
	*/
	void addInstrCombosInCfg();


	/**
	* @brief add instrs from file
	*/
	void addInstrsFromFile(const std::string& filename, const StringMapPtr& smp);

	/**
	* @brief add instr from str
	*
	* @param s
	* @param datatype
	*/
	void addInstrFromStr(const std::string& s, const std::string& datatype);

protected:
	void addInstrsFromHSInstrRefFile(const std::string& filename);

	void addInstrFromHSInstrRefStr(const std::string& line);

	void addInstrsFromHSInstrXmlFile(const std::string& filename);


	/**
	* @brief handle XTInstr file
	*/
	void addInstrsFromXTInstrFile(const std::string& filename);

	/**
	* @brief add instr from XTInstr csv str
	*/
	void addInstrFromXTInstrJsonCsvStr(const std::string& s);

	/**
	* @brief handle CTP InstrumentField jsont string
	*/
	void addInstrFromCTPInstrJsonStr(const std::string& s);

	/**
	* @brief handle CTP InstrumentField csv data vector
	*/
	void addInstrFromCTPInstrDataVector(const std::vector<std::string>& datavector, std::vector<std::string>& headervector);

	/**
	* @brief handle CTP InstrumentField csv data string
	*/
	void addInstrFromCTPInstrDataCsvStr(const std::string& datastr, const std::string& headerstr, const std::string& sep = ",");

	void addInstrsFromCTPInstrJsonFile(const std::string& filename);

 
	void addInstrsFromCTPInstrCsvFile(const std::string& filename);

	void addInstrFromDERIBITInstrID(const std::string& s);

	void addInstrsFromDERIBITInstrIDFile(const std::string& s);

public:

	/** 
	* @name instruments information
	*/
	///@{

	/**
	* @brief get exchangetypes
	*
	* @return vector of exchange types
	*/
	std::vector<ExchangeType::enumtype> getExchangeTypes();

	/**
	* @brief get exchange ids
	*
	* @return vector of exchange ids
	*/
	std::vector<std::string> getExchIDs();


	/**
	* @brief get security type vector for exchange type
	*
	* @param et as exchange type
	*
	* @return vector of security types
	*/
	std::vector<SecurityType::enumtype> getSecurityTypeForExchangeType(ExchangeType::enumtype et);

	/**
	* @brief get security type vector for exchid
	*
	* @param s as exchange id
	*
	* @return vector of security types
	*/
	std::vector<SecurityType::enumtype> getSecurityTypesForExchID(const std::string& s);

	/**
	* @brief get product ids vector for exchangetype and securitytype
	*
	* @param et as exchange type
	* @param st as security type
	*
	* @return vector of productids
	*/
	std::vector<std::string> getProductIDsForExchangeTypeAndSecurityType(ExchangeType::enumtype et, SecurityType::enumtype st);


	/**
	* @brief get stock instrids for exchangetype
	*
	* @param et as exchange type
	*
	* @return vector of stock instrids
	*/
	std::vector<std::string> getStockInstrIDsForExchangeType(ExchangeType::enumtype et);

	/**
	* @brief get etf instrids for exchangetype
	*
	* @param et as exchange type
	*
	* @return vector of etf instrids
	*/
	std::vector<std::string> getETFInstrIDsForExchangeType(ExchangeType::enumtype et);

	/**
	* @brief get future instrids for productid
	*
	* @param s as product id
	*
	* @return vector of future instrids
	*/
	std::vector<std::string> getFutureInstrIDsForProductID( const std::string & s);

	/**
	* @brief get option expireintdates for productid
	*
	* @param s as product id
	*
	* @return vector of expire intdates
	*/
	std::vector<int> getOptionExpireIntDatesForProductID(const std::string & s);

	/**
	* @brief get call instrids for productid
	*
	* @param s as product id
	* @param expireintdate
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getCallInstrIDsForProductID( const std::string & s, int expireintdate);

	/**
	* @brief get put instrids for productid
	*
	* @param s as product id
	* @param expireintdate
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getPutInstrIDsForProductID(const std::string & s, int expireintdate);


	/**
	* @brief get all instrids vector
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getAllInstrIDs();

	/**
	* @brief get all localinstrids vector
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getAllLocalInstrIDs();

	/**
	* @brief get instrids by prefix str
	*
	* @param s as prefixes str, seperated by ,
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForPrefixStr(const std::string & s);

	/**
	* @brief get localinstrids by prefix str
	*
	* @param s as prefixes str, seperated by ,
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForPrefixStr(const std::string & s);

	/**
	* @brief get instrids by prefix set
	*
	* @param items_set as set
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForPrefixSet(const std::set<std::string> & items_set);

	/**
	* @brief get localinstrids by prefix set
	*
	* @param items_set as set
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForPrefixSet(const std::set<std::string> & items_set);

	/**
	* @brief get instrids by product str
	*
	* @param s as product str, seperated by ,
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForProductIDStr(const std::string & s);

	/**
	* @brief get localinstrids by product str
	*
	* @param s as product str, seperated by ,
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForProductIDStr(const std::string & s);

	/**
	* @brief get instrids by product set
	*
	* @param items_set as product set
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForProductIDSet(const std::set<std::string> & items_set);

	/**
	* @brief get localinstrids by product set
	*
	* @param items_set as product set
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForProductIDSet(const std::set<std::string> & items_set);

	/**
	* @brief get instrids by exchid str
	*
	* @param s as exchid str, seperated by ,
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForExchIDStr(const std::string & s);

	/**
	* @brief get localinstrids by exchid str
	*
	* @param s as exchid str, seperated by ,
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForExchIDStr(const std::string & s);

	/**
	* @brief get instrids by exchid set
	*
	* @param items_set as exchid set
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForExchIDSet(const std::set<std::string> & items_set);

	/**
	* @brief get localinstrids by exchid set
	*
	* @param items_set as exchid set
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForExchIDSet(const std::set<std::string> & items_set);

	/**
	* @brief get instrids by prefix and exchid set
	*
	* @param prefix_set 
	* @param exch_set
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForPrefixExchIDSet(const std::set<std::string> & prefix_set, const std::set<std::string> & exch_set);

	/**
	* @brief get localinstrids by prefix and exchid set
	*
	* @param prefix_set
	* @param exch_set
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForPrefixExchIDSet(const std::set<std::string> & prefix_set, const std::set<std::string> & exch_set);

	/**
	* @brief get instrids by prefix and exchid str
	*
	* @param prefix_str
	* @param exch_str
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsForPrefixExchIDStr(const std::string & prefix_str, const std::string & exch_str);

	/**
	* @brief get localinstrids by prefix and exchid str
	*
	* @param prefix_str
	* @param exch_str
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsForPrefixExchIDStr(const std::string & prefix_str, const std::string & exch_str);


	/**
	* @brief get all instrument ids by filter type
	*
	* @return vector of instrids
	*/
	std::vector<std::string> getInstrIDsByFilterType(const std::string& filterstr, int filtertype);	

	/**
	* @brief get all local instrument ids by filter type
	*
	* @return vector of localinstrids
	*/
	std::vector<std::string> getLocalInstrIDsByFilterType(const std::string& filterstr, int filtertype);

	///@}

//	/**
//	* @name Md and Trd Api
//	*/
//	///@{
//protected:
//	std::unordered_map<std::string, BrokerApiType::enumtype> m_idToMdApiTypeMap; ///< map for instrument id to market data Api type
//	std::unordered_map<int, BrokerApiType::enumtype> m_iidToMdApiTypeMap;///< map for iid to market data api type
//
//	std::unordered_map<std::string, BrokerApiType::enumtype> m_idToTrdApiTypeMap; ///< map for instrument id to trd api type
//	std::unordered_map<int, BrokerApiType::enumtype> m_iidToTrdApiTypeMap; ///< map for iid to trd api type
//
//public:
//	/**
//	* @brief string id to market data api type map
//	*
//	* @return string id to market data api type map
//	*/
//	std::unordered_map<std::string, BrokerApiType::enumtype>& idToMdApiTypeMap();
//	/**
//	* @brief integer id to market data api type map
//	*
//	* @return integer id to market data api type map
//	*/
//	std::unordered_map<int, BrokerApiType::enumtype>& iidToMdApiTypeMap();
//
//	/**
//	* @brief string id to trade api type map
//	*
//	* @return string id to trade api type map
//	*/
//	std::unordered_map<std::string, BrokerApiType::enumtype>& idToTrdApiTypeMap();
//	/**
//	* @brief integer id to trade api type map
//	*
//	* @return integer id to trade api type map
//	*/
//	std::unordered_map<int, BrokerApiType::enumtype>& iidToTrdApiTypeMap();
//
//
//	/**
//	* @brief set market data api type for integer id
//	*
//	* @param iid as integer id
//	* @param api as api type
//	*/
//	void setMdApiTypeForIid(int32_t iid, BrokerApiType::enumtype api);
//	/**
//	* @brief set market data api type for integer id
//	*
//	* @param iid as integer id
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getMdApiTypeForIid(int32_t iid);
//
//	/**
//	* @brief set trade api type for integer id
//	*
//	* @param iid as integer id
//	* @param api as api type
//	*/
//	void setTrdApiTypeForIid(int32_t iid, BrokerApiType::enumtype api);
//
//	/**
//	* @brief set trade api type for integer id
//	*
//	* @param iid as integer id
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getTrdApiTypeForIid(int32_t iid);
//
//	/**
//	* @brief set market data api type for instrid
//	*
//	* @param instrid as instrid
//	* @param api as api type
//	*/
//	void setMdApiTypeForInstrID(const std::string& instrid, BrokerApiType::enumtype api);
//	/**
//	* @brief get market data api type for instrid
//	*
//	* @param instrid as instrid
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getMdApiTypeForInstrID(const std::string& instrid);
//
//	/**
//	* @brief set trade api type for instrid
//	*
//	* @param instrid as instrid
//	* @param api as api type
//	*/
//	void setTrdApiTypeForInstrID(const std::string& instrid, BrokerApiType::enumtype api);
//	/**
//	* @brief get trade api type for instrid
//	*
//	* @param instrid as instrid
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getTrdApiTypeForInstrID(const std::string& instrid);
//
//	/**
//	* @brief set market data api type for instrids
//	*
//	* @param instrids as vector of instrids
//	* @param api as api type
//	*/
//	void setMdApiTypeForInstruments(std::vector<std::string>& instriss, BrokerApiType::enumtype api);
//
//	/**
//	* @brief set trade api type for instrids
//	*
//	* @param instrids as vector of instrids
//	* @param api as api type
//	*/
//	void setTrdApiTypeForInstruments(std::vector<std::string>& instriss, BrokerApiType::enumtype api);
//
//	/**
//	* @brief get market data api type for instrument
//	*
//	* @param instr as instrument
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getMdApiTypeForInstr(const InstrPtr& instr);
//
//	/**
//	* @brief get trade api type for instrument
//	*
//	* @param instr as instrument
//	*
//	* @return api type
//	*/
//	BrokerApiType::enumtype getTrdApiTypeForInstr(const InstrPtr& instr);
//
//	/**
//	* @brief get instrids for market data api type  
//	*
//	* @param baType as api type
//	*
//	* @return vector of instrids
//	*/
//	std::vector<std::string> getInstrIDsForMdApiType(BrokerApiType::enumtype baType);
//
//	/**
//	* @brief get instrids for market data api type in settings
//	*
//	* @param baType as api type
//	*
//	* @return vector of instrids
//	*/
//	std::vector<std::string> getInstrIDsForMdApiTypeInSettings(BrokerApiType::enumtype baType);
//
//	///@}
//
//

 
	/**
	* @name pricing undly
	*/
	///@{

protected:
	sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> > m_pxUndlyProductMap;///< map for product to its px undly
	sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> > m_undlyProductMap;///< map for product to its undly
	sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> > m_hedgingProductMap;///< map for product to its px undly
public:
	/**
	* @brief initialize px undly from cfg file
	*/
	void initPxUndlyProductMapFromCfg();

	/**
	* @brief get px undly product for product
	*
	* @param product
	*/
	std::string getPxUndlyProductForProduct(const std::string& product);

	/**
	* @brief et px undly instrid for instr
	*
	* @param instr
	*/
	std::string getPxUndlyInstrIDForInstr(const InstrPtr& instr);


	/**
	* @brief get anchor instrid for product
	*
	* @param product
	*/
	std::string getPxUndlyInstrIDForProduct(const std::string& product);

//////
/**
* @brief initialize undly from cfg file
*/
	void initUndlyProductMapFromCfg();

	/**
	* @brief get px undly product for product
	*
	* @param product
	*/
	std::string getUndlyProductForProduct(const std::string& product);

	/**
	* @brief et undly instrid for instr
	*
	* @param instr
	*/
	std::string getUndlyInstrIDForInstr(const InstrPtr& instr);


	/**
	* @brief get anchor instrid for product
	*
	* @param product
	*/
	std::string getUndlyInstrIDForProduct(const std::string& product);

//////
/**
* @brief initialize hedging undly from cfg file
*/
	void initHedgingProductMapFromCfg();

	/**
	* @brief get px undly product for product
	*
	* @param product
	*/
	std::string getHedgingProductForProduct(const std::string& product);

	/**
	* @brief et px undly instrid for instr
	*
	* @param instr
	*/
	std::string getHedgingInstrIDForInstr(const InstrPtr& instr);


	/**
	* @brief get hedging instrid for product
	*
	* @param product
	*/
	std::string getHedgingInstrIDForProduct(const std::string& product);

	////////undly, pxundly and hedinginstr
	std::string getUndlyInstrIDForFCName(const std::string& fcname);

	std::string getHedgingInstrIDForFCName(const std::string& fcname);

	std::string getPxUndlyInstrIDForFCName(const std::string& fcname);

	std::string getUndlyProductForFCName(const std::string& fcname);

	std::string getHedgingProductForFCName(const std::string& fcname);

	std::string getPxUndlyProductForFCName(const std::string& fcname);

	//////
	std::string getUndlyInstrIDForOCSName(const std::string& ocsname);

	std::string getHedgingInstrIDForOCSName(const std::string& ocsname);

	std::string getPxUndlyInstrIDForOCSName(const std::string& ocsname);

	std::string getUndlyProductForOCSName(const std::string& ocsname);

	std::string getHedgingProductForOCSName(const std::string& ocsname);

	std::string getPxUndlyProductForOCSName(const std::string& ocsname);

	//////
	std::string getUndlyInstrIDForOCName(const std::string& ocname);

	std::string getHedgingInstrIDForOCName(const std::string& ocname);

	std::string getPxUndlyInstrIDForOCName(const std::string& ocname);

	std::string getUndlyProductForOCName(const std::string& ocname);

	std::string getHedgingProductForOCName(const std::string& ocname);

	std::string getPxUndlyProductForOCName(const std::string& ocname);


	///**
	//* @brief get anchor instrid for futureschain
	//*
	//* @param product
	//*/
	//const std::string& getAnchorInstrIDForFu
	 

	///@}


public:

	std::string getSessionsCfgStr(const std::string& exchid, const std::string& productid);

	std::string getSessionsStr(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);


//	std::vector<SessionInfoPtr> getSessionInfos(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);

//	std::string getSessionInfosStr(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);

	bool updateTs(int64_t ts, const std::string& exchid);

	const SessionPtr& currSession(const std::string& exchid, const std::string& productid);
	const SessionsPtr& currSessions(const std::string& exchid, const std::string& productid);

public:
	/**
	* @name Sina instruments
	*/
	///@{

	/**
	* @brief update stocks and funds from SSE and SZSE
	*/
	void updateStocksFundsFromSSESZSE();

	/**
	* @brief update sina slices
	*/
	void updateSinaSlices();

	/**
	* @brief get sse stocks string
	*
	* @return sse stocks string
	*/
	const std::string& getSSEStocksStr();

	/**
	* @brief get szse stocks string
	*
	* @return szse stocks string
	*/
	const std::string& getSZSEStocksStr();

	/**
	* @brief get sse funds string
	*
	* @return sse funds string
	*/
	const std::string& getSSEFundsStr();

	/**
	* @brief get szse funds string
	*
	* @return szse funds string
	*/
	const std::string& getSZSEFundsStr();

	/**
	* @brief get sse indexes string
	*
	* @return sse indexes string
	*/
	const std::string& getSSEIndexesStr();

	/**
	* @brief get szse indexes string
	*
	* @return szse indexes string
	*/
	const std::string& getSZSEIndexesStr();

	/**
	* @brief get cn sectors string
	*
	* @return cn sectors string
	*/
	const std::string& getCNSectorsStr();

	/**
	* @brief get number of sina slices for SSE stocks
	*
	* @return number of sina slices for SSE stocks
	*/
	int getNumSinaSlicesOfSSEStocks();

	/**
	* @brief get sina slice string for SSE stocks
	*
	* @param i as index
	*
	* @return sina slice string for SSE stocks
	*/
	const std::string& getSinaSliceStrOfSSEStocks(int i);

	/**
	* @brief get number of sina slices for SSE funds
	*
	* @return number of sina slices for SSE funds
	*/
	int getNumSinaSlicesSSEFunds();

	/**
	* @brief get sina slice string for SSE funds
	*
	* @param i as index
	*
	* @return sina slice string for SSE funds
	*/
	const std::string& getSinaSliceStrOfSSEFunds(int i);

	/**
	* @brief get number of sina slices for SZSE stocks
	*
	* @return number of sina slices for SZSE stocks
	*/
	int getNumSinaSlicesOfSZSEStocks();

	/**
	* @brief get sina slice string for SZSE stocks
	*
	* @param i as index
	*
	* @return sina slice string for SZSE stocks
	*/
	const std::string& getSinaSliceStrOfSZSEStocks(int i);

	/**
	* @brief get number of sina slices for SZSE funds
	*
	* @return number of sina slices for SZSE funds
	*/
	int getNumSinaSlicesSZSEFunds();

	/**
	* @brief get sina slice string for SZSE funds
	*
	* @param i as index
	*
	* @return sina slice string for SZSE funds
	*/
	const std::string& getSinaSliceStrOfSZSEFunds(int i);

	///@}

	/**
	* @brief check if code is SSE or SZSE stock
	*
	* @param code
	*
	* @return if code is SSE or SZSE stock
	*/
	bool isSSEOrSZSEStock(const std::string& code);

	/**
	* @brief check if code is SSE or SZSE fund
	*
	* @param code
	*
	* @return if code is SSE or SZSE fund
	*/
	bool isSSEOrSZSEFund(const std::string& code);

	/**
	* @brief check if code is SSE stock or fund
	*
	* @param code
	*
	* @return if code is SSE stock or fund
	*/
	bool isSSEStockOrFund(const std::string& code);

	/**
	* @brief check if code is SZSE stock or fund
	*
	* @param code
	*
	* @return if code is SZSE stock or fund
	*/
	bool isSZSEStockOrFund(const std::string& code);

	/**
	* @brief get productid
	*
	* @param instrid
	* 
	* @return productid
	*/
	std::string getProductIDForCNFuture(const std::string& instrid);


 protected:
	 /**
	 * @breif get slice string vector
	 *
	 * @param s as instrid string 
	 * @param prefix such as SH, SZ
	 * @param slicenum as number of instruments in one slice
	 *
	 * @return vector of slice string
	 */
	 std::vector<std::string> getSliceStrVectorForVector(std::vector<std::string>& s, const std::string& prefix, int slicenum );
 
	 std::unordered_set<std::string> m_SSE_Stocks; ///< set of SSE stocks
	 std::unordered_set<std::string> m_SZSE_Stocks; ///< set of SZSE stocks
	 std::unordered_set<std::string> m_SSE_Funds; ///< set of SSE funds
	 std::unordered_set<std::string> m_SZSE_Funds; ///< set of SZSE funds

	 std::unordered_set<std::string> m_SSE_Indexes; ///< set of SSE indexes
	 std::unordered_set<std::string> m_SZSE_Indexes; ///< set of SZSE indexes

	 std::unordered_set<std::string> m_CN_Sectors; ///< set of cn sectors

	 std::string m_SSE_Stocks_Str; ///< SSE stocks
	 std::string m_SZSE_Stocks_Str; ///< SZSE stocks
	 std::string m_SSE_Funds_Str; ///< SSE funds
	 std::string m_SZSE_Funds_Str; ///< SZSE funds

	 std::string m_SSE_Indexes_Str; ///< SSE indexes
	 std::string m_SZSE_Indexes_Str; ///< SZSE indexes
	 std::string m_CN_Sectors_Str; ///< cn sectors

	 std::vector<std::string> m_Sina_SSE_Stocks_Strs;///< sina SSE stocks
	 std::vector<std::string> m_Sina_SSE_Funds_Strs; ///< sina SSE funds
	 std::vector<std::string> m_Sina_SZSE_Stocks_Strs; ///< sina SZSE stocks
	 std::vector<std::string> m_Sina_SZSE_Funds_Strs; ///< sina SZSE funds

protected:
	std::shared_ptr< boost::signals2::signal<void(std::string)> > m_signalAddInstr; ///< add instr signal

public:
	/**
	* @brief add instr signal
	*
	* @return signal for adding instr
	*/
	std::shared_ptr< boost::signals2::signal<void(std::string)> >& singalAddInstr();


protected:
	
	boost::signals2::connection m_connectionMktTimer; ///< connection
	std::shared_ptr<ConcurrentQueue<int> > m_mktTimerEventQueue; ///< event queue
	std::thread* m_mktTimerEventTaskThread;
	void onMktTimer(int i);
	void processMktTimerEventTask();
 
}; //end class InstrMgr

} //end namespace XT

#endif
