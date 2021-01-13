#pragma once
#ifndef XT_EXCH_H
#define XT_EXCH_H

#include <cstdint>
#include <set>
#include <string>
#include <iostream>

#include <memory>


//#include <regex>
#include <boost/xpressive/xpressive.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

#include "XTConfig.h"
#include "log4z.h"

#include "StringMap.h"
#include "XTSimpleIni.h"
#include "CfgMgr.h"
#include "FileUtil.h"
#include "InstrSpec.h"

#include "Session.h"

namespace XT {

class XT_COMMON_API Exch
{

public:

	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	Exch();

	/**
	* @brief default copy constructor
	*/
	Exch(const Exch& from);// = default;
	
	/**
	* @brief default copy assignment
	*/
	Exch& operator=(const Exch& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~Exch();

public:
	void init();

public:
	/**
	* @brief access exch ini data
	*
	* @return exchIniData
	*/
	XTSimpleIniPtr& exchIniData();



	/**
	* @brief load ini file
	*
	* @param inifile as input file name
	*/
	void loadExchIni(const std::string& inifile);

	/**
	* @brief get exchID
	*
	* @return exchID
	*/
	const std::string& getExchID();

	/**
	* @brief set exchID
	*
	* @param exchID
	*/
	void setExchID(const std::string& exchid);

	/**
	* @brief get exchIid
	*
	* @return exchIid
	*/
	int getExchIid();

	/**
	* @brief set exchIid
	*
	* @param exchIid
	*/
	void setExchIid(int exchiid);

	/**
	* @brief create instrspec for instrid
	*
	* @param instrid
	*
	* @return InstrSpecPtr
	*/
	InstrSpecPtr createInstrSpecForInstrID(const std::string& instrid);

	/**
	* @brief get global params
	*
	* @return global params
	*/
	StringMapPtr getGlobalStrParams();

	/**
	* @brief get future product string params
	*
	* @param productid
	*
	* @return future product string params
	*/
	StringMapPtr getFutureProductStrParams(const std::string& productid);

	/**
	* @brief get option product string params
	*
	* @param productid
	*
	* @return future product string params
	*/
	StringMapPtr getOptionProductStrParams(const std::string& productid);

public:
	/**
	* @brief set instrprefixes
	*
	* @param instrprefixes
	*/
	void setInstrPrefixesStr(const std::string& s);

	/**
	* @brief has valid instrprefix
	*
	* @param instrid
	*/
	bool hasValidInstrPrefix(const std::string& instrid);

 
	/**
	* @brief set productids
	*
	* @param productids string
	*/
	void setProductidsStr(const std::string & s);

	/**
	* @brief has productid
	*
	* @param product
	*/
	bool hasProductid(const std::string& product);

	void addProductid(const std::string& product);


	//std::vector<SessionInfoPtr> getSessionInfos(const std::string& productid, int tradingday, int prevtradingday);

	//std::string getSessionInfosStr(const std::string& productid, int tradingday, int prevtradingday);


	int updateTs(int64_t ts);

	//const SessionInfo& currSessionInfo(const std::string& productid);
	//int currSessionIdx(const std::string& productid);
	//int currSessionSeconds(const std::string& productid);

	ExchSessionsPtr& exchSessions();
	const SessionPtr& currSession(const std::string& productid);
	const SessionsPtr& currSessions(const std::string& productid);
protected:
	ExchSessionsPtr m_exchSessions;


public:
	StringMapPtr parseInstrID(const std::string& exchid, const std::string& instrid);

protected:
	StringMapPtr parseSSEInstrID(const std::string& instrid);
	StringMapPtr parseSZSEInstrID(const std::string& instrid);
	StringMapPtr parseSHFEInstrID(const std::string& instrid);
	StringMapPtr parseDCEInstrID(const std::string& instrid);
	StringMapPtr parseCZCEInstrID(const std::string& instrid);
	StringMapPtr parseCFFEXInstrID(const std::string& instrid);

	StringMapPtr parseDERIBITInstrID(const std::string& instrid);
	
protected:
	InstrSpecPtr createCFFEXInstrSpecForInstrID(const std::string& instrid);
	InstrSpecPtr createCZCEInstrSpecForInstrID(const std::string& instrid);
	InstrSpecPtr createDCEInstrSpecForInstrID(const std::string& instrid);
	InstrSpecPtr createSHFEInstrSpecForInstrID(const std::string& instrid);

	InstrSpecPtr createSSEInstrSpecForInstrID(const std::string& instrid);
	InstrSpecPtr createSZSEInstrSpecForInstrID(const std::string& instrid);

	
	int parseDERIBITDayMonYr(const std::string & expiredatestr);
	InstrSpecPtr createDERIBITInstrSpecForInstrID(const std::string& instrid);


	InstrSpecPtr createBINANCEFInstrSpecForInstrID(const std::string& instrid);

protected:
	int m_exchIid;
	std::string m_exchID;

	std::string m_instrprefixes;
	std::string m_productids;

	std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
	std::set<std::string> m_productidSet; ///< products

	XTSimpleIniPtr m_exchIniData;


//	ExchSessionInfoListPtr m_exchSessionInfoList;
//	SessionInfo m_emptySessionInfo;

public:
	int getTradingDaysBetween(const std::string& productid, int tradingday, int expiredate);
	int getPrevTradingDay(const std::string& productid,int intdate);
protected:
	std::vector<int> m_tradingDays;

	std::shared_ptr< std::map<int, int> > m_tradingDaysMap; //tradingday to prevtradingday map
 
public:
	/**
	* @brief get default ini data
	*
	* @param exchid
	*
	* @return inidata
	*/
	static XTSimpleIniPtr getDefaultIniData(const std::string& exchid);

protected:
	static XTSimpleIniPtr getBINANCEFDefaultIniData();
	static XTSimpleIniPtr getCFFEXDefaultIniData();
	static XTSimpleIniPtr getCZCEDefaultIniData();
	static XTSimpleIniPtr getDCEDefaultIniData();
	static XTSimpleIniPtr getDERIBITDefaultIniData();
	
	static XTSimpleIniPtr getINEDefaultIniData();
	static XTSimpleIniPtr getSHFEDefaultIniData();
	static XTSimpleIniPtr getSSEDefaultIniData();
	static XTSimpleIniPtr getSZSEDefaultIniData();

};

//////typedef for Exch
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<Exch> ExchPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<Exch> ExchPtr;
//	typedef sf::contfree_safe_ptr<Exch> ExchPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<Exch> ExchPtr;

#else

typedef ::std::shared_ptr<Exch> ExchPtr;
#endif


typedef ::sf::safe_ptr<Exch> ExchSafePtr;

typedef sf::contfree_safe_ptr<Exch> ExchContFreePtr;
//////end typedef for Exch

}//namespace

#endif