#pragma once
#ifndef XT_OPTIONSCHAIN_H
#define XT_OPTIONSCHAIN_H

/**
* \file OptionsChain.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a collection of optionss for the same product and the same expiry.
*
* \description
*	Designed for use for options chain of a product.
*/


#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include <map>
 
#include <unordered_map>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

//#include <boost/lexical_cast.hpp>
#include "XTConfig.h"
#include "TagDataWrapper.h"

#include "Util.h"
#include "PxUtil.h"
#include "Instr.h"
#include "OCStrikeInfo.h"
#include "Curve.h"
#include "DoubleWingCurve.h"
#include "FlatCurve.h"
#include "LineCurve.h"

#include "Rolling.h"
#include "RollingXY.h"

#include "LogUtil.h"
#include "CfgMgr.h"
#include "ExchMgr.h"

namespace XT {



class XT_COMMON_API OptionsChain {

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* @brief constructor with product name and expiryDate
	*
	* @param product as product id
	* @param expiryDate as expiry int date
	*/
	OptionsChain(const std::string& product,int expiryDate) ;

	/**
	* @brief constructor with product name, expiryDate, and strikeScale
	*
	* @param product as product id
	* @param expiryDate as expiry int date
	* @param strikeScale as strike scale
	*/
	OptionsChain(const std::string& product, int expiryDate, double strikeScale);

	/**
	* @brief constructor
	*/
	OptionsChain() ;

	/**
	* @brief default copy constructor
	*/
	OptionsChain(const OptionsChain& from);// = default;

