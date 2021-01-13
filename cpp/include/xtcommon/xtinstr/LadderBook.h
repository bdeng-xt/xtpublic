#pragma once
#ifndef XT_LADDER_BOOK_H
#define XT_LADDER_BOOK_H
/**
* \file LadderBook.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for ladder book.
*
* \description
*	Designed for ladder book.
*/
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <set>
#include <map>
#include <list>
#include <algorithm>

#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>

#include "XTConfig.h"
#include "log4z.h"

#include "safe_ptr.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "DataUtil.h"

#include "OrderMgr.h"


namespace XT
{

class XT_COMMON_API LadderBook
{
public:
		/**
		* @name Constructor and Initialization
		*/
		///@{

		/**
		* @brief constructor
		*/
		LadderBook();

		/**
		* @brief default copy constructor
		*/
		LadderBook(const LadderBook& from);// = default;

		/**
		* @brief default copy assignment
		*/
		LadderBook& operator=(const LadderBook& from);// = default;

		/**
		 * @brief destructor
		*/
		virtual ~LadderBook();

		///@}

		/**
		* @name init
		*/
		///@{
		
		/**
		* @brief initialize
		*/
		void init();

		/**
		* @brief initialize with InstrSpec
		*
		* @param instrspecdata
		*/
		void initWithInstrSpecData(const InstrSpecDataPtr& spec);


		///@}



		/**
		* @name Update
		*/
		///@{

		/**
		* @brief update MktQuoteData
		*/
		void updateFromMktQuoteData(const MktQuoteDataPtr& quotedata);

		/**
		* @brief update book from bid ask levels string
		*
		*/
		void udpateFromBidAskLevelsStr(int64_t ts, int nbidlevels, const std::string bidstr, int nasklevels, const std::string askstr, double pxscale = 1.0, double szscale=1.0);
 
		/**
		* @brief update orderinfo
		*/
		void updateOrderInfo(const OrderInfoPtr& orderinfo);

		/**
		* @brief update quoteinfo
		*/
		void updateQuoteInfo(const QuoteInfoPtr& quoteinfo);

		///@}

protected:
 
	void updateOrdersSzByRawPtr(LadderBookData* rawp);

	void updateOrdersSzForOcflagByRawPtr(LadderBookData* rawp, int ocflag);

	void updateOrdersSzForIntPxByRawPtr(LadderBookData* rawp, int64_t intpx);

public:
 
	/**
	* @brief add ladder px for range [pxmin,pxmax]
	*
	*/
	void addLadderPxRangeByRawPtr(LadderBookData* rawp, double pxmin, double pxmax, bool addextra = true);

	/**
	* @brief add ladder px for range [pxmin,pxmax]
	*
	*/
	void addLadderPxRange(double pxmin, double pxmax, bool addextra = true);

	/**
	* @brief adjust ladder px for px vector by RawPtr
	*/
	void addLadderPxsByRawPtr(LadderBookData* rawp, std::vector<double>& pxs);

	/**
	* @brief add ladder px vector
	*/
	void addLadderPxs(std::vector<double>& pxs);

	/**
	* @brief add ladder px
	*/
	void addLadderPx(double px);

	/**
	* @brief remove ladder px out of range[pxmin,pxmax]
	*/
	void removeLadderPxOutOfRangeByRawPtr(LadderBookData* rawp, double pxmin, double pxmax);

	/**
	* @brief remove ladder px out of range[pxmin,pxmax]
	*/
	void removeLadderPxOutOfRange( double pxmin, double pxmax);

	///**
	//* @brief adjust ladder px for bidpx and askpx
	//*/
	//void adjustLadderPxRangeForBidAskPxByRawPtr(LadderBookData* rawp, double bidpx, double askpx, bool addextra = true);

	/**
	* @brief adjust ladder px for bidpx and askpx
	*/
	void adjustLadderPxRangeForBidAskPx(double bidpx, double askpx, bool addextra = true);

	/**
	* @brief adjust ladder px for bidpx and askpx
	*/
	void adjustLadderPxRangeForBidAskPxByRawPtr(LadderBookData* rawp, double bidpx, double askpx, bool addextra = true);


public:
		/**
		* @name Accessors
		*/
		///@{

		/**
		* @brief data
		*
		* @return data
		*/
		LadderBookDataPtr& data();

		/**
		* @brief empty ladder px data
		*
		* @return empty LadderPxData
		*/
		LadderPxData& emptyLadderPxData();

