#pragma once
#ifndef XT_BARMGR_H
#define XT_BARMGR_H

/**
* \file BarMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a classe for BarMgr.
*
* \description
*	Designed for managing all bars and their indicators.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>
#include <boost/unordered_map.hpp>
#include <boost/signals2.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>

#include "XTConfig.h"
#include "XTData.pb.h"
#include "TagDataWrapper.h"
#include "EnumHelper.h"

#include "SettingsMgr.h"
#include "InstrMgr.h"
#include "StringMap.h"
#include "LogUtil.h"
#include "ta_libc.h"

#include "MongoDBMgr.h"

#include "TALibFuncInfo.h"
#include "Bar.h"
#include "BarIndicator.h"
#include "BarMaker.h"

namespace XT
{

class XT_COMMON_API BarMgr {
public:
	/**
	* @name Constructors and Destructors
	*/
	///@{
	/**
	* @brief constructor
	*/
	BarMgr();

	/**
	* @brief default copy constructor
	*/
	BarMgr(const BarMgr& from);// = default;

	/**
	* @brief default copy assignment
	*/
	BarMgr& operator=(const BarMgr& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~BarMgr();
	
	///@}
	static BarMgr* getInstance();
////


public:
	/**
	* @name empty barlist, barmaker or barindicator
	*/
	///@{
	
	/**
	* @brief get empty barlist
	*
	* @return empty barlist
	*/
	BarListPtr& getEmptyBarListPtr();


	/**
	* @brief get empty barmakerptr
	*
	* @return empty barmakerptr
	*/
	BarMakerPtr& getEmptyBarMakerPtr();


	/**
	* @brief get empty barindicatorptr
	*
	* @return empty barindicatorptr
	*/
	BarIndicatorPtr& getEmptyBarIndicatorPtr();

	///@}

public:
	/**
	* @name BarList functions
	*/
	///@{


	/**
	* @brief get barlist for instr
	*
	* @param instr as instrument
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarListPtr getBarListForInstr(InstrPtr& instr, int64_t startdt, int64_t enddt, int spanseconds);

	/**
	* @brief get barlist for instrument with number limit
	*
	* @param instr as instrument
	* @param enddt as end timestamp
	* @param numlimit as maximum number of entries to pull
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarListPtr getBarListForInstrWithLimit(InstrPtr& instr, int64_t enddt, int numlimit, int spanseconds);

	/**
	* @brief get 60 seconds barlist for instrument
	*
	* @param instr as instrument
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstr(InstrPtr& instr, int64_t startdt, int64_t enddt);

	/**
	* @brief get day barlist for instr
	*
	* @param instr as instrument
	* @param startintdate as start int date
	* @param endintdate as end int date
	*
	* @return barlist
	*/
	BarListPtr getDayBarListForInstr(InstrPtr& instr, int startintdate, int endintdate);

	/**
	* @brief get 60 seconds barlist for instr with number limit
	*
	* @param instr as instrument
	* @param enddt as end timestamp
	* @param numlimt as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstrWithLimit(InstrPtr& instr, int64_t enddt, int numlimit);

	/**
	* @brief get day barlist for instr with number limit
	*
	* @param instr as instrument
	* @param enddt as end timestamp
	* @param numlimt as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr getDayBarListForInstrWithLimit(InstrPtr& instr, int  enddate, int numlimit);

	/**
	* @brief get latest barlist for instr 
	*
	* @param instr as instrument
	* @param dt as end timestamp
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarPtr getLatestBarForInstr(InstrPtr& instr, int64_t dt, int spanseconds);

	/**
	* @brief get latest 60 seconds barlist for instr 
	*
	* @param instr as instrument
	* @param dt as end timestamp
	*
	* @return barlist
	*/
	BarPtr getLatest60sBarForInstr(InstrPtr& instr, int64_t dt);

	/**
	* @brief get latest day barlist for instr 
	*
	* @param instr as instrument
	* @param intdate as int date
	*
	* @return barlist
	*/
	BarPtr getLatestDayBarForInstr(InstrPtr& instr, int intdate);

/////
	/**
	* @brief get barlist for instrcombo
	*
	* @param instrcombo 
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarListPtr getBarListForInstrCombo(InstrComboPtr& instrcombo, int64_t startdt, int64_t enddt, int spanseconds);

	/**
	* @brief get 60 seconds barlist for instrcombo
	*
	* @param instrcombo
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstrCombo(InstrComboPtr& instrcombo, int64_t startdt, int64_t enddt);

	/**
	* @brief get 60 seconds barlist for instrcombo with number limit
	*
	* @param instrcombo 
	* @param enddt as end timestamp
	* @param numlimt as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstrComboWithLimit(InstrComboPtr& instrcombo, int64_t enddt, int numlimit);


	///@}

public:
	/**
	* @name BarMaker functions
	*/
	///@{

	/**
	* @brief has barmaker with specific iid and span
	*
	* @param iid as integer id
	* @param span as bar seconds
	*
	* @return it it exists barmaker with iid and span
	*/
	bool hasBarMakerForIidWithSpan(int iid, int span);

	/**
	* @brief get barmaker with specific iid and span
	*
	* @param iid as integer id
	* @param span as bar seconds
	*
	* @return barmaker with iid and span
	*/
	BarMakerPtr& getBarMakerForIidWithSpan(int iid, int span);

	/**
	* @brief has barmaker for instrument with specific span
	*
	* @param instr as instrument
	* @param span as bar seconds
	*
	* @return if it exists barmaker for instrument with span
	*/
	bool hasBarMakerForInstr(InstrPtr& instr, int span);

	/**
	* @brief get barmaker for instrument with specific span
	*
	* @param instr as instrument
	* @param span as bar seconds
	*
	* @return barmaker for instrument with span
	*/
	BarMakerPtr& getBarMakerForInstr(InstrPtr& instr, int span);

	/**
	* @brief has barmaker for instrcombo with span
	*
	* @param instrcombo as InstrCombo
	* @param span as bar seconds
	*
	* @return if it exists barmaker for instrcombo with span
	*/
	bool hasBarMakerForInstrCombo(InstrComboPtr& instrcombo, int span);

	/**
	* @brief get barmaker for instrcombo with span
	*
	* @param instrcombo as InstrCombo
	* @param span as bar seconds
	*
	* @return barmaker for instrcombo with span
	*/
	BarMakerPtr& getBarMakerForInstrCombo(InstrComboPtr& instrcombo, int span);

	/**
	* @brief add barmaker for instr with span
	*
	* @param instr as instrument
	* @param span as bar seconds
	*/
	void addBarMakerForInstr(InstrPtr& instr, int span);

	/**
	* @brief add barmaker for instrid with span
	*
	* @param instrid as instrument id
	* @param span as bar seconds
	*/
	void addBarMakerForInstrID(const std::string& instrid, int span);

	/**
	* @brief add barmaker for instrcombo with span
	*
	* @param instrcombo 
	* @param span as bar seconds
	*/
	void addBarMakerForInstrCombo(InstrComboPtr& instrcombo, int span);

	/**
	* @brief add barmaker for instrcombo name with span
	*
	* @param comboname as name
	* @param span as bar seconds
	*/
	void addBarMakerForInstrComboName(const std::string& comboname, int span);

	/**
	* @brief add barmakers for instruments in settings
	*/
	void addBarMakersForInstrsInSettings();

	/**
	* @brief add barmakers for instrcombos in settings
	*/
	void addBarMakersForInstrCombosInSettings();

	/**
	* @brief add barmakers for strategies in settings
	*/
	void addBarIndicatorsForStratsInSettings();

	///@}

	/**
	* @name BarIndicator functions
	*/
	///@{

	/**
	* @brief has barindicator or not
	*
	* @param iid as integer
	* @param span as bar seconds
	* @param name as indicator name
	* 
	* @return if bar indicator exists or not
	*/
	bool hasBarIndicator(int iid, int span, const std::string& name);

	/**
	* @brief get barindicator
	*
	* @param iid as integer
	* @param span as bar seconds
	* @param name as indicator name
	*
	* @return barindicator
	*/
	BarIndicatorPtr& getBarIndicator(int iid, int span, const std::string& name);

	/**
	* @brief get barindicator names
	*
	* @param iid as integer
	* @param span as bar seconds
	*
	* @return vector of barindicator names
	*/
	const std::vector<std::string>& getBarIndicatorNames(int iid, int span);

	/**
	* @brief add barindicator for instrument with stringmap parameter
	*
	* @param instr as instrument
	* @param smp as parameter
	*/
	void addBarIndicatorForInstr(InstrPtr& instr, StringMapPtr smp);

	/**
	* @brief add barindicator for instrcombo with stringmap parameter
	*
	* @param instrcombo 
	* @param smp as parameter
	*/
	void addBarIndicatorForInstrCombo(InstrComboPtr& instrcombo, StringMapPtr smp);

	/**
	* @brief add barindicator for instrument with span and function name
	*
	* @param instr as instrument
	* @param span as bar seconds
	* @param funcname as function name
	*/
	void addBarIndicatorForInstrByTALibFuncName(InstrPtr& instr, int span, const std::string& funcname);

	/**
	* @brief add barindicator for instrid with span and function name
	*
	* @param instrid as instrid
	* @param span as bar seconds
	* @param funcname as function name
	*/
	void addBarIndicatorForInstrIDByTALibFuncName(const std::string& instrid, int span, const std::string& funcname);

	/**
	* @brief add barindicator for instrcombo with span and function name
	*
	* @param instrcombo
	* @param span as bar seconds
	* @param funcname as function name
	*/
	void addBarIndicatorForInstrComboByTALibFuncName(InstrComboPtr& instrcombo, int span, const std::string& funcname);

	///@}

	/**
	* @name market data events
	*/
	///@{
public:
	/**
	* @brief market data event with integer id
	*
	* @param iid as integer id
	*/
	void onMktData(int iid);
protected:
	/**
	* @brief market data event for instrument with integer id
	*
	* @param iid as integer id
	*/
	void onInstrMktData(int iid);

	/**
	* @brief market data event for instrcombo with integer id
	*
	* @param iid as integer id
	*/
	void onInstrComboMktData(int iid);

	///@}
protected:
	BarPtr m_emptyBar;
	BarListPtr m_emptyBarList;

	BarMakerPtr m_emptyBarMaker;
	BarIndicatorPtr m_emptyBarIndicator;
	std::vector<std::string> m_emptyStringVector;

	boost::unordered_map<int, boost::unordered_map<int, BarMakerPtr > > m_barMakerMap;

	boost::unordered_map<int, boost::signals2::connection> m_connectionMap;

};//class XT_COMMON_API InstrMgr



}//namespace XT



#endif