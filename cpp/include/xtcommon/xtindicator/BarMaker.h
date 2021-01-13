#pragma once
#ifndef XT_BARMAKER_H
#define XT_BARMAKER_H

/**
* \file BarMaker.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a classe for BarMaker.
*
* \description
*	Designed for generating new bars.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "TagDataWrapper.h"
#include "EnumHelper.h"

#include "SettingsMgr.h"
#include "Rolling.h"
#include "RollingXY.h"

#include "MongoDBMgr.h"

#include "Bar.h"
#include "BarIndicator.h"

namespace XT
{

class XT_COMMON_API BarMaker
{
public:
	/**
	* @name Constructors and Destructors
	*/
	///@{
	/**
	* @brief constructor
	*/
	BarMaker();

	/**
	* @brief copy constructor
	*/
	BarMaker(const BarMaker& from);

 

	/**
	* @brief constructor
	*
	* @param iid as integer id
	* @param span in seconds
	*/
	BarMaker(int iid, int span);

	/**
	* @brief constructor
	*
	* @param iid as integer id
	* @param span in seconds
	* @param rtype as RollingType
	* @param dttype as DateTimeType
	*/
	BarMaker(int iid, int span, XT::RollingType::enumtype rtype, XT::DateTimeType::enumtype dttype);


	///**
	//* @brief default copy constructor
	//*/
	//BarMaker(const BarMaker& from) = default;

	/**
	* @brief default copy assignment
	*/
	BarMaker& operator=(const BarMaker& from);// = default;


	/**
	* @brief destructor
	*/
	virtual ~BarMaker();

	///@}

	/**
	* @brief set integer id
	*
	* @param iid as integer id
	*/
	void setIid(int iid);

	/**
	* @brief get integer id
	*
	* @return integer id
	*/
	int getIid();

	/**
	* @brief set name
	* 
	* @param s as name
	*/
	void setName(const std::string& s);

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string& getName();

	/**
	* @brief set exchid
	*
	* @param exch as exchange id
	*/
	void setExchID(const std::string& exch);

	/**
	* @brief get exchid
	*
	* @return exchange id
	*/
	const std::string& getExchID();

	/**
	* @brief get mongodb column name
	*
	* @return mongodb column name
	*/
	const std::string& getMongo60sColName();

	/**
	* @brief get barlist
	*
	* @return reference to barlist
	*/
	BarListPtr& bars();

	/**
	* @brief rolling xy for price and volume
	*
	* @return RollingXYPtr
	*/
	RollingXYPtr& rxyPxVolume();

	/**
	* @brief rolling flips
	*
	* @return RollingPtr
	*/
	RollingPtr& rFlips(); 

	/**
	* @brief has indicator by name
	*
	* @param s as name
	*
	* @return if it has indicator with name s
	*/
	bool hasBarIndicatorByName(const std::string& k);

	/**
	* @brief get indicator by name
	*
	* @param k as key name
	*
	* @return BarIndicatorPtr
	*/
	BarIndicatorPtr& getBarIndicatorByName(const std::string& k);

	/**
	* @brief get indicator names
	*
	* @return vector of indicator names
	*/
	const std::vector<std::string>& getBarIndicatorNames();

	/**
	* @brief add data
	*
	* @param ts as timestamp
	* @param px as price
	* @param volume as trading volume
	* @param oichg as open interest change
	* @param turnover as sum of (volume*fillprice)
	* @param bstdiff as buy sell turnover difference
	* @param flipup as flip ups
	* @param flipdn as flip downs
	*/
	void addData(int64_t ts, double px, int64_t volume, int64_t oichg, int64_t bsvoldiff, double turnover, double bstdiff, double flipups, double flipdns);

	/**
	* @brief log bar with idx to file
	*
	* @param idx as bar idx
	*/
	void logBarByIdx(int idx);

	/**
	* @brief insert bar to mongodb 
	*
	* @param bar as BarPtr
	* @name as strng
	* @colname as column name
	*/
	void insertBarToMongo(const BarPtr& bar, const std::string& name, const std::string& colname);

	/**
	* @brief add indicator with parameter smp
	*
	* @param smp as StringMapPtr
	*/
	void addBarIndicator(StringMapPtr smp);

