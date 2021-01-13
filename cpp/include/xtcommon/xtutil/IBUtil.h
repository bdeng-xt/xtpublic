#pragma once
#ifndef XT_IB_DATA_UTIL_H
#define XT_IB_DATA_UTIL_H

/**
* \file IBUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a utilitiy class for IBData.
*
* \description
*	Designed for handling IBData.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <google/protobuf/util/json_util.h>

#include "XTConfig.h"
#include "IBData.pb.h"
#include "TagDataWrapper.h"

namespace XT
{

class XT_COMMON_API IBUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	IBUtil() {}

	/**
	* @brief copy constructor
	*/
	IBUtil(const IBUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	IBUtil& operator=(const IBUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~IBUtil() {}

	///@}

protected:
	static const std::string s_EmptyString; ///< empty string
public:

	static const std::string& getEmptyString(); ///< empty string


///////////////////////////////////////////////
public:


	static bool fromjsonOrder(IB::IBOrder& r, const std::string& s);
	static std::string tojsonOrder(const IB::IBOrder& r);
	static bool parseOrder(IB::IBOrder& r, const std::string& s);
	static std::string serializeOrder(const IB::IBOrder& r);

	static bool fromjsonOrderComboLeg(IB::IBOrderComboLeg& r, const std::string& s);
	static std::string tojsonOrderComboLeg(const IB::IBOrderComboLeg& r);
	static bool parseOrderComboLeg(IB::IBOrderComboLeg& r, const std::string& s);
	static std::string serializeOrderComboLeg(const IB::IBOrderComboLeg& r);

	static bool fromjsonExecutionFilter(IB::IBExecutionFilter& r, const std::string& s);
	static std::string tojsonExecutionFilter(const IB::IBExecutionFilter& r);
	static bool parseExecutionFilter(IB::IBExecutionFilter& r, const std::string& s);
	static std::string serializeExecutionFilter(const IB::IBExecutionFilter& r);

	static bool fromjsonOrderState(IB::IBOrderState& r, const std::string& s);
	static std::string tojsonOrderState(const IB::IBOrderState& r);
	static bool parseOrderState(IB::IBOrderState& r, const std::string& s);
	static std::string serializeOrderState(const IB::IBOrderState& r);

	static bool fromjsonCodeMsgPair(IB::IBCodeMsgPair& r, const std::string& s);
	static std::string tojsonCodeMsgPair(const IB::IBCodeMsgPair& r);
	static bool parseCodeMsgPair(IB::IBCodeMsgPair& r, const std::string& s);
	static std::string serializeCodeMsgPair(const IB::IBCodeMsgPair& r);

	static bool fromjsonScannerSubscription(IB::IBScannerSubscription& r, const std::string& s);
	static std::string tojsonScannerSubscription(const IB::IBScannerSubscription& r);
	static bool parseScannerSubscription(IB::IBScannerSubscription& r, const std::string& s);
	static std::string serializeScannerSubscription(const IB::IBScannerSubscription& r);

	static bool fromjsonIBPBTagMsg(IB::IBPBTagMsg& r, const std::string& s);
	static std::string tojsonIBPBTagMsg(const IB::IBPBTagMsg& r);
	static bool parseIBPBTagMsg(IB::IBPBTagMsg& r, const std::string& s);
	static std::string serializeIBPBTagMsg(const IB::IBPBTagMsg& r);

	static bool fromjsonOrderConditionData(IB::IBOrderConditionData& r, const std::string& s);
	static std::string tojsonOrderConditionData(const IB::IBOrderConditionData& r);
	static bool parseOrderConditionData(IB::IBOrderConditionData& r, const std::string& s);
	static std::string serializeOrderConditionData(const IB::IBOrderConditionData& r);

	static bool fromjsonContractDetails(IB::IBContractDetails& r, const std::string& s);
	static std::string tojsonContractDetails(const IB::IBContractDetails& r);
	static bool parseContractDetails(IB::IBContractDetails& r, const std::string& s);
	static std::string serializeContractDetails(const IB::IBContractDetails& r);

	static bool fromjsonBarData(IB::IBBarData& r, const std::string& s);
	static std::string tojsonBarData(const IB::IBBarData& r);
	static bool parseBarData(IB::IBBarData& r, const std::string& s);
	static std::string serializeBarData(const IB::IBBarData& r);

	static bool fromjsonScanData(IB::IBScanData& r, const std::string& s);
	static std::string tojsonScanData(const IB::IBScanData& r);
	static bool parseScanData(IB::IBScanData& r, const std::string& s);
	static std::string serializeScanData(const IB::IBScanData& r);

	static bool fromjsonComboLeg(IB::IBComboLeg& r, const std::string& s);
	static std::string tojsonComboLeg(const IB::IBComboLeg& r);
	static bool parseComboLeg(IB::IBComboLeg& r, const std::string& s);
	static std::string serializeComboLeg(const IB::IBComboLeg& r);

	static bool fromjsonCommissionReport(IB::IBCommissionReport& r, const std::string& s);
	static std::string tojsonCommissionReport(const IB::IBCommissionReport& r);
	static bool parseCommissionReport(IB::IBCommissionReport& r, const std::string& s);
	static std::string serializeCommissionReport(const IB::IBCommissionReport& r);

	static bool fromjsonSoftDollarTier(IB::IBSoftDollarTier& r, const std::string& s);
	static std::string tojsonSoftDollarTier(const IB::IBSoftDollarTier& r);
	static bool parseSoftDollarTier(IB::IBSoftDollarTier& r, const std::string& s);
	static std::string serializeSoftDollarTier(const IB::IBSoftDollarTier& r);

	static bool fromjsonUnderComp(IB::IBUnderComp& r, const std::string& s);
	static std::string tojsonUnderComp(const IB::IBUnderComp& r);
	static bool parseUnderComp(IB::IBUnderComp& r, const std::string& s);
	static std::string serializeUnderComp(const IB::IBUnderComp& r);

	static bool fromjsonTagValue(IB::IBTagValue& r, const std::string& s);
	static std::string tojsonTagValue(const IB::IBTagValue& r);
	static bool parseTagValue(IB::IBTagValue& r, const std::string& s);
	static std::string serializeTagValue(const IB::IBTagValue& r);

	static bool fromjsonExecution(IB::IBExecution& r, const std::string& s);
	static std::string tojsonExecution(const IB::IBExecution& r);
	static bool parseExecution(IB::IBExecution& r, const std::string& s);
	static std::string serializeExecution(const IB::IBExecution& r);

	static bool fromjsonContract(IB::IBContract& r, const std::string& s);
	static std::string tojsonContract(const IB::IBContract& r);
	static bool parseContract(IB::IBContract& r, const std::string& s);
	static std::string serializeContract(const IB::IBContract& r);




}; //class IBUtil

}//namespace XT

#endif
