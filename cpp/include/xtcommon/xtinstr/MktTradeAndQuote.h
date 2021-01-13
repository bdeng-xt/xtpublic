#pragma once
#ifndef XT_MKT_TAQ_H
#define XT_MKT_TAQ_H

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

#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "InstrSpec.h"
#include "PBUtil.h"

namespace XT
{

class XT_COMMON_API MktTradeAndQuote
{
public:
	/**
	* @name Constructor and Initialization
	*/
	///@{
	/**
	* @brief constructor
	*/
	MktTradeAndQuote();

	/**
	* @brief default copy constructor
	*/
	MktTradeAndQuote(const MktTradeAndQuote& from);// = default;

	/**
	* @brief default copy assignment
	*/
	MktTradeAndQuote& operator=(const MktTradeAndQuote& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~MktTradeAndQuote();


	/**
	* @brief initialization
	*
	* @param s as InstrSpec
	*/
	void init(InstrSpecPtr s);

	///@}

public:
	/**
	* @name Update
	*/
	///@{

	/**
	* @brief update mktdata
	*
	* @param ktdata as MktQuoteData
	*/
	void updateMktQuoteData(const MktQuoteDataPtr & mktdata);

	/**
	* @brief emplace mktdata
	*
	* @param mktdata as MktQuoteData
	*
	*/
	void emplaceMktQuoteData(MktQuoteDataPtr&& mktdata);

	///@}

protected:
	/**
	* @brief calculate difference between mktQuoteCurr and mktQuotePrev
	*/
	void calcMktQuoteQuoteDataCurrPrevDiff();

public:

	/**
	* @name Accessors
	*/
	///@{
	/**
	* @brief taqStatData
	*
	* @param taqStatStat
	*
	*/
	TaqStatDataPtr& taqStatData();

	/**
	* @brief get current mktQuoteData
	*
	* @return current mktQuoteData
	*/
	MktQuoteDataPtr& mktQuoteDataCurr();

	/**
	* @brief get previous mktQuotesData
	*
	* @return previous mktQuotesData
	*/
	MktQuoteDataPtr& mktQuoteDataPrev();

	/**
	* @brief get snapshot mktquotedata
	* 
	* @return snapshot mktquotedata
	*/
	MktQuoteDataPtr& mktQuoteDataSnap();

	///@}

	//////
	/**
	* @name static functions
	*/
	///@{

 	/**
	* @brief has best px and sz
	*
	* @param bs as buy or sell
	* @return if MktQuoteData has best quote on buy or sell side
	*/
	static bool hasBestQuote(const MktQuoteDataPtr& mktdata, BuySellType::enumtype bs);

	/**
	* @brief has best px
	*
	* @param bs as buy or sell
	* @return if MktQuoteData has best px on buy or sell side
	*/
	static bool hasBestPx(const MktQuoteDataPtr& mktdata, BuySellType::enumtype bs);

	/**
	* @brief has best sz
	*
	* @param bs as buy or sell
	* @return if MktQuoteData has best sz on buy or sell side
	*/
	static bool hasBestSz(const MktQuoteDataPtr& mktdata, BuySellType::enumtype bs);

	/**
	* @brief is MktQuoteData valid or not
	*
	* @return if MktQuoteData is valid or not
	*/
	static bool isValidMktQuoteData(const MktQuoteDataPtr& mktdata);



	///@}

	/**
	*@name string functions
	*/
	///@{

	/**
	* @brief get json string for  m_mktQuoteDataCurr
	*
	* @return json string
	*/
	std::string getCurrJsonStr();

	/**
	* @brief get json string for  m_mktQuoteDataPrev
	*
	* @return json string
	*/
	std::string getPrevJsonStr();


	/**
	* @brief get json string for  m_mktQuoteDataSnap
	*
	* @return json string
	*/
	std::string getSnapJsonStr();


	/**
	* @brief get csv string for  m_mktQuoteDataCurr
	*
	* @return csv string
	*/
	std::string getCurrCsvStr();

	/**
	* @brief get csv string for  m_mktQuoteDataPrev
	*
	* @return csv string
	*/
	std::string getPrevCsvStr();

	/**
	* @brief get csv string for  m_mktQuoteDataSnap
	*
	* @return csv string
	*/
	std::string getSnapCsvStr();

	/**
	* @brief get json string for  m_taqStatData
	*
	* @return json string 
	*/
	std::string getStatJsonStr();

	/**
	* @brief get csv string for  m_taqStatData
	*
	* @return csv string
	*/
	std::string getStatCsvStr();

	///@}

protected:
	InstrSpecPtr m_spec;

	MktQuoteDataPtr m_mktQuoteDataCurr;
	MktQuoteDataPtr m_mktQuoteDataPrev;
	MktQuoteDataPtr m_mktQuoteDataSnap;

	TaqStatDataPtr m_taqStatData;


};//class


  //////typedef for MktTradeAndQuote
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<MktTradeAndQuote> MktTradeAndQuotePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<MktTradeAndQuote> MktTradeAndQuotePtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<MktTradeAndQuote> MktTradeAndQuotePtr;

#else

typedef ::boost::shared_ptr<MktTradeAndQuote> MktTradeAndQuotePtr;
#endif


typedef ::sf::safe_ptr<MktTradeAndQuote> MktTradeAndQuoteSafePtr;

typedef sf::contfree_safe_ptr<MktTradeAndQuote> MktTradeAndQuoteContFreePtr;
//////end typedef for MktTradeAndQuote



}//namespace


#endif