public:
	/**
	* @name cross between indicators
	*/
	///@{

	/**
	* @brief check if indicator is crossing above or not
	*
	* @param indicator1 as indicator1 name
	* @param outputidx1 as output1 index
	* @param indicator2 as indicator2 name
	* @param outputidx2 as output2 index
	* @param baridx as bar index
	*
	* @return if indicator is crossing above or not
	*/
	bool isIndicatorsCrossAboveOnBarIdx(const std::string& indicator1, int outputidx1, const std::string& indicator2, int outputidx2, int baridx);

	/**
	* @brief check if indicator is crossing below or not
	*
	* @param indicator1 as indicator1 name
	* @param outputidx1 as output1 index
	* @param indicator2 as indicator2 name
	* @param outputidx2 as output2 index
	* @param baridx as bar index
	*
	* @return if indicator is crossing below or not
	*/
	bool isIndicatorsCrossBelowOnBarIdx(const std::string& indicator1, int outputidx1, const std::string& indicator2, int outputidx2, int baridx);


	/**
	* @brief check if indicator is crossing above or not on last idx
	*
	* @param indicator1 as indicator1 name
	* @param outputidx1 as output1 index
	* @param indicator2 as indicator2 name
	* @param outputidx2 as output2 index
	*
	* @return if indicator is crossing above or not
	*/
	bool isIndicatorsCrossAbove(const std::string& indicator1, int outputidx1, const std::string& indicator2, int outputidx2 );

	/**
	* @brief check if indicator is crossing below or not on last idx
	*
	* @param indicator1 as indicator1 name
	* @param outputidx1 as output1 index
	* @param indicator2 as indicator2 name
	* @param outputidx2 as output2 index
	*
	* @return if indicator is crossing below or not
	*/
	bool isIndicatorsCrossBelow(const std::string& indicator1, int outputidx1, const std::string& indicator2, int outputidx2);

	///@}


	/**
	* @name Rolling statistics
	*/
	///@{


	/**
	* @brief get begin px in rolling window
	*
	* @return rolling value
	*/
	double getRollingBeginPx();

	/**
	* @brief get end px in rolling window
	*
	* @return rolling value
	*/
	double getRollingEndPx();

	/**
	* @brief get begin px in previous rolling window
	*
	* @return rolling value
	*/
	double getRollingBeginPxPrev();

	/**
	* @brief get end px in previous rolling window
	*
	* @return rolling value
	*/
	double getRollingEndPxPrev();

	/**
	* @brief get rolling change
	*
	* @return rolling value
	*/
	double getRollingChange();

	/**
	* @brief get rolling change ratio
	*
	* @return rolling value
	*/
	double getRollingChangeRatio();

	/**
	* @brief get previous rolling change
	*
	* @return rolling value
	*/
	double getRollingChangePrev();

	/**
	* @brief get previous rolling change ratio
	*
	* @return rolling value
	*/
	double getRollingChangeRatioPrev();

	/**
	* @brief get rolling HighPx
	*
	* @return rolling value
	*/
	double getRollingHighPx();

	/**
	* @brief get rolling LowPx
	*
	* @return rolling value
	*/
	double getRollingLowPx();

	/**
	* @brief get prev rolling HighPx
	*
	* @return rolling value
	*/
	double getRollingHighPxPrev();

	/**
	* @brief get prev rolling LowPx
	*
	* @return rolling value
	*/
	double getRollingLowPxPrev();


	/**
	* @brief get rolling buy volume
	*
	* @return rolling value
	*/
	int getRollingBuyVolume();

	/**
	* @brief get rolling sell volume
	*
	* @return rolling value
	*/
	int getRollingSellVolume();

	/**
	* @brief get rolling volume, buyVolume + sellVolume
	*
	* @return rolling value
	*/
	int getRollingVolume();

	/**
	* @brief get rolling overlay
	*
	* @return rolling value
	*/
	double getRollingOverlay();

	/**
	* @brief get rolling average px
	*
	* @return rolling value
	*/
	double getRollingAvgPx();

	/**
	* @brief get prev rolling buy volume
	*
	* @return rolling value
	*/
	int getRollingBuyVolumePrev();

	/**
	* @brief get prev rolling sell volume
	*
	* @return rolling value
	*/
	int getRollingSellVolumePrev();

	/**
	* @brief get prev rolling volume
	*
	* @return rolling value
	*/
	int getRollingVolumePrev();


	/**
	* @brief get prev rolling overlay
	*
	* @return rolling value
	*/
	double getRollingOverlayPrev();

	/**
	* @brief get prev rolling avg px
	*
	* @return rolling value
	*/
	double getRollingAvgPxPrev();

	/**
	* @brief get buy volume total
	*
	* @return rolling value
	*/
	int getTotBuyVolume();

	/**
	* @brief get sell Volume total
	*
	* @return rolling value
	*/
	int getTotSellVolume();

	/**
	* @brief get total volume
	*
	* @return rolling value
	*/
	int getTotVolume();

	/**
	* @brief get total overlay
	*
	* @return rolling value
	*/
	double getTotOverlay();

	/**
	* @brief get avg px
	*
	* @return rolling value
	*/
	double getAvgPx();

	/**
	* @brief get rolling flip ups
	*
	* @return rolling value
	*/
	double getRollingFlipUps();

	/**
	* @brief get rolling flip dns
	*
	* @return rolling value
	*/
	double getRollingFlipDns();

	/**
	* @brief get rolling flip absolute value
	*
	* @return rolling value
	*/
	double getRollingFlipAbs();

	/**
	* @brief get rolling flip
	*
	* @return rolling value
	*/
	double getRollingFlip();


	/**
	* @brief get rolling flip ups
	*
	* @return rolling value
	*/
	double getRollingFlipUpsPrev();

	/**
	* @brief get rolling flip dns
	*
	* @return rolling value
	*/
	double getRollingFlipDnsPrev();

	/**
	* @brief get rolling flip absolute value
	*
	* @return rolling value
	*/
	double getRollingFlipAbsPrev();

	/**
	* @brief get rolling flip
	*
	* @return rolling value
	*/
	double getRollingFlipPrev();

	/**
	* @brief get rolling flip high
	*
	* @return rolling value
	*/
	double getRollingFlipHigh();

	/**
	* @brief get rolling flip low
	*
	* @return rolling value
	*/
	double getRollingFlipLow();


	///@}

