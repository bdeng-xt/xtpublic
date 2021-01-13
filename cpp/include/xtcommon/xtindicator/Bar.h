#pragma once
#ifndef XT_BAR_H
#define XT_BAR_H

/**
* \file Bar.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide classes for Bar, BarList.
*
* \description
*	Designed for bar related classes.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

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
#include "typedef_XTData.pb.h"
#include "TagDataWrapper.h"
#include "EnumHelper.h"

namespace XT
{
	class Bar;
	//////typedef for Bar
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Bar> BarPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Bar> BarPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Bar> BarPtr;

#else

	typedef ::boost::shared_ptr<Bar> BarPtr;
#endif


	typedef ::sf::safe_ptr<Bar> BarSafePtr;

	typedef sf::contfree_safe_ptr<Bar> BarContFreePtr;
	//////end typedef for Bar
	typedef std::vector<boost::shared_ptr<BarPtr> > BarPtrVec;
	typedef ::boost::shared_ptr<BarPtrVec> BarPtrVecPtr;

	class BarList;
	//////typedef for BarList
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<BarList> BarListPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<BarList> BarListPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<BarList> BarListPtr;

#else

	typedef ::std::shared_ptr<BarList> BarListPtr;
#endif


	typedef ::sf::safe_ptr<BarList> BarListSafePtr;

	typedef sf::contfree_safe_ptr<BarList> BarListContFreePtr;
	//////end typedef for BarList

//////////////////////////////////////////////////////////
	class BarMap;
	//////typedef for BarMap
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<BarMap> BarMapPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<BarMap> BarMapPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<BarMap> BarMapPtr;

#else

	typedef ::std::shared_ptr<BarMap> BarMapPtr;
#endif


	typedef ::sf::safe_ptr<BarMap> BarMapSafePtr;

	typedef sf::contfree_safe_ptr<BarMap> BarMapContFreePtr;
	//////end typedef for BarMap


/////////////////////////////////////////////////////////

	class XT_COMMON_API Bar
	{
	public:

		/** @name Constructor and Initialization
		*
		*/
		///@{
		/**
		* @brief constructor
		*/
		Bar();

		/**
		* @brief default copy constructor
		*/
		Bar(const Bar& from);// = default;

		/**
		* @brief default copy assignment
		*/
		Bar& operator=(const Bar& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~Bar();


		///@}

		/** 
		* @name BarData and TagData
		*/
		///@{
		/**
		* @brief get BarData pointer
		*
		* @return bardata
		*/
		BarDataPtr& barData();

		/**
		* @brief get TagData pointer
		*
		* @return tagdatawrapper
		*/
		TagDataWrapperPtr& tagData();
		///@}

		/** 
		* @name Getters and Setters
		*/
		///@{

		/**
		* @brief get open price
		*
		* @return open price
		*/
		double getOpen();

		/**
		* @brief get high price
		*
		* @return high price
		*/
		double getHigh();

		/**
		* @brief get low price
		*
		* @return low price
		*/
		double getLow();

		/**
		* @brief get close price
		*
		* @return close price
		*/
		double getClose();

		/**
		* @brief get volume
		*
		* @return volume
		*/
		int64_t getVolume();

		/**
		* @brief get open interest change
		* 
		* @return open interest change
		*/
		int64_t getOichg();

		/**
		* @brief get buy sell volume difference
		*
		* @return buy sell volume difference
		*/
		int64_t getBsvoldiff();

		/**
		* @brief get turnover
		*
		* @return turnover
		*/
		double getAmount();

		/**
		* @brief get buy sell amount difference
		*
		* @return buy sell amount difference
		*/
		double getBsadiff();

		/**
		* @brief get flip ups
		*
		* @return flip ups
		*/
		double getFlipups();

		/**
		* @brief get flip dns
		*
		* @return flip downs
		*/
		double getFlipdns();

		/**
		* @brief get flag
		*
		* @return flag
		*/
		int getFlag();

		/**
		* @brief is full or not
		*
		* @return if a bar is full or not
		*/
		bool isFull();

		/**
		* @briefset open price
		*
		* @param v as open price
		*/
		void setOpen(double v);

		/**
		* @brief set high price
		*
		* @param v as high price
		*/
		void setHigh(double v);

		/**
		* @brief set low price
		*
		* @param v as low price
		*/
		void setLow(double v);

		/**
		* @brief set close price
		*
		* @param v as close price
		*/
		void setClose(double v);

		/**
		* @brief set volume
		*
		* @param v as volume
		*/
		void setVolume(int64_t v);

		/**
		* @brief set open interest change
		*
		* @param v as open interest change
		*/
		void setOichg(int64_t v);

		/**
		* @brief set buy sell volume difference
		*
		* @param v as buy sell volume difference
		*/
		void setBsvoldiff(int64_t v);

		/**
		* @brief set begin datetime
		*
		* @param v as begin datetime
		*/
		void setBegindt(int64_t v);

		/**
		* @brief set end datetime
		*
		* @param v as end datetime
		*/
		void setEnddt(int64_t v);

		/**
		* @brief set turnover
		*
		* @param v as turnover
		*/
		void setAmount(double v);

		/**
		* @brief set buy sell turnover difference
		*
		* @param v as buy sell turnover difference
		*/
		void setBsadiff(double v);

		/**
		* @brief set flip ups
		*
		* @param v as flip ups
		*/
		void setFlipups(double v);

		/**
		* @brief set flip dns
		*
		* @param v as flip downs
		*/
		void setFlipdns(double v);

		/**
		* @brief set flag
		*
		* @param v as bar flag
		*/
		void setFlag(int v);

		/**
		* @brief get price change
		*
		* @return price change
		*/
		double getChg();

		/**
		* @brief get median price
		*
		* @return median price
		*/
		double getMedian();

		/**
		* @brief get typical price
		*
		* @return typical price
		*/
		double getTypical();

		/**
		* @brief get weighted price
		*
		* @return weighted price
		*/
		double getWeighted();

		//        public Int32 nPx { get { return m_data.nBuy + m_data.nSell; } }
		/**
		* @brief get q1 price
		*
		* @return 25th quantile price
		*/
		double getQ1Px();

		/**
		* @brief get q3 price
		*
		* @return 75th quantile price
		*/
		double getQ3Px();
		//        public double vwapBuy { get { return m_data.buyVolume > 0 ? m_data.sumBuyPxVolume / m_data.buyVolume : 0.0; } }
		//        public double vwapSell { get { return m_data.sellVolume > 0 ? m_data.sumSellPxVolume / m_data.sellVolume : 0.0; } }
		//        public double vwap { get { return (m_data.buyVolume + m_data.sellVolume) > 0 ? (m_data.sumBuyPxVolume + m_data.sumSellPxVolume) / (m_data.buyVolume + m_data.sellVolume) : 0.0; } }
		/**
		* @brief get begin datetime
		*
		* @return begin timestamp
		*/
		int64_t getBegindt();

		/**
		* @brief get end datetime
		*
		* @return end timestamp
		*/
		int64_t getEnddt();

		/**
		* @brief get mid datetime
		*
		* @return bar mid timestamp
		*/
		int64_t getMiddt();

		/**
		* @brief get double value from tagdata
		*
		* @return double value
		*/
		double getDouble(int tag);

		/**
		* @brief set double value for tagdata
		*
		* @param tag as integer
		* @param v as value
		*/
		void setDouble(int tag, double v);

		/**
		* @brief get int value from tagdata
		*
		* @param tag as integer
		*  
		* @return integer value 
		*/
		int getInt32(int tag);

		/**
		* @brief set int value for tagdata
		*
		* @param tag as integer
		* @param v as value
		*/
		void setInt32(int tag, int v);
		///@}

		/** 
		* @name Sql
		*/
		///@{
		/**
		* @brief get pgsql insert string
		*
		* @param exch as exchid
		* @param instrid as string
		* @param span as bar seconds
		*/
		std::string getPgsqlInsert(const std::string& exch, const std::string& instrid, int span);
		/**
		* @brief get pgsql upsert string
		*/
		std::string getPgsqlUpsert(const std::string& exch, const std::string& instrid, int span);
		/**
		* @brief get sql insert string
		*
		* @param exch as exchid
		* @param instrid as string
		* @param span as bar seconds
		*/
		std::string getSqlInsert(const std::string& exch, const std::string& instrid, int span);
		/**
		* @brief get sqlite upsert string
		*
		* @param exch as exchid
		* @param instrid as string
		* @param span as bar seconds
		*/
		std::string getSqliteUpsert(const std::string& exch, const std::string& instrid, int span);

		/**
		* @brief get mongodb insert document
		*
		* @param instrid as string
		*
		* @return mongodb document string
		*/
		std::string getMongoDocument(const std::string& instrid);
		///@}

		/** 
		* @name String Functions
		*/
		///@{
		/**
		* @brief get csv string
		*
		* @return csv string
		*/
		std::string toCsvStr();

		/**
		* @brief get json string
		*
		* @return json string
		*/
		std::string toJsonStr();
		///@}

		/**
		* @brief clone
		*
		* @return cloned bar
		*/
		BarPtr clone();

		/** @name static functions
		*/
		///@{
		/**
		* @brief compare two bars
		*
		* @param bar1 as first bar
		* @param bar2 as second bar
		*
		* @return if bar1 is less than bar2
		*/
		static bool compareBar(const BarPtr& bar1, const BarPtr& bar2);
		///@}
	protected:
		BarDataPtr m_data; ///< BarData data
		TagDataWrapperPtr m_tagdata; ///< TagDataWrapper data

	};//class XT_COMMON_API Bar 


