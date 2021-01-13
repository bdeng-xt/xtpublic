#pragma once
#ifndef STRAT_DATA_SIM_H
#define STRAT_DATA_SIM_H

/**
* \file Strat_Sim.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for sim strategy.
*
* \description
*	Designed for sim strategy.
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

class Strat_Sim : public Strat
{

};//class Strat_Sim : public Strat


}//namespace



#endif