		const LadderPxData& ladderPxDataForPxByRawPtr(LadderBookData* rawp, double px);
		/**
		* @brief get ladder px data for px
		*
		* @param px
		*
		* @return LadderPxData
		*/
		const LadderPxData& ladderPxDataForPx(double px);


		const LadderPxData& ladderPxDataForIntPxByRawPtr(LadderBookData* rawp, int64_t intpx);
		/**
		* @brief get ladder px data for intpx
		*
		* @param intpx
		*
		* @return LadderPxData
		*/
		const LadderPxData& ladderPxDataForIntPx(int64_t intpx);
////
		int getIdxForLadderIntPxByRawPtr(LadderBookData* rawp, int64_t intpx);
		/**
		* @brief get idx for ladder int px
		*
		* @param intpx
		*
		* @return idx
		*/
		int getIdxForLadderIntPx(int64_t intpx);

		int getIdxForLadderPxByRawPtr(LadderBookData* rawp, double px);
		/**
		* @brief get idx for ladde px
		*
		* @param intpx
		*
		* @return idx
		*/
		int getIdxForLadderPx(double px);

		double getLadderPxMinByRawPtr(LadderBookData* rawp);
		/**
		* @brief get ladder px min
		*
		* @return ladder px min
		*/
		double getLadderPxMin();


		double getLadderPxMaxByRawPtr(LadderBookData* rawp);
		/**
		* @brief get ladder px max
		*
		* @return ladder px max
		*/
		double getLadderPxMax();
////
		int64_t getMktTsByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market timestamp
		*
		* @return market timestamp
		*/
		int64_t getMktTs();

		int64_t getMktRcvTsByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market recieve timestamp
		*
		* @return receive timestamp
		*/
		int64_t getMktRcvTs();

		int64_t getMktLastTrdTsByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market last trade timestamp
		*
		* @return market last trade timestamp
		*/
		int64_t getMktLastTrdTs();

		double getMktLastTrdPxByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market last trade price
		*
		* @return market last trade price
		*/
		double getMktLastTrdPx();

		int64_t getMktTotVolumeByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market total volume
		*
		* @return market total volume
		*/
		int64_t getMktTotVolume();

		double getMktTotAmountByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market total amount
		*
		* @return market total amount
		*/
		double getMktTotAmount();

		int64_t getMktTotOIByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market total open interest
		*
		* @return market total open interest
		*/
		int64_t getMktTotOI();


////
		/**
		* @brief get best px
		*
		* @param data raw pointer
		* @param bs as bstype
		*
		* @return best px on side
		*/
		double getMktBestPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);

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
		* @param data raw pointer
		* @return mid px of market
		*/
		double getMktMidPxByRawPtr(LadderBookData* rawp);

		/**
		* @brief get mkt mid px
		*
		* @return mid px of market
		*/
		double getMktMidPx();

		/**
		* @brief get mkt mid px changed
		*
		* @param data raw pointer
		* @return mid px changed
		*/
		double getMktMidPxChgedByRawPtr(LadderBookData* rawp);

		/**
		* @brief get mkt mid px changed
		*
		* @return mid px changed
		*/
		double getMktMidPxChged();

		/**
		* @brief get best mkt bid px
		*
		* @param data raw pointer
		* @return best px on buy side
		*/
		double getMktBestBidPxByRawPtr(LadderBookData* rawp);

		/**
		* @brief get best mkt bid px
		*
		* @return best px on buy side
		*/
		double getMktBestBidPx();

		/**
		* @brief get best mkt ask px
		*
		* @param data raw pointer
		* @return best px on sell side
		*/
		double getMktBestAskPxByRawPtr(LadderBookData* rawp);

		/**
		* @brief get best mkt ask px
		*
		* @return best px on sell side
		*/
		double getMktBestAskPx();


		/**
		* @brief get best mkt px spread
		*
		* @param data raw pointer
		* @return mktaskpx - mktbidpx
		*/
		double getMktSpreadPxByRawPtr(LadderBookData* rawp);

		/**
		* @brief get best mkt px spread
		*
		* @return mktaskpx - mktbidpx
		*/
		double getMktSpreadPx();