////////////////////////////////////////
class XT_COMMON_API BarList
{
	public:
		/** @name Constructor and Initialization
		*
		*/

		///@{
		/**
		* @brief constructor
		*/
		BarList();

		/**
		* @brief default copy constructor
		*/
		BarList(const BarList& from);// = default;

		/**
		* @brief default copy assignment
		*/
		BarList& operator=(const BarList& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~BarList();

		///@}
	public:
		/**
		* @brief initialization
		*/
		void init();

		/**
		* @brief initialize data vector
		*/
		void initDataVectors();

	protected:
		/**
		* @brief initialization without lock
		*/
		void initWithoutLock();

		/**
		* @brief initialize data vector without lock
		*/
		void initDataVectorsWithoutLock();

	public:
		/**
		* @brief set span seconds
		*
		* @param span as seconds
		*/
		void setSpan(int span);

		/**
		* @brief get span seconds
		*
		* @return span seconds
		*/
		int getSpan();

		/**
		* @brief set rolling type
		* 
		* @param rt as RollingType
		*/
		void setRollingType(RollingType::enumtype rt);

		/**
		* @brief get rolling type
		*
		* @return RollingType
		*/
		RollingType::enumtype getRollingType();

		/**
		* @brief set date time type
		*
		* @param dttype as DateTimeType
		*/
		void setDateTimeType(DateTimeType::enumtype dttype);

		/**
		* @brief get date time type
		*
		* @return DateTimeType
		*/
		DateTimeType::enumtype getDateTimeType();


		/**
		* @brief bar list
		*
		* @return barlist
		*/
		std::map<int64_t, BarPtr >& bars();

		/**
		* @brief open data
		* 
		* @return open data vector
		*/
		std::vector<double>& opens();

		/**
		* @brief high data
		*
		* @return high data vector
		*/
		std::vector<double>& highs();

		/**
		* @brief low data
		*
		* @return low data vector
		*/
		std::vector<double>& lows();

		/**
		* @brief close data
		*
		* @return close data vector
		*/
		std::vector<double>& closes();

		/**
		* @brief volume data
		*
		* @return volume data vector
		*/
		std::vector<double>& volumes();

		/**
		* @brief open interest change data
		*
		* @return open interest change data vector
		*/
		std::vector<double>& oichgs();

		/**
		* @brief buy sell volume difference data
		*
		* @return buy sell volume difference data vector
		*/
		std::vector<double>& bsvoldiffs();

		/**
		* @brief turnover data
		*
		* @return turnover data vector
		*/
		std::vector<double>& turnovers();

		/**
		* @brief buy sell turnover difference data
		*
		* @return buy sell turnover difference data vector
		*/
		std::vector<double>& bstdiffs();

		/**
		* @brief flip ups data
		*
		* @return flip ups data vector
		*/
		std::vector<double>& flipups();

		/**
		* @brief flip downs data
		*
		* @return flip downs data vector
		*/
		std::vector<double>& flipdns();

//////
/**
* @brief open data
*
* @return open data vector
*/
		std::vector<double> getOpens();

		/**
		* @brief high data
		*
		* @return high data vector
		*/
		std::vector<double> getHighs();

		/**
		* @brief low data
		*
		* @return low data vector
		*/
		std::vector<double> getLows();

		/**
		* @brief close data
		*
		* @return close data vector
		*/
		std::vector<double> getCloses();

		/**
		* @brief volume data
		*
		* @return volume data vector
		*/
		std::vector<double> getVolumes();

		/**
		* @brief open interest change data
		*
		* @return open interest change data vector
		*/
		std::vector<double> getOichgs();

		/**
		* @brief buy sell volume difference data
		*
		* @return buy sell volume difference data vector
		*/
		std::vector<double> getBsvoldiffs();

		/**
		* @brief turnover data
		*
		* @return turnover data vector
		*/
		std::vector<double> getAmounts();

		/**
		* @brief buy sell turnover difference data
		*
		* @return buy sell turnover difference data vector
		*/
		std::vector<double> getBsadiffs();

		/**
		* @brief flip ups data
		*
		* @return flip ups data vector
		*/
		std::vector<double> getFlipups();

		/**
		* @brief flip downs data
		*
		* @return flip downs data vector
		*/
		std::vector<double> getFlipdns();
//////

		/**
		* @brief get last timestamp
		*
		* @return last timestamp
		*/
		int64_t getLastTs();

		/**
		* @brief if has new bar or not
		*
		* @return it barlist has new bar or not
		*/
		bool hasNewBar();

		/**
		* @brief if has new high or not
		*
		* @return it barlist has new high or not
		*/
		bool hasNewBarHigh();

		/**
		* @brief if has new low or not
		*
		* @return it barlist has new low or not
		*/
		bool hasNewBarLow();

		/**
		* @brief set pxpointvalue
		*
		* @param v as price point value
		*/
		void setPxPointValue(double v);

		/**
		* @brief get pxpointvalue
		*
		* @return price point value
		*/
		double getPxPointValue();

		/**
		* @brief set number
		*
		* @param n as number
		*/
		void setNum(int n);

		/**
		* @brief get number
		*
		* @return number
		*/
		int getNum();

protected:
	/**
	* @brief try to test if a new bar is needed or not
	*
	* @return if a new bar is added or not
	*/
	bool tryToAddNewBarWithoutLock(int64_t dt, double d);
public:
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
	void addData(int64_t ts, double px, int64_t volume, int64_t oichg, int64_t bsvoldiff, double turnover, double bstdiff, double flipup, double flipdn);

public:
		/**
		* @brief add a bar
		*/
		void addBar(const BarPtr& bar);

		/**
		* @brief add bars from another barlist
		*/
		void addOther(const BarListPtr& other);

		/**
		* @brief add bars vector
		*/
		void addBarVector(std::vector<BarPtr > & barsVector);

		/**
		* @brief add bars map
		*/
		void addBarMap(std::map<int64_t, BarPtr > & barsMap);

		/**
		* @brief get timestamp by bar index
		* 
		* @return timestamp
		*/
		int64_t getTsByIdx(int idx);

		/**
		* @brief get timestamp by bar index0
		*
		* @return timestamp
		*/
		int64_t getTsByIdx0(int idx);

		/**
		* @brief get first bar
		*
		* @return first bar
		*/
		BarPtr& getFirstBar();

		/**
		* @brief get last bar
		*
		* @return last bar
		*/
		BarPtr& getLastBar();

		/**
		* @brief get second to last bar
		*
		* @return second to last bar
		*/
		BarPtr& getSecondToLastBar();

		/**
		* @brief get last full bar
		*
		* @return last full bar
		*/
		BarPtr& getLastFullBar();

		/**
		* @brief get last full bar index
		*
		* @return bar index
		*/
		int getLastFullBarIdx();

		/**
		* @brief get total bar count
		*
		* @return bar count
		*/
		int getBarCount();

		/**
		* @brief get bar by index
		* 
		* @param idx as bar index
		* 
		* @return bar
		*/
		BarPtr& getBar(int idx);

		/**
		* @brief get bar by timestamp
		*
		* @param ts as timestamp
		*
		* @return bar
		*/
		BarPtr& getBarByTs(int64_t ts);

		/**
		* @brief deep clone
		*
		* @return cloned barlist
		*/
		BarListPtr clone();


	/**
	* @name Stat Functions
	*/
		///@{
		/**
		* @brief get highest price between bars
		* 
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighPxBetween(int idx0, int idx1);

		/**
		* @brief get lowest price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getLowPxBetween(int idx0, int idx1);

		/**
		* @brief get mean price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getMeanPxBetween(int idx0, int idx1);

		/**
		* @brief get standard deviation price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getStdPxBetween(int idx0, int idx1);

		/**
		* @brief get high price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getHighPxInLastNBars(int lookback);

		/**
		* @brief get low price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getLowPxInLastNBars(int lookback);


		/**
		* @brief get mean price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getMeanPxInLastNBars(int lookback);

		/**
		* @brief get standard deviation price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getStdPxInLastNBars(int lookback);


		/**
		* @brief get close volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getCloseVolatilityBetween(int idx0, int idx1);

		/**
		* @brief get high low volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighLowVolatilityBetween(int idx0, int idx1);


		/**
		* @brief get high low close volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighLowCloseVolatilityBetween(int idx0, int idx1);



		///@}

	protected:
		static BarPtr s_EmptyBar; ///< null bar
	public:
		/**
		* @brief get null bar
		*
		* @return null bar
		*/
		static BarPtr& getEmptyBar();

		/**
		* @brief create a barlist with span
		*
		* @param span as seconds
		*
		* @return a barlist
		*/
		static BarListPtr create(int span);

		/**
		* @brief resample barlist
		*
		* @param barlist0 as original barlist
		* @param span as new bar seconds
		*
		* @return a barlist
		*/
		static BarListPtr resampleBarList(BarListPtr barlist0, int span);

		/**
		* @brief add barlist vector
		*
		* @param barlistvector
		*
		* @return a added barlist
		*/
		static BarListPtr addBarListVector(std::vector<BarListPtr > barlistvec);

	protected:
		int m_span;///< bar seconds
		int64_t m_spandt; ///< bar length in microseconds
		XT::RollingType::enumtype m_rollingType; ///< rolling type
		XT::DateTimeType::enumtype m_dtType; ///< datatime type


		int64_t m_lastTs; ///< last timestamp
		bool m_hasNewBar; ///< new bar flag
		bool m_hasNewBarHigh; ///< new high flag
		bool m_hasNewBarLow; ///< new low flag

		double m_pxPointValue; ///< price point value
		int m_num; ///< number for adding

		std::map<int32_t, int64_t> m_idxTs; ///< bar index to timestamp map
		std::map<int64_t, BarPtr > m_bars; ///< bar map
		BarPtr m_currBar; ///< current bar

		std::vector<double> m_opens; ///< open vector
		std::vector<double> m_highs; ///< high vector
		std::vector<double> m_lows; ///< low vector
		std::vector<double> m_closes; ///< close vector

		std::vector<double> m_volumes; ///< volume vector
		std::vector<double> m_oichgs; ///< open interest change vector
		std::vector<double> m_bsvoldiffs; ///< buy sell volume difference vector

		std::vector<double> m_turnovers; ///< turnover vector
		std::vector<double> m_bstdiffs; ///< buy sell turnover difference vector

		std::vector<double> m_flipups; ///< flip up vector
		std::vector<double> m_flipdns; ///< flip down vector

		/**
		* @brief generate bar index to timestamp map
		*/
//		void generateIdxTsMap();

		/**
		* @brief generate data vectors
		*/
	//	void generateDataVectors();

	protected:
		void generateIdxTsMapWithoutLock();

 
		void generateDataVectorsWithoutLock();

	protected:
		mutable  boost::shared_mutex m_mutex;

	};//class XT_COMMON_API BarList


////////////////////////////////////////
	class XT_COMMON_API BarMap
	{
	public:
		/** @name Constructor and Initialization
		*
		*/

