#pragma once
#ifndef XT_EXCH_MGR_H
#define XT_EXCH_MGR_H


/**
* \file ExchMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for exchanges and products.
*
* \description
*	Designed for managing all exchanges and products.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
//#include <unordered_map>
//#include <atomic>
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>

//#include "tbb/concurrent_unordered_map.h"
//#include "tbb/concurrent_unordered_set.h"
//#include "tbb/concurrent_vector.h"

#include "XTConfig.h"

#include "safe_ptr.h"

#include "mrsw_map.h"
#include "mrsw_unordered_map.h"

#include "Exch.h"
#include "Session.h"

#include "LogUtil.h"

#include "FIXData.pb.h"
#include "XTData.pb.h"
#include "XTEnum.pb.h"

namespace XT {

class XT_COMMON_API ExchMgr {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ExchMgr();

	/**
	* @brief default copy constructor
	*/
	ExchMgr(const ExchMgr& from) {}// = delete;

	/**
	* @brief default copy assignment
	*/
	ExchMgr& operator=(const ExchMgr& from) { return *this; }// = delete;

	/**
	* @brief destructor
	*/
	virtual ~ExchMgr();

	///@}

public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static ExchMgr* getInstance();

public:
	void init();

public:
	/**
	* @brief get exchtypeint for exchid
	*
	* @param exchid
	*
	* @return exchiid
	*/
	int getExchTypeIntForExchID(const std::string& exchid);


	/**
	* @brief get exchid for exchiid
	*
	* @praam exchiid
	*
	* @param exchid
	*/
	const std::string& getExchIDForExchTypeInt(int exchiid);

	/**
	* @brief add exchid
	*/
	void addExchID(const std::string& exchid);

	/**
	* @brief has exchid
	*
	* @param exchid
	*
	* @return if exchid exists
	*/
	bool hasExchID(const std::string& exchid);

	/**
	* @brief get Exch
	*
	* @param exchid
	*
	* @return ExchPtr
	*/
	ExchPtr& getExch(const std::string& exchid);

	/**
	* @brief has exchiid
	*
	* @param exchiid
	*
	* @return if exchiid exists
	*/
	bool hasExchIid(int exchiid);

	/**
	* @brief get possible exchids for instrprefix
	*
	* @param instrprefix
	*
	* @return exchids vector
	*/
	std::vector<std::string> getExchIDs();

	/**
	* @brief get possible exchids for instrprefix
	*
	* @param instrprefix
	*
	* @return exchids vector
	*/
	std::vector<std::string> getExchIDsForInstrPrefix(const std::string& prefix);


	/**
	* @brief get Exch
	*
	* @param exchiid
	*
	* @return ExchPtr
	*/
	ExchPtr& getExchByIid(int exchiid);

	/**
	* @brief get exch ini data
	*
	* @return exchIniData
	*/
	XTSimpleIniPtr& getExchIniData(const std::string& exchid);


	/**
	* @brief get exch ini data
	*
	* @return exchIniData
	*/
	XTSimpleIniPtr getDefaultExchIniData(const std::string& exchid);

	/**
	* @brief create instrspec for instrid
	*
	* @param exchid
	* @param instrid
	*
	* @return InstrSpecPtr
	*/
	InstrSpecPtr createInstrSpecFor(const std::string& exchid, const std::string& instrid);

	/**
	* @brief get global params
	*
	* @param exchid
	*
	* @return global params
	*/
	StringMapPtr getGlobalStrParams(const std::string& exchid);

	/**
	* @brief get future product string params
	*
	* @param exchid
	* @param productid
	*
	* @return future product string params
	*/
	StringMapPtr getFutureProductStrParams(const std::string& exchid, const std::string& productid);

	/**
	* @brief get option product string params
	*
	* @param exchid
	* @param productid
	*
	* @return future product string params
	*/
	StringMapPtr getOptionProductStrParams(const std::string& exchid, const std::string& productid);


	std::string getUndlyProduct(const std::string& exchid, const std::string& productid);
	std::string getPxUndlyProduct(const std::string& exchid, const std::string& productid);
	std::string getHedgingProduct(const std::string& exchid, const std::string& productid);

//////


	std::string getSessionsCfgStr(const std::string& exchid, const std::string& productid);

	std::string getSessionsStr(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);


//	std::vector<SessionInfoPtr> getSessionInfos(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);

//	std::string getSessionInfosStr(const std::string& exchid, const std::string& productid, int tradingday, int prevtradingday);

	int updateTs(int64_t ts, const std::string& exchid);

	const SessionPtr& currSession(const std::string& exchid, const std::string& productid);

	const SessionsPtr& currSessions(const std::string& exchid, const std::string& productid);

//	int currSessionIdx(const std::string& exchid, const std::string& productid);
//	int currSessionSeconds(const std::string& exchid, const std::string& productid);


protected:
	int m_extraIntId;
	std::string m_emptyString;
	std::map<int, std::string> m_IntIdToExchIDMap;
	std::map<std::string, int> m_ExchIDtoIntIdMap;

	ExchPtr m_emptyExch;
	XTSimpleIniPtr m_emptyIni;
	SessionPtr m_emptySession;
	SessionsPtr m_emptySessions;
 

	sf::contfree_safe_ptr<std::map<std::string, ExchPtr > > m_idToExchMap;///< map for string exchID to exch
	sf::contfree_safe_ptr<std::map<int, ExchPtr > > m_iidToExchMap; ///< map for integer id to exch
public:
	double getOptionMMSpread_TA(double bidPx, int flag);

	double getOptionMMSpread_SR(double bidPx, int flag);

	double getOptionMMSpread_m(double bidPx, int flag);

	double getOptionMMSpread_c(double bidPx, int flag);

	double getOptionMMSpread_cu(double bidPx, int flag);

	double getOptionMMSpread_ru(double bidPx, int flag);

	double getOptionMMSpread_CF(double bidPx, int flag);

	double getOptionMMSpread_IF(double bidPx, int flag);

	double getOptionMMSpread_ETF(double bidPx, int flag);
	



	double getOptionMMSpread( const std::string& productid, double bidPx, int flag, const std::string& exchid="");

public:
	int getOptionExerciseType(const std::string& productid, const std::string& exchid = "");

protected:
	int getOptionExerciseTypeForCFFEX(const std::string& productid);
	int getOptionExerciseTypeForCZCE(const std::string& productid);
	int getOptionExerciseTypeForDCE(const std::string& productid);
	int getOptionExerciseTypeForSHFE(const std::string& productid);

	int getOptionExerciseTypeForINE(const std::string& productid);

	int getOptionExerciseTypeForSSE(const std::string& productid);
	int getOptionExerciseTypeForSZSE(const std::string& productid);

public:
	std::string getInstrIDPattern(const std::string& exchid, const std::string instrtype);
 
	StringMapPtr parseInstrIDForExchID(const std::string& instrid, const std::string& exchid);

protected:
	StringMapPtr parseInstrIDForCFFEX(const std::string& instrid);


public:
	/**
	* @brief get trading days between
	*
	* @param exchid
	* @param productid
	* @param tradingday
	* @param expiredate
	*/
	int getTradingDaysBetween(const std::string& exchid, const std::string& productid, int tradingday, int expiredate);

	/**
	* @brief get previous tradingday
	*
	* @param exchid
	* @param productid
	* @param intdate
	*/
	int getPrevTradingDay(const std::string& exchid, const std::string& productid, int intdate);


};//class
} //namespace




#endif