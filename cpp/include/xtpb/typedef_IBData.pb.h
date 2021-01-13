#pragma once
#include "IBData.pb.h" 
#include "safe_ptr.h"

//////typedef for IBData
namespace IB {
#if defined(USE_BOOST_SHARED_PTR)
#include <boost/smart_ptr.hpp>
	typedef boost::shared_ptr<IBTagValue> IBTagValuePtr;
	typedef boost::shared_ptr<IBCodeMsgPair> IBCodeMsgPairPtr;
	typedef boost::shared_ptr<IBBarData> IBBarDataPtr;
	typedef boost::shared_ptr<IBComboLeg> IBComboLegPtr;
	typedef boost::shared_ptr<IBSoftDollarTier> IBSoftDollarTierPtr;
	typedef boost::shared_ptr<IBUnderComp> IBUnderCompPtr;
	typedef boost::shared_ptr<IBContract> IBContractPtr;
	typedef boost::shared_ptr<IBContractDetails> IBContractDetailsPtr;
	typedef boost::shared_ptr<IBScanData> IBScanDataPtr;
	typedef boost::shared_ptr<IBCommissionReport> IBCommissionReportPtr;
	typedef boost::shared_ptr<IBExecution> IBExecutionPtr;
	typedef boost::shared_ptr<IBExecutionFilter> IBExecutionFilterPtr;
	typedef boost::shared_ptr<IBOrderState> IBOrderStatePtr;
	typedef boost::shared_ptr<IBScannerSubscription> IBScannerSubscriptionPtr;
	typedef boost::shared_ptr<IBOrderComboLeg> IBOrderComboLegPtr;
	typedef boost::shared_ptr<IBOrderConditionData> IBOrderConditionDataPtr;
	typedef boost::shared_ptr<IBOrder> IBOrderPtr;
	typedef boost::shared_ptr<IBPBTagMsg> IBPBTagMsgPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef sf::contfree_safe_ptr<IBTagValue> IBTagValuePtr;
	typedef sf::contfree_safe_ptr<IBCodeMsgPair> IBCodeMsgPairPtr;
	typedef sf::contfree_safe_ptr<IBBarData> IBBarDataPtr;
	typedef sf::contfree_safe_ptr<IBComboLeg> IBComboLegPtr;
	typedef sf::contfree_safe_ptr<IBSoftDollarTier> IBSoftDollarTierPtr;
	typedef sf::contfree_safe_ptr<IBUnderComp> IBUnderCompPtr;
	typedef sf::contfree_safe_ptr<IBContract> IBContractPtr;
	typedef sf::contfree_safe_ptr<IBContractDetails> IBContractDetailsPtr;
	typedef sf::contfree_safe_ptr<IBScanData> IBScanDataPtr;
	typedef sf::contfree_safe_ptr<IBCommissionReport> IBCommissionReportPtr;
	typedef sf::contfree_safe_ptr<IBExecution> IBExecutionPtr;
	typedef sf::contfree_safe_ptr<IBExecutionFilter> IBExecutionFilterPtr;
	typedef sf::contfree_safe_ptr<IBOrderState> IBOrderStatePtr;
	typedef sf::contfree_safe_ptr<IBScannerSubscription> IBScannerSubscriptionPtr;
	typedef sf::contfree_safe_ptr<IBOrderComboLeg> IBOrderComboLegPtr;
	typedef sf::contfree_safe_ptr<IBOrderConditionData> IBOrderConditionDataPtr;
	typedef sf::contfree_safe_ptr<IBOrder> IBOrderPtr;
	typedef sf::contfree_safe_ptr<IBPBTagMsg> IBPBTagMsgPtr;

#elif defined(USE_SAFE_PTR)

	typedef sf::safe_ptr<IBTagValue> IBTagValuePtr;
	typedef sf::safe_ptr<IBCodeMsgPair> IBCodeMsgPairPtr;
	typedef sf::safe_ptr<IBBarData> IBBarDataPtr;
	typedef sf::safe_ptr<IBComboLeg> IBComboLegPtr;
	typedef sf::safe_ptr<IBSoftDollarTier> IBSoftDollarTierPtr;
	typedef sf::safe_ptr<IBUnderComp> IBUnderCompPtr;
	typedef sf::safe_ptr<IBContract> IBContractPtr;
	typedef sf::safe_ptr<IBContractDetails> IBContractDetailsPtr;
	typedef sf::safe_ptr<IBScanData> IBScanDataPtr;
	typedef sf::safe_ptr<IBCommissionReport> IBCommissionReportPtr;
	typedef sf::safe_ptr<IBExecution> IBExecutionPtr;
	typedef sf::safe_ptr<IBExecutionFilter> IBExecutionFilterPtr;
	typedef sf::safe_ptr<IBOrderState> IBOrderStatePtr;
	typedef sf::safe_ptr<IBScannerSubscription> IBScannerSubscriptionPtr;
	typedef sf::safe_ptr<IBOrderComboLeg> IBOrderComboLegPtr;
	typedef sf::safe_ptr<IBOrderConditionData> IBOrderConditionDataPtr;
	typedef sf::safe_ptr<IBOrder> IBOrderPtr;
	typedef sf::safe_ptr<IBPBTagMsg> IBPBTagMsgPtr;

#else

