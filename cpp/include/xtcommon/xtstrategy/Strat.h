#ifndef STRAT_H
#define STRAT_H

/**
* \file Strat.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for strategy.
*
* \description
*	Designed for strategy.
*/

#include <cstdint>
#include <map>
#include <set>
#include <vector>

#include <unordered_map>

#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
 
#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
#include "TagDataWrapper.h"
#include "EnumHelper.h"

#include "Instr.h"
#include "InstrCombo.h"

//#include "InstrBarMaker.h"
//#include "InstrIndicator.h"

#include "StringMap.h"
#include "InstrMgr.h"
#include "SettingsMgr.h"
#include "InstrSettingsMgr.h"

#include "Bar.h"
#include "BarMaker.h"
#include "BarIndicator.h"
#include "BarMgr.h"

#include "XTTimer.h" 

#include "XTApiMgr.h"
#include "InstrEventHandler.h"

#include "ThreadUtil.h"

#include <boost/config.hpp>
#include <boost/dll/import.hpp>

/**
* \file Strat.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a base class for strategy.
*
* \description
*	Designed for base strategy.
*/

namespace XT {

class XT_COMMON_API Strat : public InstrEventHandler
{
public:
		/**
		* @name Constructor and Initialization
		*/
		///@{

		/**
		* @brief constructor
		*/
		Strat();

		/**
		* @brief default copy constructor
		*/
		Strat(const Strat& from);// = default;

