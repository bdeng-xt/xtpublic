#pragma once
#ifndef TAUTIL_H
#define TAUTIL_H

/**
* \file TAUtil.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a util class for ta calculation.
*
* \description
*	Designed for ta calculation.
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <vector>

#include "XTConfig.h"

#include "LogUtil.h"
#include "ta_libc.h"
#include "Util.h"



namespace XT
{
class XT_COMMON_API TAUtil
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TAUtil() {}

	/**
	* @brief copy constructor
	*/
	TAUtil(const TAUtil& from) {} // = delete;

	/**
	* @brief copy assignment
	*/
	TAUtil& operator=(const TAUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~TAUtil() {}

	///@}
public:
 
 	/**
	*  @name Calc Functions
	*/
	///@{
	static void calcSMA(int startIdx, int endIdx, std::vector<double> & closeData, std::vector<double> & outData, int period);
	static void calcSMAByIdx(int endIdx, std::vector<double> & closeData, std::vector<double> & outData, int period);

	static void calcEMA(int startIdx, int endIdx, std::vector<double> & closeData, std::vector<double> & outData, int period);
	static void calcEMAByIdx(int endIdx, std::vector<double> & closeData, std::vector<double> & outData, int period);

	static void calcBBands(int startIdx, int endIdx, std::vector<double> & inReal, std::vector<double>& outMiddle, std::vector<double>& outStd, int period);
	static void calcBBandsByIdx(int endIdx, std::vector<double> & inReal, std::vector<double>& outMiddle, std::vector<double>& outStd, int period);

	//static void calcBBSAR(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outMiddle, std::vector<double>& outStd, std::vector<double>& outMidSlope,  std::vector<double> & psar, int bbPeriod, int bbMidSlopePeriod, double accInitial , double accIncrement , double accMaximum, double dist);
	//static void calcBBSARByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outMiddle, std::vector<double>& outStd, std::vector<double>& outMidSlope, std::vector<double> & psar, int bbPeriod, int bbMidSlopePeriod, double accInitial , double accIncrement , double accMaximum, double dist);

	static void calcKBands(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outMid, std::vector<double>& outAtr,  int kbPeriod, int atrPeriod);
	static void calcKBandsByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outMid, std::vector<double>& outAtr,  int kbPeriod, int atrPeriod);

	//static void calcSAR(int startIdx, int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & psar, double accInitial , double accIncrement , double accMaximum );
	//static void calcSARByIdx(int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & psar, double accInitial , double accIncrement , double accMaximum );
	//static void calcSARStatus(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & psar, std::vector<int> & status);
	//static void calcSARStatusByIdx( int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & psar, std::vector<int> & status);

	static void calcSAR(int startIdx, int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & psar, std::vector<double>& ep, std::vector<double>& acc, std::vector<int>& sarstatus, double accInitial, double accIncrement, double accMaximum, double maxdist);
	static void calcSARByIdx( int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & psar, std::vector<double>& ep, std::vector<double>& acc, std::vector<int>& sarstatus, double accInitial, double accIncrement, double accMaximum, double maxdist);

	static void calcSARWithMaxDeviations(int startIdx, int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & deviations,
		std::vector<double> & psar, std::vector<double>& ep, std::vector<double>& acc, std::vector<int>& sarstatus, double accInitial, double accIncrement, double accMaximum, double maxdist);
	static void calcSARWithMaxDeviationsByIdx(int endIdx, std::vector<double> & m_highData, std::vector<double> & m_lowData, std::vector<double> & deviations,
		std::vector<double> & psar, std::vector<double>& ep, std::vector<double>& acc, std::vector<int>& sarstatus, double accInitial, double accIncrement, double accMaximum, double maxdist);

 

	static void calcRSI(int startIdx, int endIdx, std::vector<double> & closes, std::vector<double>& outReal, int period);
	static void calcRSIByIdx(int endIdx, std::vector<double>& closes, std::vector<double>& outReal, int period);

	static void calcMACD(int startIdx, int endIdx, std::vector<double> & inReal, std::vector<double>& outMACD, std::vector<double>& outMACDSignal, std::vector<double>& outMACDHist, std::vector<double>& outMACDHistMa, int fastPeriod, int slowPeriod, int signalPeriod, int histmaPeriod);
	static void calcMACDByIdx(int endIdx, std::vector<double> & inReal, std::vector<double>& outMACD, std::vector<double>& outMACDSignal, std::vector<double>& outMACDHist, std::vector<double>& outMACDHistMa, int fastPeriod, int slowPeriod, int signalPeriod, int histmaPeriod);

	static void calcMACDEXT(int startIdx, int endIdx, std::vector<double> & inReal, std::vector<double>& outMACD, std::vector<double>& outMACDSignal, std::vector<double>& outMACDHist,std::vector<double>& outMACDHistMa, int fastPeriod, int fastMAType, int slowPeriod, int slowMAType, int signalPeriod, int signalMAType, int histmaPeriod,int histMAType);
	static void calcMACDEXTByIdx(int endIdx, std::vector<double> & inReal, std::vector<double>& outMACD, std::vector<double>& outMACDSignal, std::vector<double>& outMACDHist, std::vector<double>& outMACDHistMa, int fastPeriod,int fastMAType,  int slowPeriod, int slowMAType, int signalPeriod, int signalMAType, int histmaPeriod,int histMAType);

	static void calcATR(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);
	static void calcATRByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);

	//static void calcATRSAR(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & atr, std::vector<double> & psar, int atrPeriod, double accInitial , double accIncrement , double accMaximum, double dist);
	//static void calcATRSARByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & atr, std::vector<double> & psar, int atrPeriod, double accInitial , double accIncrement , double accMaximum, double dist);

	static void calcCCI(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);
	static void calcCCIByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);

	static void calcADX(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);
	static void calcADXByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outReal, int period);

	static void calcMFI(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & inVolume, std::vector<double> & outReal, int period);
	static void calcMFIByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & inVolume, std::vector<double> & outReal, int period);

	static void calcSlowKD(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outK, std::vector<double>& outD, int kPeriod, int dPeriod);
	static void calcSlowKDByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outK, std::vector<double>& outD, int kPeriod, int dPeriod);

	static void calcFastKD(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outK, std::vector<double>& outD, int kPeriod, int dPeriod);
	static void calcFastKDByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double>& inClose, std::vector<double> & outK, std::vector<double>& outD, int kPeriod, int dPeriod);


	static void calcDMI(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & inClose, std::vector<double> & atr, std::vector<double> & pdi, std::vector<double> & mdi, std::vector<double> & dx, std::vector<double> & adx, std::vector<double> & dmi,  int in_atrperiod, int in_adxperiod);
	static void calcDMIByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & inClose, std::vector<double> & atr, std::vector<double> & pdi, std::vector<double> & mdi, std::vector<double> & dx, std::vector<double> & adx, std::vector<double> & dmi, int in_atrperiod, int in_adxperiod);

	static void calcMAATR(int startIdx, int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & inClose,
		std::vector<double> & atr, std::vector<double> & ma1, std::vector<double> & ma2, std::vector<double> & ma3, std::vector<double> & ma4, 
		std::vector<double>& machange, std::vector<int> & maatr, int in_atrperiod, int maperiod1, int maperiod2, int maperiod3, int maperiod4, int matype);
	static void calcMAATRByIdx(int endIdx, std::vector<double> & inHigh, std::vector<double> & inLow, std::vector<double> & inClose, 
		std::vector<double> & atr, std::vector<double> & ma1, std::vector<double> & ma2, std::vector<double> & ma3, std::vector<double> & ma4,
		std::vector<double>& machange, std::vector<int> & maatr, int in_atrperiod, int maperiod1, int maperiod2, int maperiod3, int maperiod4, int matype);

	///@}
};//class
}//namespace 


#endif