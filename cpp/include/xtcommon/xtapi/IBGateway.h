#pragma once
#ifndef XT_IB_GATEWAY_H
#define XT_IB_GATEWAY_H


/**
* \file IBGateway.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for IB gateway.
*
* \description
*	Designed for managing IB gateway.
*/

#include <string>
#include <iostream>
#include <sstream>

#include <memory>
#include <vector>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			// 
#include <boost/bind.hpp>			// 
#include <boost/any.hpp>	// 
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"


#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"


#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"


#include "ServerSettingsMgr.h"
#include "InstrSettingsMgr.h"
#include "SettingsMgr.h"
#include "InstrMgr.h"

#include "Util.h"
#include "PBUtil.h"
#include "LogUtil.h"

#include "TagDataWrapper.h"

#include "PBUtil.h"
#include "ZMQMgr.h"
 
#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

namespace XT
{
	
	enum State {
		ST_CONNECT,
		ST_TICKDATAOPERATION,
		ST_TICKDATAOPERATION_ACK,
		ST_MARKETDEPTHOPERATION,
		ST_MARKETDEPTHOPERATION_ACK,
		ST_REALTIMEBARS,
		ST_REALTIMEBARS_ACK,
		ST_MARKETDATATYPE,
		ST_MARKETDATATYPE_ACK,
		ST_HISTORICALDATAREQUESTS,
		ST_HISTORICALDATAREQUESTS_ACK,
		ST_OPTIONSOPERATIONS,
		ST_OPTIONSOPERATIONS_ACK,
		ST_CONTRACTOPERATION,
		ST_CONTRACTOPERATION_ACK,
		ST_MARKETSCANNERS,
		ST_MARKETSCANNERS_ACK,
		ST_REUTERSFUNDAMENTALS,
		ST_REUTERSFUNDAMENTALS_ACK,
		ST_BULLETINS,
		ST_BULLETINS_ACK,
		ST_ACCOUNTOPERATIONS,
		ST_ACCOUNTOPERATIONS_ACK,
		ST_ORDEROPERATIONS,
		ST_ORDEROPERATIONS_ACK,
		ST_OCASAMPLES,
		ST_OCASAMPLES_ACK,
		ST_CONDITIONSAMPLES,
		ST_CONDITIONSAMPLES_ACK,
		ST_BRACKETSAMPLES,
		ST_BRACKETSAMPLES_ACK,
		ST_HEDGESAMPLES,
		ST_HEDGESAMPLES_ACK,
		ST_TESTALGOSAMPLES,
		ST_TESTALGOSAMPLES_ACK,
		ST_FAORDERSAMPLES,
		ST_FAORDERSAMPLES_ACK,
		ST_FAOPERATIONS,
		ST_FAOPERATIONS_ACK,
		ST_DISPLAYGROUPS,
		ST_DISPLAYGROUPS_ACK,
		ST_MISCELANEOUS,
		ST_MISCELANEOUS_ACK,
		ST_CANCELORDER,
		ST_CANCELORDER_ACK,
		ST_PING,
		ST_PING_ACK,
		ST_IDLE
	};

class XT_COMMON_API IBGateway : public EWrapper
{

public:
	/** 
	* @name Constructor and Initialization
	*/
	///@{

	/**
	* @brief constructor
	*/
	IBGateway();

	/**
	* @brief default copy constructor
	*/
	IBGateway(const IBGateway& from) = default;

	/**
	* @brief default copy assignment
	*/
	IBGateway& operator=(const IBGateway& from) = default;

	/**
	*  @brief destructor
	*/
	~IBGateway();

	///@}

	/**
	*  @brief set connection options
	*/
	void setConnectOptions(const std::string&);

	/**
	*  @brief process messages
	*/
	void processMessages();

public:
	/**
	*  @brief connect to gateway
	*
	* @param host for host ip
	* @param port for port number
	* @param clientId for unique client id
	* 
	* @return if it is connected successfully
	*/
	bool connect(const char * host, unsigned int port, int clientId = 0);

	/**
	*  @brief disconnect to gateway
	*/
	void disconnect() const;