		/**
		* @brief default copy assignment
		*/
		Strat& operator=(const Strat& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~Strat();
		///@}

protected:
	StratCfgDataPtr m_cfgData;
	StratDataPtr m_data;

	StringMapPtr m_emptyStringMapPtr;

	StringMapPtr m_strParams; ///< strategy parameters
	 
	std::unordered_map<int, StringMapPtr > m_iidParameters; ///< extra parameters for iids map;
	//
	std::unordered_map<int, int> m_iidToTrdStatusMap; ///< instrument integer id to TrdStatus map;

public:
	/**
	* @brief cfg data
	*
	* @return cfg data
	*/
	StratCfgDataPtr& cfgData();

	/**
	* @brief data
	*
	* @return data
	*/
	StratDataPtr& data();

public:
	/**
	* @brief update cfg data
	*/
	virtual void updateCfgData();

	/**
	* @brief initialization
	*
	* @param smp as strategy parameter
	*/
	virtual void init(StringMapPtr& smp);



	/**
	* @brief start
	*/
	virtual void start();

public:

	void setInstrPrefixesStr(const std::string& s);
	bool hasValidInstrPrefix(const std::string& instrid);

	void setExchidsStr(const std::string & s);
	bool hasExchid(const std::string& exchid);

	void setProductidsStr(const std::string & s);
	bool hasProductid(const std::string& product);

	bool hasInstr(const InstrPtr& instr);

protected:
	std::set<std::string> m_instrPrefixSet;///< instrument prefixes set
	std::set<std::string> m_productidSet; ///< products
	std::set<std::string> m_exchidSet; ///< exchange ids
									   //////////////////////////

public:
	/**
	* @name parameter
	*/
	///@{
	
	/**
	* @brief get strategy parameters
	*
	* @return parameters
	*/
	StringMapPtr& strParams();
	
	/**
	* @brief get parameters by iid
	*
	* @return parameters
	*/
	StringMapPtr& strParamsForIid(int iid);
	
	/**
	* @brief get trdstatus by iid
	*
	* @return trdstatus
	*/
	int getTrdStatusByIid(int iid);
	
	/**
	* @brief set trdstatus for iid
	*
	* @param iid as integer id
	* @param status
	*/
	void setTrdStatusForIid(int iid, int status);
	
	///@}

public:


	/**
	* @brief handle XTMsg
	*
	* @param msg
	*/
	virtual int handleXTMsg(XTMsgPtr& msg);

	/**
	* @brief process InstrEvent
	message InstrEventType
	{
	enum enumtype {
	Unknown = 0;
	MktPxChged = 1;
	MktSzChged = 2;
	OptMktChged = 4;

	OrderSent = 8;
	OrderSentRejected = 16;
	OrderCnf = 32;
	OrderCxlSent = 64;
	OrderCxlRejected = 128;
	OrderCxled = 256;
	OrderFilled = 512;
	OrderAllFilled = 1024;

	NewBar = 2048;
	Timer = 4096;

	}
	}
	*/
	virtual void onInstrEventInfo(InstrEventInfo& mktevent);


	 
};

////

//class XT_COMMON_API Strat : public InstrEventHandler
//{
//public:
//	/** 
//	* @name Constructor and Initialization
//	*/
//	///@{
//
//	/**
//	* @brief constructor
//	*/
//	Strat();
//
//	/**
//	* @brief default copy constructor
//	*/
//	Strat(const Strat& from);// = default;
//
//	/**
//	* @brief default copy assignment
//	*/
//	Strat& operator=(const Strat& from);// = default;
//	
//	/**
//	* @brief destructor
//	*/
//	virtual ~Strat();
//	///@}
//	
//public:
//	/**
//	* @brief start task thread
//	*/
//	virtual void start();
//
//	/**
//	* @brief thread task
//	*/
//	virtual void processTask();
//
//	/**
//	* @brief process InstrEvent
//	*/
//	virtual void onInstrEvent(InstrEventInfo& mktevent);
//
//public:
//	/** 
//	* @name virtual functions
//	*/
//	///@{
//
//	/**
//	* @brief initialization
//	*
//	* @param smp as strategy parameter
//	*/
//	virtual void init(StringMapPtr smp);
//
//	/**
//	* @brief on mktdata event
//	*
//	* @param int integer instrid
//	*/
//	virtual void onMktData(int iid);
//
//	/**
//	* @brief on fill event
//	*
//	* @param int integer instrid
//	* @param int order id
//	*/
//	virtual void onFill(int iid, int orderid);
//
//	/**
//	* @brief on one second timer event
//	*/
//	virtual void onTimer();
//
//	/**
//	* @brief on one minute bar event
//	*
//	* @param int integer instrid
//	* @param int64_t begin datetime of bar
//	*/
//	virtual void onNewBar(int iid, int64_t begindt);
//
//	/**
//	* set intdate
//	* @param int intdate in YYYYMMdd format, such as 20170501
//	*/
//	virtual void setIntDate(int i);
//
//	/**
//	* @brief check if the time is just after session open
//	*
//	* @param int inttime in HHMMSS format, sucha as 180000
//	*/
//	virtual bool isJustSessionOpen(int it);
//
//	/**
//	* @brief check if time is just before session close
//	* 
//	* @param int inttime in HHMMSS format, sucha as 180000
//	*/
//	virtual bool isPreSessionClose(int it);
//
//	/**
//	* @brief add instrument
//	*
//	* @param instr as intrument
//	*/
//	virtual void addInstr(InstrPtr instr);
//
//	/**
//	* @brief add instrument combo
//	*
//	* @param instrcombo 
//	*/
//	virtual void addInstrCombo(InstrComboPtr instrcombo);
//
//
// 
//
//	///@}
//public:
//	/**
//	* @brief initialize BarIndicator parameters
//	*
//	*/
//	void initStratBarIndicatorParameters();
//
//	/**
//	* @brief initialize instruments
//	*
//	*/
//	void initInstrs();
//
//	/**
//	* @brief initialize instrcombos
//	*
//	*/
//	void initInstrCombos();
//
//	/**
//	* @brief add BarIndicator for instr
//	*
//	* @param instr
//	* @param smp as parameter
//	*
//	*/
//	void addBarIndicatorForInstr(InstrPtr instr, StringMapPtr smp);
//
//	/**
//	* @brief add BarIndicator for instrcombo
//	*
//	* @param instrcombo
//	* @param smp as parameter
//	*
//	*/
//	void addBarIndicatorForInstrCombo(InstrComboPtr instrcombo, StringMapPtr smp);
//
//
//	/**
//	* @brief get instrument by integer instrid
//	*
//	* @param iid as integer id
//	*
//	* @return instrument
//	*/
//	InstrPtr& getInstrByIid(int iid);
//
//	///**
//	//* @brief get indicator by integer id
//	//*
//	//* @param iid as integer id
//	//*
//	//* @return BarMakerPtr
//	//*/
//	//BarMakerPtr& getBarMakerByIid(int iid);
//	 
//	/**
//	* @brief is initialized or not
//	*
//	* @return if it is initialized or not
//	*/
//	bool isInitialized();
//
//	/**
//	* @brief set trading status
//	*
//	* @param i as trading status
//	*/
//	void setTrdStatus(int i);
//
//	/**
//	* @brief set istrading flag
//	*
//	* @param i as trading flag
//	*/
//	void setIsTrading(int i);
//
//	/**
//	* @brief get intdate
//	*
//	* @return int date
//	*/
//	int getIntDate();
//
//	/**
//	* @brief get strategy name
//	*
//	* @return strategy name
//	*/
//	const std::string& getStratName();
//
//	/**
//	* @brief set strategy name
//	*
//	* @param name as strategy name
//	*/
//	void setStratName(const std::string& name);
// 
//	/**
//	* @name parameter
//	*/
//	///@{
//
//	/**
//	* @brief get strategy parameters
//	*
//	* @return parameters
//	*/
//	const StringMapPtr& getStratParameters();
//
//	/**
//	* @brief get parameters by iid
//	*
//	* @return parameters
//	*/
//	const StringMapPtr& getParametersForIid(int iid);
//
//	/**
//	* @brief get trdstatus by iid
//	*
//	* @return trdstatus
//	*/
//	int getTrdStatusByIid(int iid);
//
//	/**
//	* @brief set trdstatus for iid
//	*
//	* @param iid as integer id
//	* @param status
//	*/
//	void setTrdStatusForIid(int iid, int status);
//
//
//
//	///@}
// 
//protected:
//	InstrPtr m_EmptyInstr; ///< null instrument
//	BarMakerPtr m_EmptyBarMaker; ///< null barmaker
//	BarIndicatorPtr m_empty_barindicator; ///< null indicator
//	StringMapPtr m_empty_parameters; ///< empty parameters
//
//	boost::unordered_map<int, InstrPtr > m_instrs; ///< instruemnts map
//	boost::unordered_map<std::string, InstrComboPtr > m_instrCombos; ///< instrcombos map
//
//
//	std::vector<StringMapPtr > m_stratBarIndicatorParameters; ///< bar indcator parameters
//	boost::unordered_map<int, std::vector<StringMapPtr > > m_iidToBarIndicatorParameters; ///< iit to bar indicator parameters
//
////	boost::unordered_map<int, BarMakerPtr > m_barMakerMap; ///< barmakers map
// 
//protected:
//	std::string m_stratName; ///< strategy name
//	int m_intdate; ///< int date
//	bool m_isInitialized; ///< is initialized or not
//
//	int m_isTrading; ///< is trading or not
//	int m_trdStatus; ///< trading status
// 
//	////market data
//	int64_t m_lastMktDataTs; ///< last market data timestamp
//	int m_lastMktDataIntTime; ///< last market data int time
// 
//	StringMapPtr m_stratParameters; ///< strategy parameters
// 
//	boost::unordered_map<int, StringMapPtr > m_iidParameters; ///< extra parameters for iids map;
//
//	boost::unordered_map<int, int> m_iidToTrdStatusMap; ///< instrument integer id to TrdStatus map;
//protected:
//	//boost::unordered_map<int,  boost::signals2::connection>  m_connectionMktDataMap; ///< on mkt data event connection map
//	//boost::unordered_map<int,  boost::signals2::connection>  m_connectionFillMap; ///< on fill event connection map
//	//boost::unordered_map<int,  boost::signals2::connection>  m_connectionNewBarMap; ///< new bar event connection map
// //
//	//boost::shared_ptr<XTTimer> m_timer;///< timer
//	//boost::signals2::connection m_connectionTimer; ///< connection to timer
//
//protected:
//	std::unordered_map<std::string, std::shared_ptr<std::thread> > m_threads;
// 
//
//};

//////typedef for Strat
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<Strat> StratPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<Strat> StratPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<Strat> StratPtr;

#else

typedef ::std::shared_ptr<Strat> StratPtr;
#endif


typedef ::sf::safe_ptr<Strat> StratSafePtr;

typedef sf::contfree_safe_ptr<Strat> StratContFreePtr;
//////end typedef for Strat


////////////////////
class XT_COMMON_API StratPlugin
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	StratPlugin();