protected:
	/**
	* @brief initialization
	*
	*/
	void init();

	/**
	* @brief update bar indicator names
	*/
	void updateBarIndicatorNames();
protected:
	int m_span; ///< bar seconds
	int m_iid; ///< integer id
	XT::RollingType::enumtype m_rollingType; ///< rolling type
	XT::DateTimeType::enumtype m_dtType; ///< date time type
 
	std::string m_name; ///< instrument or instrcombo name
	std::string m_exchangeID; ///< exchange id
	std::string m_mongo60sColName; ///< mongodb 60s data column name

	BarIndicatorPtr m_emptyBarIndicator; ///< null bar indicator

	BarListPtr m_barList; ///< bars
	RollingXYPtr m_rxyPxVolume; ///< rolling price volume
	RollingPtr m_rFlips; ///< rolling flips

	boost::unordered_map<std::string, BarIndicatorPtr > m_barIndicators;///< bar indicator map
	std::vector<std::string> m_barIndicatorNames; ///< bar indicator names

public:




	/** 
	* @name events
	*/
	///@{
 

	/**
	* @brief connect signal NewBar
	*/
	boost::signals2::connection connectSignalNewBar(const boost::signals2::signal<void(int, int64_t)>::slot_type & subscriber);

	/**
	* @brief fire NewBar event
	*/
	void emitSignalNewBar(int iid, int64_t begindt);


	///@}

protected:
	boost::signals2::signal<void(int, int64_t)> m_signalNewBar;///< new bar signal


};

//////typedef for BarMaker
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<BarMaker> BarMakerPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<BarMaker> BarMakerPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<BarMaker> BarMakerPtr;

#else

typedef ::boost::shared_ptr<BarMaker> BarMakerPtr;
#endif


typedef ::sf::safe_ptr<BarMaker> BarMakerSafePtr;

typedef sf::contfree_safe_ptr<BarMaker> BarMakerContFreePtr;
//////end typedef for BarMaker


}//namespace XT



#endif