	/**
	* @brief check if it is connected or not
	*
	* @return if it is connected
	*/
	bool isConnected() const;

private:
	/** 
	* @name request
	*/
	///@{
	void tickDataOperation();
	void marketDepthOperations();
	void realTimeBars();
	void mktDataType();
	void historicalDataRequests();
	void optionsOperations();
	void accountOperations();
	void orderOperations();
	void ocaSamples();
	void conditionSamples();
	void bracketSample();
	void hedgeSample();
	void contractOperations();
	void marketScanners();
	void reutersFundamentals();
	void bulletins();
	void testAlgoSamples();
	void financialAdvisorOrderSamples();
	void financialAdvisorOperations();
	void testDisplayGroups();
	void miscelaneous();

	void reqCurrentTime();

	///@}

public:
	/**
	*  @name response event
	*/
	///@{
	void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	void tickSize(TickerId tickerId, TickType field, int size);
	void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
		double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
	void tickGeneric(TickerId tickerId, TickType tickType, double value);
	void tickString(TickerId tickerId, TickType tickType, const std::string& value);
	void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
		double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate);
	void orderStatus(OrderId orderId, const std::string& status, double filled,
		double remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const std::string& whyHeld);
	void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
	void openOrderEnd();
	void winError(const std::string& str, int lastError);
	void connectionClosed();
	void updateAccountValue(const std::string& key, const std::string& val,
		const std::string& currency, const std::string& accountName);
	void updatePortfolio(const Contract& contract, double position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const std::string& accountName);
	void updateAccountTime(const std::string& timeStamp);
	void accountDownloadEnd(const std::string& accountName);
	void nextValidId(OrderId orderId);
	void contractDetails(int reqId, const ContractDetails& contractDetails);
	void bondContractDetails(int reqId, const ContractDetails& contractDetails);
	void contractDetailsEnd(int reqId);
	void execDetails(int reqId, const Contract& contract, const Execution& execution);
	void execDetailsEnd(int reqId);
	void error(const int id, const int errorCode, const std::string errorString);
	void updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size);
	void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
		int side, double price, int size);
	void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);
	void managedAccounts(const std::string& accountsList);
	void receiveFA(faDataType pFaDataType, const std::string& cxml);
	void historicalData(TickerId reqId, const std::string& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps);
	void scannerParameters(const std::string& xml);
	void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
		const std::string& distance, const std::string& benchmark, const std::string& projection,
		const std::string& legsStr);
	void scannerDataEnd(int reqId);
	void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count);
	void currentTime(long time);
	void fundamentalData(TickerId reqId, const std::string& data);
	void deltaNeutralValidation(int reqId, const UnderComp& underComp);
	void tickSnapshotEnd(int reqId);
	void marketDataType(TickerId reqId, int marketDataType);
	void commissionReport(const CommissionReport& commissionReport);
	void position(const std::string& account, const Contract& contract, double position, double avgCost);
	void positionEnd();
	void accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency);
	void accountSummaryEnd(int reqId);
	void verifyMessageAPI(const std::string& apiData);
	void verifyCompleted(bool isSuccessful, const std::string& errorText);
	void verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallenge);
	void verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText);
	void displayGroupList(int reqId, const std::string& groups);
	void displayGroupUpdated(int reqId, const std::string& contractInfo);
	void connectAck();
	void positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double avgCost);
	void positionMultiEnd(int reqId);
	void accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency);
	void accountUpdateMultiEnd(int reqId);
	void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes);
	void securityDefinitionOptionalParameterEnd(int reqId);
	void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers);
	///@}

private:
	//! [socket_declare]
	EReaderOSSignal m_osSignal; ///< os signal
	EClientSocket * const m_pClient; ///< client
	//! [socket_declare]
	State m_state; ///< socket state
	time_t m_sleepDeadline; ///< sleep deadline

	OrderId m_orderId; ///< order id
	EReader *m_pReader; ///< socket reader
	bool m_extraAuth; ///< extra authorization or not

};//calss
  //////typedef for IBGateway

#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<IBGateway> IBGatewayPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<IBGateway> IBGatewayPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<IBGateway> IBGatewayPtr;

#else

typedef ::boost::shared_ptr<IBGateway> IBGatewayPtr;
#endif


typedef ::sf::safe_ptr<IBGateway> IBGatewaySafePtr;

typedef sf::contfree_safe_ptr<IBGateway> IBGatewayContFreePtr;
//////end typedef for IBGateway
}//namespace XT

#endif