	/**
	* @brief default copy assignment
	*/
	OptionsChain& operator=(const OptionsChain& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~OptionsChain();

	///@}


	/**
	* @name Inititalization
	*/
	///@{
protected:
	/**
	* @brief initialization variables
	*
	*/
	void initVariables();

	/**
	* @brief initialize undlyInstr
	*
	*/
	void initUndlyInstr();

	/**
	* @brief initialize hedgingInstr
	*
	*/
	void initHedgingInstr();

	/**
	* @brief initialize pxUndlyInstr
	*
	*/
	void initPxUndlyInstr();

public:


	/**
	* @brief initialize curves for product
	*/
	void initCurves(const std::string& product);

	/**
	* @brief initialize curve end criterias
	*/
	void initCurveEndCriterias();

	/**
	* @brief init for previous and current prices
	*/
	void initPxs();

	/**
	* @brief initialization
	*
	*/
	void init();

	/**
	* @brief initialize with string parameters
	*
	* @param string parameters
	*/
	void updateStrParams(const StringMapPtr& smp);

	/**
	* @brief initialize productid and expireintdate
	*
	* @param productid
	* @param expireintdate
	*/
	void initProductExpireIntDate(const std::string& productid, int expireintdate);

	///@}

	/**
	* @brief convert   int64_t to double strike
	* 
	* @param intStrike as int64_t strike
	*
	* @return double strike
	*/
	double toDoubleStrike(int64_t intStrike);
	/**
	* @brief convert double to int64_t strike
	*
	* @param strike as double strike
	*
	* @return int64_t strike
	*/
	int64_t toInt64Strike(double strike);

	/**
	* @brief get call instruments map
	* 
	* @return call instruments map
	*/
	sf::contfree_safe_ptr<std::map<int64_t,InstrPtr > >& calls();

	/**
	* @brief get put instruments map
	*
	* @return put instruments map
	*/
	sf::contfree_safe_ptr<std::map<int64_t,InstrPtr > >& puts();

	/**
	* @brief get int64_t to double strike map
	*
	* @return int64_t to double strike map
	*/
	sf::contfree_safe_ptr<std::map<int64_t,double> >& int64StrikeToDoubleStrikeMap();

	/**
	* @brief get int64_t strike to idx map
	*
	* @return int64_t strike to idx map
	*/
	sf::contfree_safe_ptr<std::map<int64_t, int> >& int64StrikeToIdxMap();

	/**
	* @brief get double strike vector
	*
	* @return double strike vector
	*/
	std::vector<double>& doubleStrikes();

	/**
	* @brief get int strike vector
	*
	* @return int strike vector
	*/
	std::vector<int64_t>& int64Strikes();

	/**
	* @brief get strike informations
	*
	* @return int64_t strike to StrikeData map
	*/
	sf::contfree_safe_ptr<std::map<int64_t,OCStrikeInfoPtr > >& strikeInfoMap();

	/**
	* @brief has call with int64_t strike
	*
	* @param intstrike as int64_t strike
	*
	* @return if int64_t strike exists
	*/
	bool hasCallWithInt64Strike(int64_t intstrike);

	/**
	* @brief has call with double strike
	*
	* @param intstrike as double strike
	*
	* @return if double strike exists
	*/
	bool hasCallWithStrike(double strike);

	/**
	* @brief get call with int64_t strike
	*
	* @param intstrike as int64_t strike
	*
	* @return call
	*/
	InstrPtr& getCallWithInt64Strike(int64_t intstrike);
	/**
	* @brief get call with double strike
	*
	* @param intstrike as  strike
	*
	* @return call
	*/
	InstrPtr& getCallWithStrike(double strike);


	/**
	* @brief has put with int64_t strike
	*
	* @param intstrike as int64_t strike
	*
	* @return if int64_t strike exists
	*/
	bool hasPutWithInt64Strike(int64_t intstrike);

	/**
	* @brief has put with double strike
	*
	* @param intstrike as double strike
	*
	* @return if double strike exists
	*/
	bool hasPutWithStrike(double strike);

	/**
	* @brief get put with int64_t strike
	*
	* @param intstrike as int64_t strike
	*
	* @return put
	*/
	InstrPtr& getPutWithInt64Strike(int64_t intstrike);

	/**
	* @brief get put with double strike
	*
	* @param intstrike as double strike
	*
	* @return put
	*/
	InstrPtr& getPutWithStrike(double strike);

	/**
	* @breif get calls
	*
	* @return vector of calls
	*/
	std::vector<InstrPtr > getCalls();
	/**
	* @breif get puts
	*
	* @return vector of puts
	*/
	std::vector<InstrPtr > getPuts();

	/**
	* @breif get double strikes
	*
	* @return vector of double strikes
	*/
	std::vector<double> getStrikes();

	/**
	* @breif get  strikeinfos
	*
	* @return vector of strikeinfos
	*/
	std::vector<OCStrikeDataPtr > getStrikeDataVector();

	/**
	* @breif get  call instrids
	*
	* @return vector of call instrids
	*/
	std::vector<std::string> getCallInstrIDs();
	/**
	* @breif get  put instrids
	*
	* @return vector of put instrids
	*/
	std::vector<std::string> getPutInstrIDs();

	/**
	* @brief has instr
	*
	* @param instrid
	*
	* @eturn if instrid exists
	*/
	bool hasInstr(const std::string& instrid);

	/**
	* @brief get number of instrs
	*
	* @return number of instrs
	*/
	int getNumInstrs();

 
	/**
	* @brief get first instr
	*
	* @return instrument
	*/
	InstrPtr& firstInstr();

 ///////
	/**
	* @name Curves
	*/
	///@{

	/**
	* @brief get underlying previous settle curve
	*
	* @return underlying previous settle curve
	*/
	CurvePtr& undlyCurvePrevSettle();
	/**
	* @brief get underlying previous settle curve
	*
	* @param v as underlying previous settle curve
	*/
	void setUndlyCurvePrevSettle(const CurvePtr& v);

	/**
	* @brief get underlying bid curve
	*
	* @return underlying bid curve
	*/
	CurvePtr& undlyCurveBid();
	/**
	* @brief get underlying ask curve
	*
	* @return underlying ask curve
	*/
	CurvePtr& undlyCurveAsk();
	/**
	* @brief get underlying mid curve
	*
	* @return underlying mid curve
	*/
	CurvePtr& undlyCurveMid();

	/**
	* @brief set underlying bid curve
	*
	* @param v as underlying bid curve
	*/
	void setUndlyCurveBid(const CurvePtr& v);
	/**
	* @brief set underlying ask curve
	*
	* @param v as underlying ask curve
	*/
	void setUndlyCurveAsk(const CurvePtr& v);
	/**
	* @brief set underlying mid curve
	*
	* @param v as underlying mid curve
	*/
	void setUndlyCurveMid(const CurvePtr& v);

	/**
	* @brief get call implied volatility bid curve
	*
	* @return call implied volatility bid curve
	*/
	CurvePtr& callImpVolCurveBid();
	/**
	* @brief get call implied volatility ask curve
	*
	* @return call implied volatility ask curve
	*/
	CurvePtr& callImpVolCurveAsk();
	/**
	* @brief get call implied volatility mid curve
	*
	* @return call implied volatility mid curve
	*/
	CurvePtr& callImpVolCurveMid();

	/**
	* @brief get call implied volatility bid curve
	*
	* @param v as call implied volatility bid curve
	*/
	void setCallImpVolCurveBid(const CurvePtr& v);
	/**
	* @brief get call implied volatility ask curve
	*
	* @param v as call implied volatility ask curve
	*/
	void setCallImpVolCurveAsk(const CurvePtr& v);
	/**
	* @brief get call implied volatility mid curve
	*
	* @param v as call implied volatility mid curve
	*/
	void setCallImpVolCurveMid(const CurvePtr& v);	


	/**
	* @brief get put implied volatility bid curve
	*
	* @return put implied volatility bid curve
	*/
	CurvePtr& putImpVolCurveBid();
	/**
	* @brief get put implied volatility ask curve
	*
	* @return put implied volatility ask curve
	*/
	CurvePtr& putImpVolCurveAsk();
	/**
	* @brief get put implied volatility mid curve
	*
	* @return put implied volatility mid curve
	*/
	CurvePtr& putImpVolCurveMid();

	/**
	* @brief get put implied volatility bid curve
	*
	* @param v as put implied volatility bid curve
	*/
	void setPutImpVolCurveBid(const CurvePtr& v);
	/**
	* @brief get put implied volatility ask curve
	*
	* @param v as put implied volatility ask curve
	*/
	void setPutImpVolCurveAsk(const CurvePtr& v);
	/**
	* @brief get put implied volatility mid curve
	*
	* @param v as put implied volatility mid curve
	*/
	void setPutImpVolCurveMid(const CurvePtr& v);

	/**
	* @brief get snap volatility curve
	*
	* @return snap volatility curve
	*/
	CurvePtr& snapVolCurve();

	/**
	* @brief get theo volatility curve
	*
	* @return theo volatility curve
	*/
	CurvePtr& theoVolCurve(); 
	/**
	* @brief get risk volatility curve
	*
	* @return risk volatility curve
	*/
	CurvePtr& riskVolCurve(); 

	/**
	* @brief get prev settle vol curve
	*
	* @return prev settle vol curve
	*/
	CurvePtr& prevsettleVolCurve(); ///< prev settle vol curve

	/**
	* @brief set theo volatility curve
	*
	* @param v as theo volatility curve
	*/
	void setSnapVolCurve(const CurvePtr& v);

	/**
	* @brief set theo volatility curve
	*
	* @param v as theo volatility curve
	*/
	void setTheoVolCurve(const CurvePtr& v); 
	/**
	* @brief set risk volatility curve
	*
	* @param v as risk volatility curve
	*/
	void setRiskVolCurve(const CurvePtr& v); 	

	/**
	* @brief set prevsettle volatility curve
	*
	* @param v as prevsettle volatility curve
	*/
	void setPrevSettleVolCurve(const CurvePtr& v);

	///@}
	

	/**
	* @name Instruments
	*/
	///@{
	/**
	* @brief get underlying instrument
	*
	* @return underlying instrument
	*/
	InstrPtr& undlyInstr(); 

	/**
	* @brief get hedging instrument
	*
	* @return hedging instrument
	*/
	InstrPtr& hedgingInstr(); 

	/**
	* @brief get pricing underlying instrument
	*
	* @return pricing underlying instrument
	*/
	InstrPtr& pxUndlyInstr();

	/**
	* @brief set underlying instrument
	*
	* @param v as underlying instrument
	*/
	void setUndlyInstr(const InstrPtr& v); 
	/**
	* @brief set hedging instrument
	*
	* @param v as hedging instrument
	*/
	void setHedgingInstr(const InstrPtr& v); 

	/**
	* @brief set pricing underlying instrument
	*
	* @param v as pricing underlying instrument
	*/
	void setPxUndlyInstr(const InstrPtr& v);

	///@}
//////
/**
* @brief add instrument
*
* @param instr
*/
	void addInstr(InstrPtr instr);



/////////////


	/**
	* @name data
	*/
	///@{
	/**
	* @brief get cfg data
	*
	* @return cfg data
	*/
	OCCfgDataPtr& cfgData();

	
	/**
	* @brief get data
	*
	* @return data
	*/
	OCDataPtr& data();

	/**
	* @brief string parameters
	*
	* @return string parameters
	*/
	StringMapPtr& strParams();


	/**
	* @brief get data str
	* 
	* @return data str
	*/
	std::string getDataStr();

	/**
	* @brief get cfgdata str
	*
	* @return cfgdata str
	*/
	std::string getCfgDataStr();


	/**
	* @brief get str params string
	*
	* @return strParams str
	*/
	std::string getStrParamsStr();

	///////////////////////
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
	* @brief is initialized or not
	*
	* @return if oc is initialized
	*/
	bool isInitialized();

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string & getName();
	/**
	* @brief set name
	*
	* @param v as name
	*/
	void setName(const std::string & v);

	/**
	* @brief get product name
	*
	* @return product name
	*/
	const std::string & getProductID();
	///**
	//* @brief set product name
	//*
	//* @param v as name
	//*/
	//void setProductName(const std::string & v);

	///**
	//* @brief get underlying symbol
	//*
	//* @return underlying symbol
	//*/
	//const std::string & getUnderlyingSymbol();
	///**
	//* @brief set underlying symbol
	//*
	//* @param v as underlying symbol
	//*/
	//void setUnderlyingSymbol(const std::string& v);

	/**
	* @brief get expiry int date
	*
	* @return expiry int date
	*/
	int getExpireIntDate();
	/**
	* @brief set expiry int date
	*
	* @param v as expiry int date
	*/
	void setExpireIntDate(int v);

	/**
	* @brief get strike scale
	*
	* @return strike scale
	*/
	double getStrikeScale();
	///**
	//* @brief set strike scale
	//*
	//* @param v as strike scale
	//*/
	//void setStrikeScale(double v);

	/**
	* @brief get exercise type int
	*
	* @return exercise type int
	*/
	int getExerciseTypeInt();

	/**
	* @brief set exercise type int
	*
	* @param v
	*/
	void setExerciseTypeInt(int v);

	/**
	* @brief get underlying mid price
	*
	* @return underlying mid price
	*/
	double getUndlyMidPx();


	/**
	* @brief get pricing underlying mid price
	*
	* @return pricing underlying mid price
	*/
	double getPxUndlyMidPx();


	/**
	* @brief get underlying mid price by curve
	*
	* @return underlying mid price
	*/
	double getUndlyMidPxByCurve(double yte);

	/**
	* @brief get underlying bias
	*
	* @return underlying bias
	*/
	double getUndlyBias();

	/**
	* @brief set underlying bias
	*
	* @param v as underlying bias
	*/
	void setUndlyBias(double v);

	/**
	* @brief get prev settle S
	*
	* @return preve settle S for underlying 
	*/
	double getPrevSettleS();

	/**
	* @brief get prev close S
	*
	* @return preve close S for underlying
	*/
	double getPrevCloseS();

	/**
	* @brief get S
	*
	* @return S for underlying price
	*/
	double getS();

	/**
	* @brief get interest rate
	*
	* @return interest rate r
	*/
	double get_r();

	/**
	* @brief set interest rate
	*
	* @param v as interest rate
	*/
	void set_r(double v);

	/**
	* @brief get carry rate
	*
	* @return carry rate b
	*/
	double get_b();

	/**
	* @brief set carry rate
	*
	* @param v as carry rate
	*/
	void set_b(double v);

	
	/**
	* @brief get T (expiration time in year)
	*
	* @return T
	*/
	double getT();

	/**
	* @breif get T at the begin of the day
	* 
	* @return beginT
	*/
	double getBeginT();

	/**
	* @breif get T at the end of the day
	*
	* @return endT
	*/
	double getEndT();

	///**
	//* @brief set T
	//*
	//* @param v as T
	//*/
	//void setT(double v);

	/**
	* @brief get theo vol from theo vol curve
	*
	* @param strike
	* @return theo vol on strike
	*/
	double getTheoVolOnStrike(double strike);

	/**
	* @brief get risk vol 
	* @param strike
	* @return risk vol on strike
	*/
	double getRiskVolOnStrike(double strike);

	/**
	* @brief is vol valid or not
	*
	* @param v
	* @return if v is valid vol or not
	*/
	bool isValidVol(double v);

	/**
	* @brief atm index
	*
	* @return atm index
	*/
	int atmIndex();

	/**
	* @brief atm strike
	*
	* @return atm strike
	*/
	double atmStrike();

	/**
	* @brief atm int64strike
	*
	* @return atm int64 strike
	*/
	int64_t atmInt64Strike();

	/**
	* @brief atm straddle vega
	*
	* @return atm straddle vega
	*/
	double atmStraddleVega();

	/**
	* @brief atm call
	*
	* @return atm call
	*/
	InstrPtr& atmCall();

	/**
	* @brief atm put
	*
	* @return atm put
	*/
	InstrPtr& atmPut();


	

	///@}

	/**
	* @name data getters
	*/
	///@{

	double getDoubleDataOnStrike(double strike, const std::string& dataname);
	double getDoubleDataOnCall(double strike, const std::string& dataname);
	double getDoubleDataOnPut(double strike, const std::string& dataname);

	std::vector<double> getDoubleVectorDataOnStrikes(const std::string& dataname);

	std::vector<double> getDoubleVectorDataOnCalls(const std::string& dataname);

	std::vector<double> getDoubleVectorDataOnPuts(const std::string& dataname);

	std::vector<std::string> getStringVectorDataOnStrikes(const std::string& dataname);

	std::vector<std::string> getStringVectorDataOnCalls(const std::string& dataname);

	std::vector<std::string> getStringVectorDataOnPuts(const std::string& dataname);

	std::vector<int> getIntVectorDataOnStrikes(const std::string& dataname);

	std::vector<int> getIntVectorDataOnCalls(const std::string& dataname);

	std::vector<int> getIntVectorDataOnPuts(const std::string& dataname);

	std::vector<int64_t> getInt64VectorDataOnStrikes(const std::string& dataname);

	std::vector<int64_t> getInt64VectorDataOnCalls(const std::string& dataname);

	std::vector<int64_t> getInt64VectorDataOnPuts(const std::string& dataname);

	///@}



	/**
	* @name Update and Calculation
	*/
	///@{


	/**
	* @brief calculate prev settle and close infos
	*/
	void calcPrevInfos(double strike, int cptype);

	/**
	* @brief calculate all prev settle and close infos
	*/
	void calcAllPrevInfos();

	/**
	* @brief calculate all close infos
	*/
	void calcAllCloseInfos();

	/**
	* @brief update atm info
	*
	*/
	void updateATMInfo();


	/**
	* @brief get bid px and ask px adjust ratio
	*
	* @param cptype
	* @param strike
	* @return ratio of bid side/ask side
	*/
	double getBidAskAdjustRatio(int cptype, double strike);

	/**
	* @brief get spread ratio
	*
	* @param rspflag for response flag
	*/
	double getMMPricingRatioByStyle(int rspflag);

	/**
	* @brief update quote price by method
	* 
	* @param cptype
	* @param strike
	* @param flag
	*/
	void updateQuote(int cptype, double strike, int flag);

	/**
	* @brief reset all theo vols  
	*/
	void resetAllTheoVols();

	/**
	* @brief reset all theo pxs
	*/
	void resetAllTheoPxs();

	/**
	* @brief reset all risk vols
	*/
	void resetAllRiskVols();

	/**
	* @brief reset all risk pxs
	*/
	void resetAllRiskPxs();

	/**
	* @brief update expire time
	*/
	void updateTime();

	/**
	* @brief update all theo vols and pxs
	*/
	void updateAllTheoVolsPxs();



	/**
	* @brief update all quote vols and prices
	*/
	void updateAllQuoteVolsPxs();

	/**
	* @brief update all risk vols and prices
	*/
	void updateAllRiskVolsPxs();

	/**
	* @brief update greeks
	*
	* @param cptype
	* @param strike
	*/
	void updateGreeks(int cptype, double strike);

	/**
	* @brief update postion greeks;
	*
	* @param cptype
	* @param strike
	*/
	void updatePosGreeks(int cptype, double strike);

	/**
	* @brief update postion pnls
	*
	* @param cptype
	* @param strike
	*/
	void updatePosPnLs(int cptype, double intstrike);

	/**
	* @brief update all greeks
	*/
	void updateAllGreeks();

	/**
	* @brief fit vol curve
	*/
	void fitVolCurve();


	///@}

	/**
	* @name Events
	*/
	///@{

	/**
	* @brief do something when underling makret px changed
	*/
	void onUndlyMktChanged();


	/**
	* @brief do something when option market px changed
	*/
	void onOptionMktChanged( int cptype, double strike);

	/**
	* @brief do something when option market position changed
	*/
	void onOptionPosChanged(int cptype, double strike);




	///@}

	/**
	*@name string function
	*/
	///@{

	/**
	* @brief get snap information string
	*
	* @return snap information string
	*/
	std::string getSnapInfoStr();

	/**
	* @brief get daily information string
	*
	* @return daily information string
	*/
	std::string getDailyInfoStr();


	///@}
	
	/**
	* @name market maker related
	*/
	///@{

	/**
	* @brief get max spread for market maker
	*
	* @param px
	* @param flag
	*/
	double getMMSpreadMax(double px, int flag);

	///@}
 

	

protected:
	InstrPtr m_EmptyInstr;///< null instrument
	InstrPtr m_atmCall;
	InstrPtr m_atmPut;
	
	sf::contfree_safe_ptr<std::map<std::string, InstrPtr > > m_instrs; ///< map for instrs

	sf::contfree_safe_ptr<std::map<int64_t,InstrPtr > > m_calls; ///< map for calls
	sf::contfree_safe_ptr<std::map<int64_t,InstrPtr > > m_puts; ///< map for puts
	
	sf::contfree_safe_ptr<std::map<int64_t,double> > m_int64StrikeToDoubleStrikeMap; ///< strikes
	sf::contfree_safe_ptr<std::map<int64_t, int> > m_int64StrikeToIdxMap;///< intstrike to index map;

	std::vector<double> m_doubleStrikes; ///< double strike vector
	std::vector<int64_t> m_int64Strikes; ///< int strike vector

//	std::map<int64_t, OCStrikeDataPtr > m_strikeDataMap;
	//std::map<int64_t,OCStrikeInfoPtr > m_strikeInfos; ///< strike information
	sf::contfree_safe_ptr<std::map<int64_t, OCStrikeInfoPtr > > m_strikeInfoMap; ///< strikeinfo map
	sf::contfree_safe_ptr<std::vector<OCStrikeInfoPtr > > m_strikeInfos;  ///< strikeinfo vector

 
	CurvePtr m_undlyCurvePrevSettle; ///< underlying previous settle curve

	CurvePtr m_undlyCurveBid; ///< underlying bid curve
	CurvePtr m_undlyCurveAsk; ///< underlying ask curve
	CurvePtr m_undlyCurveMid; ///< underlying mid curve
	
	CurvePtr m_callImpVolCurveBid; ///< call implied volatility bid curve
	CurvePtr m_callImpVolCurveAsk; ///< call implied volatility ask curve
	CurvePtr m_callImpVolCurveMid; ///< call implied volatility mid curve

	CurvePtr m_putImpVolCurveBid; ///< put implied volatility bid curve
	CurvePtr m_putImpVolCurveAsk; ///< put implied volatility ask curve
	CurvePtr m_putImpVolCurveMid; ///< put implied volatility mid curve

	PointMapPtr m_midVolPointMap; ///< mid vol pointmap
	CurvePtr m_snapVolCurve; ///< snap vol curve
	CurvePtr m_theoVolCurve; ///< theo vol curve
	CurvePtr m_riskVolCurve; ///< risk vol curve
	CurvePtr m_prevsettleVolCurve; ///< prev settle vol curve

	InstrPtr m_undlyInstr; ///< underlying instrument
	InstrPtr m_hedgingInstr; ///< hedging instrument
	InstrPtr m_pxUndlyInstr; ///< pricing underlying instrument


	//std::string m_name; ///< name
	//
	//std::string m_underlyingSymbol; ///< underlying symbol
	//int32_t m_expiryIntDate; ///< expiry int date

	//double m_strikeScale; ///< strike scale
	 
protected:
	OCCfgDataPtr m_cfgData;
	OCDataPtr m_data;

	StringMapPtr m_strParams;
protected:
	RollingPtr m_unldyBiasRolling;
	RollingPtr m_undlyChgRolling;
	RollingXYPtr m_vcrRolling;


protected:
	mutable boost::shared_mutex m_mutex;

}; //end class OptionsChain