		/**
		* @brief get best level px
		*
		* @param data raw pointer
		* @param bs as bstype
		* @param i as level
		*
		* @return best px on side
		*/
		double getMktLevelPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs, int i);

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
		* @param data raw pointer
		* @param bs as bstype
		*
		* @return best size on side
		*/
		int64_t getMktBestSzByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);

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
		* @param data raw pointer
		* @return best size on buy side
		*/
		int64_t getMktBestBidSzByRawPtr(LadderBookData* rawp);

		/**
		* @brief get best buy size
		*
		* @return best size on buy side
		*/
		int64_t getMktBestBidSz();

		/**
		* @brief get best sell size
		*
		* @param data raw pointer
		* @return best size on sell side
		*/
		int64_t getMktBestAskSzByRawPtr(LadderBookData* rawp);

		/**
		* @brief get best sell size
		*
		* @return best size on sell side
		*/
		int64_t getMktBestAskSz();


		/**
		* @brief get best level size
		*
		* @param data raw pointer
		* @param bs as bstype
		* @param i as level
		*
		* @return best size on side
		*/
		int64_t getMktLevelSzByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs, int i);

		/**
		* @brief get best level size
		*
		* @param bs as bstype
		* @param i as level
		*
		* @return best size on side
		*/
		int64_t getMktLevelSz(BuySellType::enumtype bs, int i);



		///@}

		/**
		* @name mkt stat data
		*/
		///@{

		bool isBestMktPxChgedByRawPtr(LadderBookData* rawp);
		/**
		* @brief is best px changed
		*
		* @return if best px changed
		*/
		bool isBestMktPxChged();

		int64_t getBestMktPxTickChgedByRawPtr(LadderBookData* rawp);
		/**
		* @brief  best px changed ticks
		*
		* @return changed ticks
		*/
		int64_t getBestMktPxTickChged();


		int64_t getBestMktSzChgedByRawPtr(LadderBookData* rawp);
		/**
		* @brief is best sz changed
		*
		* @return if best sz changed
		*/
		int64_t getBestMktSzChged();

		bool isBestMktSzChgedByRawPtr(LadderBookData* rawp);
		/**
		* @brief is best sz changed
		*
		* @return if best sz changed
		*/
		bool isBestMktSzChged();


		bool isBestMktQuoteChgedByRawPtr(LadderBookData* rawp);
		/**
		* @brief is best quote changed
		*
		* @return if best quote changed
		*/
		bool isBestMktQuoteChged();


		int64_t getSnapVolumeByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot volume
		*
		* @return market snapshot volume
		*/
		int64_t getSnapVolume();

		double getSnapAmountByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot amount
		*
		* @return market snapshot amount
		*/
		double getSnapAmount();

		int64_t getSnapOIChgByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot oichg
		*
		* @return market snapshot oichg
		*/
		int64_t getSnapOIChg();

		double getSnapAvgPxByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot average price
		*
		* @return market snapshot average price
		*/
		double getSnapAvgPx();

		int64_t getSnapBuyVolumeByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot buy volume
		*
		* @return market snapshot buy volume
		*/
		int64_t getSnapBuyVolume();


		int64_t getSnapSellVolumeByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot sell volume
		*
		* @return market snapshot sell volume
		*/
		int64_t getSnapSellVolume();

		double getSnapBSADiffByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot buy sell amount diff
		*
		* @return market snapshot buy sell amount diff
		*/
		double getSnapBSADiff();

		double getSnapFlipupsByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot flipups
		*
		* @return market snapshot flipups
		*/
		double getSnapFlipups();

		double getSnapFlipdnsByRawPtr(LadderBookData* rawp);
		/**
		* @brief get market snapshot flipdns
		*
		* @return market snapshot flipdns
		*/
		double getSnapFlipdns();
		///@}



public:

	/**
	* @name OrderInfo and QuoteInfo
	*/
	///@{

	OrderInfoPtr& getOrderInfoForOidByRawPtr(LadderBookData* rawp, int oid);
	/**
	* @brief get OrderInfo for oid
	*
	* @param oid
	* @return OrderInfo
	*/
	OrderInfoPtr& getOrderInfoForOid(int oid);

	int getLastOrderOidByRawPtr(LadderBookData* rawp);
	/**
	* @brief get last single order oid
	*
	* @return oid
	*/
	int getLastOrderOid();

	OrderInfoPtr& getLastOrderInfoByRawPtr(LadderBookData* rawp);
	/**
	* @brief get last OrderInfo
	*
	* @return OrderInfo
	*/
	OrderInfoPtr& getLastOrderInfo();


	QuoteInfoPtr& getQuoteInfoForQidByRawPtr(LadderBookData* rawp, int qid);
	/**
	* @brief get QuoteInfo for qid
	*
	* @param qid
	*
	* @return QuoteInfo
	*/
	QuoteInfoPtr& getQuoteInfoForQid(int qid);

	int getLastQuoteQidByRawPtr(LadderBookData* rawp);
	/**
	* @brief get last quote qid
	*
	* @return qid
	*/
	int getLastQuoteQid();


	QuoteInfoPtr& getLastQuoteInfoByRawPtr(LadderBookData* rawp);
	/**
	* @brief get last QuoteInfo
	*
	* @return QuoteInfo
	*/
	QuoteInfoPtr& getLastQuoteInfo();

	///@}

