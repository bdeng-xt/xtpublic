#pragma once
#ifndef XT_INSTRUMENT_H
#define XT_INSTRUMENT_H

#include <cstdint>
#include <set>

//#include <unordered_map>
#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/array.hpp>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "SettingsMgr.h"

#include "InstrSpec.h"

#include "MktTradeAndQuote.h"
#include "OrderTracker.h"

#include "LadderBook.h"

#include "FillTracker.h"




namespace XT {
	class Instr;


	//////typedef for Instr
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Instr> InstrPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Instr> InstrPtr;
//	typedef sf::contfree_safe_ptr<Instr> InstrPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Instr> InstrPtr;

#else

	typedef ::boost::shared_ptr<Instr> InstrPtr;
#endif


	typedef ::sf::safe_ptr<Instr> InstrSafePtr;

	typedef sf::contfree_safe_ptr<Instr> InstrContFreePtr;
	//////end typedef for Instr

class XT_COMMON_API Instr
{

public:

	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	Instr();

	/**
	* @brief default copy constructor
	*/
	Instr(const Instr& from);// = default;

	/**
	* @brief default copy assignment
	*/
	Instr& operator=(const Instr& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~Instr();

	/**
	* @brief initialization
	*
	* @param s as InstrSpec
	* @param booklevels as book levels
	*/
	void init(InstrSpecPtr& s, int booklevels);

	/**
	* @brief initialize with string parameters
	*
	* @param string parameters
	*/
	void updateStrParams(const StringMapPtr& smp);

	/**
	* @brief is initialized or not
	*
	* @return if oc is initialized
	*/
	bool isInitialized();


	///@}


	/**
	* @brief get iid
	*
	* @return iid
	*/
	int getIid();

	/**
	* @brief set iid
	*
	* @param v as iid
	*/
	void setIid(int v);


	/**
	* @name specifications
	*/
	///@{

	/**
	* @brief get InstrSpecsPtr
	*
	* @return   specifications  
	*/
	InstrSpecPtr& spec();

 

	/**
	* @brief get exchid
	*
	* @return exchid
	*/
	const std::string& getExchID();
	/**
	* @brief set exchid
	*
	* @param s as exchid
	*/
	void setExchID(const std::string& s);

	/**
	* @brief get localexchid
	*
	* @return localexchid
	*/
	const std::string& getLocalExchID();
	/**
	* @brief set localexchid
	*
	* @param s as localexchid
	*/
	void setLocalExchID(const std::string& s);

	/**
	* @brief get instrid
	*
	* @return instrid
	*/
	const std::string& getInstrID();
	/**
	* @brief set instrid
	*
	* @param s as instrid
	*/
	void setInstrID(const std::string& s);

	/**
	* @brief get local instrid
	*
	* @return local instrid
	*/
	const std::string& getLocalInstrID();
	/**
	* @brief set instrid
	*
	* @param s as instrid
	*/
	void setLocalInstrID(const std::string& s);

	/**
	* @brief get productid
	*
	* @return productid
	*/
	const std::string& getProductID();
	/**
	* @brief set productid
	*
	* @param s as productid
	*/
	void setProductID(const std::string& s);

	/**
	* @brief get local instrid
	*
	* @return local instrid
	*/
	const std::string& getLocalProductID();
	/**
	* @brief set local productid
	*
	* @param s as local productid
	*/
	void setLocalProductID(const std::string& s);

	/**
	* @brief get securitytypestr
	*
	* @return securitytypestr
	*/
	const std::string& getSecurityTypeStr();
	/**
	* @brief set securitytype string
	*
	* @param s as securitytypestr
	*/
	void setSecurityTypeStr(const std::string& s);


	/**
	* @brief get securitytypeint
	*
	* @return securitytypeint
	*/
	int getSecurityTypeInt();
	/**
	* @brief set securitytypeint
	*
	* @param s as securitytypeint
	*/
	void setSecurityTypeInt(int v);

	/**
	* @brief get securitytype
	*
	* @return securitytype
	*/
	SecurityType::enumtype getSecurityType();
	/**
	* @brief set securitytype 
	*
	* @param s as securitytype
	*/
	void setSecurityType(SecurityType::enumtype sectype);

	///@}


	/**
	* @name CfgData
	*/
	///@{

	/**
	* @brief get cfgData
	*
	* @return   cfgData
	*/
	InstrCfgDataPtr& cfgData();

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	StringMapPtr& strParams();

 

	/**
	* @brief get cfg double value
	*
	* @param tag
	*
	* @return tag cfg double value
	*/
	const std::string& getNameCfgStrValue(const std::string& name);

	/**
	* @brief set cfg string value
	*
	* @param tag
	* @param v as cfg string value
	*
	*/
	void setNameCfgStrValue(const std::string& name, const std::string& v);

 
 

	///@}

	/**
	* @name Data
	*/
	///@{

	/**
	* @brief get instrData ptr
	*
	* @return   instrData ptr
	*/
	InstrDataPtr& data();

	/**
	* @brief get time to expiration in years
	*
	* @return time to expiration in years
	*/
	double getT();

	/**
	* @brief get time to expiration in days
	*
	* @return time to expiration in days
	*/
	double getDTE();

	/**
	* @brief get trading time to expiration in years
	*
	* @return trading time to expiration in years
	*/
	double getTTE();

 

	/**
	* @brief get double value
	*
	* @param tag
	* 
	* @return tag double value
	*/
	double getTagDoubleValue(int tag);

	/**
	* @brief set double value
	*
	* @param tag
	* @param v as double value
	*
	*/
	void setTagDoubleValue(int tag, double v);

	/**
	* @brief get int value
	*
	* @param tag
	*
	* @return tag int value
	*/
	double getTagIntValue(int tag);


	/**
	* @brief set int value
	*
	* @param tag
	* @param v as int value
	*
	*/
	void setTagIntValue(int tag, int v);

	///@}

	/**
	* @name GreeksData
	*/
	///@{

	/**
	* @brief get greeksData ptr
	*
	* @return   greeksData ptr
	*/
	GreeksDataPtr& greeksData();

 
	
	///@}

	/**
	* @name PosGreeksData
	*/
	///@{

	/**
	* @brief get posGreeksData ptr
	*
	* @return   posGreeksData ptr
	*/
	PosGreeksDataPtr& posGreeksData();

 
	///@}

	/**
	* @name QuoteData
	*/
	///@{

	/**
	* @brief get quoteData ptr
	*
	* @return   quoteData ptr
	*/
	QuoteDataPtr& quoteData();

 

	///@}


	/**
	* @name VolatilityData
	*/
	///@{

	/**
	* @brief get volatilityData ptr
	*
	* @return   volatilityData ptr
	*/
	VolatilityDataPtr& volatilityData();
 

	///@}



	/**
	* @name DayData
	*/
	///@{

	/**
	* @brief get dayData ptr
	*
	* @return   dayData ptr
	*/
	DayDataPtr& dayData();

 

	/**
	* @brief has prev close
	*
	* @return if day data has previous close price
	*/
	bool hasPrevClosePx();


	/**
	* @brief set prev close
	*
	* @param px as previous close price
	*/
	void setPrevClosePx(double px);

	/**
	* @brief get prev close
	*
	* @return previous close price
	*/
	double getPrevClosePx();

	/**
	* @brief has prev settle
	*
	* @return if day data has previous settle price
	*/
	bool hasPrevSettlePx();


	/**
	* @brief set prev close
	*
	* @param px as previous close price
	*/
	void setPrevSettlePx(double px);

	/**
	* @brief get prev settle
	*
	* @return previous settle price
	*/
	double getPrevSettlePx();

	/**
	* @brief has limit prices
	*
	* @return if day data has limit price information
	*/
	bool hasLimitPx();


	/**
	* @brief set lower and upper limit prices
	*
	* @param lowerpx as lower limit price
	* @param upperpx as upper limit price
	*/
	void setLimitPx(double lowerpx, double upperpx);

	/**
	* @brief get lower limit price
	*
	* @return lower limit price
	*/
	double getLowerLimitPx();


	/**
	* @brief get upper limit price
	*
	* @return upper limit price
	*/
	double getUpperLimitPx();


	/**
	* @brief get day openprice
	*/
	double getDayOpenPrice();

	/**
	* @brief get day high price
	*/
	double getDayHighPx();

	/**
	* @brief get day low price
	*/
	double getDayLowPx();

	/**
	* @brief get day close price
	*/
	double getDayClosePrice();


	/**
	* @brief get previous day total volume
	*/
	int64_t getPrevDayTotVolume();

	/**
	* @brief get preious day total amount
	*/
	double getPrevDayTotAmount();

	/**
	* @brief get previous day total open interest
	*/
	int64_t getPrevDayTotOI();


	/**
	* @ get double data by dataname
	*
	* @param dataname
	*/
	double getDoubleDataByName(const std::string& dataname);

	/**
	* @brief is px valid or not
	*
	* @param px as price
	*
	* @return if the px is valid or not
	*/
	bool isValidPx(double px);


	///@}

	/**
	* @name ladder book
	*/
	///@{
	
	/**
	* @brief ladder book
	*
	* @return ladderbook
	*/
	LadderBookPtr& ladderBook();

	/**
	* @brief ladder book data
	*
	* @return ladderbookdata
	*/
	LadderBookDataPtr& ladderBookData();

	///@}


	/**
	* @name mkt quote
	*/
	///@{

	///**
	//* @brief mkt trade and quote ptr
	//*
	//* @return mkt trade and quote ptr
	//*/
	//MktTradeAndQuotePtr& taq();

 //

	///**
	//* @brief get current mktQuoteData ptr
	//*
	//* @return current mktQuoteData ptr
	//*/
	//MktQuoteDataPtr& mktQuoteDataCurr();

 //

	///**
	//* @brief get previous mktQuotesData ptr
	//*
	//* @return previous mktQuotesData ptr
	//*/
	//MktQuoteDataPtr& mktQuoteDataPrev();

 //

	///**
	//* @brief get snapshot mktquotedata ptr
	//*
	//* @return snapshot mktquotedata ptr
	//*/
	//MktQuoteDataPtr& mktQuoteDataSnap();

 //

	///**
	//* @brief emplace mktdata
	//*
	//* @param mktdata as MktQuoteData
	//*
	//*/
	//void emplaceMktQuoteData(MktQuoteDataPtr&& mktdata);


	/**
	* @brief update mktdata
	*
	* @param mktdata as MktQuoteData
	*
	*/
	void updateMktQuoteData(const MktQuoteDataPtr & mktdata);

	///**
	//* @brief update ladder from mktdata
	//*
	//* @param mktdata as MktQuoteData
	//*
	//*/
	//void updateLadderFromMktQuoteData(const MktQuoteDataPtr & mktdata);

	///**
	//* @brief update mktdata by snap
	//*
	//*/
	//void updateMktQuoteDataBySnap();

	/**
	* @brief has best buy
	*
	* @return quotes have best buy
	*/
	bool hasMktBestBuy();

	/**
	* @brief has best sell
	*
	* @return quotes have best sell
	*/
	bool hasMktBestSell();

	/**
	* @brief not crossed
	*
	* @return if it is not crossed
	*/
	bool isMktNotCrossed();

	/**
	* @brief has best buy only
	*
	* @return if quotes have best buy only
	*/
	bool hasMktBestBuyOnly();

	/**
	* @brief has best sell only
	*
	* @return if quotes have best sell only
	*/
	bool hasMktBestSellOnly();

	/**
	* @brief has best buy and sell
	*
	* @return if quotes have best buy and sell
	*/
	bool hasMktBestBuySell();

	/**
	* @brief has valid quotes
	*
	* @return if quotes are valid
	*/
	bool hasValidMktQuotes();

	///**
	//* @brief has valid previous quotes
	//*
	//*@return if previous quotes are valid
	//*/
	//bool hasValidMktQuotesPrev();


	/**
	* @brief get market timestamp
	*
	* @return market timestamp
	*/
	int64_t getMktTs();

	/**
	* @brief get market recieve timestamp
	* 
	* @return receive timestamp
	*/
	int64_t getMktRcvTs();

	/**
	* @brief get market last trade timestamp
	*
	* @return market last trade timestamp
	*/
	int64_t getMktLastTrdTs();

	/**
	* @brief get market last trade price
	*
	* @return market last trade price
	*/
	double getMktLastTrdPx();

	/**
	* @brief get market total volume
	*
	* @return market total volume
	*/
	int64_t getMktTotVolume();

	/**
	* @brief get market total amount
	*
	* @return market total amount
	*/
	double getMktTotAmount();

	/**
	* @brief get market total open interest
	*
	* @return market total open interest
	*/
	int64_t getMktTotOI();



	/**
	* @brief get best px
	*
	* @param bs as bstype
	*
	* @return best px on side
	*/
	double getMktBestPx(BuySellType::enumtype bs);

	/**
	* @brief get mkt mid px
	*
	* @return mid px of market
	*/
	double getMktMidPx();

	/**
	* @brief get mkt mid px changed
	*
	* @return mid px changed
	*/
	double getMktMidPxChged();


	/**
	* @brief get best mkt bid px
	*
	* @return best px on buy side
	*/
	double getMktBestBidPx();

	/**
	* @brief get best mkt ask px
	*
	* @return best px on sell side
	*/
	double getMktBestAskPx();

	/**
	* @brief get best mkt px spread
	*
	* @return mktaskpx - mktbidpx
	*/
	double getMktSpreadPx();

	/**
	* @brief get best level px
	*
	* @param bs as bstype
	* @param i as level
	*
	* @return best px on side
	*/
	double getMktLevelPx(BuySellType::enumtype bs, int i);

	/**
	* @brief get best size
	*
	* @param bs as bstype
	*
	* @return best size on side
	*/
	int64_t getMktBestSz(BuySellType::enumtype bs);


	/**
	* @brief get best buy size
	*
	* @return best size on buy side
	*/
	int64_t getMktBestBidSz();

	/**
	* @brief get best sell size
	*
	* @return best size on sell side
	*/
	int64_t getMktBestAskSz();

	/**
	* @brief get best level size
	*
	* @param bs as bstype
	* @param i as level
	*
	* @return best size on side
	*/
	int64_t getMktLevelSz(BuySellType::enumtype bs, int i);




	////
	///**
	//* @brief trade and quote stat data ptr
	//*
	//* @return tagStatData ptr
	//*/
	//TaqStatDataPtr& mktTaqStatData();

 

	/**
	* @brief is best px changed
	*
	* @return if best px changed
	*/
	bool isBestMktPxChged();

	/**
	* @brief is best sz changed
	*
	* @return if best sz changed
	*/
	bool isBestMktSzChged();

	/**
	* @brief is best quote changed
	*
	* @return if best quote changed
	*/
	bool isBestMktQuoteChged();

	 


	/**
	* @brief get market snapshot volume
	*
	* @return market snapshot volume
	*/
	int64_t getSnapVolume();

	/**
	* @brief get market snapshot amount
	*
	* @return market snapshot amount
	*/
	double getSnapAmount();

	/**
	* @brief get market snapshot oichg
	*
	* @return market snapshot oichg
	*/
	int64_t getSnapOIChg();


	/**
	* @brief get market snapshot average price
	*
	* @return market snapshot average price
	*/
	double getSnapAvgPx();

	/**
	* @brief get market snapshot buy volume
	*
	* @return market snapshot buy volume
	*/
	int64_t getSnapBuyVolume();

	/**
	* @brief get market snapshot sell volume
	*
	* @return market snapshot sell volume
	*/
	int64_t getSnapSellVolume();

	/**
	* @brief get market snapshot buy sell amount diff
	*
	* @return market snapshot buy sell amount diff
	*/
	double getSnapBSADiff();

	/**
	* @brief get market snapshot flipups
	*
	* @return market snapshot flipups
	*/
	double getSnapFlipups();


	/**
	* @brief get market snapshot flipdns
	*
	* @return market snapshot flipdns
	*/
	double getSnapFlipdns();

	///@}



	/**
	* @name order and fill trackers
	*/
	///@{

	///**
	//* @brief get orderTracker ptr
	//*
	//* @return  orderTracker ptr
	//*/
	//OrderTrackerPtr& orderTracker();

 

	/**
	* @brief get fillTracker ptr
	*
	* @return  fillTracker ptr
	*/
	FillTrackerPtr& fillTracker();

 

	/**
	* @brief get pnls info ptr
	*
	* @return pnls ptr
	*/
	PnLDataPtr& pnls();
 

	/**
	* @brief get pnls info before last change
	*
	* @return  pnls before last change
	*/
	PnLDataPtr& pnlsB4Chg();

 
	/**
	* @brief update pnls
	*/
	void updatePnLs();


	///**
	//* @brief get xpStatData
	//*
	//* @return  xpStatData
	//*/
	//XpStatDataPtr& xpStatData();

 

	/**
	* @brief update OrderInfo
	*
	* @param orderinfo as OrderInfo
	* @param oqstatus as OrderQuoteStatus
	*/
	void updateOrderInfo(const OrderInfoPtr& orderinfo);

	/**
	* @brief update QuoteInfo
	*
	* @param quoteinfo as QuoteInfo
	* @param oqstatus as OrderQuoteStatus
	*/
	void updateQuoteInfo(const QuoteInfoPtr& quoteinfo);

	/**
	* @brief add FillInfo
	*
	* @param fillinfo as FillInfo
	*/
	void addFillInfo(const FillInfoPtr& fillinfo);

	/**
	* @brief add FillInfo for prev trading days
	*
	* @param fillinfo as FillInfo
	*/
	void addPrevFillInfo(const FillInfoPtr& fillinfo);

	/**
	* @brief add FillInfo for current trading day
	*
	* @param fillinfo as FillInfo
	*/
	void addCurrFillInfo(const FillInfoPtr& fillinfo);


////
/**
* @brief get last fill orderid
*
* @return orderid of last fill
*/
	int getLastFillOrderId();

	/**
	* @brief get last fill px
	*
	* @return px of last fill
	*/
	double getLastFillPx();


	/**
	* @brief get last fill sz
	*
	* @return size of last fill
	*/
	int64_t getLastFillSz();

	/**
	* @brief get last fill timestamp
	*
	* @return timestamp of last fill
	*/
	int64_t getLastFillTs();

	/**
	* @brief filled volume on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return filled volume
	*/
	int64_t getFillVolume(BuySellType::enumtype bs);


	/**
	* @brief filled outlay on by or sell side
	*
	* @param bs as buy sell type
	*
	* @return filled outlay
	*/
	double getFillPxVolume(BuySellType::enumtype bs);

	/**
	* @brief get buy px*volume
	*
	* @return total sum of buy px*volume
	*/
	double getBuyPxVolume();

	/**
	* @brief get sell px*volume
	*
	* @return total sum of sell px*volume
	*/
	double getSellPxVolume();

	/**
	* @brief get buy volume
	*
	* @return total sum of buy volume
	*/
	int64_t getBuyVolume();


	/**
	* @brief get sell volume
	*
	* @return total sum of sell volume
	*/
	int64_t getSellVolume();




	/**
	* @brief get volume
	*
	* @return total sum of volume
	*/
	int64_t getTotVolume();

	/**
	* @brief get exit px for calculating pnl
	*
	* @return exit px
	*/
	double getPnLExitPx(int exitpxtype);

	/**
	* @brief get realized px pnl
	*
	* @return realized px pnl
	*/
	double getRPxPnL();

	/**
	* @brief get realized pnl
	*
	* @return realized pnl
	*/
	double getRPnL();


	/**
	* @brief get unrealized px pnl
	*
	* @return unrealized px pnl
	*/
	double getUPxPnL(double exitpx);

	/**
	* @brief get unrealized  pnl
	*
	* @return unrealized  pnl
	*/
	double getUPnL(double exitpx);

	/**
	* @brief get realized px pnl for previous position
	*
	* @return realized px pnl for previous position
	*/
	double getRPxPnLPrev();

	/**
	* @brief get realized  pnl for previous position
	*
	* @return realized   pnl for previous position
	*/
	double getRPnLPrev();

	/**
	* @brief get unrealized px pnl for previous position
	*
	* @return unrealized px pnl for previous position
	*/
	double getUPxPnLPrev(double exitpx);

	/**
	* @brief get unrealized   pnl for previous position
	*
	* @return unrealized  pnl for previous position
	*/
	double getUPnLPrev(double exitpx);

	/**
	* @brief get realized px pnl for current trading day position
	*
	* @return realized px pnl for current trading day position
	*/
	double getRPxPnLCurr();

	/**
	* @brief get realized  pnl for current trading day position
	*
	* @return realized   pnl for current trading day position
	*/
	double getRPnLCurr();

	/**
	* @brief get unrealized px pnl for current trading day position
	*
	* @return unrealized px pnl for current trading day position
	*/
	double getUPxPnLCurr(double exitpx);

	/**
	* @brief get unrealized  pnl for current trading day position
	*
	* @return unrealized   pnl for current trading day position
	*/
	double getUPnLCurr(double exitpx);

	/**
	* @brief get last unrealized px pnl
	*
	* @return last unrealized px pnl
	*/
	double getLastUPxPnL(double exitpx);

	/**
	* @brief get last unrealized   pnl
	*
	* @return last unrealized   pnl
	*/
	double getLastUPnL(double exitpx);

	/**
	* @brief get last position cost
	*
	* @return last position cost
	*/
	double getPosCost();

	/**
	* @brief get last position cost
	*
	* @return last position cost
	*/
	double getLastPosCost();

	/**
	* @brief get last position min cost
	*
	* @return last position min cost
	*/
	double getLastPosCostMin();

	/**
	* @brief get last position max cost
	*
	* @return last position max cost
	*/
	double getLastPosCostMax();




	/**
	* @brief get net position
	*
	* @return net position
	*/
	int64_t getNetPos();


	/**
	* @brief get previous net position
	*
	* @return previous net position
	*/
	int64_t getNetPosPrev();

	/**
	* @brief get new  position
	*
	* @return new net position
	*/
	int64_t getNetPosNew();

	/**
	* @brief volume to flat on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume to flat
	*/
	int64_t getVolumeToFlat(BuySellType::enumtype bs);

	/**
	* @brief volume to flat Yesterday on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume to flat yesterday
	*/
	int64_t getVolumeToFlatYtd(BuySellType::enumtype bs);

	/**
	* @brief volume to flat Today on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume to flat Today
	*/
	int64_t getVolumeToFlatTdy(BuySellType::enumtype bs);

	/**
	* @brief volume can flat on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume can flat
	*/
	int64_t getVolumeCanFlat(BuySellType::enumtype bs);

	/**
	* @brief volume can flat Yesterday on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume can flat yesterday
	*/
	int64_t getVolumeCanFlatYtd(BuySellType::enumtype bs);

	/**
	* @brief volume can flat today on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return volume can flat today
	*/
	int64_t getVolumeCanFlatTdy(BuySellType::enumtype bs);

	///@}

//////
/**
* @name Exposure Working Orders Information
*/
///@{

	/**
	* @brief has working orders
	*
	* @return if working orders still exist
	*/
	bool hasWorkingOrders();

	/**
	* @brief is working oid with open size not equal 0
	*
	* @param oid as order id
	*
	* @return if order id is working or not
	*/
	bool isOidWorking(int32_t orderId);

	/**
	* @brief is working qid
	*
	* @param qid as quote id
	*
	* @return if quote id is working or not
	*/
	bool isQidWorking(int32_t qid);

	/**
	* @brief working number of orders on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return working number of orders
	*/
	int getWorkingNumOrders(BuySellType::enumtype bs);


	/**
	* @brief working sz on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return working size
	*/
	int64_t getWorkingSz(BuySellType::enumtype bs);


	/**
	* @brief working sz for orderid
	*
	* @param oid as orderid
	*
	* @return working size
	*/
	int64_t getWorkingSzByOid(int oid);

	/**
	* @brief working sz with flag Open on buy or sell side
	*
	* @param bs as buy sell type
	* @param ocflag as OpenCloseFlag
	*
	* @return working size open
	*/
	int64_t getWorkingSzByFlag(BuySellType::enumtype bs, OpenCloseFlag::enumtype ocflag);

	
	/**
	* @brief lowest order intpx on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return lowest order int64_t price
	*/
	int64_t getLowestOrderIntPx(BuySellType::enumtype bs);

	/**
	* @brief lowest order px on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return lowest order price
	*/
	double getLowestOrderPx(BuySellType::enumtype bs);

	/**
	* @brief highest order intpx on by or sell side
	*
	* @param bs as buy sell type
	*
	* @return highest order int64_t price
	*/
	int64_t getHighestOrderIntPx(BuySellType::enumtype bs);

	/**
	* @brief highest order px on by or sell side
	*
	* @param bs as buy sell type
	*
	* @return highest order price
	*/
	double getHighestOrderPx(BuySellType::enumtype bs);

	/**
	* @brief best order intpx on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return order int64_t price
	*/
	int64_t getBestOrderIntPx(BuySellType::enumtype bs);

	/**
	* @brief best order sz on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return best order sz
	*/
	int64_t getBestOrderSz(BuySellType::enumtype bs);

	/**
	* @brief best order px on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return order price
	*/
	double getBestOrderPx(BuySellType::enumtype bs);

	/**
	* @brief get last quote timestamp
	*
	* @return last quote timestamp
	*/
	int64_t getLastQuoteTs();

	/**
	* @brief last quote order px on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return quote price
	*/
	double getLastQuotePx(BuySellType::enumtype bs);

	/**
	* @brief best quote int64_t price on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return int64_t price
	*/
	int64_t getLastQuoteIntPx(BuySellType::enumtype bs);

	/**
	* @brief best quote size on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return quote size
	*/
	int64_t getLastQuoteSz(BuySellType::enumtype bs);

	///@} 

////////////
	///@{
	/**
	* @name intpx info
	*/

	/**
	* @brief intPxInfoMap
	*
	* @return intPxInfoMap
	*/
	std::map<int64_t, IntPxInfoPtr >& intPxInfoMap();

	///@}

 
////////////
///@{
/**
* @name string functions
*/

	/**
	* @brief position csv string
	*
	* @return csv string for position
	*/
	std::string posCsvStr();

	/**
	* @brief position json string
	*
	* @return json string for position
	*/
	std::string posJsonStr();

///@}

//////


/**
* @name events
*/
///@{

/**
* @brief connect signal MktData
*
* @param subscriber
*
* @return connection
*/
	boost::signals2::connection connectSignalMktData(const boost::signals2::signal<void(int)>::slot_type & subscriber);

	/**
	* @brief fire MktData Event
	*
	* @param iid as integer id
	*/
	void emitSignalMktData(int iid);

	/**
	* @brief connect order sent rejected
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalSentRejected(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);

	/**
	* @brief emit signal sent rejected
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalSentRejected(int iid, int orderid);

	/**
	* @brief connect order confirmed
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalOrderCnf(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);

	/**
	* @brief emit signal order confirmed
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalOrderCnf(int iid, int orderid);


	/**
	* @brief connect order cxl rejected
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalOrderCxlRejected(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);


	/**
	* @brief fire signal order cxl rejected
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalOrderCxlRejected(int iid, int orderid);

	/**
	* @brief connect signal order cxl
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalOrderCxl(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);

	/**
	* @brief fire signal order cxl
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalOrderCxl(int iid, int orderid);

	/**
	* @brief connect singal Order Fill
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalOrderFill(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);


	/**
	* @brief fire Order Fill Event
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalOrderFill(int iid, int orderid);





	/**
	* @brief connect singal order finished
	*
	* @param subscriber
	*
	* @return connection
	*/
	boost::signals2::connection connectSignalOrderFinished(const boost::signals2::signal<void(int, int)>::slot_type & subscriber);

	/**
	* @brief fire signal order finished
	*
	* @param iid as integer id
	* @param orderid as order id
	*/
	void emitSignalOrderFinished(int iid, int orderid);

	
	///@}



//////
	/**
	* @name static functions
	*/
	///@{

	/**
	* @brief creat instr
	*
	* @param spec as InstrSpec
	* @param booklevels
	*
	* @return Instr pointer
	*/
	static InstrPtr createWithParams(InstrSpecPtr& spec, int booklevels);


	///@}

protected:
	int m_iid = 0;

	InstrSpecPtr m_spec; //  

	InstrCfgDataPtr m_cfgData;
	InstrDataPtr m_data;
	GreeksDataPtr m_greeksData;

	PosGreeksDataPtr m_posGreeksData;

	QuoteDataPtr m_quoteData;
	VolatilityDataPtr m_volatilityData;
		
	DayDataPtr m_dayData;

	StringMapPtr m_strParams;
//protected:
//	MktTradeAndQuotePtr m_taq;
//	OrderTrackerPtr m_orderTracker;
//	XpStatDataPtr m_xpStatData;
//protected:
//	std::map<int64_t, IntPxInfoPtr > m_intPxInfoMap;
// the above is replace by the following m_ladderBook
protected:
	LadderBookPtr m_ladderBook;



protected:
	FillTrackerPtr m_fillTracker;

	PnLDataPtr m_pnls;
	PnLDataPtr m_pnlsB4Chg;

protected:
	boost::signals2::signal<void(int)> m_signalMktData; ///< market data signal

	boost::signals2::signal<void(int, int)> m_signalOrderSentRejected; ///< order sent rejected signal
	boost::signals2::signal<void(int, int)> m_signalOrderCnf; ///< order confirmed signal
	boost::signals2::signal<void(int, int)> m_signalOrderCxlRejected; ///< order cancel rejected signal
	boost::signals2::signal<void(int, int)> m_signalOrderCxl; ///< order cancel signal

	boost::signals2::signal<void(int, int)> m_signalOrderFinished;  ///< order finished signal

	boost::signals2::signal<void(int, int)> m_signalOrderFill; ///< order fill signal

protected:
//	mutable  boost::shared_mutex m_mutex;

};//class


}//namespace

#endif
