#pragma once
#ifndef DATA_UTIL_H
#define DATA_UTIL_H

/**
* \file DataUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a util class for data.
*
* \description
*	Designed for data utilities.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <google/protobuf/stubs/common.h>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/text_format.h>

#include <google/protobuf/util/json_util.h>

#include "XTConfig.h"


 
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "XTSimpleIni.h"
#include "StringMap.h"
#include "json/json.h"

#include "StringUtil.h"
#include "PBUtil.h"

#include "LogUtil.h"

namespace XT
{

class XT_COMMON_API DataUtil
{
public:

	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	DataUtil() {}

	/**
	* @brief copy constructor
	*/
	DataUtil(const DataUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	DataUtil& operator=(const DataUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~DataUtil() {}

	///@}
 

protected:
	static std::string m_EmptyString; ///< empty string
public:
	//static void updateMktQuoteDataFromCTPLevel1Data(MktQuoteDataPtr& mktquote,
	//	int TradingDay, const std::string& InstrID,const std::string& ExchID, const std::string& ExchangeInstID,
	//	double LastPrice, double PreSettlementPrice, double PreClosePrice, double PreOpenInterest,
	//	double OpenPrice, double HighestPrice, double LowestPrice, int Volume,double Turnover, double OpenInterest, 
	//	double ClosePrice, double SettlementPrice, double UpperLimitPrice, double LowerLimitPrice,
	//	double PreDelta, double CurrDelta, const std::string& UpdateTime, int UpdateMillisec,
	//	double BidPrice1, int BidVolume1, double AskPrice1, int AskVolume1,
	//	double AveragePrice, 
	//	int ActionDay
	//);
	
	/**
	* @brief get StringMapPtr for json string
	*
	* @param json string
	*
	* @return StringMapPtr
	*/
	static StringMapPtr getStringMapPtrForJsonStr(const std::string& s);

	/**
	* @brief get json string for StringMapPtr
	*
	* @param stringmapptr
	*
	* @return json string
	*/
	static std::string getJsonStrForStringMapPtr(const StringMapPtr& smp);


//////////////////////////////////
//////begin_IntIntData
	static std::string getPBStrForIntIntData(const IntIntDataPtr& p);
	static bool parseIntIntDataFromPBStr(const std::string& s, IntIntDataPtr& p);

	static std::string getStrForIntIntData(const IntIntDataPtr& p);
	static std::string getJsonStrForIntIntData(const IntIntDataPtr& p);
	static bool parseIntIntDataFromJsonStr(const std::string& s, IntIntDataPtr& p);

	static std::string getCsvStrForIntIntData(const IntIntDataPtr& p, const std::string& sep = "|");
	static bool parseIntIntDataFromCsvStr(const std::string& s, IntIntDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntIntData(const IntIntDataPtr& p, const std::string& sep = "|");
	static bool parseIntIntDataFromPlainCsvStr(const std::string& s, IntIntDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntIntData(const IntIntDataPtr& p);
	static bool parseIntIntDataFromStringMapPtr(const StringMapPtr& smp, IntIntDataPtr& p);

	static void updateIntIntDataFromStringMapPtr(const StringMapPtr& smp, IntIntDataPtr& p);

	//////end_IntIntData

	//////begin_IntStringData
	static std::string getPBStrForIntStringData(const IntStringDataPtr& p);
	static bool parseIntStringDataFromPBStr(const std::string& s, IntStringDataPtr& p);

	static std::string getStrForIntStringData(const IntStringDataPtr& p);
	static std::string getJsonStrForIntStringData(const IntStringDataPtr& p);
	static bool parseIntStringDataFromJsonStr(const std::string& s, IntStringDataPtr& p);

	static std::string getCsvStrForIntStringData(const IntStringDataPtr& p, const std::string& sep = "|");
	static bool parseIntStringDataFromCsvStr(const std::string& s, IntStringDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntStringData(const IntStringDataPtr& p, const std::string& sep = "|");
	static bool parseIntStringDataFromPlainCsvStr(const std::string& s, IntStringDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntStringData(const IntStringDataPtr& p);
	static bool parseIntStringDataFromStringMapPtr(const StringMapPtr& smp, IntStringDataPtr& p);

	static void updateIntStringDataFromStringMapPtr(const StringMapPtr& smp, IntStringDataPtr& p);

	//////end_IntStringData

	//////begin_IntDoubleData
	static std::string getPBStrForIntDoubleData(const IntDoubleDataPtr& p);
	static bool parseIntDoubleDataFromPBStr(const std::string& s, IntDoubleDataPtr& p);

	static std::string getStrForIntDoubleData(const IntDoubleDataPtr& p);
	static std::string getJsonStrForIntDoubleData(const IntDoubleDataPtr& p);
	static bool parseIntDoubleDataFromJsonStr(const std::string& s, IntDoubleDataPtr& p);

	static std::string getCsvStrForIntDoubleData(const IntDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseIntDoubleDataFromCsvStr(const std::string& s, IntDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntDoubleData(const IntDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseIntDoubleDataFromPlainCsvStr(const std::string& s, IntDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntDoubleData(const IntDoubleDataPtr& p);
	static bool parseIntDoubleDataFromStringMapPtr(const StringMapPtr& smp, IntDoubleDataPtr& p);

	static void updateIntDoubleDataFromStringMapPtr(const StringMapPtr& smp, IntDoubleDataPtr& p);

	//////end_IntDoubleData

	//////begin_IntInt64Data
	static std::string getPBStrForIntInt64Data(const IntInt64DataPtr& p);
	static bool parseIntInt64DataFromPBStr(const std::string& s, IntInt64DataPtr& p);

	static std::string getStrForIntInt64Data(const IntInt64DataPtr& p);
	static std::string getJsonStrForIntInt64Data(const IntInt64DataPtr& p);
	static bool parseIntInt64DataFromJsonStr(const std::string& s, IntInt64DataPtr& p);

	static std::string getCsvStrForIntInt64Data(const IntInt64DataPtr& p, const std::string& sep = "|");
	static bool parseIntInt64DataFromCsvStr(const std::string& s, IntInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntInt64Data(const IntInt64DataPtr& p, const std::string& sep = "|");
	static bool parseIntInt64DataFromPlainCsvStr(const std::string& s, IntInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntInt64Data(const IntInt64DataPtr& p);
	static bool parseIntInt64DataFromStringMapPtr(const StringMapPtr& smp, IntInt64DataPtr& p);

	static void updateIntInt64DataFromStringMapPtr(const StringMapPtr& smp, IntInt64DataPtr& p);

	//////end_IntInt64Data

	//////begin_StringStringData
	static std::string getPBStrForStringStringData(const StringStringDataPtr& p);
	static bool parseStringStringDataFromPBStr(const std::string& s, StringStringDataPtr& p);

	static std::string getStrForStringStringData(const StringStringDataPtr& p);
	static std::string getJsonStrForStringStringData(const StringStringDataPtr& p);
	static bool parseStringStringDataFromJsonStr(const std::string& s, StringStringDataPtr& p);

	static std::string getCsvStrForStringStringData(const StringStringDataPtr& p, const std::string& sep = "|");
	static bool parseStringStringDataFromCsvStr(const std::string& s, StringStringDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringStringData(const StringStringDataPtr& p, const std::string& sep = "|");
	static bool parseStringStringDataFromPlainCsvStr(const std::string& s, StringStringDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringStringData(const StringStringDataPtr& p);
	static bool parseStringStringDataFromStringMapPtr(const StringMapPtr& smp, StringStringDataPtr& p);

	static void updateStringStringDataFromStringMapPtr(const StringMapPtr& smp, StringStringDataPtr& p);

	//////end_StringStringData

	//////begin_StringDoubleData
	static std::string getPBStrForStringDoubleData(const StringDoubleDataPtr& p);
	static bool parseStringDoubleDataFromPBStr(const std::string& s, StringDoubleDataPtr& p);

	static std::string getStrForStringDoubleData(const StringDoubleDataPtr& p);
	static std::string getJsonStrForStringDoubleData(const StringDoubleDataPtr& p);
	static bool parseStringDoubleDataFromJsonStr(const std::string& s, StringDoubleDataPtr& p);

	static std::string getCsvStrForStringDoubleData(const StringDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseStringDoubleDataFromCsvStr(const std::string& s, StringDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringDoubleData(const StringDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseStringDoubleDataFromPlainCsvStr(const std::string& s, StringDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringDoubleData(const StringDoubleDataPtr& p);
	static bool parseStringDoubleDataFromStringMapPtr(const StringMapPtr& smp, StringDoubleDataPtr& p);

	static void updateStringDoubleDataFromStringMapPtr(const StringMapPtr& smp, StringDoubleDataPtr& p);

	//////end_StringDoubleData

	//////begin_StringInt64Data
	static std::string getPBStrForStringInt64Data(const StringInt64DataPtr& p);
	static bool parseStringInt64DataFromPBStr(const std::string& s, StringInt64DataPtr& p);

	static std::string getStrForStringInt64Data(const StringInt64DataPtr& p);
	static std::string getJsonStrForStringInt64Data(const StringInt64DataPtr& p);
	static bool parseStringInt64DataFromJsonStr(const std::string& s, StringInt64DataPtr& p);

	static std::string getCsvStrForStringInt64Data(const StringInt64DataPtr& p, const std::string& sep = "|");
	static bool parseStringInt64DataFromCsvStr(const std::string& s, StringInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringInt64Data(const StringInt64DataPtr& p, const std::string& sep = "|");
	static bool parseStringInt64DataFromPlainCsvStr(const std::string& s, StringInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringInt64Data(const StringInt64DataPtr& p);
	static bool parseStringInt64DataFromStringMapPtr(const StringMapPtr& smp, StringInt64DataPtr& p);

	static void updateStringInt64DataFromStringMapPtr(const StringMapPtr& smp, StringInt64DataPtr& p);

	//////end_StringInt64Data

	//////begin_DoubleDoubleData
	static std::string getPBStrForDoubleDoubleData(const DoubleDoubleDataPtr& p);
	static bool parseDoubleDoubleDataFromPBStr(const std::string& s, DoubleDoubleDataPtr& p);

	static std::string getStrForDoubleDoubleData(const DoubleDoubleDataPtr& p);
	static std::string getJsonStrForDoubleDoubleData(const DoubleDoubleDataPtr& p);
	static bool parseDoubleDoubleDataFromJsonStr(const std::string& s, DoubleDoubleDataPtr& p);

	static std::string getCsvStrForDoubleDoubleData(const DoubleDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseDoubleDoubleDataFromCsvStr(const std::string& s, DoubleDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleDoubleData(const DoubleDoubleDataPtr& p, const std::string& sep = "|");
	static bool parseDoubleDoubleDataFromPlainCsvStr(const std::string& s, DoubleDoubleDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleDoubleData(const DoubleDoubleDataPtr& p);
	static bool parseDoubleDoubleDataFromStringMapPtr(const StringMapPtr& smp, DoubleDoubleDataPtr& p);

	static void updateDoubleDoubleDataFromStringMapPtr(const StringMapPtr& smp, DoubleDoubleDataPtr& p);

	//////end_DoubleDoubleData

	//////begin_DoubleInt64Data
	static std::string getPBStrForDoubleInt64Data(const DoubleInt64DataPtr& p);
	static bool parseDoubleInt64DataFromPBStr(const std::string& s, DoubleInt64DataPtr& p);

	static std::string getStrForDoubleInt64Data(const DoubleInt64DataPtr& p);
	static std::string getJsonStrForDoubleInt64Data(const DoubleInt64DataPtr& p);
	static bool parseDoubleInt64DataFromJsonStr(const std::string& s, DoubleInt64DataPtr& p);

	static std::string getCsvStrForDoubleInt64Data(const DoubleInt64DataPtr& p, const std::string& sep = "|");
	static bool parseDoubleInt64DataFromCsvStr(const std::string& s, DoubleInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleInt64Data(const DoubleInt64DataPtr& p, const std::string& sep = "|");
	static bool parseDoubleInt64DataFromPlainCsvStr(const std::string& s, DoubleInt64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleInt64Data(const DoubleInt64DataPtr& p);
	static bool parseDoubleInt64DataFromStringMapPtr(const StringMapPtr& smp, DoubleInt64DataPtr& p);

	static void updateDoubleInt64DataFromStringMapPtr(const StringMapPtr& smp, DoubleInt64DataPtr& p);

	//////end_DoubleInt64Data

	//////begin_Int64Int64Data
	static std::string getPBStrForInt64Int64Data(const Int64Int64DataPtr& p);
	static bool parseInt64Int64DataFromPBStr(const std::string& s, Int64Int64DataPtr& p);

	static std::string getStrForInt64Int64Data(const Int64Int64DataPtr& p);
	static std::string getJsonStrForInt64Int64Data(const Int64Int64DataPtr& p);
	static bool parseInt64Int64DataFromJsonStr(const std::string& s, Int64Int64DataPtr& p);

	static std::string getCsvStrForInt64Int64Data(const Int64Int64DataPtr& p, const std::string& sep = "|");
	static bool parseInt64Int64DataFromCsvStr(const std::string& s, Int64Int64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64Int64Data(const Int64Int64DataPtr& p, const std::string& sep = "|");
	static bool parseInt64Int64DataFromPlainCsvStr(const std::string& s, Int64Int64DataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64Int64Data(const Int64Int64DataPtr& p);
	static bool parseInt64Int64DataFromStringMapPtr(const StringMapPtr& smp, Int64Int64DataPtr& p);

	static void updateInt64Int64DataFromStringMapPtr(const StringMapPtr& smp, Int64Int64DataPtr& p);

	//////end_Int64Int64Data

	//////begin_IntVectorData
	static std::string getPBStrForIntVectorData(const IntVectorDataPtr& p);
	static bool parseIntVectorDataFromPBStr(const std::string& s, IntVectorDataPtr& p);

	static std::string getStrForIntVectorData(const IntVectorDataPtr& p);
	static std::string getJsonStrForIntVectorData(const IntVectorDataPtr& p);
	static bool parseIntVectorDataFromJsonStr(const std::string& s, IntVectorDataPtr& p);

	static std::string getCsvStrForIntVectorData(const IntVectorDataPtr& p, const std::string& sep = "|");
	static bool parseIntVectorDataFromCsvStr(const std::string& s, IntVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntVectorData(const IntVectorDataPtr& p, const std::string& sep = "|");
	static bool parseIntVectorDataFromPlainCsvStr(const std::string& s, IntVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntVectorData(const IntVectorDataPtr& p);
	static bool parseIntVectorDataFromStringMapPtr(const StringMapPtr& smp, IntVectorDataPtr& p);

	static void updateIntVectorDataFromStringMapPtr(const StringMapPtr& smp, IntVectorDataPtr& p);

	//////end_IntVectorData

	//////begin_StringVectorData
	static std::string getPBStrForStringVectorData(const StringVectorDataPtr& p);
	static bool parseStringVectorDataFromPBStr(const std::string& s, StringVectorDataPtr& p);

	static std::string getStrForStringVectorData(const StringVectorDataPtr& p);
	static std::string getJsonStrForStringVectorData(const StringVectorDataPtr& p);
	static bool parseStringVectorDataFromJsonStr(const std::string& s, StringVectorDataPtr& p);

	static std::string getCsvStrForStringVectorData(const StringVectorDataPtr& p, const std::string& sep = "|");
	static bool parseStringVectorDataFromCsvStr(const std::string& s, StringVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringVectorData(const StringVectorDataPtr& p, const std::string& sep = "|");
	static bool parseStringVectorDataFromPlainCsvStr(const std::string& s, StringVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringVectorData(const StringVectorDataPtr& p);
	static bool parseStringVectorDataFromStringMapPtr(const StringMapPtr& smp, StringVectorDataPtr& p);

	static void updateStringVectorDataFromStringMapPtr(const StringMapPtr& smp, StringVectorDataPtr& p);

	//////end_StringVectorData

	//////begin_DoubleVectorData
	static std::string getPBStrForDoubleVectorData(const DoubleVectorDataPtr& p);
	static bool parseDoubleVectorDataFromPBStr(const std::string& s, DoubleVectorDataPtr& p);

	static std::string getStrForDoubleVectorData(const DoubleVectorDataPtr& p);
	static std::string getJsonStrForDoubleVectorData(const DoubleVectorDataPtr& p);
	static bool parseDoubleVectorDataFromJsonStr(const std::string& s, DoubleVectorDataPtr& p);

	static std::string getCsvStrForDoubleVectorData(const DoubleVectorDataPtr& p, const std::string& sep = "|");
	static bool parseDoubleVectorDataFromCsvStr(const std::string& s, DoubleVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleVectorData(const DoubleVectorDataPtr& p, const std::string& sep = "|");
	static bool parseDoubleVectorDataFromPlainCsvStr(const std::string& s, DoubleVectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleVectorData(const DoubleVectorDataPtr& p);
	static bool parseDoubleVectorDataFromStringMapPtr(const StringMapPtr& smp, DoubleVectorDataPtr& p);

	static void updateDoubleVectorDataFromStringMapPtr(const StringMapPtr& smp, DoubleVectorDataPtr& p);

	//////end_DoubleVectorData

	//////begin_Int64VectorData
	static std::string getPBStrForInt64VectorData(const Int64VectorDataPtr& p);
	static bool parseInt64VectorDataFromPBStr(const std::string& s, Int64VectorDataPtr& p);

	static std::string getStrForInt64VectorData(const Int64VectorDataPtr& p);
	static std::string getJsonStrForInt64VectorData(const Int64VectorDataPtr& p);
	static bool parseInt64VectorDataFromJsonStr(const std::string& s, Int64VectorDataPtr& p);

	static std::string getCsvStrForInt64VectorData(const Int64VectorDataPtr& p, const std::string& sep = "|");
	static bool parseInt64VectorDataFromCsvStr(const std::string& s, Int64VectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64VectorData(const Int64VectorDataPtr& p, const std::string& sep = "|");
	static bool parseInt64VectorDataFromPlainCsvStr(const std::string& s, Int64VectorDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64VectorData(const Int64VectorDataPtr& p);
	static bool parseInt64VectorDataFromStringMapPtr(const StringMapPtr& smp, Int64VectorDataPtr& p);

	static void updateInt64VectorDataFromStringMapPtr(const StringMapPtr& smp, Int64VectorDataPtr& p);

	//////end_Int64VectorData

	//////begin_IntIntMapData
	static std::string getPBStrForIntIntMapData(const IntIntMapDataPtr& p);
	static bool parseIntIntMapDataFromPBStr(const std::string& s, IntIntMapDataPtr& p);

	static std::string getStrForIntIntMapData(const IntIntMapDataPtr& p);
	static std::string getJsonStrForIntIntMapData(const IntIntMapDataPtr& p);
	static bool parseIntIntMapDataFromJsonStr(const std::string& s, IntIntMapDataPtr& p);

	static std::string getCsvStrForIntIntMapData(const IntIntMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntIntMapDataFromCsvStr(const std::string& s, IntIntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntIntMapData(const IntIntMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntIntMapDataFromPlainCsvStr(const std::string& s, IntIntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntIntMapData(const IntIntMapDataPtr& p);
	static bool parseIntIntMapDataFromStringMapPtr(const StringMapPtr& smp, IntIntMapDataPtr& p);

	static void updateIntIntMapDataFromStringMapPtr(const StringMapPtr& smp, IntIntMapDataPtr& p);

	//////end_IntIntMapData

	//////begin_IntStringMapData
	static std::string getPBStrForIntStringMapData(const IntStringMapDataPtr& p);
	static bool parseIntStringMapDataFromPBStr(const std::string& s, IntStringMapDataPtr& p);

	static std::string getStrForIntStringMapData(const IntStringMapDataPtr& p);
	static std::string getJsonStrForIntStringMapData(const IntStringMapDataPtr& p);
	static bool parseIntStringMapDataFromJsonStr(const std::string& s, IntStringMapDataPtr& p);

	static std::string getCsvStrForIntStringMapData(const IntStringMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntStringMapDataFromCsvStr(const std::string& s, IntStringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntStringMapData(const IntStringMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntStringMapDataFromPlainCsvStr(const std::string& s, IntStringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntStringMapData(const IntStringMapDataPtr& p);
	static bool parseIntStringMapDataFromStringMapPtr(const StringMapPtr& smp, IntStringMapDataPtr& p);

	static void updateIntStringMapDataFromStringMapPtr(const StringMapPtr& smp, IntStringMapDataPtr& p);

	//////end_IntStringMapData

	//////begin_IntInt64MapData
	static std::string getPBStrForIntInt64MapData(const IntInt64MapDataPtr& p);
	static bool parseIntInt64MapDataFromPBStr(const std::string& s, IntInt64MapDataPtr& p);

	static std::string getStrForIntInt64MapData(const IntInt64MapDataPtr& p);
	static std::string getJsonStrForIntInt64MapData(const IntInt64MapDataPtr& p);
	static bool parseIntInt64MapDataFromJsonStr(const std::string& s, IntInt64MapDataPtr& p);

	static std::string getCsvStrForIntInt64MapData(const IntInt64MapDataPtr& p, const std::string& sep = "|");
	static bool parseIntInt64MapDataFromCsvStr(const std::string& s, IntInt64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntInt64MapData(const IntInt64MapDataPtr& p, const std::string& sep = "|");
	static bool parseIntInt64MapDataFromPlainCsvStr(const std::string& s, IntInt64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntInt64MapData(const IntInt64MapDataPtr& p);
	static bool parseIntInt64MapDataFromStringMapPtr(const StringMapPtr& smp, IntInt64MapDataPtr& p);

	static void updateIntInt64MapDataFromStringMapPtr(const StringMapPtr& smp, IntInt64MapDataPtr& p);

	//////end_IntInt64MapData

	//////begin_IntDoubleMapData
	static std::string getPBStrForIntDoubleMapData(const IntDoubleMapDataPtr& p);
	static bool parseIntDoubleMapDataFromPBStr(const std::string& s, IntDoubleMapDataPtr& p);

	static std::string getStrForIntDoubleMapData(const IntDoubleMapDataPtr& p);
	static std::string getJsonStrForIntDoubleMapData(const IntDoubleMapDataPtr& p);
	static bool parseIntDoubleMapDataFromJsonStr(const std::string& s, IntDoubleMapDataPtr& p);

	static std::string getCsvStrForIntDoubleMapData(const IntDoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntDoubleMapDataFromCsvStr(const std::string& s, IntDoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntDoubleMapData(const IntDoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseIntDoubleMapDataFromPlainCsvStr(const std::string& s, IntDoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntDoubleMapData(const IntDoubleMapDataPtr& p);
	static bool parseIntDoubleMapDataFromStringMapPtr(const StringMapPtr& smp, IntDoubleMapDataPtr& p);

	static void updateIntDoubleMapDataFromStringMapPtr(const StringMapPtr& smp, IntDoubleMapDataPtr& p);

	//////end_IntDoubleMapData

	//////begin_StringIntMapData
	static std::string getPBStrForStringIntMapData(const StringIntMapDataPtr& p);
	static bool parseStringIntMapDataFromPBStr(const std::string& s, StringIntMapDataPtr& p);

	static std::string getStrForStringIntMapData(const StringIntMapDataPtr& p);
	static std::string getJsonStrForStringIntMapData(const StringIntMapDataPtr& p);
	static bool parseStringIntMapDataFromJsonStr(const std::string& s, StringIntMapDataPtr& p);

	static std::string getCsvStrForStringIntMapData(const StringIntMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringIntMapDataFromCsvStr(const std::string& s, StringIntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringIntMapData(const StringIntMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringIntMapDataFromPlainCsvStr(const std::string& s, StringIntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringIntMapData(const StringIntMapDataPtr& p);
	static bool parseStringIntMapDataFromStringMapPtr(const StringMapPtr& smp, StringIntMapDataPtr& p);

	static void updateStringIntMapDataFromStringMapPtr(const StringMapPtr& smp, StringIntMapDataPtr& p);

	//////end_StringIntMapData

	//////begin_StringStringMapData
	static std::string getPBStrForStringStringMapData(const StringStringMapDataPtr& p);
	static bool parseStringStringMapDataFromPBStr(const std::string& s, StringStringMapDataPtr& p);

	static std::string getStrForStringStringMapData(const StringStringMapDataPtr& p);
	static std::string getJsonStrForStringStringMapData(const StringStringMapDataPtr& p);
	static bool parseStringStringMapDataFromJsonStr(const std::string& s, StringStringMapDataPtr& p);

	static std::string getCsvStrForStringStringMapData(const StringStringMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringStringMapDataFromCsvStr(const std::string& s, StringStringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringStringMapData(const StringStringMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringStringMapDataFromPlainCsvStr(const std::string& s, StringStringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringStringMapData(const StringStringMapDataPtr& p);
	static bool parseStringStringMapDataFromStringMapPtr(const StringMapPtr& smp, StringStringMapDataPtr& p);

	static void updateStringStringMapDataFromStringMapPtr(const StringMapPtr& smp, StringStringMapDataPtr& p);

	//////end_StringStringMapData

	//////begin_StringDoubleMapData
	static std::string getPBStrForStringDoubleMapData(const StringDoubleMapDataPtr& p);
	static bool parseStringDoubleMapDataFromPBStr(const std::string& s, StringDoubleMapDataPtr& p);

	static std::string getStrForStringDoubleMapData(const StringDoubleMapDataPtr& p);
	static std::string getJsonStrForStringDoubleMapData(const StringDoubleMapDataPtr& p);
	static bool parseStringDoubleMapDataFromJsonStr(const std::string& s, StringDoubleMapDataPtr& p);

	static std::string getCsvStrForStringDoubleMapData(const StringDoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringDoubleMapDataFromCsvStr(const std::string& s, StringDoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringDoubleMapData(const StringDoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringDoubleMapDataFromPlainCsvStr(const std::string& s, StringDoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringDoubleMapData(const StringDoubleMapDataPtr& p);
	static bool parseStringDoubleMapDataFromStringMapPtr(const StringMapPtr& smp, StringDoubleMapDataPtr& p);

	static void updateStringDoubleMapDataFromStringMapPtr(const StringMapPtr& smp, StringDoubleMapDataPtr& p);

	//////end_StringDoubleMapData

	//////begin_StringInt64MapData
	static std::string getPBStrForStringInt64MapData(const StringInt64MapDataPtr& p);
	static bool parseStringInt64MapDataFromPBStr(const std::string& s, StringInt64MapDataPtr& p);

	static std::string getStrForStringInt64MapData(const StringInt64MapDataPtr& p);
	static std::string getJsonStrForStringInt64MapData(const StringInt64MapDataPtr& p);
	static bool parseStringInt64MapDataFromJsonStr(const std::string& s, StringInt64MapDataPtr& p);

	static std::string getCsvStrForStringInt64MapData(const StringInt64MapDataPtr& p, const std::string& sep = "|");
	static bool parseStringInt64MapDataFromCsvStr(const std::string& s, StringInt64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringInt64MapData(const StringInt64MapDataPtr& p, const std::string& sep = "|");
	static bool parseStringInt64MapDataFromPlainCsvStr(const std::string& s, StringInt64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringInt64MapData(const StringInt64MapDataPtr& p);
	static bool parseStringInt64MapDataFromStringMapPtr(const StringMapPtr& smp, StringInt64MapDataPtr& p);

	static void updateStringInt64MapDataFromStringMapPtr(const StringMapPtr& smp, StringInt64MapDataPtr& p);

	//////end_StringInt64MapData

	//////begin_Int64IntMapData
	static std::string getPBStrForInt64IntMapData(const Int64IntMapDataPtr& p);
	static bool parseInt64IntMapDataFromPBStr(const std::string& s, Int64IntMapDataPtr& p);

	static std::string getStrForInt64IntMapData(const Int64IntMapDataPtr& p);
	static std::string getJsonStrForInt64IntMapData(const Int64IntMapDataPtr& p);
	static bool parseInt64IntMapDataFromJsonStr(const std::string& s, Int64IntMapDataPtr& p);

	static std::string getCsvStrForInt64IntMapData(const Int64IntMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64IntMapDataFromCsvStr(const std::string& s, Int64IntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64IntMapData(const Int64IntMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64IntMapDataFromPlainCsvStr(const std::string& s, Int64IntMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64IntMapData(const Int64IntMapDataPtr& p);
	static bool parseInt64IntMapDataFromStringMapPtr(const StringMapPtr& smp, Int64IntMapDataPtr& p);

	static void updateInt64IntMapDataFromStringMapPtr(const StringMapPtr& smp, Int64IntMapDataPtr& p);

	//////end_Int64IntMapData

	//////begin_Int64StringMapData
	static std::string getPBStrForInt64StringMapData(const Int64StringMapDataPtr& p);
	static bool parseInt64StringMapDataFromPBStr(const std::string& s, Int64StringMapDataPtr& p);

	static std::string getStrForInt64StringMapData(const Int64StringMapDataPtr& p);
	static std::string getJsonStrForInt64StringMapData(const Int64StringMapDataPtr& p);
	static bool parseInt64StringMapDataFromJsonStr(const std::string& s, Int64StringMapDataPtr& p);

	static std::string getCsvStrForInt64StringMapData(const Int64StringMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64StringMapDataFromCsvStr(const std::string& s, Int64StringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64StringMapData(const Int64StringMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64StringMapDataFromPlainCsvStr(const std::string& s, Int64StringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64StringMapData(const Int64StringMapDataPtr& p);
	static bool parseInt64StringMapDataFromStringMapPtr(const StringMapPtr& smp, Int64StringMapDataPtr& p);

	static void updateInt64StringMapDataFromStringMapPtr(const StringMapPtr& smp, Int64StringMapDataPtr& p);

	//////end_Int64StringMapData

	//////begin_Int64DoubleMapData
	static std::string getPBStrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p);
	static bool parseInt64DoubleMapDataFromPBStr(const std::string& s, Int64DoubleMapDataPtr& p);

	static std::string getStrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p);
	static std::string getJsonStrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p);
	static bool parseInt64DoubleMapDataFromJsonStr(const std::string& s, Int64DoubleMapDataPtr& p);

	static std::string getCsvStrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64DoubleMapDataFromCsvStr(const std::string& s, Int64DoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64DoubleMapDataFromPlainCsvStr(const std::string& s, Int64DoubleMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64DoubleMapData(const Int64DoubleMapDataPtr& p);
	static bool parseInt64DoubleMapDataFromStringMapPtr(const StringMapPtr& smp, Int64DoubleMapDataPtr& p);

	static void updateInt64DoubleMapDataFromStringMapPtr(const StringMapPtr& smp, Int64DoubleMapDataPtr& p);

	//////end_Int64DoubleMapData

	//////begin_Int64Int64MapData
	static std::string getPBStrForInt64Int64MapData(const Int64Int64MapDataPtr& p);
	static bool parseInt64Int64MapDataFromPBStr(const std::string& s, Int64Int64MapDataPtr& p);

	static std::string getStrForInt64Int64MapData(const Int64Int64MapDataPtr& p);
	static std::string getJsonStrForInt64Int64MapData(const Int64Int64MapDataPtr& p);
	static bool parseInt64Int64MapDataFromJsonStr(const std::string& s, Int64Int64MapDataPtr& p);

	static std::string getCsvStrForInt64Int64MapData(const Int64Int64MapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64Int64MapDataFromCsvStr(const std::string& s, Int64Int64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64Int64MapData(const Int64Int64MapDataPtr& p, const std::string& sep = "|");
	static bool parseInt64Int64MapDataFromPlainCsvStr(const std::string& s, Int64Int64MapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64Int64MapData(const Int64Int64MapDataPtr& p);
	static bool parseInt64Int64MapDataFromStringMapPtr(const StringMapPtr& smp, Int64Int64MapDataPtr& p);

	static void updateInt64Int64MapDataFromStringMapPtr(const StringMapPtr& smp, Int64Int64MapDataPtr& p);

	//////end_Int64Int64MapData

	//////begin_XTMsgData
	static std::string getPBStrForXTMsgData(const XTMsgDataPtr& p);
	static bool parseXTMsgDataFromPBStr(const std::string& s, XTMsgDataPtr& p);

	static std::string getStrForXTMsgData(const XTMsgDataPtr& p);
	static std::string getJsonStrForXTMsgData(const XTMsgDataPtr& p);
	static bool parseXTMsgDataFromJsonStr(const std::string& s, XTMsgDataPtr& p);

	static std::string getCsvStrForXTMsgData(const XTMsgDataPtr& p, const std::string& sep = "|");
	static bool parseXTMsgDataFromCsvStr(const std::string& s, XTMsgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForXTMsgData(const XTMsgDataPtr& p, const std::string& sep = "|");
	static bool parseXTMsgDataFromPlainCsvStr(const std::string& s, XTMsgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForXTMsgData(const XTMsgDataPtr& p);
	static bool parseXTMsgDataFromStringMapPtr(const StringMapPtr& smp, XTMsgDataPtr& p);

	static void updateXTMsgDataFromStringMapPtr(const StringMapPtr& smp, XTMsgDataPtr& p);

	//////end_XTMsgData

	//////begin_PBTagMsg
	static std::string getPBStrForPBTagMsg(const PBTagMsgPtr& p);
	static bool parsePBTagMsgFromPBStr(const std::string& s, PBTagMsgPtr& p);

	static std::string getStrForPBTagMsg(const PBTagMsgPtr& p);
	static std::string getJsonStrForPBTagMsg(const PBTagMsgPtr& p);
	static bool parsePBTagMsgFromJsonStr(const std::string& s, PBTagMsgPtr& p);

	static std::string getCsvStrForPBTagMsg(const PBTagMsgPtr& p, const std::string& sep = "|");
	static bool parsePBTagMsgFromCsvStr(const std::string& s, PBTagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPBTagMsg(const PBTagMsgPtr& p, const std::string& sep = "|");
	static bool parsePBTagMsgFromPlainCsvStr(const std::string& s, PBTagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPBTagMsg(const PBTagMsgPtr& p);
	static bool parsePBTagMsgFromStringMapPtr(const StringMapPtr& smp, PBTagMsgPtr& p);

	static void updatePBTagMsgFromStringMapPtr(const StringMapPtr& smp, PBTagMsgPtr& p);

	//////end_PBTagMsg

	//////begin_PBMsg
	static std::string getPBStrForPBMsg(const PBMsgPtr& p);
	static bool parsePBMsgFromPBStr(const std::string& s, PBMsgPtr& p);

	static std::string getStrForPBMsg(const PBMsgPtr& p);
	static std::string getJsonStrForPBMsg(const PBMsgPtr& p);
	static bool parsePBMsgFromJsonStr(const std::string& s, PBMsgPtr& p);

	static std::string getCsvStrForPBMsg(const PBMsgPtr& p, const std::string& sep = "|");
	static bool parsePBMsgFromCsvStr(const std::string& s, PBMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPBMsg(const PBMsgPtr& p, const std::string& sep = "|");
	static bool parsePBMsgFromPlainCsvStr(const std::string& s, PBMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPBMsg(const PBMsgPtr& p);
	static bool parsePBMsgFromStringMapPtr(const StringMapPtr& smp, PBMsgPtr& p);

	static void updatePBMsgFromStringMapPtr(const StringMapPtr& smp, PBMsgPtr& p);

	//////end_PBMsg

	//////begin_PBMsgMap
	static std::string getPBStrForPBMsgMap(const PBMsgMapPtr& p);
	static bool parsePBMsgMapFromPBStr(const std::string& s, PBMsgMapPtr& p);

	static std::string getStrForPBMsgMap(const PBMsgMapPtr& p);
	static std::string getJsonStrForPBMsgMap(const PBMsgMapPtr& p);
	static bool parsePBMsgMapFromJsonStr(const std::string& s, PBMsgMapPtr& p);

	static std::string getCsvStrForPBMsgMap(const PBMsgMapPtr& p, const std::string& sep = "|");
	static bool parsePBMsgMapFromCsvStr(const std::string& s, PBMsgMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPBMsgMap(const PBMsgMapPtr& p, const std::string& sep = "|");
	static bool parsePBMsgMapFromPlainCsvStr(const std::string& s, PBMsgMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPBMsgMap(const PBMsgMapPtr& p);
	static bool parsePBMsgMapFromStringMapPtr(const StringMapPtr& smp, PBMsgMapPtr& p);

	static void updatePBMsgMapFromStringMapPtr(const StringMapPtr& smp, PBMsgMapPtr& p);

	//////end_PBMsgMap

	//////begin_PBTagMsgMap
	static std::string getPBStrForPBTagMsgMap(const PBTagMsgMapPtr& p);
	static bool parsePBTagMsgMapFromPBStr(const std::string& s, PBTagMsgMapPtr& p);

	static std::string getStrForPBTagMsgMap(const PBTagMsgMapPtr& p);
	static std::string getJsonStrForPBTagMsgMap(const PBTagMsgMapPtr& p);
	static bool parsePBTagMsgMapFromJsonStr(const std::string& s, PBTagMsgMapPtr& p);

	static std::string getCsvStrForPBTagMsgMap(const PBTagMsgMapPtr& p, const std::string& sep = "|");
	static bool parsePBTagMsgMapFromCsvStr(const std::string& s, PBTagMsgMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPBTagMsgMap(const PBTagMsgMapPtr& p, const std::string& sep = "|");
	static bool parsePBTagMsgMapFromPlainCsvStr(const std::string& s, PBTagMsgMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPBTagMsgMap(const PBTagMsgMapPtr& p);
	static bool parsePBTagMsgMapFromStringMapPtr(const StringMapPtr& smp, PBTagMsgMapPtr& p);

	static void updatePBTagMsgMapFromStringMapPtr(const StringMapPtr& smp, PBTagMsgMapPtr& p);

	//////end_PBTagMsgMap

	//////begin_ApiPBTagMsg
	static std::string getPBStrForApiPBTagMsg(const ApiPBTagMsgPtr& p);
	static bool parseApiPBTagMsgFromPBStr(const std::string& s, ApiPBTagMsgPtr& p);

	static std::string getStrForApiPBTagMsg(const ApiPBTagMsgPtr& p);
	static std::string getJsonStrForApiPBTagMsg(const ApiPBTagMsgPtr& p);
	static bool parseApiPBTagMsgFromJsonStr(const std::string& s, ApiPBTagMsgPtr& p);

	static std::string getCsvStrForApiPBTagMsg(const ApiPBTagMsgPtr& p, const std::string& sep = "|");
	static bool parseApiPBTagMsgFromCsvStr(const std::string& s, ApiPBTagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForApiPBTagMsg(const ApiPBTagMsgPtr& p, const std::string& sep = "|");
	static bool parseApiPBTagMsgFromPlainCsvStr(const std::string& s, ApiPBTagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForApiPBTagMsg(const ApiPBTagMsgPtr& p);
	static bool parseApiPBTagMsgFromStringMapPtr(const StringMapPtr& smp, ApiPBTagMsgPtr& p);

	static void updateApiPBTagMsgFromStringMapPtr(const StringMapPtr& smp, ApiPBTagMsgPtr& p);

	//////end_ApiPBTagMsg

	//////begin_ApiData
	static std::string getPBStrForApiData(const ApiDataPtr& p);
	static bool parseApiDataFromPBStr(const std::string& s, ApiDataPtr& p);

	static std::string getStrForApiData(const ApiDataPtr& p);
	static std::string getJsonStrForApiData(const ApiDataPtr& p);
	static bool parseApiDataFromJsonStr(const std::string& s, ApiDataPtr& p);

	static std::string getCsvStrForApiData(const ApiDataPtr& p, const std::string& sep = "|");
	static bool parseApiDataFromCsvStr(const std::string& s, ApiDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForApiData(const ApiDataPtr& p, const std::string& sep = "|");
	static bool parseApiDataFromPlainCsvStr(const std::string& s, ApiDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForApiData(const ApiDataPtr& p);
	static bool parseApiDataFromStringMapPtr(const StringMapPtr& smp, ApiDataPtr& p);

	static void updateApiDataFromStringMapPtr(const StringMapPtr& smp, ApiDataPtr& p);

	//////end_ApiData

	//////begin_TagMsg
	static std::string getPBStrForTagMsg(const TagMsgPtr& p);
	static bool parseTagMsgFromPBStr(const std::string& s, TagMsgPtr& p);

	static std::string getStrForTagMsg(const TagMsgPtr& p);
	static std::string getJsonStrForTagMsg(const TagMsgPtr& p);
	static bool parseTagMsgFromJsonStr(const std::string& s, TagMsgPtr& p);

	static std::string getCsvStrForTagMsg(const TagMsgPtr& p, const std::string& sep = "|");
	static bool parseTagMsgFromCsvStr(const std::string& s, TagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTagMsg(const TagMsgPtr& p, const std::string& sep = "|");
	static bool parseTagMsgFromPlainCsvStr(const std::string& s, TagMsgPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTagMsg(const TagMsgPtr& p);
	static bool parseTagMsgFromStringMapPtr(const StringMapPtr& smp, TagMsgPtr& p);

	static void updateTagMsgFromStringMapPtr(const StringMapPtr& smp, TagMsgPtr& p);

	//////end_TagMsg

	//////begin_TagData
	static std::string getPBStrForTagData(const TagDataPtr& p);
	static bool parseTagDataFromPBStr(const std::string& s, TagDataPtr& p);

	static std::string getStrForTagData(const TagDataPtr& p);
	static std::string getJsonStrForTagData(const TagDataPtr& p);
	static bool parseTagDataFromJsonStr(const std::string& s, TagDataPtr& p);

	static std::string getCsvStrForTagData(const TagDataPtr& p, const std::string& sep = "|");
	static bool parseTagDataFromCsvStr(const std::string& s, TagDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTagData(const TagDataPtr& p, const std::string& sep = "|");
	static bool parseTagDataFromPlainCsvStr(const std::string& s, TagDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTagData(const TagDataPtr& p);
	static bool parseTagDataFromStringMapPtr(const StringMapPtr& smp, TagDataPtr& p);

	static void updateTagDataFromStringMapPtr(const StringMapPtr& smp, TagDataPtr& p);

	//////end_TagData

	//////begin_StringMapData
	static std::string getPBStrForStringMapData(const StringMapDataPtr& p);
	static bool parseStringMapDataFromPBStr(const std::string& s, StringMapDataPtr& p);

	static std::string getStrForStringMapData(const StringMapDataPtr& p);
	static std::string getJsonStrForStringMapData(const StringMapDataPtr& p);
	static bool parseStringMapDataFromJsonStr(const std::string& s, StringMapDataPtr& p);

	static std::string getCsvStrForStringMapData(const StringMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringMapDataFromCsvStr(const std::string& s, StringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStringMapData(const StringMapDataPtr& p, const std::string& sep = "|");
	static bool parseStringMapDataFromPlainCsvStr(const std::string& s, StringMapDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStringMapData(const StringMapDataPtr& p);
	static bool parseStringMapDataFromStringMapPtr(const StringMapPtr& smp, StringMapDataPtr& p);

	static void updateStringMapDataFromStringMapPtr(const StringMapPtr& smp, StringMapDataPtr& p);

	//////end_StringMapData

	//////begin_TsRange
	static std::string getPBStrForTsRange(const TsRangePtr& p);
	static bool parseTsRangeFromPBStr(const std::string& s, TsRangePtr& p);

	static std::string getStrForTsRange(const TsRangePtr& p);
	static std::string getJsonStrForTsRange(const TsRangePtr& p);
	static bool parseTsRangeFromJsonStr(const std::string& s, TsRangePtr& p);

	static std::string getCsvStrForTsRange(const TsRangePtr& p, const std::string& sep = "|");
	static bool parseTsRangeFromCsvStr(const std::string& s, TsRangePtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTsRange(const TsRangePtr& p, const std::string& sep = "|");
	static bool parseTsRangeFromPlainCsvStr(const std::string& s, TsRangePtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTsRange(const TsRangePtr& p);
	static bool parseTsRangeFromStringMapPtr(const StringMapPtr& smp, TsRangePtr& p);

	static void updateTsRangeFromStringMapPtr(const StringMapPtr& smp, TsRangePtr& p);

	//////end_TsRange

	//////begin_SessionData
	static std::string getPBStrForSessionData(const SessionDataPtr& p);
	static bool parseSessionDataFromPBStr(const std::string& s, SessionDataPtr& p);

	static std::string getStrForSessionData(const SessionDataPtr& p);
	static std::string getJsonStrForSessionData(const SessionDataPtr& p);
	static bool parseSessionDataFromJsonStr(const std::string& s, SessionDataPtr& p);

	static std::string getCsvStrForSessionData(const SessionDataPtr& p, const std::string& sep = "|");
	static bool parseSessionDataFromCsvStr(const std::string& s, SessionDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForSessionData(const SessionDataPtr& p, const std::string& sep = "|");
	static bool parseSessionDataFromPlainCsvStr(const std::string& s, SessionDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForSessionData(const SessionDataPtr& p);
	static bool parseSessionDataFromStringMapPtr(const StringMapPtr& smp, SessionDataPtr& p);

	static void updateSessionDataFromStringMapPtr(const StringMapPtr& smp, SessionDataPtr& p);

	//////end_SessionData

	//////begin_DoubleParam
	static std::string getPBStrForDoubleParam(const DoubleParamPtr& p);
	static bool parseDoubleParamFromPBStr(const std::string& s, DoubleParamPtr& p);

	static std::string getStrForDoubleParam(const DoubleParamPtr& p);
	static std::string getJsonStrForDoubleParam(const DoubleParamPtr& p);
	static bool parseDoubleParamFromJsonStr(const std::string& s, DoubleParamPtr& p);

	static std::string getCsvStrForDoubleParam(const DoubleParamPtr& p, const std::string& sep = "|");
	static bool parseDoubleParamFromCsvStr(const std::string& s, DoubleParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleParam(const DoubleParamPtr& p, const std::string& sep = "|");
	static bool parseDoubleParamFromPlainCsvStr(const std::string& s, DoubleParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleParam(const DoubleParamPtr& p);
	static bool parseDoubleParamFromStringMapPtr(const StringMapPtr& smp, DoubleParamPtr& p);

	static void updateDoubleParamFromStringMapPtr(const StringMapPtr& smp, DoubleParamPtr& p);

	//////end_DoubleParam

	//////begin_IntParam
	static std::string getPBStrForIntParam(const IntParamPtr& p);
	static bool parseIntParamFromPBStr(const std::string& s, IntParamPtr& p);

	static std::string getStrForIntParam(const IntParamPtr& p);
	static std::string getJsonStrForIntParam(const IntParamPtr& p);
	static bool parseIntParamFromJsonStr(const std::string& s, IntParamPtr& p);

	static std::string getCsvStrForIntParam(const IntParamPtr& p, const std::string& sep = "|");
	static bool parseIntParamFromCsvStr(const std::string& s, IntParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntParam(const IntParamPtr& p, const std::string& sep = "|");
	static bool parseIntParamFromPlainCsvStr(const std::string& s, IntParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntParam(const IntParamPtr& p);
	static bool parseIntParamFromStringMapPtr(const StringMapPtr& smp, IntParamPtr& p);

	static void updateIntParamFromStringMapPtr(const StringMapPtr& smp, IntParamPtr& p);

	//////end_IntParam

	//////begin_Int64Param
	static std::string getPBStrForInt64Param(const Int64ParamPtr& p);
	static bool parseInt64ParamFromPBStr(const std::string& s, Int64ParamPtr& p);

	static std::string getStrForInt64Param(const Int64ParamPtr& p);
	static std::string getJsonStrForInt64Param(const Int64ParamPtr& p);
	static bool parseInt64ParamFromJsonStr(const std::string& s, Int64ParamPtr& p);

	static std::string getCsvStrForInt64Param(const Int64ParamPtr& p, const std::string& sep = "|");
	static bool parseInt64ParamFromCsvStr(const std::string& s, Int64ParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInt64Param(const Int64ParamPtr& p, const std::string& sep = "|");
	static bool parseInt64ParamFromPlainCsvStr(const std::string& s, Int64ParamPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInt64Param(const Int64ParamPtr& p);
	static bool parseInt64ParamFromStringMapPtr(const StringMapPtr& smp, Int64ParamPtr& p);

	static void updateInt64ParamFromStringMapPtr(const StringMapPtr& smp, Int64ParamPtr& p);

	//////end_Int64Param

	//////begin_DoubleIntParams
	static std::string getPBStrForDoubleIntParams(const DoubleIntParamsPtr& p);
	static bool parseDoubleIntParamsFromPBStr(const std::string& s, DoubleIntParamsPtr& p);

	static std::string getStrForDoubleIntParams(const DoubleIntParamsPtr& p);
	static std::string getJsonStrForDoubleIntParams(const DoubleIntParamsPtr& p);
	static bool parseDoubleIntParamsFromJsonStr(const std::string& s, DoubleIntParamsPtr& p);

	static std::string getCsvStrForDoubleIntParams(const DoubleIntParamsPtr& p, const std::string& sep = "|");
	static bool parseDoubleIntParamsFromCsvStr(const std::string& s, DoubleIntParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleIntParams(const DoubleIntParamsPtr& p, const std::string& sep = "|");
	static bool parseDoubleIntParamsFromPlainCsvStr(const std::string& s, DoubleIntParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleIntParams(const DoubleIntParamsPtr& p);
	static bool parseDoubleIntParamsFromStringMapPtr(const StringMapPtr& smp, DoubleIntParamsPtr& p);

	static void updateDoubleIntParamsFromStringMapPtr(const StringMapPtr& smp, DoubleIntParamsPtr& p);

	//////end_DoubleIntParams

	//////begin_DoubleFunctionParams
	static std::string getPBStrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p);
	static bool parseDoubleFunctionParamsFromPBStr(const std::string& s, DoubleFunctionParamsPtr& p);

	static std::string getStrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p);
	static std::string getJsonStrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p);
	static bool parseDoubleFunctionParamsFromJsonStr(const std::string& s, DoubleFunctionParamsPtr& p);

	static std::string getCsvStrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p, const std::string& sep = "|");
	static bool parseDoubleFunctionParamsFromCsvStr(const std::string& s, DoubleFunctionParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p, const std::string& sep = "|");
	static bool parseDoubleFunctionParamsFromPlainCsvStr(const std::string& s, DoubleFunctionParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDoubleFunctionParams(const DoubleFunctionParamsPtr& p);
	static bool parseDoubleFunctionParamsFromStringMapPtr(const StringMapPtr& smp, DoubleFunctionParamsPtr& p);

	static void updateDoubleFunctionParamsFromStringMapPtr(const StringMapPtr& smp, DoubleFunctionParamsPtr& p);

	//////end_DoubleFunctionParams

	//////begin_PointData
	static std::string getPBStrForPointData(const PointDataPtr& p);
	static bool parsePointDataFromPBStr(const std::string& s, PointDataPtr& p);

	static std::string getStrForPointData(const PointDataPtr& p);
	static std::string getJsonStrForPointData(const PointDataPtr& p);
	static bool parsePointDataFromJsonStr(const std::string& s, PointDataPtr& p);

	static std::string getCsvStrForPointData(const PointDataPtr& p, const std::string& sep = "|");
	static bool parsePointDataFromCsvStr(const std::string& s, PointDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPointData(const PointDataPtr& p, const std::string& sep = "|");
	static bool parsePointDataFromPlainCsvStr(const std::string& s, PointDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPointData(const PointDataPtr& p);
	static bool parsePointDataFromStringMapPtr(const StringMapPtr& smp, PointDataPtr& p);

	static void updatePointDataFromStringMapPtr(const StringMapPtr& smp, PointDataPtr& p);

	//////end_PointData

	//////begin_PointDataMap
	static std::string getPBStrForPointDataMap(const PointDataMapPtr& p);
	static bool parsePointDataMapFromPBStr(const std::string& s, PointDataMapPtr& p);

	static std::string getStrForPointDataMap(const PointDataMapPtr& p);
	static std::string getJsonStrForPointDataMap(const PointDataMapPtr& p);
	static bool parsePointDataMapFromJsonStr(const std::string& s, PointDataMapPtr& p);

	static std::string getCsvStrForPointDataMap(const PointDataMapPtr& p, const std::string& sep = "|");
	static bool parsePointDataMapFromCsvStr(const std::string& s, PointDataMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPointDataMap(const PointDataMapPtr& p, const std::string& sep = "|");
	static bool parsePointDataMapFromPlainCsvStr(const std::string& s, PointDataMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPointDataMap(const PointDataMapPtr& p);
	static bool parsePointDataMapFromStringMapPtr(const StringMapPtr& smp, PointDataMapPtr& p);

	static void updatePointDataMapFromStringMapPtr(const StringMapPtr& smp, PointDataMapPtr& p);

	//////end_PointDataMap

	//////begin_PointDataList
	static std::string getPBStrForPointDataList(const PointDataListPtr& p);
	static bool parsePointDataListFromPBStr(const std::string& s, PointDataListPtr& p);

	static std::string getStrForPointDataList(const PointDataListPtr& p);
	static std::string getJsonStrForPointDataList(const PointDataListPtr& p);
	static bool parsePointDataListFromJsonStr(const std::string& s, PointDataListPtr& p);

	static std::string getCsvStrForPointDataList(const PointDataListPtr& p, const std::string& sep = "|");
	static bool parsePointDataListFromCsvStr(const std::string& s, PointDataListPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPointDataList(const PointDataListPtr& p, const std::string& sep = "|");
	static bool parsePointDataListFromPlainCsvStr(const std::string& s, PointDataListPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPointDataList(const PointDataListPtr& p);
	static bool parsePointDataListFromStringMapPtr(const StringMapPtr& smp, PointDataListPtr& p);

	static void updatePointDataListFromStringMapPtr(const StringMapPtr& smp, PointDataListPtr& p);

	//////end_PointDataList

	//////begin_CurveCfgData
	static std::string getPBStrForCurveCfgData(const CurveCfgDataPtr& p);
	static bool parseCurveCfgDataFromPBStr(const std::string& s, CurveCfgDataPtr& p);

	static std::string getStrForCurveCfgData(const CurveCfgDataPtr& p);
	static std::string getJsonStrForCurveCfgData(const CurveCfgDataPtr& p);
	static bool parseCurveCfgDataFromJsonStr(const std::string& s, CurveCfgDataPtr& p);

	static std::string getCsvStrForCurveCfgData(const CurveCfgDataPtr& p, const std::string& sep = "|");
	static bool parseCurveCfgDataFromCsvStr(const std::string& s, CurveCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForCurveCfgData(const CurveCfgDataPtr& p, const std::string& sep = "|");
	static bool parseCurveCfgDataFromPlainCsvStr(const std::string& s, CurveCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForCurveCfgData(const CurveCfgDataPtr& p);
	static bool parseCurveCfgDataFromStringMapPtr(const StringMapPtr& smp, CurveCfgDataPtr& p);

	static void updateCurveCfgDataFromStringMapPtr(const StringMapPtr& smp, CurveCfgDataPtr& p);

	//////end_CurveCfgData

	//////begin_CurveData
	static std::string getPBStrForCurveData(const CurveDataPtr& p);
	static bool parseCurveDataFromPBStr(const std::string& s, CurveDataPtr& p);

	static std::string getStrForCurveData(const CurveDataPtr& p);
	static std::string getJsonStrForCurveData(const CurveDataPtr& p);
	static bool parseCurveDataFromJsonStr(const std::string& s, CurveDataPtr& p);

	static std::string getCsvStrForCurveData(const CurveDataPtr& p, const std::string& sep = "|");
	static bool parseCurveDataFromCsvStr(const std::string& s, CurveDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForCurveData(const CurveDataPtr& p, const std::string& sep = "|");
	static bool parseCurveDataFromPlainCsvStr(const std::string& s, CurveDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForCurveData(const CurveDataPtr& p);
	static bool parseCurveDataFromStringMapPtr(const StringMapPtr& smp, CurveDataPtr& p);

	static void updateCurveDataFromStringMapPtr(const StringMapPtr& smp, CurveDataPtr& p);

	//////end_CurveData

	//////begin_GatewayCfgData
	static std::string getPBStrForGatewayCfgData(const GatewayCfgDataPtr& p);
	static bool parseGatewayCfgDataFromPBStr(const std::string& s, GatewayCfgDataPtr& p);

	static std::string getStrForGatewayCfgData(const GatewayCfgDataPtr& p);
	static std::string getJsonStrForGatewayCfgData(const GatewayCfgDataPtr& p);
	static bool parseGatewayCfgDataFromJsonStr(const std::string& s, GatewayCfgDataPtr& p);

	static std::string getCsvStrForGatewayCfgData(const GatewayCfgDataPtr& p, const std::string& sep = "|");
	static bool parseGatewayCfgDataFromCsvStr(const std::string& s, GatewayCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForGatewayCfgData(const GatewayCfgDataPtr& p, const std::string& sep = "|");
	static bool parseGatewayCfgDataFromPlainCsvStr(const std::string& s, GatewayCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForGatewayCfgData(const GatewayCfgDataPtr& p);
	static bool parseGatewayCfgDataFromStringMapPtr(const StringMapPtr& smp, GatewayCfgDataPtr& p);

	static void updateGatewayCfgDataFromStringMapPtr(const StringMapPtr& smp, GatewayCfgDataPtr& p);

	//////end_GatewayCfgData

	//////begin_GatewayData
	static std::string getPBStrForGatewayData(const GatewayDataPtr& p);
	static bool parseGatewayDataFromPBStr(const std::string& s, GatewayDataPtr& p);

	static std::string getStrForGatewayData(const GatewayDataPtr& p);
	static std::string getJsonStrForGatewayData(const GatewayDataPtr& p);
	static bool parseGatewayDataFromJsonStr(const std::string& s, GatewayDataPtr& p);

	static std::string getCsvStrForGatewayData(const GatewayDataPtr& p, const std::string& sep = "|");
	static bool parseGatewayDataFromCsvStr(const std::string& s, GatewayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForGatewayData(const GatewayDataPtr& p, const std::string& sep = "|");
	static bool parseGatewayDataFromPlainCsvStr(const std::string& s, GatewayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForGatewayData(const GatewayDataPtr& p);
	static bool parseGatewayDataFromStringMapPtr(const StringMapPtr& smp, GatewayDataPtr& p);

	static void updateGatewayDataFromStringMapPtr(const StringMapPtr& smp, GatewayDataPtr& p);

	//////end_GatewayData

	//////begin_VolumeOutlayPair
	static std::string getPBStrForVolumeOutlayPair(const VolumeOutlayPairPtr& p);
	static bool parseVolumeOutlayPairFromPBStr(const std::string& s, VolumeOutlayPairPtr& p);

	static std::string getStrForVolumeOutlayPair(const VolumeOutlayPairPtr& p);
	static std::string getJsonStrForVolumeOutlayPair(const VolumeOutlayPairPtr& p);
	static bool parseVolumeOutlayPairFromJsonStr(const std::string& s, VolumeOutlayPairPtr& p);

	static std::string getCsvStrForVolumeOutlayPair(const VolumeOutlayPairPtr& p, const std::string& sep = "|");
	static bool parseVolumeOutlayPairFromCsvStr(const std::string& s, VolumeOutlayPairPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForVolumeOutlayPair(const VolumeOutlayPairPtr& p, const std::string& sep = "|");
	static bool parseVolumeOutlayPairFromPlainCsvStr(const std::string& s, VolumeOutlayPairPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForVolumeOutlayPair(const VolumeOutlayPairPtr& p);
	static bool parseVolumeOutlayPairFromStringMapPtr(const StringMapPtr& smp, VolumeOutlayPairPtr& p);

	static void updateVolumeOutlayPairFromStringMapPtr(const StringMapPtr& smp, VolumeOutlayPairPtr& p);

	//////end_VolumeOutlayPair

	//////begin_VolumeAmountData
	static std::string getPBStrForVolumeAmountData(const VolumeAmountDataPtr& p);
	static bool parseVolumeAmountDataFromPBStr(const std::string& s, VolumeAmountDataPtr& p);

	static std::string getStrForVolumeAmountData(const VolumeAmountDataPtr& p);
	static std::string getJsonStrForVolumeAmountData(const VolumeAmountDataPtr& p);
	static bool parseVolumeAmountDataFromJsonStr(const std::string& s, VolumeAmountDataPtr& p);

	static std::string getCsvStrForVolumeAmountData(const VolumeAmountDataPtr& p, const std::string& sep = "|");
	static bool parseVolumeAmountDataFromCsvStr(const std::string& s, VolumeAmountDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForVolumeAmountData(const VolumeAmountDataPtr& p, const std::string& sep = "|");
	static bool parseVolumeAmountDataFromPlainCsvStr(const std::string& s, VolumeAmountDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForVolumeAmountData(const VolumeAmountDataPtr& p);
	static bool parseVolumeAmountDataFromStringMapPtr(const StringMapPtr& smp, VolumeAmountDataPtr& p);

	static void updateVolumeAmountDataFromStringMapPtr(const StringMapPtr& smp, VolumeAmountDataPtr& p);

	//////end_VolumeAmountData

	//////begin_TradePxVolumeData
	static std::string getPBStrForTradePxVolumeData(const TradePxVolumeDataPtr& p);
	static bool parseTradePxVolumeDataFromPBStr(const std::string& s, TradePxVolumeDataPtr& p);

	static std::string getStrForTradePxVolumeData(const TradePxVolumeDataPtr& p);
	static std::string getJsonStrForTradePxVolumeData(const TradePxVolumeDataPtr& p);
	static bool parseTradePxVolumeDataFromJsonStr(const std::string& s, TradePxVolumeDataPtr& p);

	static std::string getCsvStrForTradePxVolumeData(const TradePxVolumeDataPtr& p, const std::string& sep = "|");
	static bool parseTradePxVolumeDataFromCsvStr(const std::string& s, TradePxVolumeDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTradePxVolumeData(const TradePxVolumeDataPtr& p, const std::string& sep = "|");
	static bool parseTradePxVolumeDataFromPlainCsvStr(const std::string& s, TradePxVolumeDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTradePxVolumeData(const TradePxVolumeDataPtr& p);
	static bool parseTradePxVolumeDataFromStringMapPtr(const StringMapPtr& smp, TradePxVolumeDataPtr& p);

	static void updateTradePxVolumeDataFromStringMapPtr(const StringMapPtr& smp, TradePxVolumeDataPtr& p);

	//////end_TradePxVolumeData

	//////begin_InstrSpecData
	static std::string getPBStrForInstrSpecData(const InstrSpecDataPtr& p);
	static bool parseInstrSpecDataFromPBStr(const std::string& s, InstrSpecDataPtr& p);

	static std::string getStrForInstrSpecData(const InstrSpecDataPtr& p);
	static std::string getJsonStrForInstrSpecData(const InstrSpecDataPtr& p);
	static bool parseInstrSpecDataFromJsonStr(const std::string& s, InstrSpecDataPtr& p);

	static std::string getCsvStrForInstrSpecData(const InstrSpecDataPtr& p, const std::string& sep = "|");
	static bool parseInstrSpecDataFromCsvStr(const std::string& s, InstrSpecDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrSpecData(const InstrSpecDataPtr& p, const std::string& sep = "|");
	static bool parseInstrSpecDataFromPlainCsvStr(const std::string& s, InstrSpecDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrSpecData(const InstrSpecDataPtr& p);
	static bool parseInstrSpecDataFromStringMapPtr(const StringMapPtr& smp, InstrSpecDataPtr& p);

	static void updateInstrSpecDataFromStringMapPtr(const StringMapPtr& smp, InstrSpecDataPtr& p);

	//////end_InstrSpecData

	//////begin_GlobalCfgData
	static std::string getPBStrForGlobalCfgData(const GlobalCfgDataPtr& p);
	static bool parseGlobalCfgDataFromPBStr(const std::string& s, GlobalCfgDataPtr& p);

	static std::string getStrForGlobalCfgData(const GlobalCfgDataPtr& p);
	static std::string getJsonStrForGlobalCfgData(const GlobalCfgDataPtr& p);
	static bool parseGlobalCfgDataFromJsonStr(const std::string& s, GlobalCfgDataPtr& p);

	static std::string getCsvStrForGlobalCfgData(const GlobalCfgDataPtr& p, const std::string& sep = "|");
	static bool parseGlobalCfgDataFromCsvStr(const std::string& s, GlobalCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForGlobalCfgData(const GlobalCfgDataPtr& p, const std::string& sep = "|");
	static bool parseGlobalCfgDataFromPlainCsvStr(const std::string& s, GlobalCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForGlobalCfgData(const GlobalCfgDataPtr& p);
	static bool parseGlobalCfgDataFromStringMapPtr(const StringMapPtr& smp, GlobalCfgDataPtr& p);

	static void updateGlobalCfgDataFromStringMapPtr(const StringMapPtr& smp, GlobalCfgDataPtr& p);

	//////end_GlobalCfgData

	//////begin_GlobalData
	static std::string getPBStrForGlobalData(const GlobalDataPtr& p);
	static bool parseGlobalDataFromPBStr(const std::string& s, GlobalDataPtr& p);

	static std::string getStrForGlobalData(const GlobalDataPtr& p);
	static std::string getJsonStrForGlobalData(const GlobalDataPtr& p);
	static bool parseGlobalDataFromJsonStr(const std::string& s, GlobalDataPtr& p);

	static std::string getCsvStrForGlobalData(const GlobalDataPtr& p, const std::string& sep = "|");
	static bool parseGlobalDataFromCsvStr(const std::string& s, GlobalDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForGlobalData(const GlobalDataPtr& p, const std::string& sep = "|");
	static bool parseGlobalDataFromPlainCsvStr(const std::string& s, GlobalDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForGlobalData(const GlobalDataPtr& p);
	static bool parseGlobalDataFromStringMapPtr(const StringMapPtr& smp, GlobalDataPtr& p);

	static void updateGlobalDataFromStringMapPtr(const StringMapPtr& smp, GlobalDataPtr& p);

	//////end_GlobalData

	//////begin_MongoDBCfgData
	static std::string getPBStrForMongoDBCfgData(const MongoDBCfgDataPtr& p);
	static bool parseMongoDBCfgDataFromPBStr(const std::string& s, MongoDBCfgDataPtr& p);

	static std::string getStrForMongoDBCfgData(const MongoDBCfgDataPtr& p);
	static std::string getJsonStrForMongoDBCfgData(const MongoDBCfgDataPtr& p);
	static bool parseMongoDBCfgDataFromJsonStr(const std::string& s, MongoDBCfgDataPtr& p);

	static std::string getCsvStrForMongoDBCfgData(const MongoDBCfgDataPtr& p, const std::string& sep = "|");
	static bool parseMongoDBCfgDataFromCsvStr(const std::string& s, MongoDBCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForMongoDBCfgData(const MongoDBCfgDataPtr& p, const std::string& sep = "|");
	static bool parseMongoDBCfgDataFromPlainCsvStr(const std::string& s, MongoDBCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForMongoDBCfgData(const MongoDBCfgDataPtr& p);
	static bool parseMongoDBCfgDataFromStringMapPtr(const StringMapPtr& smp, MongoDBCfgDataPtr& p);

	static void updateMongoDBCfgDataFromStringMapPtr(const StringMapPtr& smp, MongoDBCfgDataPtr& p);

	//////end_MongoDBCfgData

	//////begin_SQLiteCfgData
	static std::string getPBStrForSQLiteCfgData(const SQLiteCfgDataPtr& p);
	static bool parseSQLiteCfgDataFromPBStr(const std::string& s, SQLiteCfgDataPtr& p);

	static std::string getStrForSQLiteCfgData(const SQLiteCfgDataPtr& p);
	static std::string getJsonStrForSQLiteCfgData(const SQLiteCfgDataPtr& p);
	static bool parseSQLiteCfgDataFromJsonStr(const std::string& s, SQLiteCfgDataPtr& p);

	static std::string getCsvStrForSQLiteCfgData(const SQLiteCfgDataPtr& p, const std::string& sep = "|");
	static bool parseSQLiteCfgDataFromCsvStr(const std::string& s, SQLiteCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForSQLiteCfgData(const SQLiteCfgDataPtr& p, const std::string& sep = "|");
	static bool parseSQLiteCfgDataFromPlainCsvStr(const std::string& s, SQLiteCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForSQLiteCfgData(const SQLiteCfgDataPtr& p);
	static bool parseSQLiteCfgDataFromStringMapPtr(const StringMapPtr& smp, SQLiteCfgDataPtr& p);

	static void updateSQLiteCfgDataFromStringMapPtr(const StringMapPtr& smp, SQLiteCfgDataPtr& p);

	//////end_SQLiteCfgData

	//////begin_ZMQCfgData
	static std::string getPBStrForZMQCfgData(const ZMQCfgDataPtr& p);
	static bool parseZMQCfgDataFromPBStr(const std::string& s, ZMQCfgDataPtr& p);

	static std::string getStrForZMQCfgData(const ZMQCfgDataPtr& p);
	static std::string getJsonStrForZMQCfgData(const ZMQCfgDataPtr& p);
	static bool parseZMQCfgDataFromJsonStr(const std::string& s, ZMQCfgDataPtr& p);

	static std::string getCsvStrForZMQCfgData(const ZMQCfgDataPtr& p, const std::string& sep = "|");
	static bool parseZMQCfgDataFromCsvStr(const std::string& s, ZMQCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForZMQCfgData(const ZMQCfgDataPtr& p, const std::string& sep = "|");
	static bool parseZMQCfgDataFromPlainCsvStr(const std::string& s, ZMQCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForZMQCfgData(const ZMQCfgDataPtr& p);
	static bool parseZMQCfgDataFromStringMapPtr(const StringMapPtr& smp, ZMQCfgDataPtr& p);

	static void updateZMQCfgDataFromStringMapPtr(const StringMapPtr& smp, ZMQCfgDataPtr& p);

	//////end_ZMQCfgData

	//////begin_ZMQData
	static std::string getPBStrForZMQData(const ZMQDataPtr& p);
	static bool parseZMQDataFromPBStr(const std::string& s, ZMQDataPtr& p);

	static std::string getStrForZMQData(const ZMQDataPtr& p);
	static std::string getJsonStrForZMQData(const ZMQDataPtr& p);
	static bool parseZMQDataFromJsonStr(const std::string& s, ZMQDataPtr& p);

	static std::string getCsvStrForZMQData(const ZMQDataPtr& p, const std::string& sep = "|");
	static bool parseZMQDataFromCsvStr(const std::string& s, ZMQDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForZMQData(const ZMQDataPtr& p, const std::string& sep = "|");
	static bool parseZMQDataFromPlainCsvStr(const std::string& s, ZMQDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForZMQData(const ZMQDataPtr& p);
	static bool parseZMQDataFromStringMapPtr(const StringMapPtr& smp, ZMQDataPtr& p);

	static void updateZMQDataFromStringMapPtr(const StringMapPtr& smp, ZMQDataPtr& p);

	//////end_ZMQData

	//////begin_StratCfgData
	static std::string getPBStrForStratCfgData(const StratCfgDataPtr& p);
	static bool parseStratCfgDataFromPBStr(const std::string& s, StratCfgDataPtr& p);

	static std::string getStrForStratCfgData(const StratCfgDataPtr& p);
	static std::string getJsonStrForStratCfgData(const StratCfgDataPtr& p);
	static bool parseStratCfgDataFromJsonStr(const std::string& s, StratCfgDataPtr& p);

	static std::string getCsvStrForStratCfgData(const StratCfgDataPtr& p, const std::string& sep = "|");
	static bool parseStratCfgDataFromCsvStr(const std::string& s, StratCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStratCfgData(const StratCfgDataPtr& p, const std::string& sep = "|");
	static bool parseStratCfgDataFromPlainCsvStr(const std::string& s, StratCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStratCfgData(const StratCfgDataPtr& p);
	static bool parseStratCfgDataFromStringMapPtr(const StringMapPtr& smp, StratCfgDataPtr& p);

	static void updateStratCfgDataFromStringMapPtr(const StringMapPtr& smp, StratCfgDataPtr& p);

	//////end_StratCfgData

	//////begin_StratData
	static std::string getPBStrForStratData(const StratDataPtr& p);
	static bool parseStratDataFromPBStr(const std::string& s, StratDataPtr& p);

	static std::string getStrForStratData(const StratDataPtr& p);
	static std::string getJsonStrForStratData(const StratDataPtr& p);
	static bool parseStratDataFromJsonStr(const std::string& s, StratDataPtr& p);

	static std::string getCsvStrForStratData(const StratDataPtr& p, const std::string& sep = "|");
	static bool parseStratDataFromCsvStr(const std::string& s, StratDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForStratData(const StratDataPtr& p, const std::string& sep = "|");
	static bool parseStratDataFromPlainCsvStr(const std::string& s, StratDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForStratData(const StratDataPtr& p);
	static bool parseStratDataFromStringMapPtr(const StringMapPtr& smp, StratDataPtr& p);

	static void updateStratDataFromStringMapPtr(const StringMapPtr& smp, StratDataPtr& p);

	//////end_StratData

	//////begin_InstrCfgData
	static std::string getPBStrForInstrCfgData(const InstrCfgDataPtr& p);
	static bool parseInstrCfgDataFromPBStr(const std::string& s, InstrCfgDataPtr& p);

	static std::string getStrForInstrCfgData(const InstrCfgDataPtr& p);
	static std::string getJsonStrForInstrCfgData(const InstrCfgDataPtr& p);
	static bool parseInstrCfgDataFromJsonStr(const std::string& s, InstrCfgDataPtr& p);

	static std::string getCsvStrForInstrCfgData(const InstrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseInstrCfgDataFromCsvStr(const std::string& s, InstrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrCfgData(const InstrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseInstrCfgDataFromPlainCsvStr(const std::string& s, InstrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrCfgData(const InstrCfgDataPtr& p);
	static bool parseInstrCfgDataFromStringMapPtr(const StringMapPtr& smp, InstrCfgDataPtr& p);

	static void updateInstrCfgDataFromStringMapPtr(const StringMapPtr& smp, InstrCfgDataPtr& p);

	//////end_InstrCfgData

	//////begin_InstrData
	static std::string getPBStrForInstrData(const InstrDataPtr& p);
	static bool parseInstrDataFromPBStr(const std::string& s, InstrDataPtr& p);

	static std::string getStrForInstrData(const InstrDataPtr& p);
	static std::string getJsonStrForInstrData(const InstrDataPtr& p);
	static bool parseInstrDataFromJsonStr(const std::string& s, InstrDataPtr& p);

	static std::string getCsvStrForInstrData(const InstrDataPtr& p, const std::string& sep = "|");
	static bool parseInstrDataFromCsvStr(const std::string& s, InstrDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrData(const InstrDataPtr& p, const std::string& sep = "|");
	static bool parseInstrDataFromPlainCsvStr(const std::string& s, InstrDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrData(const InstrDataPtr& p);
	static bool parseInstrDataFromStringMapPtr(const StringMapPtr& smp, InstrDataPtr& p);

	static void updateInstrDataFromStringMapPtr(const StringMapPtr& smp, InstrDataPtr& p);

	//////end_InstrData

	//////begin_FCCfgData
	static std::string getPBStrForFCCfgData(const FCCfgDataPtr& p);
	static bool parseFCCfgDataFromPBStr(const std::string& s, FCCfgDataPtr& p);

	static std::string getStrForFCCfgData(const FCCfgDataPtr& p);
	static std::string getJsonStrForFCCfgData(const FCCfgDataPtr& p);
	static bool parseFCCfgDataFromJsonStr(const std::string& s, FCCfgDataPtr& p);

	static std::string getCsvStrForFCCfgData(const FCCfgDataPtr& p, const std::string& sep = "|");
	static bool parseFCCfgDataFromCsvStr(const std::string& s, FCCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForFCCfgData(const FCCfgDataPtr& p, const std::string& sep = "|");
	static bool parseFCCfgDataFromPlainCsvStr(const std::string& s, FCCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForFCCfgData(const FCCfgDataPtr& p);
	static bool parseFCCfgDataFromStringMapPtr(const StringMapPtr& smp, FCCfgDataPtr& p);

	static void updateFCCfgDataFromStringMapPtr(const StringMapPtr& smp, FCCfgDataPtr& p);

	//////end_FCCfgData

	//////begin_FCData
	static std::string getPBStrForFCData(const FCDataPtr& p);
	static bool parseFCDataFromPBStr(const std::string& s, FCDataPtr& p);

	static std::string getStrForFCData(const FCDataPtr& p);
	static std::string getJsonStrForFCData(const FCDataPtr& p);
	static bool parseFCDataFromJsonStr(const std::string& s, FCDataPtr& p);

	static std::string getCsvStrForFCData(const FCDataPtr& p, const std::string& sep = "|");
	static bool parseFCDataFromCsvStr(const std::string& s, FCDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForFCData(const FCDataPtr& p, const std::string& sep = "|");
	static bool parseFCDataFromPlainCsvStr(const std::string& s, FCDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForFCData(const FCDataPtr& p);
	static bool parseFCDataFromStringMapPtr(const StringMapPtr& smp, FCDataPtr& p);

	static void updateFCDataFromStringMapPtr(const StringMapPtr& smp, FCDataPtr& p);

	//////end_FCData

	//////begin_OCCfgData
	static std::string getPBStrForOCCfgData(const OCCfgDataPtr& p);
	static bool parseOCCfgDataFromPBStr(const std::string& s, OCCfgDataPtr& p);

	static std::string getStrForOCCfgData(const OCCfgDataPtr& p);
	static std::string getJsonStrForOCCfgData(const OCCfgDataPtr& p);
	static bool parseOCCfgDataFromJsonStr(const std::string& s, OCCfgDataPtr& p);

	static std::string getCsvStrForOCCfgData(const OCCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOCCfgDataFromCsvStr(const std::string& s, OCCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOCCfgData(const OCCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOCCfgDataFromPlainCsvStr(const std::string& s, OCCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOCCfgData(const OCCfgDataPtr& p);
	static bool parseOCCfgDataFromStringMapPtr(const StringMapPtr& smp, OCCfgDataPtr& p);

	static void updateOCCfgDataFromStringMapPtr(const StringMapPtr& smp, OCCfgDataPtr& p);

	//////end_OCCfgData

	//////begin_OCStrikeData
	static std::string getPBStrForOCStrikeData(const OCStrikeDataPtr& p);
	static bool parseOCStrikeDataFromPBStr(const std::string& s, OCStrikeDataPtr& p);

	static std::string getStrForOCStrikeData(const OCStrikeDataPtr& p);
	static std::string getJsonStrForOCStrikeData(const OCStrikeDataPtr& p);
	static bool parseOCStrikeDataFromJsonStr(const std::string& s, OCStrikeDataPtr& p);

	static std::string getCsvStrForOCStrikeData(const OCStrikeDataPtr& p, const std::string& sep = "|");
	static bool parseOCStrikeDataFromCsvStr(const std::string& s, OCStrikeDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOCStrikeData(const OCStrikeDataPtr& p, const std::string& sep = "|");
	static bool parseOCStrikeDataFromPlainCsvStr(const std::string& s, OCStrikeDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOCStrikeData(const OCStrikeDataPtr& p);
	static bool parseOCStrikeDataFromStringMapPtr(const StringMapPtr& smp, OCStrikeDataPtr& p);

	static void updateOCStrikeDataFromStringMapPtr(const StringMapPtr& smp, OCStrikeDataPtr& p);

	//////end_OCStrikeData

	//////begin_ATMInfo
	static std::string getPBStrForATMInfo(const ATMInfoPtr& p);
	static bool parseATMInfoFromPBStr(const std::string& s, ATMInfoPtr& p);

	static std::string getStrForATMInfo(const ATMInfoPtr& p);
	static std::string getJsonStrForATMInfo(const ATMInfoPtr& p);
	static bool parseATMInfoFromJsonStr(const std::string& s, ATMInfoPtr& p);

	static std::string getCsvStrForATMInfo(const ATMInfoPtr& p, const std::string& sep = "|");
	static bool parseATMInfoFromCsvStr(const std::string& s, ATMInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForATMInfo(const ATMInfoPtr& p, const std::string& sep = "|");
	static bool parseATMInfoFromPlainCsvStr(const std::string& s, ATMInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForATMInfo(const ATMInfoPtr& p);
	static bool parseATMInfoFromStringMapPtr(const StringMapPtr& smp, ATMInfoPtr& p);

	static void updateATMInfoFromStringMapPtr(const StringMapPtr& smp, ATMInfoPtr& p);

	//////end_ATMInfo

	//////begin_OCData
	static std::string getPBStrForOCData(const OCDataPtr& p);
	static bool parseOCDataFromPBStr(const std::string& s, OCDataPtr& p);

	static std::string getStrForOCData(const OCDataPtr& p);
	static std::string getJsonStrForOCData(const OCDataPtr& p);
	static bool parseOCDataFromJsonStr(const std::string& s, OCDataPtr& p);

	static std::string getCsvStrForOCData(const OCDataPtr& p, const std::string& sep = "|");
	static bool parseOCDataFromCsvStr(const std::string& s, OCDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOCData(const OCDataPtr& p, const std::string& sep = "|");
	static bool parseOCDataFromPlainCsvStr(const std::string& s, OCDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOCData(const OCDataPtr& p);
	static bool parseOCDataFromStringMapPtr(const StringMapPtr& smp, OCDataPtr& p);

	static void updateOCDataFromStringMapPtr(const StringMapPtr& smp, OCDataPtr& p);

	//////end_OCData

	//////begin_OCSCfgData
	static std::string getPBStrForOCSCfgData(const OCSCfgDataPtr& p);
	static bool parseOCSCfgDataFromPBStr(const std::string& s, OCSCfgDataPtr& p);

	static std::string getStrForOCSCfgData(const OCSCfgDataPtr& p);
	static std::string getJsonStrForOCSCfgData(const OCSCfgDataPtr& p);
	static bool parseOCSCfgDataFromJsonStr(const std::string& s, OCSCfgDataPtr& p);

	static std::string getCsvStrForOCSCfgData(const OCSCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOCSCfgDataFromCsvStr(const std::string& s, OCSCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOCSCfgData(const OCSCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOCSCfgDataFromPlainCsvStr(const std::string& s, OCSCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOCSCfgData(const OCSCfgDataPtr& p);
	static bool parseOCSCfgDataFromStringMapPtr(const StringMapPtr& smp, OCSCfgDataPtr& p);

	static void updateOCSCfgDataFromStringMapPtr(const StringMapPtr& smp, OCSCfgDataPtr& p);

	//////end_OCSCfgData

	//////begin_OCSData
	static std::string getPBStrForOCSData(const OCSDataPtr& p);
	static bool parseOCSDataFromPBStr(const std::string& s, OCSDataPtr& p);

	static std::string getStrForOCSData(const OCSDataPtr& p);
	static std::string getJsonStrForOCSData(const OCSDataPtr& p);
	static bool parseOCSDataFromJsonStr(const std::string& s, OCSDataPtr& p);

	static std::string getCsvStrForOCSData(const OCSDataPtr& p, const std::string& sep = "|");
	static bool parseOCSDataFromCsvStr(const std::string& s, OCSDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOCSData(const OCSDataPtr& p, const std::string& sep = "|");
	static bool parseOCSDataFromPlainCsvStr(const std::string& s, OCSDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOCSData(const OCSDataPtr& p);
	static bool parseOCSDataFromStringMapPtr(const StringMapPtr& smp, OCSDataPtr& p);

	static void updateOCSDataFromStringMapPtr(const StringMapPtr& smp, OCSDataPtr& p);

	//////end_OCSData

	//////begin_PortfolioCfgData
	static std::string getPBStrForPortfolioCfgData(const PortfolioCfgDataPtr& p);
	static bool parsePortfolioCfgDataFromPBStr(const std::string& s, PortfolioCfgDataPtr& p);

	static std::string getStrForPortfolioCfgData(const PortfolioCfgDataPtr& p);
	static std::string getJsonStrForPortfolioCfgData(const PortfolioCfgDataPtr& p);
	static bool parsePortfolioCfgDataFromJsonStr(const std::string& s, PortfolioCfgDataPtr& p);

	static std::string getCsvStrForPortfolioCfgData(const PortfolioCfgDataPtr& p, const std::string& sep = "|");
	static bool parsePortfolioCfgDataFromCsvStr(const std::string& s, PortfolioCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPortfolioCfgData(const PortfolioCfgDataPtr& p, const std::string& sep = "|");
	static bool parsePortfolioCfgDataFromPlainCsvStr(const std::string& s, PortfolioCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPortfolioCfgData(const PortfolioCfgDataPtr& p);
	static bool parsePortfolioCfgDataFromStringMapPtr(const StringMapPtr& smp, PortfolioCfgDataPtr& p);

	static void updatePortfolioCfgDataFromStringMapPtr(const StringMapPtr& smp, PortfolioCfgDataPtr& p);

	//////end_PortfolioCfgData

	//////begin_PortfolioData
	static std::string getPBStrForPortfolioData(const PortfolioDataPtr& p);
	static bool parsePortfolioDataFromPBStr(const std::string& s, PortfolioDataPtr& p);

	static std::string getStrForPortfolioData(const PortfolioDataPtr& p);
	static std::string getJsonStrForPortfolioData(const PortfolioDataPtr& p);
	static bool parsePortfolioDataFromJsonStr(const std::string& s, PortfolioDataPtr& p);

	static std::string getCsvStrForPortfolioData(const PortfolioDataPtr& p, const std::string& sep = "|");
	static bool parsePortfolioDataFromCsvStr(const std::string& s, PortfolioDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPortfolioData(const PortfolioDataPtr& p, const std::string& sep = "|");
	static bool parsePortfolioDataFromPlainCsvStr(const std::string& s, PortfolioDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPortfolioData(const PortfolioDataPtr& p);
	static bool parsePortfolioDataFromStringMapPtr(const StringMapPtr& smp, PortfolioDataPtr& p);

	static void updatePortfolioDataFromStringMapPtr(const StringMapPtr& smp, PortfolioDataPtr& p);

	//////end_PortfolioData

	//////begin_PICfgData
	static std::string getPBStrForPICfgData(const PICfgDataPtr& p);
	static bool parsePICfgDataFromPBStr(const std::string& s, PICfgDataPtr& p);

	static std::string getStrForPICfgData(const PICfgDataPtr& p);
	static std::string getJsonStrForPICfgData(const PICfgDataPtr& p);
	static bool parsePICfgDataFromJsonStr(const std::string& s, PICfgDataPtr& p);

	static std::string getCsvStrForPICfgData(const PICfgDataPtr& p, const std::string& sep = "|");
	static bool parsePICfgDataFromCsvStr(const std::string& s, PICfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPICfgData(const PICfgDataPtr& p, const std::string& sep = "|");
	static bool parsePICfgDataFromPlainCsvStr(const std::string& s, PICfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPICfgData(const PICfgDataPtr& p);
	static bool parsePICfgDataFromStringMapPtr(const StringMapPtr& smp, PICfgDataPtr& p);

	static void updatePICfgDataFromStringMapPtr(const StringMapPtr& smp, PICfgDataPtr& p);

	//////end_PICfgData

	//////begin_PIData
	static std::string getPBStrForPIData(const PIDataPtr& p);
	static bool parsePIDataFromPBStr(const std::string& s, PIDataPtr& p);

	static std::string getStrForPIData(const PIDataPtr& p);
	static std::string getJsonStrForPIData(const PIDataPtr& p);
	static bool parsePIDataFromJsonStr(const std::string& s, PIDataPtr& p);

	static std::string getCsvStrForPIData(const PIDataPtr& p, const std::string& sep = "|");
	static bool parsePIDataFromCsvStr(const std::string& s, PIDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPIData(const PIDataPtr& p, const std::string& sep = "|");
	static bool parsePIDataFromPlainCsvStr(const std::string& s, PIDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPIData(const PIDataPtr& p);
	static bool parsePIDataFromStringMapPtr(const StringMapPtr& smp, PIDataPtr& p);

	static void updatePIDataFromStringMapPtr(const StringMapPtr& smp, PIDataPtr& p);

	//////end_PIData

	//////begin_OrderMgrData
	static std::string getPBStrForOrderMgrData(const OrderMgrDataPtr& p);
	static bool parseOrderMgrDataFromPBStr(const std::string& s, OrderMgrDataPtr& p);

	static std::string getStrForOrderMgrData(const OrderMgrDataPtr& p);
	static std::string getJsonStrForOrderMgrData(const OrderMgrDataPtr& p);
	static bool parseOrderMgrDataFromJsonStr(const std::string& s, OrderMgrDataPtr& p);

	static std::string getCsvStrForOrderMgrData(const OrderMgrDataPtr& p, const std::string& sep = "|");
	static bool parseOrderMgrDataFromCsvStr(const std::string& s, OrderMgrDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrderMgrData(const OrderMgrDataPtr& p, const std::string& sep = "|");
	static bool parseOrderMgrDataFromPlainCsvStr(const std::string& s, OrderMgrDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrderMgrData(const OrderMgrDataPtr& p);
	static bool parseOrderMgrDataFromStringMapPtr(const StringMapPtr& smp, OrderMgrDataPtr& p);

	static void updateOrderMgrDataFromStringMapPtr(const StringMapPtr& smp, OrderMgrDataPtr& p);

	//////end_OrderMgrData

	//////begin_OrderMgrCfgData
	static std::string getPBStrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p);
	static bool parseOrderMgrCfgDataFromPBStr(const std::string& s, OrderMgrCfgDataPtr& p);

	static std::string getStrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p);
	static std::string getJsonStrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p);
	static bool parseOrderMgrCfgDataFromJsonStr(const std::string& s, OrderMgrCfgDataPtr& p);

	static std::string getCsvStrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOrderMgrCfgDataFromCsvStr(const std::string& s, OrderMgrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseOrderMgrCfgDataFromPlainCsvStr(const std::string& s, OrderMgrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrderMgrCfgData(const OrderMgrCfgDataPtr& p);
	static bool parseOrderMgrCfgDataFromStringMapPtr(const StringMapPtr& smp, OrderMgrCfgDataPtr& p);

	static void updateOrderMgrCfgDataFromStringMapPtr(const StringMapPtr& smp, OrderMgrCfgDataPtr& p);

	//////end_OrderMgrCfgData

	//////begin_ForQuoteMgrCfgData
	static std::string getPBStrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p);
	static bool parseForQuoteMgrCfgDataFromPBStr(const std::string& s, ForQuoteMgrCfgDataPtr& p);

	static std::string getStrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p);
	static std::string getJsonStrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p);
	static bool parseForQuoteMgrCfgDataFromJsonStr(const std::string& s, ForQuoteMgrCfgDataPtr& p);

	static std::string getCsvStrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseForQuoteMgrCfgDataFromCsvStr(const std::string& s, ForQuoteMgrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p, const std::string& sep = "|");
	static bool parseForQuoteMgrCfgDataFromPlainCsvStr(const std::string& s, ForQuoteMgrCfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForForQuoteMgrCfgData(const ForQuoteMgrCfgDataPtr& p);
	static bool parseForQuoteMgrCfgDataFromStringMapPtr(const StringMapPtr& smp, ForQuoteMgrCfgDataPtr& p);

	static void updateForQuoteMgrCfgDataFromStringMapPtr(const StringMapPtr& smp, ForQuoteMgrCfgDataPtr& p);

	//////end_ForQuoteMgrCfgData

	//////begin_CfgData
	static std::string getPBStrForCfgData(const CfgDataPtr& p);
	static bool parseCfgDataFromPBStr(const std::string& s, CfgDataPtr& p);

	static std::string getStrForCfgData(const CfgDataPtr& p);
	static std::string getJsonStrForCfgData(const CfgDataPtr& p);
	static bool parseCfgDataFromJsonStr(const std::string& s, CfgDataPtr& p);

	static std::string getCsvStrForCfgData(const CfgDataPtr& p, const std::string& sep = "|");
	static bool parseCfgDataFromCsvStr(const std::string& s, CfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForCfgData(const CfgDataPtr& p, const std::string& sep = "|");
	static bool parseCfgDataFromPlainCsvStr(const std::string& s, CfgDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForCfgData(const CfgDataPtr& p);
	static bool parseCfgDataFromStringMapPtr(const StringMapPtr& smp, CfgDataPtr& p);

	static void updateCfgDataFromStringMapPtr(const StringMapPtr& smp, CfgDataPtr& p);

	//////end_CfgData

	//////begin_ExchangeInfo
	static std::string getPBStrForExchangeInfo(const ExchangeInfoPtr& p);
	static bool parseExchangeInfoFromPBStr(const std::string& s, ExchangeInfoPtr& p);

	static std::string getStrForExchangeInfo(const ExchangeInfoPtr& p);
	static std::string getJsonStrForExchangeInfo(const ExchangeInfoPtr& p);
	static bool parseExchangeInfoFromJsonStr(const std::string& s, ExchangeInfoPtr& p);

	static std::string getCsvStrForExchangeInfo(const ExchangeInfoPtr& p, const std::string& sep = "|");
	static bool parseExchangeInfoFromCsvStr(const std::string& s, ExchangeInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForExchangeInfo(const ExchangeInfoPtr& p, const std::string& sep = "|");
	static bool parseExchangeInfoFromPlainCsvStr(const std::string& s, ExchangeInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForExchangeInfo(const ExchangeInfoPtr& p);
	static bool parseExchangeInfoFromStringMapPtr(const StringMapPtr& smp, ExchangeInfoPtr& p);

	static void updateExchangeInfoFromStringMapPtr(const StringMapPtr& smp, ExchangeInfoPtr& p);

	//////end_ExchangeInfo

	//////begin_FillInfo
	static std::string getPBStrForFillInfo(const FillInfoPtr& p);
	static bool parseFillInfoFromPBStr(const std::string& s, FillInfoPtr& p);

	static std::string getStrForFillInfo(const FillInfoPtr& p);
	static std::string getJsonStrForFillInfo(const FillInfoPtr& p);
	static bool parseFillInfoFromJsonStr(const std::string& s, FillInfoPtr& p);

	static std::string getCsvStrForFillInfo(const FillInfoPtr& p, const std::string& sep = "|");
	static bool parseFillInfoFromCsvStr(const std::string& s, FillInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForFillInfo(const FillInfoPtr& p, const std::string& sep = "|");
	static bool parseFillInfoFromPlainCsvStr(const std::string& s, FillInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForFillInfo(const FillInfoPtr& p);
	static bool parseFillInfoFromStringMapPtr(const StringMapPtr& smp, FillInfoPtr& p);

	static void updateFillInfoFromStringMapPtr(const StringMapPtr& smp, FillInfoPtr& p);

	//////end_FillInfo

	//////begin_FillStatData
	static std::string getPBStrForFillStatData(const FillStatDataPtr& p);
	static bool parseFillStatDataFromPBStr(const std::string& s, FillStatDataPtr& p);

	static std::string getStrForFillStatData(const FillStatDataPtr& p);
	static std::string getJsonStrForFillStatData(const FillStatDataPtr& p);
	static bool parseFillStatDataFromJsonStr(const std::string& s, FillStatDataPtr& p);

	static std::string getCsvStrForFillStatData(const FillStatDataPtr& p, const std::string& sep = "|");
	static bool parseFillStatDataFromCsvStr(const std::string& s, FillStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForFillStatData(const FillStatDataPtr& p, const std::string& sep = "|");
	static bool parseFillStatDataFromPlainCsvStr(const std::string& s, FillStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForFillStatData(const FillStatDataPtr& p);
	static bool parseFillStatDataFromStringMapPtr(const StringMapPtr& smp, FillStatDataPtr& p);

	static void updateFillStatDataFromStringMapPtr(const StringMapPtr& smp, FillStatDataPtr& p);

	//////end_FillStatData

	//////begin_RequestIdData
	static std::string getPBStrForRequestIdData(const RequestIdDataPtr& p);
	static bool parseRequestIdDataFromPBStr(const std::string& s, RequestIdDataPtr& p);

	static std::string getStrForRequestIdData(const RequestIdDataPtr& p);
	static std::string getJsonStrForRequestIdData(const RequestIdDataPtr& p);
	static bool parseRequestIdDataFromJsonStr(const std::string& s, RequestIdDataPtr& p);

	static std::string getCsvStrForRequestIdData(const RequestIdDataPtr& p, const std::string& sep = "|");
	static bool parseRequestIdDataFromCsvStr(const std::string& s, RequestIdDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForRequestIdData(const RequestIdDataPtr& p, const std::string& sep = "|");
	static bool parseRequestIdDataFromPlainCsvStr(const std::string& s, RequestIdDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForRequestIdData(const RequestIdDataPtr& p);
	static bool parseRequestIdDataFromStringMapPtr(const StringMapPtr& smp, RequestIdDataPtr& p);

	static void updateRequestIdDataFromStringMapPtr(const StringMapPtr& smp, RequestIdDataPtr& p);

	//////end_RequestIdData

	//////begin_OrderInfo
	static std::string getPBStrForOrderInfo(const OrderInfoPtr& p);
	static bool parseOrderInfoFromPBStr(const std::string& s, OrderInfoPtr& p);

	static std::string getStrForOrderInfo(const OrderInfoPtr& p);
	static std::string getJsonStrForOrderInfo(const OrderInfoPtr& p);
	static bool parseOrderInfoFromJsonStr(const std::string& s, OrderInfoPtr& p);

	static std::string getCsvStrForOrderInfo(const OrderInfoPtr& p, const std::string& sep = "|");
	static bool parseOrderInfoFromCsvStr(const std::string& s, OrderInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrderInfo(const OrderInfoPtr& p, const std::string& sep = "|");
	static bool parseOrderInfoFromPlainCsvStr(const std::string& s, OrderInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrderInfo(const OrderInfoPtr& p);
	static bool parseOrderInfoFromStringMapPtr(const StringMapPtr& smp, OrderInfoPtr& p);

	static void updateOrderInfoFromStringMapPtr(const StringMapPtr& smp, OrderInfoPtr& p);

	//////end_OrderInfo

	//////begin_QuoteInfo
	static std::string getPBStrForQuoteInfo(const QuoteInfoPtr& p);
	static bool parseQuoteInfoFromPBStr(const std::string& s, QuoteInfoPtr& p);

	static std::string getStrForQuoteInfo(const QuoteInfoPtr& p);
	static std::string getJsonStrForQuoteInfo(const QuoteInfoPtr& p);
	static bool parseQuoteInfoFromJsonStr(const std::string& s, QuoteInfoPtr& p);

	static std::string getCsvStrForQuoteInfo(const QuoteInfoPtr& p, const std::string& sep = "|");
	static bool parseQuoteInfoFromCsvStr(const std::string& s, QuoteInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForQuoteInfo(const QuoteInfoPtr& p, const std::string& sep = "|");
	static bool parseQuoteInfoFromPlainCsvStr(const std::string& s, QuoteInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForQuoteInfo(const QuoteInfoPtr& p);
	static bool parseQuoteInfoFromStringMapPtr(const StringMapPtr& smp, QuoteInfoPtr& p);

	static void updateQuoteInfoFromStringMapPtr(const StringMapPtr& smp, QuoteInfoPtr& p);

	//////end_QuoteInfo

	//////begin_MktDataEventInfo
	static std::string getPBStrForMktDataEventInfo(const MktDataEventInfoPtr& p);
	static bool parseMktDataEventInfoFromPBStr(const std::string& s, MktDataEventInfoPtr& p);

	static std::string getStrForMktDataEventInfo(const MktDataEventInfoPtr& p);
	static std::string getJsonStrForMktDataEventInfo(const MktDataEventInfoPtr& p);
	static bool parseMktDataEventInfoFromJsonStr(const std::string& s, MktDataEventInfoPtr& p);

	static std::string getCsvStrForMktDataEventInfo(const MktDataEventInfoPtr& p, const std::string& sep = "|");
	static bool parseMktDataEventInfoFromCsvStr(const std::string& s, MktDataEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForMktDataEventInfo(const MktDataEventInfoPtr& p, const std::string& sep = "|");
	static bool parseMktDataEventInfoFromPlainCsvStr(const std::string& s, MktDataEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForMktDataEventInfo(const MktDataEventInfoPtr& p);
	static bool parseMktDataEventInfoFromStringMapPtr(const StringMapPtr& smp, MktDataEventInfoPtr& p);

	static void updateMktDataEventInfoFromStringMapPtr(const StringMapPtr& smp, MktDataEventInfoPtr& p);

	//////end_MktDataEventInfo

	//////begin_OrderEventInfo
	static std::string getPBStrForOrderEventInfo(const OrderEventInfoPtr& p);
	static bool parseOrderEventInfoFromPBStr(const std::string& s, OrderEventInfoPtr& p);

	static std::string getStrForOrderEventInfo(const OrderEventInfoPtr& p);
	static std::string getJsonStrForOrderEventInfo(const OrderEventInfoPtr& p);
	static bool parseOrderEventInfoFromJsonStr(const std::string& s, OrderEventInfoPtr& p);

	static std::string getCsvStrForOrderEventInfo(const OrderEventInfoPtr& p, const std::string& sep = "|");
	static bool parseOrderEventInfoFromCsvStr(const std::string& s, OrderEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrderEventInfo(const OrderEventInfoPtr& p, const std::string& sep = "|");
	static bool parseOrderEventInfoFromPlainCsvStr(const std::string& s, OrderEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrderEventInfo(const OrderEventInfoPtr& p);
	static bool parseOrderEventInfoFromStringMapPtr(const StringMapPtr& smp, OrderEventInfoPtr& p);

	static void updateOrderEventInfoFromStringMapPtr(const StringMapPtr& smp, OrderEventInfoPtr& p);

	//////end_OrderEventInfo

	//////begin_InstrEventInfo
	static std::string getPBStrForInstrEventInfo(const InstrEventInfoPtr& p);
	static bool parseInstrEventInfoFromPBStr(const std::string& s, InstrEventInfoPtr& p);

	static std::string getStrForInstrEventInfo(const InstrEventInfoPtr& p);
	static std::string getJsonStrForInstrEventInfo(const InstrEventInfoPtr& p);
	static bool parseInstrEventInfoFromJsonStr(const std::string& s, InstrEventInfoPtr& p);

	static std::string getCsvStrForInstrEventInfo(const InstrEventInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrEventInfoFromCsvStr(const std::string& s, InstrEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrEventInfo(const InstrEventInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrEventInfoFromPlainCsvStr(const std::string& s, InstrEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrEventInfo(const InstrEventInfoPtr& p);
	static bool parseInstrEventInfoFromStringMapPtr(const StringMapPtr& smp, InstrEventInfoPtr& p);

	static void updateInstrEventInfoFromStringMapPtr(const StringMapPtr& smp, InstrEventInfoPtr& p);

	//////end_InstrEventInfo

	//////begin_ForQuoteInfo
	static std::string getPBStrForForQuoteInfo(const ForQuoteInfoPtr& p);
	static bool parseForQuoteInfoFromPBStr(const std::string& s, ForQuoteInfoPtr& p);

	static std::string getStrForForQuoteInfo(const ForQuoteInfoPtr& p);
	static std::string getJsonStrForForQuoteInfo(const ForQuoteInfoPtr& p);
	static bool parseForQuoteInfoFromJsonStr(const std::string& s, ForQuoteInfoPtr& p);

	static std::string getCsvStrForForQuoteInfo(const ForQuoteInfoPtr& p, const std::string& sep = "|");
	static bool parseForQuoteInfoFromCsvStr(const std::string& s, ForQuoteInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForForQuoteInfo(const ForQuoteInfoPtr& p, const std::string& sep = "|");
	static bool parseForQuoteInfoFromPlainCsvStr(const std::string& s, ForQuoteInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForForQuoteInfo(const ForQuoteInfoPtr& p);
	static bool parseForQuoteInfoFromStringMapPtr(const StringMapPtr& smp, ForQuoteInfoPtr& p);

	static void updateForQuoteInfoFromStringMapPtr(const StringMapPtr& smp, ForQuoteInfoPtr& p);

	//////end_ForQuoteInfo

	//////begin_VolumeAmount
	static std::string getPBStrForVolumeAmount(const VolumeAmountPtr& p);
	static bool parseVolumeAmountFromPBStr(const std::string& s, VolumeAmountPtr& p);

	static std::string getStrForVolumeAmount(const VolumeAmountPtr& p);
	static std::string getJsonStrForVolumeAmount(const VolumeAmountPtr& p);
	static bool parseVolumeAmountFromJsonStr(const std::string& s, VolumeAmountPtr& p);

	static std::string getCsvStrForVolumeAmount(const VolumeAmountPtr& p, const std::string& sep = "|");
	static bool parseVolumeAmountFromCsvStr(const std::string& s, VolumeAmountPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForVolumeAmount(const VolumeAmountPtr& p, const std::string& sep = "|");
	static bool parseVolumeAmountFromPlainCsvStr(const std::string& s, VolumeAmountPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForVolumeAmount(const VolumeAmountPtr& p);
	static bool parseVolumeAmountFromStringMapPtr(const StringMapPtr& smp, VolumeAmountPtr& p);

	static void updateVolumeAmountFromStringMapPtr(const StringMapPtr& smp, VolumeAmountPtr& p);

	//////end_VolumeAmount

	//////begin_PxVolume
	static std::string getPBStrForPxVolume(const PxVolumePtr& p);
	static bool parsePxVolumeFromPBStr(const std::string& s, PxVolumePtr& p);

	static std::string getStrForPxVolume(const PxVolumePtr& p);
	static std::string getJsonStrForPxVolume(const PxVolumePtr& p);
	static bool parsePxVolumeFromJsonStr(const std::string& s, PxVolumePtr& p);

	static std::string getCsvStrForPxVolume(const PxVolumePtr& p, const std::string& sep = "|");
	static bool parsePxVolumeFromCsvStr(const std::string& s, PxVolumePtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPxVolume(const PxVolumePtr& p, const std::string& sep = "|");
	static bool parsePxVolumeFromPlainCsvStr(const std::string& s, PxVolumePtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPxVolume(const PxVolumePtr& p);
	static bool parsePxVolumeFromStringMapPtr(const StringMapPtr& smp, PxVolumePtr& p);

	static void updatePxVolumeFromStringMapPtr(const StringMapPtr& smp, PxVolumePtr& p);

	//////end_PxVolume

	//////begin_IntPxHalfExposure
	static std::string getPBStrForIntPxHalfExposure(const IntPxHalfExposurePtr& p);
	static bool parseIntPxHalfExposureFromPBStr(const std::string& s, IntPxHalfExposurePtr& p);

	static std::string getStrForIntPxHalfExposure(const IntPxHalfExposurePtr& p);
	static std::string getJsonStrForIntPxHalfExposure(const IntPxHalfExposurePtr& p);
	static bool parseIntPxHalfExposureFromJsonStr(const std::string& s, IntPxHalfExposurePtr& p);

	static std::string getCsvStrForIntPxHalfExposure(const IntPxHalfExposurePtr& p, const std::string& sep = "|");
	static bool parseIntPxHalfExposureFromCsvStr(const std::string& s, IntPxHalfExposurePtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntPxHalfExposure(const IntPxHalfExposurePtr& p, const std::string& sep = "|");
	static bool parseIntPxHalfExposureFromPlainCsvStr(const std::string& s, IntPxHalfExposurePtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntPxHalfExposure(const IntPxHalfExposurePtr& p);
	static bool parseIntPxHalfExposureFromStringMapPtr(const StringMapPtr& smp, IntPxHalfExposurePtr& p);

	static void updateIntPxHalfExposureFromStringMapPtr(const StringMapPtr& smp, IntPxHalfExposurePtr& p);

	//////end_IntPxHalfExposure

	//////begin_IntPxInfo
	static std::string getPBStrForIntPxInfo(const IntPxInfoPtr& p);
	static bool parseIntPxInfoFromPBStr(const std::string& s, IntPxInfoPtr& p);

	static std::string getStrForIntPxInfo(const IntPxInfoPtr& p);
	static std::string getJsonStrForIntPxInfo(const IntPxInfoPtr& p);
	static bool parseIntPxInfoFromJsonStr(const std::string& s, IntPxInfoPtr& p);

	static std::string getCsvStrForIntPxInfo(const IntPxInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxInfoFromCsvStr(const std::string& s, IntPxInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntPxInfo(const IntPxInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxInfoFromPlainCsvStr(const std::string& s, IntPxInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntPxInfo(const IntPxInfoPtr& p);
	static bool parseIntPxInfoFromStringMapPtr(const StringMapPtr& smp, IntPxInfoPtr& p);

	static void updateIntPxInfoFromStringMapPtr(const StringMapPtr& smp, IntPxInfoPtr& p);

	//////end_IntPxInfo

	//////begin_IntPxMktInfo
	static std::string getPBStrForIntPxMktInfo(const IntPxMktInfoPtr& p);
	static bool parseIntPxMktInfoFromPBStr(const std::string& s, IntPxMktInfoPtr& p);

	static std::string getStrForIntPxMktInfo(const IntPxMktInfoPtr& p);
	static std::string getJsonStrForIntPxMktInfo(const IntPxMktInfoPtr& p);
	static bool parseIntPxMktInfoFromJsonStr(const std::string& s, IntPxMktInfoPtr& p);

	static std::string getCsvStrForIntPxMktInfo(const IntPxMktInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxMktInfoFromCsvStr(const std::string& s, IntPxMktInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntPxMktInfo(const IntPxMktInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxMktInfoFromPlainCsvStr(const std::string& s, IntPxMktInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntPxMktInfo(const IntPxMktInfoPtr& p);
	static bool parseIntPxMktInfoFromStringMapPtr(const StringMapPtr& smp, IntPxMktInfoPtr& p);

	static void updateIntPxMktInfoFromStringMapPtr(const StringMapPtr& smp, IntPxMktInfoPtr& p);

	//////end_IntPxMktInfo

	//////begin_IntPxOrderInfo
	static std::string getPBStrForIntPxOrderInfo(const IntPxOrderInfoPtr& p);
	static bool parseIntPxOrderInfoFromPBStr(const std::string& s, IntPxOrderInfoPtr& p);

	static std::string getStrForIntPxOrderInfo(const IntPxOrderInfoPtr& p);
	static std::string getJsonStrForIntPxOrderInfo(const IntPxOrderInfoPtr& p);
	static bool parseIntPxOrderInfoFromJsonStr(const std::string& s, IntPxOrderInfoPtr& p);

	static std::string getCsvStrForIntPxOrderInfo(const IntPxOrderInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxOrderInfoFromCsvStr(const std::string& s, IntPxOrderInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForIntPxOrderInfo(const IntPxOrderInfoPtr& p, const std::string& sep = "|");
	static bool parseIntPxOrderInfoFromPlainCsvStr(const std::string& s, IntPxOrderInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForIntPxOrderInfo(const IntPxOrderInfoPtr& p);
	static bool parseIntPxOrderInfoFromStringMapPtr(const StringMapPtr& smp, IntPxOrderInfoPtr& p);

	static void updateIntPxOrderInfoFromStringMapPtr(const StringMapPtr& smp, IntPxOrderInfoPtr& p);

	//////end_IntPxOrderInfo

	//////begin_HalfExposure
	static std::string getPBStrForHalfExposure(const HalfExposurePtr& p);
	static bool parseHalfExposureFromPBStr(const std::string& s, HalfExposurePtr& p);

	static std::string getStrForHalfExposure(const HalfExposurePtr& p);
	static std::string getJsonStrForHalfExposure(const HalfExposurePtr& p);
	static bool parseHalfExposureFromJsonStr(const std::string& s, HalfExposurePtr& p);

	static std::string getCsvStrForHalfExposure(const HalfExposurePtr& p, const std::string& sep = "|");
	static bool parseHalfExposureFromCsvStr(const std::string& s, HalfExposurePtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForHalfExposure(const HalfExposurePtr& p, const std::string& sep = "|");
	static bool parseHalfExposureFromPlainCsvStr(const std::string& s, HalfExposurePtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForHalfExposure(const HalfExposurePtr& p);
	static bool parseHalfExposureFromStringMapPtr(const StringMapPtr& smp, HalfExposurePtr& p);

	static void updateHalfExposureFromStringMapPtr(const StringMapPtr& smp, HalfExposurePtr& p);

	//////end_HalfExposure

	//////begin_MktQuoteData
	static std::string getPBStrForMktQuoteData(const MktQuoteDataPtr& p);
	static bool parseMktQuoteDataFromPBStr(const std::string& s, MktQuoteDataPtr& p);

	static std::string getStrForMktQuoteData(const MktQuoteDataPtr& p);
	static std::string getJsonStrForMktQuoteData(const MktQuoteDataPtr& p);
	static bool parseMktQuoteDataFromJsonStr(const std::string& s, MktQuoteDataPtr& p);

	static std::string getCsvStrForMktQuoteData(const MktQuoteDataPtr& p, const std::string& sep = "|");
	static bool parseMktQuoteDataFromCsvStr(const std::string& s, MktQuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForMktQuoteData(const MktQuoteDataPtr& p, const std::string& sep = "|");
	static bool parseMktQuoteDataFromPlainCsvStr(const std::string& s, MktQuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForMktQuoteData(const MktQuoteDataPtr& p);
	static bool parseMktQuoteDataFromStringMapPtr(const StringMapPtr& smp, MktQuoteDataPtr& p);

	static void updateMktQuoteDataFromStringMapPtr(const StringMapPtr& smp, MktQuoteDataPtr& p);

	//////end_MktQuoteData

	//////begin_GreeksData
	static std::string getPBStrForGreeksData(const GreeksDataPtr& p);
	static bool parseGreeksDataFromPBStr(const std::string& s, GreeksDataPtr& p);

	static std::string getStrForGreeksData(const GreeksDataPtr& p);
	static std::string getJsonStrForGreeksData(const GreeksDataPtr& p);
	static bool parseGreeksDataFromJsonStr(const std::string& s, GreeksDataPtr& p);

	static std::string getCsvStrForGreeksData(const GreeksDataPtr& p, const std::string& sep = "|");
	static bool parseGreeksDataFromCsvStr(const std::string& s, GreeksDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForGreeksData(const GreeksDataPtr& p, const std::string& sep = "|");
	static bool parseGreeksDataFromPlainCsvStr(const std::string& s, GreeksDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForGreeksData(const GreeksDataPtr& p);
	static bool parseGreeksDataFromStringMapPtr(const StringMapPtr& smp, GreeksDataPtr& p);

	static void updateGreeksDataFromStringMapPtr(const StringMapPtr& smp, GreeksDataPtr& p);

	//////end_GreeksData

	//////begin_PosData
	static std::string getPBStrForPosData(const PosDataPtr& p);
	static bool parsePosDataFromPBStr(const std::string& s, PosDataPtr& p);

	static std::string getStrForPosData(const PosDataPtr& p);
	static std::string getJsonStrForPosData(const PosDataPtr& p);
	static bool parsePosDataFromJsonStr(const std::string& s, PosDataPtr& p);

	static std::string getCsvStrForPosData(const PosDataPtr& p, const std::string& sep = "|");
	static bool parsePosDataFromCsvStr(const std::string& s, PosDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPosData(const PosDataPtr& p, const std::string& sep = "|");
	static bool parsePosDataFromPlainCsvStr(const std::string& s, PosDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPosData(const PosDataPtr& p);
	static bool parsePosDataFromStringMapPtr(const StringMapPtr& smp, PosDataPtr& p);

	static void updatePosDataFromStringMapPtr(const StringMapPtr& smp, PosDataPtr& p);

	//////end_PosData

	//////begin_PnLData
	static std::string getPBStrForPnLData(const PnLDataPtr& p);
	static bool parsePnLDataFromPBStr(const std::string& s, PnLDataPtr& p);

	static std::string getStrForPnLData(const PnLDataPtr& p);
	static std::string getJsonStrForPnLData(const PnLDataPtr& p);
	static bool parsePnLDataFromJsonStr(const std::string& s, PnLDataPtr& p);

	static std::string getCsvStrForPnLData(const PnLDataPtr& p, const std::string& sep = "|");
	static bool parsePnLDataFromCsvStr(const std::string& s, PnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPnLData(const PnLDataPtr& p, const std::string& sep = "|");
	static bool parsePnLDataFromPlainCsvStr(const std::string& s, PnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPnLData(const PnLDataPtr& p);
	static bool parsePnLDataFromStringMapPtr(const StringMapPtr& smp, PnLDataPtr& p);

	static void updatePnLDataFromStringMapPtr(const StringMapPtr& smp, PnLDataPtr& p);

	//////end_PnLData

	//////begin_PxPnLData
	static std::string getPBStrForPxPnLData(const PxPnLDataPtr& p);
	static bool parsePxPnLDataFromPBStr(const std::string& s, PxPnLDataPtr& p);

	static std::string getStrForPxPnLData(const PxPnLDataPtr& p);
	static std::string getJsonStrForPxPnLData(const PxPnLDataPtr& p);
	static bool parsePxPnLDataFromJsonStr(const std::string& s, PxPnLDataPtr& p);

	static std::string getCsvStrForPxPnLData(const PxPnLDataPtr& p, const std::string& sep = "|");
	static bool parsePxPnLDataFromCsvStr(const std::string& s, PxPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPxPnLData(const PxPnLDataPtr& p, const std::string& sep = "|");
	static bool parsePxPnLDataFromPlainCsvStr(const std::string& s, PxPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPxPnLData(const PxPnLDataPtr& p);
	static bool parsePxPnLDataFromStringMapPtr(const StringMapPtr& smp, PxPnLDataPtr& p);

	static void updatePxPnLDataFromStringMapPtr(const StringMapPtr& smp, PxPnLDataPtr& p);

	//////end_PxPnLData

	//////begin_RPnLData
	static std::string getPBStrForRPnLData(const RPnLDataPtr& p);
	static bool parseRPnLDataFromPBStr(const std::string& s, RPnLDataPtr& p);

	static std::string getStrForRPnLData(const RPnLDataPtr& p);
	static std::string getJsonStrForRPnLData(const RPnLDataPtr& p);
	static bool parseRPnLDataFromJsonStr(const std::string& s, RPnLDataPtr& p);

	static std::string getCsvStrForRPnLData(const RPnLDataPtr& p, const std::string& sep = "|");
	static bool parseRPnLDataFromCsvStr(const std::string& s, RPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForRPnLData(const RPnLDataPtr& p, const std::string& sep = "|");
	static bool parseRPnLDataFromPlainCsvStr(const std::string& s, RPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForRPnLData(const RPnLDataPtr& p);
	static bool parseRPnLDataFromStringMapPtr(const StringMapPtr& smp, RPnLDataPtr& p);

	static void updateRPnLDataFromStringMapPtr(const StringMapPtr& smp, RPnLDataPtr& p);

	//////end_RPnLData

	//////begin_UPnLData
	static std::string getPBStrForUPnLData(const UPnLDataPtr& p);
	static bool parseUPnLDataFromPBStr(const std::string& s, UPnLDataPtr& p);

	static std::string getStrForUPnLData(const UPnLDataPtr& p);
	static std::string getJsonStrForUPnLData(const UPnLDataPtr& p);
	static bool parseUPnLDataFromJsonStr(const std::string& s, UPnLDataPtr& p);

	static std::string getCsvStrForUPnLData(const UPnLDataPtr& p, const std::string& sep = "|");
	static bool parseUPnLDataFromCsvStr(const std::string& s, UPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForUPnLData(const UPnLDataPtr& p, const std::string& sep = "|");
	static bool parseUPnLDataFromPlainCsvStr(const std::string& s, UPnLDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForUPnLData(const UPnLDataPtr& p);
	static bool parseUPnLDataFromStringMapPtr(const StringMapPtr& smp, UPnLDataPtr& p);

	static void updateUPnLDataFromStringMapPtr(const StringMapPtr& smp, UPnLDataPtr& p);

	//////end_UPnLData

	//////begin_PosGreeksData
	static std::string getPBStrForPosGreeksData(const PosGreeksDataPtr& p);
	static bool parsePosGreeksDataFromPBStr(const std::string& s, PosGreeksDataPtr& p);

	static std::string getStrForPosGreeksData(const PosGreeksDataPtr& p);
	static std::string getJsonStrForPosGreeksData(const PosGreeksDataPtr& p);
	static bool parsePosGreeksDataFromJsonStr(const std::string& s, PosGreeksDataPtr& p);

	static std::string getCsvStrForPosGreeksData(const PosGreeksDataPtr& p, const std::string& sep = "|");
	static bool parsePosGreeksDataFromCsvStr(const std::string& s, PosGreeksDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPosGreeksData(const PosGreeksDataPtr& p, const std::string& sep = "|");
	static bool parsePosGreeksDataFromPlainCsvStr(const std::string& s, PosGreeksDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPosGreeksData(const PosGreeksDataPtr& p);
	static bool parsePosGreeksDataFromStringMapPtr(const StringMapPtr& smp, PosGreeksDataPtr& p);

	static void updatePosGreeksDataFromStringMapPtr(const StringMapPtr& smp, PosGreeksDataPtr& p);

	//////end_PosGreeksData

	//////begin_QuoteData
	static std::string getPBStrForQuoteData(const QuoteDataPtr& p);
	static bool parseQuoteDataFromPBStr(const std::string& s, QuoteDataPtr& p);

	static std::string getStrForQuoteData(const QuoteDataPtr& p);
	static std::string getJsonStrForQuoteData(const QuoteDataPtr& p);
	static bool parseQuoteDataFromJsonStr(const std::string& s, QuoteDataPtr& p);

	static std::string getCsvStrForQuoteData(const QuoteDataPtr& p, const std::string& sep = "|");
	static bool parseQuoteDataFromCsvStr(const std::string& s, QuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForQuoteData(const QuoteDataPtr& p, const std::string& sep = "|");
	static bool parseQuoteDataFromPlainCsvStr(const std::string& s, QuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForQuoteData(const QuoteDataPtr& p);
	static bool parseQuoteDataFromStringMapPtr(const StringMapPtr& smp, QuoteDataPtr& p);

	static void updateQuoteDataFromStringMapPtr(const StringMapPtr& smp, QuoteDataPtr& p);

	//////end_QuoteData

	//////begin_VolatilityData
	static std::string getPBStrForVolatilityData(const VolatilityDataPtr& p);
	static bool parseVolatilityDataFromPBStr(const std::string& s, VolatilityDataPtr& p);

	static std::string getStrForVolatilityData(const VolatilityDataPtr& p);
	static std::string getJsonStrForVolatilityData(const VolatilityDataPtr& p);
	static bool parseVolatilityDataFromJsonStr(const std::string& s, VolatilityDataPtr& p);

	static std::string getCsvStrForVolatilityData(const VolatilityDataPtr& p, const std::string& sep = "|");
	static bool parseVolatilityDataFromCsvStr(const std::string& s, VolatilityDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForVolatilityData(const VolatilityDataPtr& p, const std::string& sep = "|");
	static bool parseVolatilityDataFromPlainCsvStr(const std::string& s, VolatilityDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForVolatilityData(const VolatilityDataPtr& p);
	static bool parseVolatilityDataFromStringMapPtr(const StringMapPtr& smp, VolatilityDataPtr& p);

	static void updateVolatilityDataFromStringMapPtr(const StringMapPtr& smp, VolatilityDataPtr& p);

	//////end_VolatilityData

	//////begin_TaqStatData
	static std::string getPBStrForTaqStatData(const TaqStatDataPtr& p);
	static bool parseTaqStatDataFromPBStr(const std::string& s, TaqStatDataPtr& p);

	static std::string getStrForTaqStatData(const TaqStatDataPtr& p);
	static std::string getJsonStrForTaqStatData(const TaqStatDataPtr& p);
	static bool parseTaqStatDataFromJsonStr(const std::string& s, TaqStatDataPtr& p);

	static std::string getCsvStrForTaqStatData(const TaqStatDataPtr& p, const std::string& sep = "|");
	static bool parseTaqStatDataFromCsvStr(const std::string& s, TaqStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTaqStatData(const TaqStatDataPtr& p, const std::string& sep = "|");
	static bool parseTaqStatDataFromPlainCsvStr(const std::string& s, TaqStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTaqStatData(const TaqStatDataPtr& p);
	static bool parseTaqStatDataFromStringMapPtr(const StringMapPtr& smp, TaqStatDataPtr& p);

	static void updateTaqStatDataFromStringMapPtr(const StringMapPtr& smp, TaqStatDataPtr& p);

	//////end_TaqStatData

	//////begin_XpStatData
	static std::string getPBStrForXpStatData(const XpStatDataPtr& p);
	static bool parseXpStatDataFromPBStr(const std::string& s, XpStatDataPtr& p);

	static std::string getStrForXpStatData(const XpStatDataPtr& p);
	static std::string getJsonStrForXpStatData(const XpStatDataPtr& p);
	static bool parseXpStatDataFromJsonStr(const std::string& s, XpStatDataPtr& p);

	static std::string getCsvStrForXpStatData(const XpStatDataPtr& p, const std::string& sep = "|");
	static bool parseXpStatDataFromCsvStr(const std::string& s, XpStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForXpStatData(const XpStatDataPtr& p, const std::string& sep = "|");
	static bool parseXpStatDataFromPlainCsvStr(const std::string& s, XpStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForXpStatData(const XpStatDataPtr& p);
	static bool parseXpStatDataFromStringMapPtr(const StringMapPtr& smp, XpStatDataPtr& p);

	static void updateXpStatDataFromStringMapPtr(const StringMapPtr& smp, XpStatDataPtr& p);

	//////end_XpStatData

	//////begin_OrdersSzPair
	static std::string getPBStrForOrdersSzPair(const OrdersSzPairPtr& p);
	static bool parseOrdersSzPairFromPBStr(const std::string& s, OrdersSzPairPtr& p);

	static std::string getStrForOrdersSzPair(const OrdersSzPairPtr& p);
	static std::string getJsonStrForOrdersSzPair(const OrdersSzPairPtr& p);
	static bool parseOrdersSzPairFromJsonStr(const std::string& s, OrdersSzPairPtr& p);

	static std::string getCsvStrForOrdersSzPair(const OrdersSzPairPtr& p, const std::string& sep = "|");
	static bool parseOrdersSzPairFromCsvStr(const std::string& s, OrdersSzPairPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrdersSzPair(const OrdersSzPairPtr& p, const std::string& sep = "|");
	static bool parseOrdersSzPairFromPlainCsvStr(const std::string& s, OrdersSzPairPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrdersSzPair(const OrdersSzPairPtr& p);
	static bool parseOrdersSzPairFromStringMapPtr(const StringMapPtr& smp, OrdersSzPairPtr& p);

	static void updateOrdersSzPairFromStringMapPtr(const StringMapPtr& smp, OrdersSzPairPtr& p);

	//////end_OrdersSzPair

	//////begin_OrderStatData
	static std::string getPBStrForOrderStatData(const OrderStatDataPtr& p);
	static bool parseOrderStatDataFromPBStr(const std::string& s, OrderStatDataPtr& p);

	static std::string getStrForOrderStatData(const OrderStatDataPtr& p);
	static std::string getJsonStrForOrderStatData(const OrderStatDataPtr& p);
	static bool parseOrderStatDataFromJsonStr(const std::string& s, OrderStatDataPtr& p);

	static std::string getCsvStrForOrderStatData(const OrderStatDataPtr& p, const std::string& sep = "|");
	static bool parseOrderStatDataFromCsvStr(const std::string& s, OrderStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOrderStatData(const OrderStatDataPtr& p, const std::string& sep = "|");
	static bool parseOrderStatDataFromPlainCsvStr(const std::string& s, OrderStatDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOrderStatData(const OrderStatDataPtr& p);
	static bool parseOrderStatDataFromStringMapPtr(const StringMapPtr& smp, OrderStatDataPtr& p);

	static void updateOrderStatDataFromStringMapPtr(const StringMapPtr& smp, OrderStatDataPtr& p);

	//////end_OrderStatData

	//////begin_LadderPxData
	static std::string getPBStrForLadderPxData(const LadderPxDataPtr& p);
	static bool parseLadderPxDataFromPBStr(const std::string& s, LadderPxDataPtr& p);

	static std::string getStrForLadderPxData(const LadderPxDataPtr& p);
	static std::string getJsonStrForLadderPxData(const LadderPxDataPtr& p);
	static bool parseLadderPxDataFromJsonStr(const std::string& s, LadderPxDataPtr& p);

	static std::string getCsvStrForLadderPxData(const LadderPxDataPtr& p, const std::string& sep = "|");
	static bool parseLadderPxDataFromCsvStr(const std::string& s, LadderPxDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForLadderPxData(const LadderPxDataPtr& p, const std::string& sep = "|");
	static bool parseLadderPxDataFromPlainCsvStr(const std::string& s, LadderPxDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForLadderPxData(const LadderPxDataPtr& p);
	static bool parseLadderPxDataFromStringMapPtr(const StringMapPtr& smp, LadderPxDataPtr& p);

	static void updateLadderPxDataFromStringMapPtr(const StringMapPtr& smp, LadderPxDataPtr& p);

	//////end_LadderPxData

	//////begin_LadderBookData
	static std::string getPBStrForLadderBookData(const LadderBookDataPtr& p);
	static bool parseLadderBookDataFromPBStr(const std::string& s, LadderBookDataPtr& p);

	static std::string getStrForLadderBookData(const LadderBookDataPtr& p);
	static std::string getJsonStrForLadderBookData(const LadderBookDataPtr& p);
	static bool parseLadderBookDataFromJsonStr(const std::string& s, LadderBookDataPtr& p);

	static std::string getCsvStrForLadderBookData(const LadderBookDataPtr& p, const std::string& sep = "|");
	static bool parseLadderBookDataFromCsvStr(const std::string& s, LadderBookDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForLadderBookData(const LadderBookDataPtr& p, const std::string& sep = "|");
	static bool parseLadderBookDataFromPlainCsvStr(const std::string& s, LadderBookDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForLadderBookData(const LadderBookDataPtr& p);
	static bool parseLadderBookDataFromStringMapPtr(const StringMapPtr& smp, LadderBookDataPtr& p);

	static void updateLadderBookDataFromStringMapPtr(const StringMapPtr& smp, LadderBookDataPtr& p);

	//////end_LadderBookData

	//////begin_DayData
	static std::string getPBStrForDayData(const DayDataPtr& p);
	static bool parseDayDataFromPBStr(const std::string& s, DayDataPtr& p);

	static std::string getStrForDayData(const DayDataPtr& p);
	static std::string getJsonStrForDayData(const DayDataPtr& p);
	static bool parseDayDataFromJsonStr(const std::string& s, DayDataPtr& p);

	static std::string getCsvStrForDayData(const DayDataPtr& p, const std::string& sep = "|");
	static bool parseDayDataFromCsvStr(const std::string& s, DayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDayData(const DayDataPtr& p, const std::string& sep = "|");
	static bool parseDayDataFromPlainCsvStr(const std::string& s, DayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDayData(const DayDataPtr& p);
	static bool parseDayDataFromStringMapPtr(const StringMapPtr& smp, DayDataPtr& p);

	static void updateDayDataFromStringMapPtr(const StringMapPtr& smp, DayDataPtr& p);

	//////end_DayData

	//////begin_BarData
	static std::string getPBStrForBarData(const BarDataPtr& p);
	static bool parseBarDataFromPBStr(const std::string& s, BarDataPtr& p);

	static std::string getStrForBarData(const BarDataPtr& p);
	static std::string getJsonStrForBarData(const BarDataPtr& p);
	static bool parseBarDataFromJsonStr(const std::string& s, BarDataPtr& p);

	static std::string getCsvStrForBarData(const BarDataPtr& p, const std::string& sep = "|");
	static bool parseBarDataFromCsvStr(const std::string& s, BarDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForBarData(const BarDataPtr& p, const std::string& sep = "|");
	static bool parseBarDataFromPlainCsvStr(const std::string& s, BarDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForBarData(const BarDataPtr& p);
	static bool parseBarDataFromStringMapPtr(const StringMapPtr& smp, BarDataPtr& p);

	static void updateBarDataFromStringMapPtr(const StringMapPtr& smp, BarDataPtr& p);

	//////end_BarData

	//////begin_BarDataMap
	static std::string getPBStrForBarDataMap(const BarDataMapPtr& p);
	static bool parseBarDataMapFromPBStr(const std::string& s, BarDataMapPtr& p);

	static std::string getStrForBarDataMap(const BarDataMapPtr& p);
	static std::string getJsonStrForBarDataMap(const BarDataMapPtr& p);
	static bool parseBarDataMapFromJsonStr(const std::string& s, BarDataMapPtr& p);

	static std::string getCsvStrForBarDataMap(const BarDataMapPtr& p, const std::string& sep = "|");
	static bool parseBarDataMapFromCsvStr(const std::string& s, BarDataMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForBarDataMap(const BarDataMapPtr& p, const std::string& sep = "|");
	static bool parseBarDataMapFromPlainCsvStr(const std::string& s, BarDataMapPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForBarDataMap(const BarDataMapPtr& p);
	static bool parseBarDataMapFromStringMapPtr(const StringMapPtr& smp, BarDataMapPtr& p);

	static void updateBarDataMapFromStringMapPtr(const StringMapPtr& smp, BarDataMapPtr& p);

	//////end_BarDataMap

	//////begin_ProductInfo
	static std::string getPBStrForProductInfo(const ProductInfoPtr& p);
	static bool parseProductInfoFromPBStr(const std::string& s, ProductInfoPtr& p);

	static std::string getStrForProductInfo(const ProductInfoPtr& p);
	static std::string getJsonStrForProductInfo(const ProductInfoPtr& p);
	static bool parseProductInfoFromJsonStr(const std::string& s, ProductInfoPtr& p);

	static std::string getCsvStrForProductInfo(const ProductInfoPtr& p, const std::string& sep = "|");
	static bool parseProductInfoFromCsvStr(const std::string& s, ProductInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForProductInfo(const ProductInfoPtr& p, const std::string& sep = "|");
	static bool parseProductInfoFromPlainCsvStr(const std::string& s, ProductInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForProductInfo(const ProductInfoPtr& p);
	static bool parseProductInfoFromStringMapPtr(const StringMapPtr& smp, ProductInfoPtr& p);

	static void updateProductInfoFromStringMapPtr(const StringMapPtr& smp, ProductInfoPtr& p);

	//////end_ProductInfo

	//////begin_InstrumentInfo
	static std::string getPBStrForInstrumentInfo(const InstrumentInfoPtr& p);
	static bool parseInstrumentInfoFromPBStr(const std::string& s, InstrumentInfoPtr& p);

	static std::string getStrForInstrumentInfo(const InstrumentInfoPtr& p);
	static std::string getJsonStrForInstrumentInfo(const InstrumentInfoPtr& p);
	static bool parseInstrumentInfoFromJsonStr(const std::string& s, InstrumentInfoPtr& p);

	static std::string getCsvStrForInstrumentInfo(const InstrumentInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrumentInfoFromCsvStr(const std::string& s, InstrumentInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrumentInfo(const InstrumentInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrumentInfoFromPlainCsvStr(const std::string& s, InstrumentInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrumentInfo(const InstrumentInfoPtr& p);
	static bool parseInstrumentInfoFromStringMapPtr(const StringMapPtr& smp, InstrumentInfoPtr& p);

	static void updateInstrumentInfoFromStringMapPtr(const StringMapPtr& smp, InstrumentInfoPtr& p);

	//////end_InstrumentInfo

	//////begin_InstrumentEventInfo
	static std::string getPBStrForInstrumentEventInfo(const InstrumentEventInfoPtr& p);
	static bool parseInstrumentEventInfoFromPBStr(const std::string& s, InstrumentEventInfoPtr& p);

	static std::string getStrForInstrumentEventInfo(const InstrumentEventInfoPtr& p);
	static std::string getJsonStrForInstrumentEventInfo(const InstrumentEventInfoPtr& p);
	static bool parseInstrumentEventInfoFromJsonStr(const std::string& s, InstrumentEventInfoPtr& p);

	static std::string getCsvStrForInstrumentEventInfo(const InstrumentEventInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrumentEventInfoFromCsvStr(const std::string& s, InstrumentEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForInstrumentEventInfo(const InstrumentEventInfoPtr& p, const std::string& sep = "|");
	static bool parseInstrumentEventInfoFromPlainCsvStr(const std::string& s, InstrumentEventInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForInstrumentEventInfo(const InstrumentEventInfoPtr& p);
	static bool parseInstrumentEventInfoFromStringMapPtr(const StringMapPtr& smp, InstrumentEventInfoPtr& p);

	static void updateInstrumentEventInfoFromStringMapPtr(const StringMapPtr& smp, InstrumentEventInfoPtr& p);

	//////end_InstrumentEventInfo

	//////begin_TAParams
	static std::string getPBStrForTAParams(const TAParamsPtr& p);
	static bool parseTAParamsFromPBStr(const std::string& s, TAParamsPtr& p);

	static std::string getStrForTAParams(const TAParamsPtr& p);
	static std::string getJsonStrForTAParams(const TAParamsPtr& p);
	static bool parseTAParamsFromJsonStr(const std::string& s, TAParamsPtr& p);

	static std::string getCsvStrForTAParams(const TAParamsPtr& p, const std::string& sep = "|");
	static bool parseTAParamsFromCsvStr(const std::string& s, TAParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTAParams(const TAParamsPtr& p, const std::string& sep = "|");
	static bool parseTAParamsFromPlainCsvStr(const std::string& s, TAParamsPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTAParams(const TAParamsPtr& p);
	static bool parseTAParamsFromStringMapPtr(const StringMapPtr& smp, TAParamsPtr& p);

	static void updateTAParamsFromStringMapPtr(const StringMapPtr& smp, TAParamsPtr& p);

	//////end_TAParams

	//////begin_OHLCVData
	static std::string getPBStrForOHLCVData(const OHLCVDataPtr& p);
	static bool parseOHLCVDataFromPBStr(const std::string& s, OHLCVDataPtr& p);

	static std::string getStrForOHLCVData(const OHLCVDataPtr& p);
	static std::string getJsonStrForOHLCVData(const OHLCVDataPtr& p);
	static bool parseOHLCVDataFromJsonStr(const std::string& s, OHLCVDataPtr& p);

	static std::string getCsvStrForOHLCVData(const OHLCVDataPtr& p, const std::string& sep = "|");
	static bool parseOHLCVDataFromCsvStr(const std::string& s, OHLCVDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForOHLCVData(const OHLCVDataPtr& p, const std::string& sep = "|");
	static bool parseOHLCVDataFromPlainCsvStr(const std::string& s, OHLCVDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForOHLCVData(const OHLCVDataPtr& p);
	static bool parseOHLCVDataFromStringMapPtr(const StringMapPtr& smp, OHLCVDataPtr& p);

	static void updateOHLCVDataFromStringMapPtr(const StringMapPtr& smp, OHLCVDataPtr& p);

	//////end_OHLCVData

	//////begin_DateOHLCV
	static std::string getPBStrForDateOHLCV(const DateOHLCVPtr& p);
	static bool parseDateOHLCVFromPBStr(const std::string& s, DateOHLCVPtr& p);

	static std::string getStrForDateOHLCV(const DateOHLCVPtr& p);
	static std::string getJsonStrForDateOHLCV(const DateOHLCVPtr& p);
	static bool parseDateOHLCVFromJsonStr(const std::string& s, DateOHLCVPtr& p);

	static std::string getCsvStrForDateOHLCV(const DateOHLCVPtr& p, const std::string& sep = "|");
	static bool parseDateOHLCVFromCsvStr(const std::string& s, DateOHLCVPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDateOHLCV(const DateOHLCVPtr& p, const std::string& sep = "|");
	static bool parseDateOHLCVFromPlainCsvStr(const std::string& s, DateOHLCVPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDateOHLCV(const DateOHLCVPtr& p);
	static bool parseDateOHLCVFromStringMapPtr(const StringMapPtr& smp, DateOHLCVPtr& p);

	static void updateDateOHLCVFromStringMapPtr(const StringMapPtr& smp, DateOHLCVPtr& p);

	//////end_DateOHLCV

	//////begin_DateTimeOHLCV
	static std::string getPBStrForDateTimeOHLCV(const DateTimeOHLCVPtr& p);
	static bool parseDateTimeOHLCVFromPBStr(const std::string& s, DateTimeOHLCVPtr& p);

	static std::string getStrForDateTimeOHLCV(const DateTimeOHLCVPtr& p);
	static std::string getJsonStrForDateTimeOHLCV(const DateTimeOHLCVPtr& p);
	static bool parseDateTimeOHLCVFromJsonStr(const std::string& s, DateTimeOHLCVPtr& p);

	static std::string getCsvStrForDateTimeOHLCV(const DateTimeOHLCVPtr& p, const std::string& sep = "|");
	static bool parseDateTimeOHLCVFromCsvStr(const std::string& s, DateTimeOHLCVPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForDateTimeOHLCV(const DateTimeOHLCVPtr& p, const std::string& sep = "|");
	static bool parseDateTimeOHLCVFromPlainCsvStr(const std::string& s, DateTimeOHLCVPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForDateTimeOHLCV(const DateTimeOHLCVPtr& p);
	static bool parseDateTimeOHLCVFromStringMapPtr(const StringMapPtr& smp, DateTimeOHLCVPtr& p);

	static void updateDateTimeOHLCVFromStringMapPtr(const StringMapPtr& smp, DateTimeOHLCVPtr& p);

	//////end_DateTimeOHLCV

	//////begin_TDXDayData
	static std::string getPBStrForTDXDayData(const TDXDayDataPtr& p);
	static bool parseTDXDayDataFromPBStr(const std::string& s, TDXDayDataPtr& p);

	static std::string getStrForTDXDayData(const TDXDayDataPtr& p);
	static std::string getJsonStrForTDXDayData(const TDXDayDataPtr& p);
	static bool parseTDXDayDataFromJsonStr(const std::string& s, TDXDayDataPtr& p);

	static std::string getCsvStrForTDXDayData(const TDXDayDataPtr& p, const std::string& sep = "|");
	static bool parseTDXDayDataFromCsvStr(const std::string& s, TDXDayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTDXDayData(const TDXDayDataPtr& p, const std::string& sep = "|");
	static bool parseTDXDayDataFromPlainCsvStr(const std::string& s, TDXDayDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTDXDayData(const TDXDayDataPtr& p);
	static bool parseTDXDayDataFromStringMapPtr(const StringMapPtr& smp, TDXDayDataPtr& p);

	static void updateTDXDayDataFromStringMapPtr(const StringMapPtr& smp, TDXDayDataPtr& p);

	//////end_TDXDayData

	//////begin_TDXMinData
	static std::string getPBStrForTDXMinData(const TDXMinDataPtr& p);
	static bool parseTDXMinDataFromPBStr(const std::string& s, TDXMinDataPtr& p);

	static std::string getStrForTDXMinData(const TDXMinDataPtr& p);
	static std::string getJsonStrForTDXMinData(const TDXMinDataPtr& p);
	static bool parseTDXMinDataFromJsonStr(const std::string& s, TDXMinDataPtr& p);

	static std::string getCsvStrForTDXMinData(const TDXMinDataPtr& p, const std::string& sep = "|");
	static bool parseTDXMinDataFromCsvStr(const std::string& s, TDXMinDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForTDXMinData(const TDXMinDataPtr& p, const std::string& sep = "|");
	static bool parseTDXMinDataFromPlainCsvStr(const std::string& s, TDXMinDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForTDXMinData(const TDXMinDataPtr& p);
	static bool parseTDXMinDataFromStringMapPtr(const StringMapPtr& smp, TDXMinDataPtr& p);

	static void updateTDXMinDataFromStringMapPtr(const StringMapPtr& smp, TDXMinDataPtr& p);

	//////end_TDXMinData

	//////begin_KCBPTagQuoteInfo10
	static std::string getPBStrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p);
	static bool parseKCBPTagQuoteInfo10FromPBStr(const std::string& s, KCBPTagQuoteInfo10Ptr& p);

	static std::string getStrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p);
	static std::string getJsonStrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p);
	static bool parseKCBPTagQuoteInfo10FromJsonStr(const std::string& s, KCBPTagQuoteInfo10Ptr& p);

	static std::string getCsvStrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p, const std::string& sep = "|");
	static bool parseKCBPTagQuoteInfo10FromCsvStr(const std::string& s, KCBPTagQuoteInfo10Ptr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p, const std::string& sep = "|");
	static bool parseKCBPTagQuoteInfo10FromPlainCsvStr(const std::string& s, KCBPTagQuoteInfo10Ptr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForKCBPTagQuoteInfo10(const KCBPTagQuoteInfo10Ptr& p);
	static bool parseKCBPTagQuoteInfo10FromStringMapPtr(const StringMapPtr& smp, KCBPTagQuoteInfo10Ptr& p);

	static void updateKCBPTagQuoteInfo10FromStringMapPtr(const StringMapPtr& smp, KCBPTagQuoteInfo10Ptr& p);

	//////end_KCBPTagQuoteInfo10

	//////begin_KCBPTagQuoteInfo5
	static std::string getPBStrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p);
	static bool parseKCBPTagQuoteInfo5FromPBStr(const std::string& s, KCBPTagQuoteInfo5Ptr& p);

	static std::string getStrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p);
	static std::string getJsonStrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p);
	static bool parseKCBPTagQuoteInfo5FromJsonStr(const std::string& s, KCBPTagQuoteInfo5Ptr& p);

	static std::string getCsvStrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p, const std::string& sep = "|");
	static bool parseKCBPTagQuoteInfo5FromCsvStr(const std::string& s, KCBPTagQuoteInfo5Ptr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p, const std::string& sep = "|");
	static bool parseKCBPTagQuoteInfo5FromPlainCsvStr(const std::string& s, KCBPTagQuoteInfo5Ptr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForKCBPTagQuoteInfo5(const KCBPTagQuoteInfo5Ptr& p);
	static bool parseKCBPTagQuoteInfo5FromStringMapPtr(const StringMapPtr& smp, KCBPTagQuoteInfo5Ptr& p);

	static void updateKCBPTagQuoteInfo5FromStringMapPtr(const StringMapPtr& smp, KCBPTagQuoteInfo5Ptr& p);

	//////end_KCBPTagQuoteInfo5

	//////begin_SinaQuoteData
	static std::string getPBStrForSinaQuoteData(const SinaQuoteDataPtr& p);
	static bool parseSinaQuoteDataFromPBStr(const std::string& s, SinaQuoteDataPtr& p);

	static std::string getStrForSinaQuoteData(const SinaQuoteDataPtr& p);
	static std::string getJsonStrForSinaQuoteData(const SinaQuoteDataPtr& p);
	static bool parseSinaQuoteDataFromJsonStr(const std::string& s, SinaQuoteDataPtr& p);

	static std::string getCsvStrForSinaQuoteData(const SinaQuoteDataPtr& p, const std::string& sep = "|");
	static bool parseSinaQuoteDataFromCsvStr(const std::string& s, SinaQuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForSinaQuoteData(const SinaQuoteDataPtr& p, const std::string& sep = "|");
	static bool parseSinaQuoteDataFromPlainCsvStr(const std::string& s, SinaQuoteDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForSinaQuoteData(const SinaQuoteDataPtr& p);
	static bool parseSinaQuoteDataFromStringMapPtr(const StringMapPtr& smp, SinaQuoteDataPtr& p);

	static void updateSinaQuoteDataFromStringMapPtr(const StringMapPtr& smp, SinaQuoteDataPtr& p);

	//////end_SinaQuoteData

	//////begin_PyAT_OrderExecutionInfo
	static std::string getPBStrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p);
	static bool parsePyAT_OrderExecutionInfoFromPBStr(const std::string& s, PyAT_OrderExecutionInfoPtr& p);

	static std::string getStrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p);
	static std::string getJsonStrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p);
	static bool parsePyAT_OrderExecutionInfoFromJsonStr(const std::string& s, PyAT_OrderExecutionInfoPtr& p);

	static std::string getCsvStrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p, const std::string& sep = "|");
	static bool parsePyAT_OrderExecutionInfoFromCsvStr(const std::string& s, PyAT_OrderExecutionInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p, const std::string& sep = "|");
	static bool parsePyAT_OrderExecutionInfoFromPlainCsvStr(const std::string& s, PyAT_OrderExecutionInfoPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPyAT_OrderExecutionInfo(const PyAT_OrderExecutionInfoPtr& p);
	static bool parsePyAT_OrderExecutionInfoFromStringMapPtr(const StringMapPtr& smp, PyAT_OrderExecutionInfoPtr& p);

	static void updatePyAT_OrderExecutionInfoFromStringMapPtr(const StringMapPtr& smp, PyAT_OrderExecutionInfoPtr& p);

	//////end_PyAT_OrderExecutionInfo

	//////begin_PyAT_OrderData
	static std::string getPBStrForPyAT_OrderData(const PyAT_OrderDataPtr& p);
	static bool parsePyAT_OrderDataFromPBStr(const std::string& s, PyAT_OrderDataPtr& p);

	static std::string getStrForPyAT_OrderData(const PyAT_OrderDataPtr& p);
	static std::string getJsonStrForPyAT_OrderData(const PyAT_OrderDataPtr& p);
	static bool parsePyAT_OrderDataFromJsonStr(const std::string& s, PyAT_OrderDataPtr& p);

	static std::string getCsvStrForPyAT_OrderData(const PyAT_OrderDataPtr& p, const std::string& sep = "|");
	static bool parsePyAT_OrderDataFromCsvStr(const std::string& s, PyAT_OrderDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static std::string getPlainCsvStrForPyAT_OrderData(const PyAT_OrderDataPtr& p, const std::string& sep = "|");
	static bool parsePyAT_OrderDataFromPlainCsvStr(const std::string& s, PyAT_OrderDataPtr&p, const std::string& sep = "|", int skipcols = 0);

	static StringMapPtr getStringMapPtrForPyAT_OrderData(const PyAT_OrderDataPtr& p);
	static bool parsePyAT_OrderDataFromStringMapPtr(const StringMapPtr& smp, PyAT_OrderDataPtr& p);

	static void updatePyAT_OrderDataFromStringMapPtr(const StringMapPtr& smp, PyAT_OrderDataPtr& p);

	//////end_PyAT_OrderData










};


}//namespace 


#endif