public:
	//////
	/**
	* @name Exposure Working Orders Information
	*/
	///@{


	bool hasWorkingOrdersByRawPtr(LadderBookData* rawp);
	/**
	* @brief has working orders
	*
	* @return if working orders still exist
	*/
	bool hasWorkingOrders();


	bool isOidWorkingByRawPtr(LadderBookData* rawp, int oid);

	/**
	* @brief is working oid with open size not equal 0
	*
	* @param oid as order id
	*
	* @return if order id is working or not
	*/
	bool isOidWorking(int orderId);

	bool isQidWorkingByRawPtr(LadderBookData* rawp, int qid);

	/**
	* @brief is working qid
	*
	* @param qid as quote id
	*
	* @return if quote id is working or not
	*/
	bool isQidWorking(int qid);


	int getWorkingNumOrdersByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief working number of orders on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return working number of orders
	*/
	int getWorkingNumOrders(BuySellType::enumtype bs);


	
	int64_t getWorkingSzByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief working sz on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return working size
	*/
	int64_t getWorkingSz(BuySellType::enumtype bs);


 
////
	int64_t getWorkingSzByOidByRawPtr(LadderBookData* rawp, int oid);
	/**
	* @brief working sz for orderid
	*
	* @param oid as orderid
	*
	* @return working size
	*/
	int64_t getWorkingSzByOid(int oid);

////

	int getWorkingNumOrdersByFlagByRawPtr(LadderBookData*rawp, BuySellType::enumtype bs, OpenCloseFlag::enumtype ocflag);
	/**
	* @brief number of orders with flag Open on buy or sell side
	*
	* @param bs as buy sell type
	* @param ocflag as OpenCloseFlag
	*
	* @return number of orders
	*/
	int getWorkingNumOrdersByFlag(BuySellType::enumtype bs, OpenCloseFlag::enumtype ocflag);

	int64_t getWorkingSzByFlagByRawPtr(LadderBookData*rawp, BuySellType::enumtype bs, OpenCloseFlag::enumtype ocflag);
	/**
	* @brief working sz with flag Open on buy or sell side
	*
	* @param bs as buy sell type
	* @param ocflag as OpenCloseFlag
	*
	* @return working size open
	*/
	int64_t getWorkingSzByFlag(BuySellType::enumtype bs, OpenCloseFlag::enumtype ocflag);

	////
	int64_t getLowestOrderIntPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief lowest order intpx on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return lowest order int64_t price
	*/
	int64_t getLowestOrderIntPx(BuySellType::enumtype bs);

	double getLowestOrderPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief lowest order px on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return lowest order price
	*/
	double getLowestOrderPx(BuySellType::enumtype bs);

	int64_t getHighestOrderIntPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief highest order intpx on by or sell side
	*
	* @param bs as buy sell type
	*
	* @return highest order int64_t price
	*/
	int64_t getHighestOrderIntPx(BuySellType::enumtype bs);

	double getHighestOrderPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief highest order px on by or sell side
	*
	* @param bs as buy sell type
	*
	* @return highest order price
	*/
	double getHighestOrderPx(BuySellType::enumtype bs);

	int64_t getBestOrderIntPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief best order intpx on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return order int64_t price
	*/
	int64_t getBestOrderIntPx(BuySellType::enumtype bs);

	double getBestOrderPxByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief best order px on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return order price
	*/
	double getBestOrderPx(BuySellType::enumtype bs);


	int64_t getBestOrderSzByRawPtr(LadderBookData* rawp, BuySellType::enumtype bs);
	/**
	* @brief best order sz on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return order sz
	*/
	int64_t getBestOrderSz(BuySellType::enumtype bs);