		///@{
		/**
		* @brief constructor
		*/
		BarMap();

		/**
		* @brief default copy constructor
		*/
		BarMap(const BarMap& from);// = default;

									 /**
									 * @brief default copy assignment
									 */
		BarMap& operator=(const BarMap& from);// = default;

												/**
												* @brief destructor
												*/
		virtual ~BarMap();

		///@}
	public:
		/**
		* @brief initialization
		*/
		void init();

		/**
		* @brief initialize data vector
		*/
		void initDataVectors();

	public:
		/**
		* @brief set span seconds
		*
		* @param span as seconds
		*/
		void setSpan(int span);

		/**
		* @brief get span seconds
		*
		* @return span seconds
		*/
		int getSpan();

		/**
		* @brief set rolling type
		*
		* @param rt as RollingType
		*/
		void setRollingType(RollingType::enumtype rt);

		/**
		* @brief get rolling type
		*
		* @return RollingType
		*/
		RollingType::enumtype getRollingType();

		/**
		* @brief set date time type
		*
		* @param dttype as DateTimeType
		*/
		void setDateTimeType(DateTimeType::enumtype dttype);

		/**
		* @brief get date time type
		*
		* @return DateTimeType
		*/
		DateTimeType::enumtype getDateTimeType();


		/**
		* @brief bar list
		*
		* @return barlist
		*/
		::google::protobuf::Map< ::google::protobuf::int64, ::XT::BarData >* bars();

