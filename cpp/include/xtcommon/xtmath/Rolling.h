#pragma once
#ifndef XT_ROLLING_H
#define XT_ROLLING_H
/**
* \file Rolling.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for rolling window.
*
* \description
*	Designed for storing value information of a rolling window.
*/

#include <cstdint>
#include <queue>
#include <deque>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "EnumHelper.h"

#include "Util.h"

namespace XT {

class XT_COMMON_API Rolling {
public:

 	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	Rolling();

	/**
	* @brief constructor
	*
	* @param span in seconds
	* @param rtype as rolling type
	* @param dttype as date time type
	*/
  Rolling(int32_t span , RollingType::enumtype rtype , DateTimeType::enumtype dttype  );

  /**
  * @brief default copy constructor
  */
  Rolling(const Rolling& from) = default;

  /**
  * @brief default copy assignment
  */
  Rolling& operator=(const Rolling& from) = default;

  /**
  * @brief destructor
  */
  virtual ~Rolling();

  /**
  * @brief initialization
  *
  * @param span in seconds
  * @param rtype as rolling type
  * @param dttype as date time type
  */
  void init(int32_t span, RollingType::enumtype rtype, DateTimeType::enumtype dttype);

	///@}

 	/** 
	* @name Updating Functions
	*/
	///@{
  
  /**
  * @brief add x value
  *
  * @param dt as timestamp or tick
  * @param x as double value
  */
  void add(int64_t dt, double x);
  
  /**
  * @brief update time or tick
  *
  * @param dt as timestamp or tick
  */
  void update(int64_t dt);

  /**
  * @brief update time
  *
  * @param dt as timestamp
  */
  void updateByTime(int64_t dt);

  /**
  * @brief update tick
  *
  * @param dt as tick number
  */
  void updateByTick(int64_t dt);

	///@}

 	/** 
	* @name Getters
	*/
	///@{
 
		/**
		* @brief sequence number
		*
		* @return sequence number
		*/
        int32_t getSeqnum() ;

		/**
		* @brief begin timestamp
		*
		* @return begin timestamp
		*/
        int64_t getBeginDT();

		/**
		* @brief span timestamp
		*
		* @return span timestamp
		*/
        int64_t getSpanDT();

		/**
		* @brief current timestamp
		*
		* @return current timestamp
		*/
        int64_t getCurrDT();

		/**
		* @brief last value
		*
		* @return last value
		*/
        double getLast();

		/**
		* @brief sum of all values
		*
		* @return sum of all values
		*/
        double getSumTot();

		/**
		* @brief average of all values
		*
		* @return average of all values
		*/
        double getAvgTot() ;

		/**
		* @brief sum of all absolute values
		*
		* @return sum of all absolute values
		*/
        double getSumAbsTot() ;

		/**
		* @brief average of all absolute values
		*
		* @return average of all absolute values
		*/
        double getAvgAbsTot() ;

		/**
		* @brief sum of all positives
		*
		* @return sum of all positives
		*/
        double getSumPosTot() ;

		/**
		* @brief average all positives
		*
		* @return average all positives
		*/
        double getAvgPosTot() ;

		/**
		* @brief sum of all negatives
		*
		* @return sum of all negatives
		*/
        double getSumNegTot() ;

		/**
		* @brief average of all negatives
		*
		* @return average of all negatives
		*/
        double getAvgNegTot() ;

		/**
		* @brief sum of all x*x
		*
		* @return sum of all x*x
		*/
        double getSumM2Tot() ;

		/**
		* @brief average of all x*x
		*
		* @return average of all x*x
		*/
        double getAvgM2Tot() ;


		/**
		* @brief begin value of rolling window
		*
		* @return begin value of window
		*/
		double getBeginValue();

		/**
		* @brief end value of rolling window
		*
		* @return end value of window
		*/
		double getEndValue();

		/**
		* @brief begin value of previous rolling window
		*
		* @return begin value of previous window
		*/
		double getBeginValuePrev();

		/**
		* @brief end value of previous rolling window
		*
		* @return end value of previous window
		*/
		double getEndValuePrev();


