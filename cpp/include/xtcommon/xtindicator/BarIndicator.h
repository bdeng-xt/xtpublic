#pragma once
#ifndef XT_BARINDICATOR_H
#define XT_BARINDICATOR_H

/**
* \file BarIndicator.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide classes for BarIndicator.
*
* \description
*	Designed for calculating bar indcators.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/array.hpp>

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

#include "StringMap.h"

#include "Bar.h"
#include "TALibFuncInfo.h"
#include "TALibMgr.h"
#include "ta_libc.h"

namespace XT
{



class XT_COMMON_API BarIndicator
{

public:
	/**
	* @name Constructors and Destructors
	*/
	///@{
	/**
	* @brief constructor
	*/
	BarIndicator();

	/**
	* @brief default copy constructor
	*/
	BarIndicator(const BarIndicator& from);// = default;

	/**
	* @brief default copy assignment
	*/
	BarIndicator& operator=(const BarIndicator& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~BarIndicator();
	///@}
public:
	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string& getName();

	/**
	* @brief set data barlist
	*
	* @param barlist as data 
	*/
	void setBarList(BarListPtr barlist);

	/**
	* @brief get data barlist
	*
	* @return barlist
	*/
	const BarListPtr& getBarList();

	/**
	* @brief get parameters
	*
	* @return stringmap as parameters
	*/
	const StringMapPtr& getParameters();

	/**
	* @brief get talib function information
	*
	* @return tablib function information
	*/
	const TALibFuncInfoPtr& getTALibFuncInfo();

 
	/**
	* @brief get double output value
	*
	* @param outidx as output index, it could be 0,1,2
	* @param baridx as bar index
	*
	* @return double output
	*/
	double getDoubleByIdx(int outidx, int baridx);

	/**
	* @brief get int output value
	*
	* @param baridx as bar index
	*
	* @return int output
	*/
	int getIntByIdx(int baridx);

	/**
	* @brief get double output vector
	*
	* @param outidx as output index, it could be 0,1,2
	* 
	* @return double vector output
	*/
	const std::vector<double>& getDoubleOutVector(int outidx);
	
	/**
	* @brief get int output vector
	*
	* @return int vector output
	*/
	const std::vector<int>& getIntOutVector();

	/**
	* @brief get double value by output name and baridx
	*
	* @param outputname as string
	* @param baridx as bar index
	*
	* @return double output value
	*/
	double getDoubleByOutputName(const std::string& outputname, int baridx);

	/**
	* @brief get int value by outputname and baridx
	*
	* @param outputname as string
	* @param baridx as bar index
	* 
	* @return int output value
	*/
	int getIntByOutputName(const std::string& outputname, int baridx);

	/**
	* @brief get output string by baridx
	*
	* @param baridx as bar index
	* 
	* @return output information as string
	*/
	std::string getOutputStrByIdx(int baridx);

public:
	/**
	* @name cross functions
	*/
	///@{
	/**
	* @brief check if output is crossing above on baridx
	*
	* @param outputidx as output index
	* @param thresh as threshold value
	* @param baridx as bar index
	*
	* @return if output is crossing above or not
	*/
	bool isCrossAboveOnBarIdx(int outputidx, double thresh, int baridx);

	/**
	* @brief check if output is crossing below on baridx
	*
	* @param outputidx as output index
	* @param thresh as threshold value
	* @param baridx as bar index
	*
	* @return if output is crossing below or not
	*/
	bool isCrossBelowOnBarIdx(int outputidx, double thresh, int baridx);

	/**
	* @brief check if output is crossing above on last index
	*
	* @param outputidx as output index
	* @param thresh as threshold value
	*
	* @return if output is crossing above or not
	*/
	bool isCrossAbove(int outputidx, double thresh);

	/**
	* @brief check if output is crossing below on last index
	*
	* @param outputidx as output index
	* @param thresh as threshold value
	*
	* @return if output is crossing below or not
	*/
	bool isCrossBelow(int outputidx, double thresh);

	/**
	* @brief check if output1 is crossing output2 above on baridx
	*
	* @param outputidx1 as output1 index
	* @param outputidx2 as output2 index
	* @param baridx as bar index
	*
	* @return if output is crossing above or not
	*/
	bool isOutputsCrossAboveOnBarIdx(int outputidx1, int outputidx2,   int baridx);

	/**
	* @brief check if output1 is crossing output2 below on baridx
	*
	* @param outputidx1 as output1 index
	* @param outputidx2 as output2 index
	* @param baridx as bar index
	*
	* @return if output is crossing below or not
	*/
	bool isOutputsCrossBelowOnBarIdx(int outputidx1, int outputidx2,   int baridx);

	/**
	* @brief check if output1 is crossing output2 above on last index
	*
	* @param outputidx1 as output1 index
	* @param outputidx2 as output2 index
	*
	* @return if output is crossing above or not
	*/
	bool isOutputsCrossAbove(int outputidx1, int outputidx2  );

	/**
	* @brief check if output1 is crossing output2 below on last index
	*
	* @param outputidx1 as output1 index
	* @param outputidx2 as output2 index
	*
	* @return if output is crossing below or not
	*/
	bool isOutputsCrossBelow(int outputidx1, int outputidx2  );
	///@}

public:
	/**
	* @name virtual functions
	*/
	///@{
	
	/**
	* @brief initialize with parameters
	*
	* @param smp as string map parameters
	*/
	virtual void init(StringMapPtr& smp);

	/**
	* @brief calculate all 
	*/
	virtual void calcAll();

	/**
	* @brief calculate in a range
	* 
	* @param startidx as start index
	* @param endidx as end index
	*/
	virtual void calcByIdx(int startidx, int endidx);

	/**
	* @brief handle new bar event
	*/
	virtual void onNewBar();
	///@}
protected:
	/**
	* @brief check if all vectors has consistent sizes
	*
	* @return if data vectors are consistent or not
	*/
	bool checkVectorSizes();

protected:
	std::string m_name; ///< name of indicator
 
	BarListPtr m_barList; ///< bar list
 
	boost::array<std::vector<double>, 3 > m_doubleOutputs; ///< three double output arrays

	std::vector<int> m_intOut; ///< integer output array

	std::vector<double> m_outReals1; ///< temporary double array1
	std::vector<double> m_outReals2; ///< temporary double array2
	std::vector<double> m_outReals3; ///< temporary double array3

	std::vector<int > m_outInts; ///< temporary int array

	StringMapPtr m_parameters; ///< parameters

	TALibFuncInfoPtr m_talibFuncInfo; ///< talib function information

};//class XT_COMMON_API BarIndicator

  //////typedef for BarIndicator
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<BarIndicator> BarIndicatorPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<BarIndicator> BarIndicatorPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<BarIndicator> BarIndicatorPtr;

#else

typedef ::boost::shared_ptr<BarIndicator> BarIndicatorPtr;
#endif


typedef ::sf::safe_ptr<BarIndicator> BarIndicatorSafePtr;

typedef sf::contfree_safe_ptr<BarIndicator> BarIndicatorContFreePtr;
//////end typedef for BarIndicator

}//namespace XT



#endif