		/**
		* @brief open data
		*
		* @return open data vector
		*/
		std::vector<double> getOpens();

		/**
		* @brief high data
		*
		* @return high data vector
		*/
		std::vector<double> getHighs();

		/**
		* @brief low data
		*
		* @return low data vector
		*/
		std::vector<double> getLows();

		/**
		* @brief close data
		*
		* @return close data vector
		*/
		std::vector<double> getCloses();

		/**
		* @brief volume data
		*
		* @return volume data vector
		*/
		std::vector<double> getVolumes();

		/**
		* @brief open interest change data
		*
		* @return open interest change data vector
		*/
		std::vector<double> getOichgs();

		/**
		* @brief buy sell volume difference data
		*
		* @return buy sell volume difference data vector
		*/
		std::vector<double> getBsvoldiffs();

		/**
		* @brief turnover data
		*
		* @return turnover data vector
		*/
		std::vector<double> getAmounts();

		/**
		* @brief buy sell turnover difference data
		*
		* @return buy sell turnover difference data vector
		*/
		std::vector<double> getBsadiffs();

		/**
		* @brief flip ups data
		*
		* @return flip ups data vector
		*/
		std::vector<double> getFlipups();

		/**
		* @brief flip downs data
		*
		* @return flip downs data vector
		*/
		std::vector<double> getFlipdns();

