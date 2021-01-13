#pragma once
#ifndef XT_EMQUANTUTIL_H
#define XT_EMQUANTUTIL_H

/**
* \file EmQuantUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all EmQuant utilities.
*
* \description
*	Designed for managing all EmQuant utilities.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "XTConfig.h"
#include "LogUtil.h"
#include "Util.h"
#include "Instr.h"
#include "InstrMgr.h"
#include "OrderQuoteMgr.h"
#include "RequestMgr.h"

#include "SettingsMgr.h"


#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"


#include "PBUtil.h"
#include "ZMQMgr.h"

namespace XT
{

	class XT_COMMON_API EmQuantUtil
	{
	};//

}//namespace

#endif