////



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

	/**
	* @brief best quote open size on buy or sell side
	*
	* @param bs as buy sell type
	*
	* @return quote size
	*/
	int64_t getLastQuoteOpenSz(BuySellType::enumtype bs);

	///@} 

	/**
	* @name oids and qids
	*/
	///@{

	bool hasWorkingOidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief has working oids
	*
	* @return if there is any working oid
	*/
	bool hasWorkingOids();

	std::vector<int> getWorkingOidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief get working oids
	* 
	* @return all working oids(oids from quote included)
	*/
	std::vector<int> getWorkingOids();


	std::vector<int> getOrderWorkingOidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief get order(not quote) working oids
	*
	* @return all order(not quote) working oids
	*/
	std::vector<int> getOrderWorkingOids();



	std::vector<int> getQuoteWorkingOidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief get quote working oids
	*
	* @return all quote(not single order) working oids
	*/
	std::vector<int> getQuoteWorkingOids();


	bool hasWorkingQidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief has working qids
	*
	* @return if there is any working qid
	*/
	bool hasWorkingQids();

	std::vector<int> getWorkingQidsByRawPtr(LadderBookData* rawp);
	/**
	* @brief get working qids
	*
	* @return working qids
	*/
	std::vector<int> getWorkingQids();

////
	std::vector<int> getOidsForPxByRawPtr(LadderBookData* rawp, double px);
	/**
	* @brief get all oids at price 
	*
	* @param lowerpx
	*
	* @return vector of oids
	*/
	std::vector<int> getOidsForPx(double px);

	std::vector<int> getOidsForPxInRangeByRawPtr(LadderBookData* rawp, double lowerpx, double upperpx);
	/**
	* @brief get all oids with price between lowerpx and upperpx
	*
	* @param lowerpx
	* @param upperpx
	*
	* @return vector of oids
	*/
	std::vector<int> getOidsForPxInRange(double lowerpx, double upperpx);


	std::vector<int> getOidsForPxOutOfRangeByRawPtr(LadderBookData* rawp, double lowerpx, double upperpx);
	/**
	* @brief get all oids with price NOT between lowerpx and upperpx
	*
	* @param lowerpx
	* @param upperpx
	*
	* @return vector of oids
	*/
	std::vector<int> getOidsForPxOutOfRange(double lowerpx, double upperpx);

	///@}

	/**
	* @brief clear all sz
	*/
	void clearAllMktOrdersByRawPtr(LadderBookData* rawp);

	/**
	* @brief clear all sz
	*/
	void clearAllMktOrders();


	/**
	* @brief clear all px
	*/
	void clearAllByRawPtr(LadderBookData* rawp);

	/**
	* @brief clear all px
	*/
	void clearAll();

public:
	/**
	* @name str functions  
	*/
	///@{

	/**
	* @brief range information
	*
	* @param raw pointer
	* @return range information string
	*/
	std::string getRangeInfoStrByRawPtr(LadderBookData* rawp);

	/**
	* @brief range information
	*
	* @return range information string
	*/
	std::string getRangeInfoStr();

	/**
	* @brief csv str
	*
	* @param raw pointer
	* @return range information string
	*/
	std::string getCsvStrByRawPtr(LadderBookData* rawp);

	/**
	* @brief csv str
	*
	* @return level1 information string
	*/
	std::string getCsvStr();


	/**
	* @brief csv str
	*
	* @param raw pointer
	* @return level 1  information string
	*/
	std::string getCsvStr1ByRawPtr(LadderBookData* rawp);

	/**
	* @brief csv str
	*
	* @return range information string
	*/
	std::string getCsvStr1();


	/**
	* @brief csv str
	*
	* @param raw pointer
	* @return range information string
	*/
	std::string getCsvStr5ByRawPtr(LadderBookData* rawp);

	/**
	* @brief csv str
	*
	* @return range information string
	*/
	std::string getCsvStr5();

	/**
	* @brief csv str
	*
	* @param raw pointer
	* @return range information string
	*/
	std::string getStrByRawPtr(LadderBookData* rawp);

	/**
	* @brief csv str
	*
	* @return range information string
	*/
	std::string getStr();


	///@}

	protected:

		LadderBookDataPtr m_data;
		LadderPxData m_emptyLadderPxData;
 

};//class


	  //////typedef for LadderBook
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<LadderBook> LadderBookPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<LadderBook> LadderBookPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<LadderBook> LadderBookPtr;

#else

	typedef ::boost::shared_ptr<LadderBook> LadderBookPtr;
#endif


	typedef ::sf::safe_ptr<LadderBook> LadderBookSafePtr;

	typedef sf::contfree_safe_ptr<LadderBook> LadderBookContFreePtr;
	//////end typedef for LadderBook

}//namespace


#endif