		/**
		* @brief get last timestamp
		*
		* @return last timestamp
		*/
		int64_t getLastTs();

		/**
		* @brief if has new bar or not
		*
		* @return it barlist has new bar or not
		*/
		bool hasNewBar();

		/**
		* @brief if has new high or not
		*
		* @return it barlist has new high or not
		*/
		bool hasNewBarHigh();

		/**
		* @brief if has new low or not
		*
		* @return it barlist has new low or not
		*/
		bool hasNewBarLow();

		/**
		* @brief set pxpointvalue
		*
		* @param v as price point value
		*/
		void setPxPointValue(double v);

		/**
		* @brief get pxpointvalue
		*
		* @return price point value
		*/
		double getPxPointValue();

		/**
		* @brief set number
		*
		* @param n as number
		*/
		void setNum(int n);

		/**
		* @brief get number
		*
		* @return number
		*/
		int getNum();

	protected:
		/**
		* @brief try to test if a new bar is needed or not
		*
		* @return if a new bar is added or not
		*/
		bool tryToAddNewBarWithoutLock(int64_t dt, double d);
	public:
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
		void addData(int64_t ts, double px, int64_t volume, int64_t oichg, int64_t bsvoldiff, double amount, double bsadiff, double flipup, double flipdn);

	public:
		/**
		* @brief add a bar
		*/
		void addBar(const BarDataPtr& bar);

