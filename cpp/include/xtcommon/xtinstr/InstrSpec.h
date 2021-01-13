#pragma once
#ifndef XT_INSTRSPEC_H
#define XT_INSTRSPEC_H

/**
* \file InstrSpec.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for instrument specification.
*
* \description
*	Designed for specific information of an instrument.
*/

#include <stdint.h>
#include <string>
#include <sstream>
#include <math.h>

#include <set>

#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"

#include "Util.h"
#include "PBUtil.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"


#include "TagDataWrapper.h"
#include "EnumUtil.h"
#include "EnumHelper.h"

namespace XT
{
	class InstrSpec;
	//////typedef for InstrSpec
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<InstrSpec> InstrSpecPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<InstrSpec> InstrSpecPtr;
//	typedef sf::contfree_safe_ptr<InstrSpec> InstrSpecPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<InstrSpec> InstrSpecPtr;

#else

	typedef ::boost::shared_ptr<InstrSpec> InstrSpecPtr;
#endif


	typedef ::sf::safe_ptr<InstrSpec> InstrSpecSafePtr;

	typedef sf::contfree_safe_ptr<InstrSpec> InstrSpecContFreePtr;
	//////end typedef for InstrSpec

class XT_COMMON_API InstrSpec
{

public:


	/** 
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	InstrSpec();

	/**
	* @brief default copy constructor
	*/
	InstrSpec(const InstrSpec& from) = default;

	/**
	* @brief default copy assignment
	*/
	InstrSpec& operator=(const InstrSpec& from) = default;

	/**
	* @brief destructor
	*/
	virtual ~InstrSpec();

	/**
	* @brief initialization
	*/
	void init();

	/**
	* @brief is valid or not
	*
	* @return if specification is valid or not
	*/
	bool isValid();

	///@}


	/**
	* @name Price Converter
	* functions for converting between double price and int64_t price
	*/
	///@{
	/**
	* @brief convert int64_t price to double price
	* 
	* @param intPx as int64_t price
	*
	* @reutnr double price
	*/
	double int64ToDouble(int64_t intPx);
	/**
	* @brief convert double price to int64_t price
	*
	* @param px as double price
	*
	* @return int64_t price
	*/
	int64_t doubleToInt64(double px) ;
	///@}

	/** 
	* @name Data Pointer
	*/
	///@{
	/**
	* @brief get data pointer
	*
	* @return data
	*/
	InstrSpecDataPtr& data();
//	TagDataWrapperPtr& getData();

 

	///@}

	/** 
	* @name Getters and Setters
	*/
	///@{
	/**
	* @brief get InstrID
	*
	* @return instrid
	*/
	const std::string& getInstrID();
	/**
	* @brief set InstrID
	*
	* @param v as instrid
	*/
	void setInstrID(const std::string& v);

	/**
	* @brief get ExchID
	*
	* @return exchid
	*/
	const std::string& getExchID();
	/**
	* @brief set ExchID
	*
	* @param v as exchid
	*/
	void setExchID(const std::string& v);

	/**
	* @brief get ExchangeType
	*
	* @return exchange type
	*/
	ExchangeType::enumtype getExchangeType();

	/**
	* @brief get ExchangeType int value
	*
	* @return exchange type int value
	*/
	int getExchangeTypeInt();

	/**
	* @brief set ExchangeType
	*
	* @param et as exchange type
	*/
	void setExchangeType(ExchangeType::enumtype et);

	/**
	* @brief set ExchangeType int value
	*
	* @param i as ExchangeType int value
	*/
	void setExchangeTypeInt(int i);

	/**
	* @brief get ProductID
	*
	* @return product id
	*/
	const std::string& getProductID();
	/**
	* @brief set ProductID
	*
	* @param v as product id
	*/
	void setProductID(const std::string& v);

	/**
	* @brief get SecurityType
	*
	* @return security type
	*/
	XT::SecurityType::enumtype getSecurityType();

	/**
	* @brief get SecurityType int value
	*
	* @return security type int value
	*/
	int getSecurityTypeInt();

	/**
	* @brief get name of SecurityType
	*
	* @return security type name
	*/
	const std::string& getSecurityTypeName();

	/**
	* @brief set SecurityType int value
	*
	* @param i as security type int value
	*/
	void setSecurityTypeInt(int i);

	/**
	* @brief set SecurityType
	*
	* @param i as security type
	*/
	void setSecurityType(SecurityType::enumtype et);

	/**
	* @brief set security type name
	*
	* @param v as security type name
	*/
	void setSecurityTypeName(const std::string& v);

	/**
	* @brief get PriceTick
	*
	* @return price tick
	*/
	double getPriceTick();
	/**
	* @brief set PriceTick
	*
	* @param d as price tick
	*/
	void setPriceTick(double d);

	/**
	* @brief get ContractMultiplier
	*
	* @return contract multiplier
	*/
	double getContractMultiplier();
	/**
	* @brief set ContractMultiplier
	*
	* @param d as contract multiplier
	*/
	void setContractMultiplier(double d);

	/**
	* @brief get PxPointValue
	*
	* @return price point value
	*/
	double getPxPointValue();
	/**
	* @brief get TickInt64Px
	*
	* @return int64_t price tick
	*/
	int64_t getTickInt64Px();
	/**
	* @brief get Int64PxPointValue
	*
	* @return int64_t price point value
	*/
	double getInt64PxPointValue();
	
