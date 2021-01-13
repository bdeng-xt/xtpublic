#pragma once
#ifndef XT_INSTR_UTIL_H
#define XT_INSTR_UTIL_H


/**
* \file InstrUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for instrument utility.
*
* \description
*	Designed for utility functions of an instrument.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <boost/unordered_set.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/sliced.hpp>

//#include <boost/regex.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include "XTConfig.h"
#include "SettingsMgr.h"
#include "XTData.pb.h"
#include "Util.h"
#include "XTUtil.h"
 
#include "Instr.h"
#include "InstrMgr.h"

#include <HttpUtil.h>
#include "WebMgr.h"

#include "PBUtil.h"
#include "StringUtil.h"

#include <json/json.h> //use jsoncpp1.8.3

namespace XT
{

class XT_COMMON_API InstrUtil
{

protected:
	static std::string m_EmptyString; ///< empty string
	
public:
	InstrUtil() {}
	InstrUtil(const InstrUtil& from) {} // = delete;
	InstrUtil& operator=(const InstrUtil& from) { return *this; } // = delete;
	virtual ~InstrUtil() {}


public:
	static std::vector<std::string> getMktDataTypeNames();

	static std::vector<std::string> getInstrDataTypeNames();

	static std::vector<std::string> getTradeDataTypeNames();

public:
	/**
	* @brief update MktQuoteDataPtr on mkt data string
	*
	* @param mktquote
	* @param line
	* @param datatype
	*/
	static void updateMktQuoteDataOnMktDataStr(MktQuoteDataPtr& mktquote, const std::string& line, const std::string& datatype);

	/**
	* @brief update instrument book on mkt data string
	* @param line
	* @param datatype
	*/
	static void updateInstrOnMktDataStr(const std::string& line, const std::string& datatype);

	/**
	* @brief update instrument on mkt data file
	* @param filename
	* @param datatype
	*/
	static void updateInstrOnMktDataFile(const std::string& filename, const std::string& datatype);

protected:

	static void updateMktQuoteDataOnMktDataCTPCsvStr(MktQuoteDataPtr& mktquote, const std::string& line);
	static void updateInstrOnMktDataCTPCsvStr(const std::string& line);

	static void updateMktQuoteDataOnMktDataDERIBITCsvStr(MktQuoteDataPtr& mktquote, const std::string& line);
	static void updateInstrOnMktDataDERIBITCsvStr(const std::string& line);

	static void updateMktQuoteDataOnMktDataHSCsvStr(MktQuoteDataPtr& mktquote, const std::string& line);
	static void updateInstrOnMktDataHSCsvStr(const std::string& line);


public:
	/**
	* @brief update instrument on trade data string
	* @param line
	* @param datatype
	*/
	static void updateInstrOnTradeDataStr(const std::string& line, const std::string& datatype);

public:
	/**
	* @brief handle   Instrument   file
	*/
	static void handleInstrFile(const std::string& filename, const StringMapPtr& smp);

	/**
	* @brief handle instrument spec string
	*/
	static void handleInstrStr(const std::string& s, const std::string& datatype);



public:

	/** 
	* @name Util Functions
	*  utility functions
	*/
	///@{



	///**
	//* @brief get timestamp from date string and time string
	//*
	//* @param date as date string
	//* @param time as time string
	//*
	//* @return timestamp
	//*/
	//static int64_t getTsFromDateAndTimeStr(const std::string& date, const std::string& time);


	///@}	

	/**
	* @brief handle CTP InstrumentField jsont string
	*/
	static void handleCTPInstrJsonStr(const std::string& s);

	/**
	* @brief handle CTP InstrumentField csv data vector
	*/
	static void handleCTPInstrDataVector(const std::vector<std::string>& datavector, std::vector<std::string>& headervector);

	/**
	* @brief handle CTP InstrumentField csv data string
	*/
	static void handleCTPInstrDataCsvStr(const std::string& datastr, const std::string& headerstr, const std::string& sep=",");

	/**
	* @brief handle CTP Instrument json file
	*/
	static void handleCTPInstrJsonFile(const std::string& filename);


	/**
	* @brief handle CTP Instrument json file
	*/
	static void handleCTPInstrCsvFile(const std::string& filename);



protected:
	static void handleHSInstrRefFile(const std::string& filename);

	static void handleHSInstrXmlFile(const std::string& filename);


