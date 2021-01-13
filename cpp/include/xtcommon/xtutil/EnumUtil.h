#pragma once
#ifndef XT_ENUMUTIL_H
#define XT_ENUMUTIL_H

/**
* \file EnumUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide help functions for enums.
*
* \description
*	Designed for use for all enums and their utilities.
*/

#include <assert.h>
#include <string>
#include <sstream>
#include <map>
#include "XTConfig.h"
#include "FIXEnum.pb.h"
#include "FIXData.pb.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
//#include "FIXData.h"
//#include "XTData.h"


namespace XT {

class XT_COMMON_API EnumUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	EnumUtil() {}

	/**
	* @brief copy constructor
	*/
	EnumUtil(const EnumUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	EnumUtil& operator=(const EnumUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~EnumUtil() {}

	///@}

public:

	/**
	* get display name of exchangetype
	*/
	static std::string getDisplayNameOfExchangeType(ExchangeType::enumtype et, DisplayLanguageType::enumtype dlt);


	/**
	* get display name of SecurityType
	*/
	static std::string getDisplayNameOfSecurityType(SecurityType::enumtype st, DisplayLanguageType::enumtype dlt);


protected:
	/** @name Static Variables
	* 
	*/
	///@{
	static const std::string s_EmptyString;
	///@}

	/** @name Helper Functions
	* 
	*/
	///@{

public:
	static const std::string& getEmptyString();


//protected:
//	static const char* m_FieldType_Names[];
//	static int m_FieldType_Values[];
//
//	static std::map<int, std::string> m_FieldType_ValuesToNames;
//	static std::map<std::string, int> m_FieldType_NamesToValues;
//
//public:
//	static int valueOf_FieldType(const std::string& s);
//	static const std::string& nameOf_FieldType(int i);
//	static bool hasValue_FieldType(int i);
//	static bool hasName_FieldType(const std::string& s);
//	static std::map<int, std::string>& map_FieldType_ValuesToNames();
//	static std::map<std::string, int>& map_FieldType_NamesToValues();

// 
//protected:
//	static const char* m_ExchID_Names[];
////	static int m_ExchangeType_Values[];
//
//	static std::map<int, std::string> m_ExchID_ValuesToNames;
//	static std::map<std::string, int> m_ExchID_NamesToValues;
//
//public:
//	static int valueOf_ExchID(const std::string& s);
//	static const std::string& nameOf_ExchID(int i);
//	static bool hasValue_ExchID(int i);
//	static bool hasName_ExchID(const std::string& s);
//	static std::map<int, std::string>& map_ExchID_ValuesToNames();
//	static std::map<std::string, int>& map_ExchID_NamesToValues();
//
//
//
// 
/////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//protected:
//	static const char* m_MessageType_Names[];
//	static int m_MessageType_Values[];
//
//	static std::map<int, std::string> m_MessageType_ValuesToNames;
//	static std::map<std::string, int> m_MessageType_NamesToValues;
//
//public:
//	static int valueOf_MessageType(const std::string& s);
//	static const std::string& nameOf_MessageType(int i);
//	static bool hasValue_MessageType(int i);
//	static bool hasName_MessageType(const std::string& s);
//	static std::map<int, std::string>& map_MessageType_ValuesToNames();
//	static std::map<std::string, int>& map_MessageType_NamesToValues();
//
//
//protected:
//	static const char* m_ProductType_Names[];
//	static int m_ProductType_Values[];
//
//	static std::map<int, std::string> m_ProductType_ValuesToNames;
//	static std::map<std::string, int> m_ProductType_NamesToValues;
//
//public:
//	static int valueOf_ProductType(const std::string& s);
//	static const std::string& nameOf_ProductType(int i);
//	static bool hasValue_ProductType(int i);
//	static bool hasName_ProductType(const std::string& s);
//	static std::map<int, std::string>& map_ProductType_ValuesToNames();
//	static std::map<std::string, int>& map_ProductType_NamesToValues();
//
//
//protected:
//	static const char* m_SecurityType_Names[];
//	static int m_SecurityType_Values[];
//
//	static std::map<int, std::string> m_SecurityType_ValuesToNames;
//	static std::map<std::string, int> m_SecurityType_NamesToValues;
//
//public:
//	static int valueOf_SecurityType(const std::string& s);
//	static const std::string& nameOf_SecurityType(int i);
//	static bool hasValue_SecurityType(int i);
//	static bool hasName_SecurityType(const std::string& s);
//	static std::map<int, std::string>& map_SecurityType_ValuesToNames();
//	static std::map<std::string, int>& map_SecurityType_NamesToValues();
//
//
//
//
//
//
////////////////////////////////////////////////////////////////////////
//
//
//
//
//protected:
//	static const char* m_AccountTypeMask_Names[];
//	static int m_AccountTypeMask_Values[];
//
//	static std::map<int, std::string> m_AccountTypeMask_ValuesToNames;
//	static std::map<std::string, int> m_AccountTypeMask_NamesToValues;
//
//public:
//	static int valueOf_AccountTypeMask(const std::string& s);
//	static const std::string& nameOf_AccountTypeMask(int i);
//	static bool hasValue_AccountTypeMask(int i);
//	static bool hasName_AccountTypeMask(const std::string& s);
//	static std::map<int, std::string>& map_AccountTypeMask_ValuesToNames();
//	static std::map<std::string, int>& map_AccountTypeMask_NamesToValues();
//
//
//protected:
//	static const char* m_AsyncTaskStatus_Names[];
//	static int m_AsyncTaskStatus_Values[];
//
//	static std::map<int, std::string> m_AsyncTaskStatus_ValuesToNames;
//	static std::map<std::string, int> m_AsyncTaskStatus_NamesToValues;
//
//public:
//	static int valueOf_AsyncTaskStatus(const std::string& s);
//	static const std::string& nameOf_AsyncTaskStatus(int i);
//	static bool hasValue_AsyncTaskStatus(int i);
//	static bool hasName_AsyncTaskStatus(const std::string& s);
//	static std::map<int, std::string>& map_AsyncTaskStatus_ValuesToNames();
//	static std::map<std::string, int>& map_AsyncTaskStatus_NamesToValues();
//
//
//protected:
//	static const char* m_BrokerApiType_Names[];
//	static int m_BrokerApiType_Values[];
//
//	static std::map<int, std::string> m_BrokerApiType_ValuesToNames;
//	static std::map<std::string, int> m_BrokerApiType_NamesToValues;
//
//public:
//	static int valueOf_BrokerApiType(const std::string& s);
//	static const std::string& nameOf_BrokerApiType(int i);
//	static bool hasValue_BrokerApiType(int i);
//	static bool hasName_BrokerApiType(const std::string& s);
//	static std::map<int, std::string>& map_BrokerApiType_ValuesToNames();
//	static std::map<std::string, int>& map_BrokerApiType_NamesToValues();
//
//
//protected:
//	static const char* m_ExchangeType_Names[];
//	static int m_ExchangeType_Values[];
//
//	static std::map<int, std::string> m_ExchangeType_ValuesToNames;
//	static std::map<std::string, int> m_ExchangeType_NamesToValues;
//
//public:
//	static int valueOf_ExchangeType(const std::string& s);
//	static const std::string& nameOf_ExchangeType(int i);
//	static bool hasValue_ExchangeType(int i);
//	static bool hasName_ExchangeType(const std::string& s);
//	static std::map<int, std::string>& map_ExchangeType_ValuesToNames();
//	static std::map<std::string, int>& map_ExchangeType_NamesToValues();
//
//
//protected:
//	static const char* m_BuySellType_Names[];
//	static int m_BuySellType_Values[];
//
//	static std::map<int, std::string> m_BuySellType_ValuesToNames;
//	static std::map<std::string, int> m_BuySellType_NamesToValues;
//
//public:
//	static int valueOf_BuySellType(const std::string& s);
//	static const std::string& nameOf_BuySellType(int i);
//	static bool hasValue_BuySellType(int i);
//	static bool hasName_BuySellType(const std::string& s);
//	static std::map<int, std::string>& map_BuySellType_ValuesToNames();
//	static std::map<std::string, int>& map_BuySellType_NamesToValues();
//
//
//protected:
//	static const char* m_InstrumentCommissionRateType_Names[];
//	static int m_InstrumentCommissionRateType_Values[];
//
//	static std::map<int, std::string> m_InstrumentCommissionRateType_ValuesToNames;
//	static std::map<std::string, int> m_InstrumentCommissionRateType_NamesToValues;
//
//public:
//	static int valueOf_InstrumentCommissionRateType(const std::string& s);
//	static const std::string& nameOf_InstrumentCommissionRateType(int i);
//	static bool hasValue_InstrumentCommissionRateType(int i);
//	static bool hasName_InstrumentCommissionRateType(const std::string& s);
//	static std::map<int, std::string>& map_InstrumentCommissionRateType_ValuesToNames();
//	static std::map<std::string, int>& map_InstrumentCommissionRateType_NamesToValues();
//
//
//protected:
//	static const char* m_RollingType_Names[];
//	static int m_RollingType_Values[];
//
//	static std::map<int, std::string> m_RollingType_ValuesToNames;
//	static std::map<std::string, int> m_RollingType_NamesToValues;
//
//public:
//	static int valueOf_RollingType(const std::string& s);
//	static const std::string& nameOf_RollingType(int i);
//	static bool hasValue_RollingType(int i);
//	static bool hasName_RollingType(const std::string& s);
//	static std::map<int, std::string>& map_RollingType_ValuesToNames();
//	static std::map<std::string, int>& map_RollingType_NamesToValues();
//
//
//protected:
//	static const char* m_CallPutType_Names[];
//	static int m_CallPutType_Values[];
//
//	static std::map<int, std::string> m_CallPutType_ValuesToNames;
//	static std::map<std::string, int> m_CallPutType_NamesToValues;
//
//public:
//	static int valueOf_CallPutType(const std::string& s);
//	static const std::string& nameOf_CallPutType(int i);
//	static bool hasValue_CallPutType(int i);
//	static bool hasName_CallPutType(const std::string& s);
//	static std::map<int, std::string>& map_CallPutType_ValuesToNames();
//	static std::map<std::string, int>& map_CallPutType_NamesToValues();
//
//
//protected:
//	static const char* m_OptionExerciseStyle_Names[];
//	static int m_OptionExerciseStyle_Values[];
//
//	static std::map<int, std::string> m_OptionExerciseStyle_ValuesToNames;
//	static std::map<std::string, int> m_OptionExerciseStyle_NamesToValues;
//
//public:
//	static int valueOf_OptionExerciseStyle(const std::string& s);
//	static const std::string& nameOf_OptionExerciseStyle(int i);
//	static bool hasValue_OptionExerciseStyle(int i);
//	static bool hasName_OptionExerciseStyle(const std::string& s);
//	static std::map<int, std::string>& map_OptionExerciseStyle_ValuesToNames();
//	static std::map<std::string, int>& map_OptionExerciseStyle_NamesToValues();
//
//
//protected:
//	static const char* m_OptionCalcType_Names[];
//	static int m_OptionCalcType_Values[];
//
//	static std::map<int, std::string> m_OptionCalcType_ValuesToNames;
//	static std::map<std::string, int> m_OptionCalcType_NamesToValues;
//
//public:
//	static int valueOf_OptionCalcType(const std::string& s);
//	static const std::string& nameOf_OptionCalcType(int i);
//	static bool hasValue_OptionCalcType(int i);
//	static bool hasName_OptionCalcType(const std::string& s);
//	static std::map<int, std::string>& map_OptionCalcType_ValuesToNames();
//	static std::map<std::string, int>& map_OptionCalcType_NamesToValues();
//
//
//protected:
//	static const char* m_OptionPxMethod_Names[];
//	static int m_OptionPxMethod_Values[];
//
//	static std::map<int, std::string> m_OptionPxMethod_ValuesToNames;
//	static std::map<std::string, int> m_OptionPxMethod_NamesToValues;
//
//public:
//	static int valueOf_OptionPxMethod(const std::string& s);
//	static const std::string& nameOf_OptionPxMethod(int i);
//	static bool hasValue_OptionPxMethod(int i);
//	static bool hasName_OptionPxMethod(const std::string& s);
//	static std::map<int, std::string>& map_OptionPxMethod_ValuesToNames();
//	static std::map<std::string, int>& map_OptionPxMethod_NamesToValues();
//
//
//protected:
//	static const char* m_DateTimeType_Names[];
//	static int m_DateTimeType_Values[];
//
//	static std::map<int, std::string> m_DateTimeType_ValuesToNames;
//	static std::map<std::string, int> m_DateTimeType_NamesToValues;
//
//public:
//	static int valueOf_DateTimeType(const std::string& s);
//	static const std::string& nameOf_DateTimeType(int i);
//	static bool hasValue_DateTimeType(int i);
//	static bool hasName_DateTimeType(const std::string& s);
//	static std::map<int, std::string>& map_DateTimeType_ValuesToNames();
//	static std::map<std::string, int>& map_DateTimeType_NamesToValues();
//
//
//protected:
//	static const char* m_DataType_Names[];
//	static int m_DataType_Values[];
//
//	static std::map<int, std::string> m_DataType_ValuesToNames;
//	static std::map<std::string, int> m_DataType_NamesToValues;
//
//public:
//	static int valueOf_DataType(const std::string& s);
//	static const std::string& nameOf_DataType(int i);
//	static bool hasValue_DataType(int i);
//	static bool hasName_DataType(const std::string& s);
//	static std::map<int, std::string>& map_DataType_ValuesToNames();
//	static std::map<std::string, int>& map_DataType_NamesToValues();
//
//
//protected:
//	static const char* m_DisplayLanguageType_Names[];
//	static int m_DisplayLanguageType_Values[];
//
//	static std::map<int, std::string> m_DisplayLanguageType_ValuesToNames;
//	static std::map<std::string, int> m_DisplayLanguageType_NamesToValues;
//
//public:
//	static int valueOf_DisplayLanguageType(const std::string& s);
//	static const std::string& nameOf_DisplayLanguageType(int i);
//	static bool hasValue_DisplayLanguageType(int i);
//	static bool hasName_DisplayLanguageType(const std::string& s);
//	static std::map<int, std::string>& map_DisplayLanguageType_ValuesToNames();
//	static std::map<std::string, int>& map_DisplayLanguageType_NamesToValues();
//
//
//protected:
//	static const char* m_OpenCloseFlag_Names[];
//	static int m_OpenCloseFlag_Values[];
//
//	static std::map<int, std::string> m_OpenCloseFlag_ValuesToNames;
//	static std::map<std::string, int> m_OpenCloseFlag_NamesToValues;
//
//public:
//	static int valueOf_OpenCloseFlag(const std::string& s);
//	static const std::string& nameOf_OpenCloseFlag(int i);
//	static bool hasValue_OpenCloseFlag(int i);
//	static bool hasName_OpenCloseFlag(const std::string& s);
//	static std::map<int, std::string>& map_OpenCloseFlag_ValuesToNames();
//	static std::map<std::string, int>& map_OpenCloseFlag_NamesToValues();
//
//
//protected:
//	static const char* m_OrderQuoteTsType_Names[];
//	static int m_OrderQuoteTsType_Values[];
//
//	static std::map<int, std::string> m_OrderQuoteTsType_ValuesToNames;
//	static std::map<std::string, int> m_OrderQuoteTsType_NamesToValues;
//
//public:
//	static int valueOf_OrderQuoteTsType(const std::string& s);
//	static const std::string& nameOf_OrderQuoteTsType(int i);
//	static bool hasValue_OrderQuoteTsType(int i);
//	static bool hasName_OrderQuoteTsType(const std::string& s);
//	static std::map<int, std::string>& map_OrderQuoteTsType_ValuesToNames();
//	static std::map<std::string, int>& map_OrderQuoteTsType_NamesToValues();
//
//
//protected:
//	static const char* m_OrderQuoteReasonType_Names[];
//	static int m_OrderQuoteReasonType_Values[];
//
//	static std::map<int, std::string> m_OrderQuoteReasonType_ValuesToNames;
//	static std::map<std::string, int> m_OrderQuoteReasonType_NamesToValues;
//
//public:
//	static int valueOf_OrderQuoteReasonType(const std::string& s);
//	static const std::string& nameOf_OrderQuoteReasonType(int i);
//	static bool hasValue_OrderQuoteReasonType(int i);
//	static bool hasName_OrderQuoteReasonType(const std::string& s);
//	static std::map<int, std::string>& map_OrderQuoteReasonType_ValuesToNames();
//	static std::map<std::string, int>& map_OrderQuoteReasonType_NamesToValues();
//
//
//protected:
//	static const char* m_AggressiveType_Names[];
//	static int m_AggressiveType_Values[];
//
//	static std::map<int, std::string> m_AggressiveType_ValuesToNames;
//	static std::map<std::string, int> m_AggressiveType_NamesToValues;
//
//public:
//	static int valueOf_AggressiveType(const std::string& s);
//	static const std::string& nameOf_AggressiveType(int i);
//	static bool hasValue_AggressiveType(int i);
//	static bool hasName_AggressiveType(const std::string& s);
//	static std::map<int, std::string>& map_AggressiveType_ValuesToNames();
//	static std::map<std::string, int>& map_AggressiveType_NamesToValues();
//
//
//protected:
//	static const char* m_TagType_Names[];
//	static int m_TagType_Values[];
//
//	static std::map<int, std::string> m_TagType_ValuesToNames;
//	static std::map<std::string, int> m_TagType_NamesToValues;
//
//public:
//	static int valueOf_TagType(const std::string& s);
//	static const std::string& nameOf_TagType(int i);
//	static bool hasValue_TagType(int i);
//	static bool hasName_TagType(const std::string& s);
//	static std::map<int, std::string>& map_TagType_ValuesToNames();
//	static std::map<std::string, int>& map_TagType_NamesToValues();
//
//
//protected:
//	static const char* m_MktRegimeType_Names[];
//	static int m_MktRegimeType_Values[];
//
//	static std::map<int, std::string> m_MktRegimeType_ValuesToNames;
//	static std::map<std::string, int> m_MktRegimeType_NamesToValues;
//
//public:
//	static int valueOf_MktRegimeType(const std::string& s);
//	static const std::string& nameOf_MktRegimeType(int i);
//	static bool hasValue_MktRegimeType(int i);
//	static bool hasName_MktRegimeType(const std::string& s);
//	static std::map<int, std::string>& map_MktRegimeType_ValuesToNames();
//	static std::map<std::string, int>& map_MktRegimeType_NamesToValues();
//
//
//protected:
//	static const char* m_TrendingOrRangingType_Names[];
//	static int m_TrendingOrRangingType_Values[];
//
//	static std::map<int, std::string> m_TrendingOrRangingType_ValuesToNames;
//	static std::map<std::string, int> m_TrendingOrRangingType_NamesToValues;
//
//public:
//	static int valueOf_TrendingOrRangingType(const std::string& s);
//	static const std::string& nameOf_TrendingOrRangingType(int i);
//	static bool hasValue_TrendingOrRangingType(int i);
//	static bool hasName_TrendingOrRangingType(const std::string& s);
//	static std::map<int, std::string>& map_TrendingOrRangingType_ValuesToNames();
//	static std::map<std::string, int>& map_TrendingOrRangingType_NamesToValues();
//
//
//protected:
//	static const char* m_TrdSigType_Names[];
//	static int m_TrdSigType_Values[];
//
//	static std::map<int, std::string> m_TrdSigType_ValuesToNames;
//	static std::map<std::string, int> m_TrdSigType_NamesToValues;
//
//public:
//	static int valueOf_TrdSigType(const std::string& s);
//	static const std::string& nameOf_TrdSigType(int i);
//	static bool hasValue_TrdSigType(int i);
//	static bool hasName_TrdSigType(const std::string& s);
//	static std::map<int, std::string>& map_TrdSigType_ValuesToNames();
//	static std::map<std::string, int>& map_TrdSigType_NamesToValues();
//
//
//protected:
//	static const char* m_TrdStatType_Names[];
//	static int m_TrdStatType_Values[];
//
//	static std::map<int, std::string> m_TrdStatType_ValuesToNames;
//	static std::map<std::string, int> m_TrdStatType_NamesToValues;
//
//public:
//	static int valueOf_TrdStatType(const std::string& s);
//	static const std::string& nameOf_TrdStatType(int i);
//	static bool hasValue_TrdStatType(int i);
//	static bool hasName_TrdStatType(const std::string& s);
//	static std::map<int, std::string>& map_TrdStatType_ValuesToNames();
//	static std::map<std::string, int>& map_TrdStatType_NamesToValues();
//
//
//protected:
//	static const char* m_CrossAboveBelowType_Names[];
//	static int m_CrossAboveBelowType_Values[];
//
//	static std::map<int, std::string> m_CrossAboveBelowType_ValuesToNames;
//	static std::map<std::string, int> m_CrossAboveBelowType_NamesToValues;
//
//public:
//	static int valueOf_CrossAboveBelowType(const std::string& s);
//	static const std::string& nameOf_CrossAboveBelowType(int i);
//	static bool hasValue_CrossAboveBelowType(int i);
//	static bool hasName_CrossAboveBelowType(const std::string& s);
//	static std::map<int, std::string>& map_CrossAboveBelowType_ValuesToNames();
//	static std::map<std::string, int>& map_CrossAboveBelowType_NamesToValues();
//
//
//protected:
//	static const char* m_TAType_Names[];
//	static int m_TAType_Values[];
//
//	static std::map<int, std::string> m_TAType_ValuesToNames;
//	static std::map<std::string, int> m_TAType_NamesToValues;
//
//public:
//	static int valueOf_TAType(const std::string& s);
//	static const std::string& nameOf_TAType(int i);
//	static bool hasValue_TAType(int i);
//	static bool hasName_TAType(const std::string& s);
//	static std::map<int, std::string>& map_TAType_ValuesToNames();
//	static std::map<std::string, int>& map_TAType_NamesToValues();
//
//
//protected:
//	static const char* m_YahooQuoteType_Names[];
//	static int m_YahooQuoteType_Values[];
//
//	static std::map<int, std::string> m_YahooQuoteType_ValuesToNames;
//	static std::map<std::string, int> m_YahooQuoteType_NamesToValues;
//
//public:
//	static int valueOf_YahooQuoteType(const std::string& s);
//	static const std::string& nameOf_YahooQuoteType(int i);
//	static bool hasValue_YahooQuoteType(int i);
//	static bool hasName_YahooQuoteType(const std::string& s);
//	static std::map<int, std::string>& map_YahooQuoteType_ValuesToNames();
//	static std::map<std::string, int>& map_YahooQuoteType_NamesToValues();
//
//
//protected:
//	static const char* m_YahooRangeType_Names[];
//	static int m_YahooRangeType_Values[];
//
//	static std::map<int, std::string> m_YahooRangeType_ValuesToNames;
//	static std::map<std::string, int> m_YahooRangeType_NamesToValues;
//
//public:
//	static int valueOf_YahooRangeType(const std::string& s);
//	static const std::string& nameOf_YahooRangeType(int i);
//	static bool hasValue_YahooRangeType(int i);
//	static bool hasName_YahooRangeType(const std::string& s);
//	static std::map<int, std::string>& map_YahooRangeType_ValuesToNames();
//	static std::map<std::string, int>& map_YahooRangeType_NamesToValues();
//





 
 
///////////////////////////////
 

 
	///@}
 
 




}; //end class EnumUtil
}//end namespace XT

#endif