	/**
	* @brief get StrikePrice
	*
	* @return strike price
	*/
	double getStrikePrice();
	/**
	* @brief set StrikePrice
	*
	* @return d as strike price
	*/
	void setStrikePrice(double d);

	/**
	* @brief get UnderlyingMultiple
	*
	* @retrun underlying multiple
	*/
	double getUnderlyingMultiple();
	/**
	* @brief set UnderlyingMultiple
	*
	* @param d as underlyng multiple
	*/
	void setUnderlyingMultiple(double d);

	/**
	* @brief get UnderlyingProduct
	*
	* @return underlying product
	*/
	const std::string& getUnderlyingProduct();
	/**
	* @brief set UnderlyingProduct
	*
	* @param s as underlying product
	*/
	void setUnderlyingProduct(const std::string& s);

	///**
	//* @brief get ExpireDate
	//*
	//* @return expire date string
	//*/
	//const std::string& getExpireDate();
	///**
	//* @brief set ExpireDate
	//*
	//* @param s as expire date string
	//*/
	//void setExpireDate(const std::string& s);
	/**
	* @brief get ExpireIntDate
	*
	* @return expire int date
	*/
	int32_t getExpireIntDate();

	/**
	* @brief set expireintdate
	*
	* @param i as expire int date
	*/
	void setExpireIntDate(int i);

	/**
	* @brief get ListIntDate
	*
	* @return list int date
	*/
	int getListIntDate();

	/**
	* @brief set ListIntDate
	*
	* @param i as list int date
	*/
	void setListIntDate(int i);

	/**
	* @brief get CallPutType
	*
	* @return call put type
	*/
	XT::CallPutType::enumtype getCallPutType();

	/**
	* @brief get CallPutType int value
	*
	* @return call put type int value
	*/
	int getCallPutTypeInt();

	/**
	* @brief get name of CallPutType 
	*
	* @return name of call put type
	*/
	const std::string& getCallPutTypeName();
	/**
	* @brief set CallPutType int value
	*
	* @param i as call put type
	*/
	void setCallPutTypeInt(int i);

	/**
	* @brief set CallPutType 
	*
	* @param cp as call put type
	*/
	void setCallPutType(CallPutType::enumtype cp);

	/**
	* @brief get areas str
	*
	* @return areas string
	*/
	const std::string& getAreasStr();

	/**
	* @brief set areas str
	*
	* @param s as areas string
	*/
	void setAreasStr(const std::string& s);

	/**
	* @brief is area
	*
	* @param s as area
	*
	* @return if s is area or not
	*/
	bool isArea(const std::string& s);

	/**
	* @brief get areas
	*
	* @return set of areas
	*/
	std::set<std::string>& areas();

	/**
	* @brief get concepts str
	*
	* @return concepts string
	*/
	const std::string& getConceptsStr();
	/**
	* @brief set concepts str
	*
	* @param s as concepts string
	*/
	void setConceptsStr(const std::string& s);

	/**
	* @brief is concept
	*
	* @param s as concept
	*
	* @return if s is a concept or not
	*/
	bool isConcept(const std::string& s);

	/**
	* @brief get concepts
	*
	* @return set of concepts
	*/
	std::set<std::string>& concepts();

	/**
	* @brief get industries str
	*
	* @return industries string
	*/
	const std::string& getIndustriesStr();

	/**
	* @brief set industries str
	*
	* @param s as industries string
	*/
	void setIndustriesStr(const std::string& s);

	/**
	* @brief is industry
	*
	* @param s as industry
	*
	* @return if it is industry s or not
	*/
	bool isIndustry(const std::string& s);

	/**
	* @brief get industries
	*
	* @return set of industries
	*/
	std::set<std::string>& industries();

 

	///@}


	/** 
	* @name String Functions
	*/
	///@{
	/**
	* @brief to json string
	*
	* @return json string
	*/
	std::string toJsonStr();
	
	///**
	//* @brief to pretty json string
	//*
	//* @return pretty json string
	//*/
	//std::string toPrettyJsonStr();

	/**
	* @brief from json string
	*
	* @param s as json string
	*/
	void fromJsonStr(const std::string& s);

	/**
	* @brief get insert sql
	*/
	std::string getSqlInsert();

	///@}

	/** 
	* @name Static Factory
	*/
	///@{

	/**
	* @brief factory function
	*
	* @return InstrSpec
	*/
	static InstrSpecPtr create();

	/**
	* @brief factory function with parameters
	*
	* @param exchangeID
	* @param instrumentID
	* @param securityType
	* @param symbol
	* @param expireintdate
	* @param callputtype
	* @param strikeprice
	* @param pricetick
	* @param contractmultiplier
	*
	* @return InstrSpec
	*/
	static  InstrSpecPtr createWithParams(const std::string& exchangeID, const std::string& instrumentID, const std::string& securityType,
		const std::string& symbol, int expireintdate, int callputtype, double strikeprice, double pricetick, double contractmultiplier);

	///@}

protected:
	InstrSpecDataPtr m_data;
	std::set<std::string> m_areas; ///< set of areas
	std::set<std::string> m_concepts; ///< set of concepts
	std::set<std::string> m_industries; ///< set of industries
	

 
 

}; //end class InstrSpec




} //end namespace XT


#endif