   //////typedef for OptionsChain
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OptionsChain> OptionsChainPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OptionsChain> OptionsChainPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OptionsChain> OptionsChainPtr;

#else

typedef ::boost::shared_ptr<OptionsChain> OptionsChainPtr;
#endif


typedef ::sf::safe_ptr<OptionsChain> OptionsChainSafePtr;

typedef sf::contfree_safe_ptr<OptionsChain> OptionsChainContFreePtr;
//////end typedef for OptionsChain

/////////////////////////////////////////////////////

class XT_COMMON_API OptionsChainMap {
public:

	/**
	* @name Constructor and Initialization
	*/
	///@{


	/**
	* @brief constructor
	*/
	OptionsChainMap();

	/**
	* @brief default copy constructor
	*/
	OptionsChainMap(const OptionsChainMap& from);// = default;

												 /**
												 * @brief default copy assignment
												 */
	OptionsChainMap& operator=(const OptionsChainMap& from);// = default;

															/**
															* @brief destructor
															*/
	virtual ~OptionsChainMap() {};

	///@}



public:
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainPtr > >& ocMap();

	void add(OptionsChainPtr& fc);

	void removeByOCName(const std::string& name);
	void removeByOCProductIDExpireIntDate(const std::string& product, int expireintdate);

	bool hasOCName(const std::string& name);
	bool hasOCProductID(const std::string& product);

	std::vector<std::string> getOCNames();
	std::vector<std::string> getOCProductIDs();
	std::vector<int> getOCExpireIntDates(const std::string& product);

	OptionsChainPtr& getOptionsChainByName(const std::string& name);

	OptionsChainPtr& getOptionsChainByProductIDExpireIntDate(const std::string& product, int expireintdate);



protected:
	sf::contfree_safe_ptr<std::map<std::string, OptionsChainPtr > > m_ocMap;
	OptionsChainPtr m_EmptyOptionsChain; ///< null OptionsChain


}; //class XT_COMMON_API OptionsChainMap {
   //////typedef for OptionsChainMap
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<OptionsChainMap> OptionsChainMapPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<OptionsChainMap> OptionsChainMapPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<OptionsChainMap> OptionsChainMapPtr;

#else

typedef ::std::shared_ptr<OptionsChainMap> OptionsChainMapPtr;
#endif


typedef ::sf::safe_ptr<OptionsChainMap> OptionsChainMapSafePtr;

typedef sf::contfree_safe_ptr<OptionsChainMap> OptionsChainMapContFreePtr;
//////end typedef for OptionsChainMap


} //end namespace XT


#endif