public:

	/** 
	* @name Update Functions
	*  updating instrument on callbacks
	*/
	///@{

	
	/**
	* @brief update instrument on snapshot data
	*
	* @param instr
	* @param ts as timestamp
	* @param lastPx as last price
	* @param totVolume as total volume
	* @param totBuyVolume as total buy volume
	* @param totSellVolume as total sell volume
	*/
	static void updateInstrOnSnapshotData(InstrPtr& instr, int64_t ts, double lastPx, int64_t totVolume, int64_t totBuyVolume, int64_t totSellVolume);

	/**
	* @brief update instrument on snapshot data
	*
	* @param instr
	* @param ts as timestamp
	* @param openprice
	* @param highpx as high price
	* @param lowpx as low price
	* @param closeprice
	* @param volume
	* @param oichg as open interest change
	* @param bsvoldiff as buy sell volume difference
	* @param turnover
	* @param bstdiff as buy sell turnover difference
	* @param flipups as flip ups
	* @param flipdns as flip downs
	*/
	static void updateInstrOnBarData(InstrPtr& instr, int64_t ts,
		double openprice, double highpx, double lowpx, double closeprice, 
		int64_t volume,int64_t oichg, int64_t bsvoldiff,
		double turnover, double bstdiff, double flipups,double flipdns
		);

 

	///@}	

	///**
	//* @name Update Functions for ctp data
	//*/
	/////@{

	///**
	//* @brief update instrument on ctp level1 data
	//*/
	//static void updateInstrOnCTPLevel1Data(InstrPtr& instr,
	//	int TradingDay, const std::string& InstrID, const std::string& ExchID, const std::string& ExchangeInstID,
	//	double LastPrice, double PreSettlementPrice, double PreClosePrice, double PreOpenInterest,
	//	double OpenPrice, double HighestPrice, double LowestPrice, int Volume, double Turnover, double OpenInterest,
	//	double ClosePrice, double SettlementPrice, double UpperLimitPrice, double LowerLimitPrice,
	//	double PreDelta, double CurrDelta, const std::string& UpdateTime, int UpdateMillisec,
	//	double BidPrice1, int BidVolume1, double AskPrice1, int AskVolume1,
	//	double AveragePrice,
	//	int ActionDay
	//);

	///@}

	/** 
	* @name Update Functions for sina
	*  updating instrument on sina quote data
	*/
	///@{

	/**
	* @brief update instrument on sina market quote string
	*
	* @param s as sina market quote string
	*/
	static void updateInstrOnSinaMktQuoteStr(const std::string& s);

	/**
	* @brief get sina quote data string for instrid
	*
	* @param instrid as instrid
	*
	* @return SinaQuoteData
	*/
	static SinaQuoteData getSinaQuoteDataForInstrID(const std::string& instrid);

	/**
	* @brief convert sina quote data string to SinaQuoteData
	*
	* @param line as sina quote data string
	* @param d as SinaQuoteData
	*/
	static bool toSinaQuoteDataFromLineStr(const std::string& line, XT::SinaQuoteData& d);

	/**
	* @brief add instrument on SinaQuoteData
	*
	* @param d as SinaQuoteData
	*/
	static void addInstrOnSinaQuoteData(const XT::SinaQuoteData& d);

	/**
	* @brief update instrument on SinaQuoteData
	*
	* @param d as SinaQuoteData
	*/
	static void updateInstrOnSinaQuoteData(const XT::SinaQuoteData& d);

	///**
	//* @brief update instrument on sina snapshot data
	//*
	//* @param instr as instrument
	//* @param date as date string
	//* @param time as time string
	//* @param dvolume as double volume
	//* @param turnover
	//* @param now as last price
	//* @param open
	//* @param high
	//* @param low
	//* @param close
	//* @param ask1
	//* @param ask1_volume
	//* @param ask2
	//* @param ask2_volume
	//* @param ask3
	//* @param ask3_volume
	//* @param ask4
	//* @param ask4_volume
	//* @param ask5
	//* @param ask5_volume
	//* @param bid1
	//* @param bid1_volume
	//* @param bid2
	//* @param bid2_volume
	//* @param bid3
	//* @param bid3_volume
	//* @param bid4
	//* @param bid4_volume
	//* @param bid5
	//* @param bid5_volume
	//*/
	//static void updateInstrOnSinaSnapshotData(InstrPtr& instr, const std::string& date, const std::string& time, double dvolume, double turnover, double now, 
	//	double open, double high, double low, double close,
	//	double ask1, int ask1_volume,double ask2, int ask2_volume, double ask3, int ask3_volume, double ask4, int ask4_volume, double ask5, int ask5_volume,
	//	double bid1, int bid1_volume,double bid2, int bid2_volume, double bid3, int bid3_volume, double bid4, int bid4_volume, double bid5, int bid5_volume );


	///@}	


	/**
	* @name Update Functions for PyAlgoTrade
	*/
	///@{

	/**
	* @brief add oid pyoid pair
	*
	* @param oid as xt order id
	* @param pyoid as pyat order id
	*
	*/
	static void addOidPyOid(int oid, int pyoid);

	/**
	* @brief get oid by pyoid
	*
	* @param pyoid as pyat order id
	*
	* @return oid as xt order id
	*/
	static int getOidByPyOid(int pyoid);

	/**
	* @brief get pyoid by oid
	*
	* @param oid as order id
	*
	* @return pyoid as pyat order id
	*/
	static int getPyOidByOid(int oid);
 
	/**
	* @brief update instr on PyAT_OrderData
	*
	* @param instr as instrument
	* @param d as PyAT_OrderData
	*/
	static void updateInstrOnPyATOrderData(InstrPtr& instr, const PyAT_OrderData & d);


	protected:
		static boost::unordered_map<int, int> m_oidToPyOidMap; ///< map for xt oid to pyoid 
		static boost::unordered_map<int, int> m_pyoidToOidMap;///< map for pyoid to xtoid


	///@}

};//class 

}//namespace

#endif
