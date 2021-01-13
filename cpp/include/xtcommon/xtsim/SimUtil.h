#pragma once
#ifndef XT_SIM_UTIL_H
#define XT_SIM_UTIL_H

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include "XTConfig.h"
#include "log4z.h"
#include "Util.h"
#include "Instr.h"
#include "InstrMgr.h"
#include "OrderMgr.h"
#include "RequestMgr.h"

#include <google/protobuf/util/json_util.h>
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "DataUtil.h"

#include "SimOrderMgr.h"

namespace XT
{
class XT_COMMON_API SimUtil
{
public:
	/**
	* handle MktQuoteData
	*/
	static void handleOnMktQuoteData(XT::MktQuoteDataPtr& mktdata);  
						
	/**
	* handle FillInfo
	*/
	static void handleOnFillInfo(XT::FillInfoPtr& fillinfo);

	/**
	* handle orderinfo
	*/
	static void handleOnOrderInfo(XT::OrderInfoPtr& orderinfo);

};

}//namespace 

#endif
