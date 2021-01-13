#pragma once
#ifndef STRAT_DATA_LOG_H
#define STRAT_DATA_LOG_H

/**
* \file Strat_DataLog.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for data log strategy.
*
* \description
*	Designed for data log strategy.
*/

#include <cstdint>
#include <map>
#include <set>
#include <vector>

#include <boost/unordered_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "TagDataWrapper.h"
#include "EnumHelper.h"

#include "Instr.h"
#include "InstrCombo.h"
#include "StringMap.h"
#include "InstrMgr.h"

#include "SettingsMgr.h"
#include "InstrSettingsMgr.h"

#include "Strat.h"

namespace XT
{

class Strat_DataLog : public Strat
{

public:
	/**
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	Strat_DataLog();

	/**
	* @brief default copy constructor
	*/
	Strat_DataLog(const Strat_DataLog& from);// = default;

	/**
	* @brief default copy assignment
	*/
	Strat_DataLog& operator=(const Strat_DataLog& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~Strat_DataLog();
	///@}

public:

	virtual int handleXTMsg(XTMsgPtr& msg);

	/**
	* @brief override base function onInstrEventInfo
	*/
	virtual void onInstrEventInfo(InstrEventInfo& mktevent);

	/**
	* @brief on mktdata event
	*
	* @param int integer instrid
	*/
	virtual void onMktData(int iid);


};//class Strat_DataLog : public Strat


}//namespace



#endif