#pragma once
#ifndef XT_PRICINGENGINE_H
#define XT_PRICINGENGINE_H

/**
* \file PricingEngine.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide abstract class for pricing engine.
*
* \description
*	Designed for use for interface for all pricing engines.
*/


#include <string>
#include <sstream>
#include <vector>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>
//#include <unordered_map>

#include "safe_ptr.h"
#include "XTConfig.h"
#include "XTData.pb.h"
#include "Util.h"
namespace XT {

	class PricingEngine;
	//////typedef for PricingEngine
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<PricingEngine> PricingEnginePtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<PricingEngine> PricingEnginePtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<PricingEngine> PricingEnginePtr;

#else

	typedef ::boost::shared_ptr<PricingEngine> PricingEnginePtr;
#endif


	typedef ::sf::safe_ptr<PricingEngine> PricingEngineSafePtr;

	typedef sf::contfree_safe_ptr<PricingEngine> PricingEngineContFreePtr;
	//////end typedef for PricingEngine

class XT_COMMON_API PricingEngine {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{
	/**
	* constructor
	*/
	PricingEngine() ;

	/**
	* @brief default copy constructor
	*/
	PricingEngine(const PricingEngine& from) = default;

	/**
	* @brief default copy assignment
	*/
	PricingEngine& operator=(const PricingEngine& from) = default;

	/**
	* destructor
	*/
	virtual ~PricingEngine() {}

	///@}

	/** 
	* @name Calc
	*/
	///@{
	/**
	* @brief perform calculation
	*/
	virtual void calc() {}

	/**
	* @brief add calculation type
	*
	* @param i as calc type
	*/
	void addCalcType(int i);

	/**
	* @brief clear all calculation types
	*/
	void clearCalcTypes();
	///@}


	/** 
	* @name Setters and Getters
	*/
	///@{

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string & getName();

	/**
	* @brief set name
	*
	* @param s as name
	*/
	void setName(const std::string & s);

	/**
	* @brief set integer input
	*
	* @param tag
	* @param i as int input
	*/
	void setIntIntput(int tag,int i);

	/**
	* @brief get integer input
	*
	* @param tag
	* 
	* @return int input
	*/
	int getIntInput(int tag);

	/**
	* @brief set double input
	*
	* @param tag
	* @param d as double input
	*/
	void setDoubleInput(int tag,double d);

	/**
	* @brief get double input
	*
	* @param tag
	*
	* @return double input
	*/
	double getDoubleInput(int tag);

	/**
	* @brief get result
	*
	* @param tag
	*
	* @return double result
	*/
	double getResult(int tag);

	///@}

	/** 
	* @name Map
	*/
	///@{
	/**
	* @brief get int inputs map
	*
	* @return int inputs
	*/
	boost::unordered_map<int,int>& intInputs(); 

	/**
	* @brief get double inputs
	*
	* @return double inputs
	*/
	boost::unordered_map<int,double>& doubleInputs(); 

	/**
	* @brief get results
	*
	* @return results map
	*/
	boost::unordered_map<int,double>& results(); 

	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @return PricingEngine pointer
	*/
	static PricingEnginePtr create() ;
	///@}
protected:
	std::string m_name; ///< name
	std::set<int> m_calcTypes; ///< all calculation types
	boost::unordered_map<int,int> m_intInputs; ///< integer inputs
	boost::unordered_map<int,double> m_doubleInputs; ///< double inputs
	boost::unordered_map<int,double> m_results; ///< results

protected:


}; //end class PricingEngine





} //end namespace XT


#endif