	/**
	* @brief default copy constructor
	*/
	StratPlugin(const StratPlugin& from) = default;

	/**
	* @brief default copy assignment
	*/
	StratPlugin& operator=(const StratPlugin& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~StratPlugin();

	///@}
public:
	/**
	* @name virtual functions
	*/
	///@{

	/**
	* @brief has strategy with name or not
	*
	* @param stratname as strategy name
	*
	* @return if it has strategy with name or not
	*/
	virtual bool hasStrat(const std::string& stratname);

	/**
	* @brief get strategy names
	*
	* @return vector of strategy names
	*/
	virtual std::vector<std::string> getStratNames();

	/**
	* @brief create strategy
	*
	* @param stratname as strategy name
	*
	* @return StratPtr
	*/
	virtual StratPtr createStrat(const std::string& stratname);

	/**
	* @brief add default setting for strategy
	*
	* @param stratname as strategy name
	*/
	virtual void addDefaultStratSetting(const std::string& stratname);

	/**
	* @brief get default setting for strategy
	*
	* @param stratname as strategy name
	*
	* @return StringMapPtr setting
	*/
	virtual StringMapPtr getDefaultStratSetting(const std::string& stratname);

	///@}
};//

  //////typedef for StratPlugin
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<StratPlugin> StratPluginPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<StratPlugin> StratPluginPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<StratPlugin> StratPluginPtr;

#else

typedef ::boost::shared_ptr<StratPlugin> StratPluginPtr;
#endif


typedef ::sf::safe_ptr<StratPlugin> StratPluginSafePtr;

typedef sf::contfree_safe_ptr<StratPlugin> StratPluginContFreePtr;
//////end typedef for StratPlugin


}
#endif