		/**
		* @brief add bars from another barlist
		*/
		void addOther(const BarMapPtr& other);

		/**
		* @brief add bars vector
		*/
		void addBarVector(std::vector<BarDataPtr > & barsVector);

		/**
		* @brief add bars map
		*/
		void addBars(std::map<int64_t, BarDataPtr > & barsMap);

		/**
		* @brief get timestamp by bar index
		*
		* @return timestamp
		*/
		int64_t getTsByIdx(int idx);

		/**
		* @brief get timestamp by bar index0
		*
		* @return timestamp
		*/
		int64_t getTsByIdx0(int idx);

		/**
		* @brief get first bar
		*
		* @return first bar
		*/
		BarDataPtr& getFirstBar();

		/**
		* @brief get last bar
		*
		* @return last bar
		*/
		BarDataPtr& getLastBar();

		/**
		* @brief get second to last bar
		*
		* @return second to last bar
		*/
		BarDataPtr& getSecondToLastBar();

		/**
		* @brief get last full bar
		*
		* @return last full bar
		*/
		BarDataPtr& getLastFullBar();

		/**
		* @brief get last full bar index
		*
		* @return bar index
		*/
		int getLastFullBarIdx();

		/**
		* @brief get total bar count
		*
		* @return bar count
		*/
		int getBarCount();

