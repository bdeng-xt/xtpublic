#pragma once
#ifndef STRAT_DATA_ANALYSIS_H
#define STRAT_DATA_ANALYSIS_H

/**
* \file Strat_DataAnalysis.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for data analysis strategy.
*
* \description
*	Designed for data analysis strategy.
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

class Strat_DataAnalysis : public Strat
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	Strat_DataAnalysis();

	/**
	* @brief default copy constructor
	*/
	Strat_DataAnalysis(const Strat_DataAnalysis& from);// = default;

											 /**
											 * @brief default copy assignment
											 */
	Strat_DataAnalysis& operator=(const Strat_DataAnalysis& from);// = default;

														/**
														* @brief destructor
														*/
	virtual ~Strat_DataAnalysis();
	///@}

public:
 

};//class Strat_DataAnalysis : public Strat


}//namespace
#endif