		/**
		* @brief begin timestamp of rolling window
		*
		* @return begin timestamp of window
		*/
		int64_t getBeginTs();

		/**
		* @brief end timestamp of rolling window
		*
		* @return end timestamp of window
		*/
		int64_t getEndTs();

		/**
		* @brief begin timestamp of previous rolling window
		*
		* @return begin timestamp of previous window
		*/
		int64_t getBeginTsPrev();

		/**
		* @brief end timestamp of previous rolling window
		*
		* @return end timestamp of previous window
		*/
		int64_t getEndTsPrev();

		/**
		* @brief min value
		*
		* @return min value
		*/
        double getMinValue();

		/**
		* @brief max value
		*
		* @return max value
		*/
        double getMaxValue() ;

		/**
		* @brief got new min value
		*
		* @return if it has a new min
		*/
        bool hasNewMin() ;

		/*
		* @brief got new max value
		*
		* @return if it has a new max
		*/
        bool hasNewMax();

		/**
		* @brief sum
		*/
        double getSum() ;
		/**
		* @brief average
		*
		* @return average
		*/
        double getAvg()  ;

		/**
		* @brief sum of absolute values
		*
		* @return sum of absolute values
		*/
        double getSumAbs()  ;

		/**
		* @brief average of absolute values
		* 
		* @return average of absolute values
		*/
        double getAvgAbs() ;

		/**
		* @brief sum of positives
		*
		* @return sum of positives
		*/
        double getSumPos() ;

		/**
		* @brief average of positives
		*
		* @return average of positives
		*/
        double getAvgPos() ;

		/**
		* @brief sum of negatives
		*
		* @return sum of negatives
		*/
        double getSumNeg() ;

		/**
		* @brief average of negatives
		*
		* @return average of negatives
		*/
        double getAvgNeg() ;

		/**
		* @brief sum of x*x
		*
		* @return sum of x*x
		*/
        double getSumM2() ;

		/**
		* @brief average of 2nd moment
		*/
        double getAvgM2()  ;

		/**
		* @brief get current size
		*/
		int getSizeCurr();

		/**
		* @brief get previous size
		*/
		int getSizePrev();


		/**
		* @brief previous sum
		*
		* @return previous sum
		*/
        double getSumPrev()  ;

		/**
		* @brief previous average
		*
		* @return previous average 
		*/
        double getAvgPrev()  ;

		/**
		* @brief previous sum of absolute values
		* 
		* @return previous sum of absolute values
		*/
        double getSumAbsPrev()  ;

		/**
		* @brief previous average of absolute values
		*
		* @return previous average of absolute values
		*/
        double getAvgAbsPrev() ;

		/**
		* @brief previous sum of positives
		*
		* @return prvious sum of positions
		*/
        double getSumPosPrev() ;

		/**
		* @brief previous average of positives
		*
		* @return previous average of positives
		*/
        double getAvgPosPrev()  ;

		/**
		* @brief previous sum of negatives
		*
		* @return previous sum of nagatives
		*/
        double getSumNegPrev()  ;

		/**
		* @brief previous average of negatives
		* 
		* @return previous average of negative values
		*/
        double getAvgNegPrev()  ;
		
		/**
		* @brief previous sum of x*x
		*
		* @return previous sum of x*x
		*/
        double getSumM2Prev() ;

		/**
		* @brief previous average 2nd moment
		*
		* @return previous average of 2nd moment
		*/
        double getAvgM2Prev()  ;

		/**
		* @brief relative strength indicator
		*
		* @return rsi value
		*/
        double getRsi() ;

		/**
		* @brief previous relative strength indicator
		*
		* @return previous rsi
		*/
        double getRsiPrev() ;

		/**
		* @brief relative strength indicator change
		* 
		* @return rsi change
		*/
        double getRsiChg() ;

		/**
		* @brief min in rolling window
		* 
		* @return min value
		*/
		double getMinRolling();

		/**
		* @brief min in prev rolling wiindow
		*
		* @return previous min value
		*/
		double getMinRollingPrev();