		/**
		* @brief get bar by index
		*
		* @param idx as bar index
		*
		* @return bar
		*/
		BarDataPtr& getBar(int idx);

		/**
		* @brief get bar by timestamp
		*
		* @param ts as timestamp
		*
		* @return bar
		*/
		BarDataPtr& getBarByTs(int64_t ts);

		/**
		* @brief deep clone
		*
		* @return cloned barlist
		*/
		BarMapPtr clone();


		/**
		* @name Stat Functions
		*/
		///@{
		/**
		* @brief get highest price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighPxBetween(int idx0, int idx1);

		/**
		* @brief get lowest price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getLowPxBetween(int idx0, int idx1);

		/**
		* @brief get mean price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getMeanPxBetween(int idx0, int idx1);

		/**
		* @brief get standard deviation price between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getStdPxBetween(int idx0, int idx1);

		/**
		* @brief get high price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getHighPxInLastNBars(int lookback);

		/**
		* @brief get low price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getLowPxInLastNBars(int lookback);


		/**
		* @brief get mean price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getMeanPxInLastNBars(int lookback);

		/**
		* @brief get standard deviation price in last N Bars
		*
		* @param lookback as number of bars to look back
		*/
		double getStdPxInLastNBars(int lookback);


		/**
		* @brief get close volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getCloseVolatilityBetween(int idx0, int idx1);

		/**
		* @brief get high low volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighLowVolatilityBetween(int idx0, int idx1);


		/**
		* @brief get high low close volatility between bars
		*
		* @param idx0 as start index
		* @param idx1 as end index
		*
		* @return double value
		*/
		double getHighLowCloseVolatilityBetween(int idx0, int idx1);



		///@}

	protected:
		static BarDataPtr s_EmptyBar; ///< null bar
	public:
		/**
		* @brief get null bar
		*
		* @return null bar
		*/
		static BarDataPtr& getEmptyBar();

		/**
		* @brief create a barmap with span
		*
		* @param span as seconds
		*
		* @return a barmap
		*/
		static BarMapPtr create(int span);

		/**
		* @brief resample barlist
		*
		* @param barlist0 as original barlist
		* @param span as new bar seconds
		*
		* @return a barlist
		*/
		static BarMapPtr resampleBarMap(BarMapPtr& barlist0, int span);

		/**
		* @brief add barmap vector
		*
		* @param barmapvector
		*
		* @return a added barmap
		*/
		static BarMapPtr addBarMapVector(std::vector<BarMapPtr > barmapvec);

	protected:
		
		BarDataMapPtr m_data; //map data
		
		int m_span;///< bar seconds
		int64_t m_spandt; ///< bar length in microseconds
		XT::RollingType::enumtype m_rollingType; ///< rolling type
		XT::DateTimeType::enumtype m_dtType; ///< datatime type



		int64_t m_lastTs; ///< last timestamp
		bool m_hasNewBar; ///< new bar flag
		bool m_hasNewBarHigh; ///< new high flag
		bool m_hasNewBarLow; ///< new low flag

		double m_pxPointValue; ///< price point value
		int m_num; ///< number for adding



		std::map<int32_t, int64_t> m_idxTs; ///< bar index to timestamp map
		std::map<int64_t, BarPtr > m_bars; ///< bar map
		BarPtr m_currBar; ///< current bar

		std::vector<double> m_opens; ///< open vector
		std::vector<double> m_highs; ///< high vector
		std::vector<double> m_lows; ///< low vector
		std::vector<double> m_closes; ///< close vector

		std::vector<double> m_volumes; ///< volume vector
		std::vector<double> m_oichgs; ///< open interest change vector
		std::vector<double> m_bsvoldiffs; ///< buy sell volume difference vector

		std::vector<double> m_turnovers; ///< turnover vector
		std::vector<double> m_bstdiffs; ///< buy sell turnover difference vector

		std::vector<double> m_flipups; ///< flip up vector
		std::vector<double> m_flipdns; ///< flip down vector

									   /**
									   * @brief generate bar index to timestamp map
									   */
		void generateIdxTsMapWithoutLock();

		/**
		* @brief generate data vectors
		*/
		void generateDataVectorsWithoutLock();

	};//class XT_COMMON_API BarList




}//namespace XT



#endif