	typedef sf::contfree_safe_ptr<IBTagValue> IBTagValuePtr;
	typedef sf::contfree_safe_ptr<IBCodeMsgPair> IBCodeMsgPairPtr;
	typedef sf::contfree_safe_ptr<IBBarData> IBBarDataPtr;
	typedef sf::contfree_safe_ptr<IBComboLeg> IBComboLegPtr;
	typedef sf::contfree_safe_ptr<IBSoftDollarTier> IBSoftDollarTierPtr;
	typedef sf::contfree_safe_ptr<IBUnderComp> IBUnderCompPtr;
	typedef sf::contfree_safe_ptr<IBContract> IBContractPtr;
	typedef sf::contfree_safe_ptr<IBContractDetails> IBContractDetailsPtr;
	typedef sf::contfree_safe_ptr<IBScanData> IBScanDataPtr;
	typedef sf::contfree_safe_ptr<IBCommissionReport> IBCommissionReportPtr;
	typedef sf::contfree_safe_ptr<IBExecution> IBExecutionPtr;
	typedef sf::contfree_safe_ptr<IBExecutionFilter> IBExecutionFilterPtr;
	typedef sf::contfree_safe_ptr<IBOrderState> IBOrderStatePtr;
	typedef sf::contfree_safe_ptr<IBScannerSubscription> IBScannerSubscriptionPtr;
	typedef sf::contfree_safe_ptr<IBOrderComboLeg> IBOrderComboLegPtr;
	typedef sf::contfree_safe_ptr<IBOrderConditionData> IBOrderConditionDataPtr;
	typedef sf::contfree_safe_ptr<IBOrder> IBOrderPtr;
	typedef sf::contfree_safe_ptr<IBPBTagMsg> IBPBTagMsgPtr;
#endif


	typedef sf::safe_ptr<IBTagValue> IBTagValueSafePtr;
	typedef sf::safe_ptr<IBCodeMsgPair> IBCodeMsgPairSafePtr;
	typedef sf::safe_ptr<IBBarData> IBBarDataSafePtr;
	typedef sf::safe_ptr<IBComboLeg> IBComboLegSafePtr;
	typedef sf::safe_ptr<IBSoftDollarTier> IBSoftDollarTierSafePtr;
	typedef sf::safe_ptr<IBUnderComp> IBUnderCompSafePtr;
	typedef sf::safe_ptr<IBContract> IBContractSafePtr;
	typedef sf::safe_ptr<IBContractDetails> IBContractDetailsSafePtr;
	typedef sf::safe_ptr<IBScanData> IBScanDataSafePtr;
	typedef sf::safe_ptr<IBCommissionReport> IBCommissionReportSafePtr;
	typedef sf::safe_ptr<IBExecution> IBExecutionSafePtr;
	typedef sf::safe_ptr<IBExecutionFilter> IBExecutionFilterSafePtr;
	typedef sf::safe_ptr<IBOrderState> IBOrderStateSafePtr;
	typedef sf::safe_ptr<IBScannerSubscription> IBScannerSubscriptionSafePtr;
	typedef sf::safe_ptr<IBOrderComboLeg> IBOrderComboLegSafePtr;
	typedef sf::safe_ptr<IBOrderConditionData> IBOrderConditionDataSafePtr;
	typedef sf::safe_ptr<IBOrder> IBOrderSafePtr;
	typedef sf::safe_ptr<IBPBTagMsg> IBPBTagMsgSafePtr;

	typedef sf::contfree_safe_ptr<IBTagValue> IBTagValueContFreePtr;
	typedef sf::contfree_safe_ptr<IBCodeMsgPair> IBCodeMsgPairContFreePtr;
	typedef sf::contfree_safe_ptr<IBBarData> IBBarDataContFreePtr;
	typedef sf::contfree_safe_ptr<IBComboLeg> IBComboLegContFreePtr;
	typedef sf::contfree_safe_ptr<IBSoftDollarTier> IBSoftDollarTierContFreePtr;
	typedef sf::contfree_safe_ptr<IBUnderComp> IBUnderCompContFreePtr;
	typedef sf::contfree_safe_ptr<IBContract> IBContractContFreePtr;
	typedef sf::contfree_safe_ptr<IBContractDetails> IBContractDetailsContFreePtr;
	typedef sf::contfree_safe_ptr<IBScanData> IBScanDataContFreePtr;
	typedef sf::contfree_safe_ptr<IBCommissionReport> IBCommissionReportContFreePtr;
	typedef sf::contfree_safe_ptr<IBExecution> IBExecutionContFreePtr;
	typedef sf::contfree_safe_ptr<IBExecutionFilter> IBExecutionFilterContFreePtr;
	typedef sf::contfree_safe_ptr<IBOrderState> IBOrderStateContFreePtr;
	typedef sf::contfree_safe_ptr<IBScannerSubscription> IBScannerSubscriptionContFreePtr;
	typedef sf::contfree_safe_ptr<IBOrderComboLeg> IBOrderComboLegContFreePtr;
	typedef sf::contfree_safe_ptr<IBOrderConditionData> IBOrderConditionDataContFreePtr;
	typedef sf::contfree_safe_ptr<IBOrder> IBOrderContFreePtr;
	typedef sf::contfree_safe_ptr<IBPBTagMsg> IBPBTagMsgContFreePtr;
}//namespace IB
//////end typedef for IBData