		/**
		* @brief max in rolling window
		*
		* @return max value
		*/
		double getMaxRolling();

		/**
		* @brief max in prev rolling window
		*
		* @reurn previous max value
		*/
		double getMaxRollingPrev();

	///@}

protected:
	RollingType::enumtype m_rollingType; ///< rolling type
    DateTimeType::enumtype m_dtType; ///< datetime type

    int32_t m_span; ///< span
    int64_t m_spanDT; ///< span datetime
    int32_t m_seqnum; ///< sequence number
    int64_t m_beginDT; ///< begin datetime
    int64_t m_currDT; ///< current datetime
    double m_last; ///< last value

    double m_min; ///< min value
    double m_max; ///< max value

    bool m_hasNewMin; ///< got new min
    bool m_hasNewMax; ///< got new max

    double m_sum; ///< sum
    double m_sumAbs;///< absolute sum
    double m_sumPos; ///< positive sum
    double m_sumNeg; ///< negative sum
    double m_summ2; ///< sum of x*x

	double m_sumPrev; ///< sum of previous
    double m_sumAbsPrev; ///< sum of preivous absolute
    double m_sumPosPrev; ///< sum of previous positives
    double m_sumNegPrev; ///< sum of previous negatives
    double m_summ2Prev; ///< sum of previous x*x

    double m_sumTot; ///< sum total
    double m_sumAbsTot; ///< sum of absolute total
    double m_sumPosTot; ///< sum of postive total
    double m_sumNegTot; ///< sum of negative total
    double m_summ2Tot; ///< sum of x*x total

	sf::contfree_safe_ptr<std::queue<int64_t> > m_timestamps; ///< timestamps
	sf::contfree_safe_ptr<std::queue<double> > m_values; ///< values
	sf::contfree_safe_ptr<std::queue<int64_t> > m_timestampsPrev; ///< previous timestamps
	sf::contfree_safe_ptr<std::queue<double> > m_valuesPrev; ///< previous values


// min and max
protected:
	double m_minRolling; ///< min value in rolling window
	double m_minRollingPrev; ///< min value in previous rolling window
	double m_maxRolling; ///< max value in rolling window
	double m_maxRollingPrev; ///< max value in previous rolling window

	sf::contfree_safe_ptr<std::deque<std::pair<int64_t, double> > > m_minWindow; ///< rolling window for min valuc calucaltion
	sf::contfree_safe_ptr<std::deque<std::pair<int64_t, double> > > m_minWindowPrev; ///< previous rolling window for min valuc calucaltion

	sf::contfree_safe_ptr<std::deque<std::pair<int64_t, double> > > m_maxWindow; ///< rolling window for max valuc calucaltion
	sf::contfree_safe_ptr<std::deque<std::pair<int64_t, double> > > m_maxWindowPrev; ///< previous rolling window for max valuc calucaltion

protected:
	/**
	* @brief add value to calculate min/max value
	*
	* @param ts as timestamp
	* @param v as double value
	*/
	void addForMinMax(int64_t ts, double v);

	/**
	* @brief add value to calculate previous min/max value
	*
	* @param ts as timestamp
	* @param v as double value
	*/
	void addForMinMaxPrev(int64_t ts, double v);

	/**
	* @brief add value to calculate min/max value in a tick rolling window
	*
	* @param ts as timestamp
	* @param v as double value
	*/
	void addForMinMaxByTick(  double v);

	/**
	* @brief add value to calculate min/max value in a previous tick rolling window
	*
	* @param ts as timestamp
	* @param v as double value
	*/
	void addForMinMaxPrevByTick(  double v);


}; //end class Rolling

   //////typedef for Rolling
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<Rolling> RollingPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<Rolling> RollingPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<Rolling> RollingPtr;

#else

typedef ::boost::shared_ptr<Rolling> RollingPtr;
#endif


typedef ::sf::safe_ptr<Rolling> RollingSafePtr;

typedef sf::contfree_safe_ptr<Rolling> RollingContFreePtr;
//////end typedef for Rolling

} //end namespace XT


#endif