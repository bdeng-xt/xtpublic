#pragma once
#ifndef XT_DOUBLEFUNCTION_H
#define XT_DOUBLEFUNCTION_H

/**
* \file DoubleFunction.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide an abstract class for a function with double return value.
*
* \description
*	Designed for base class for all functions with a double return value.
*/

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>


//#include <boost/unordered_map.hpp>
//#include <boost/smart_ptr.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>		 
#include <boost/any.hpp>
#include <boost/thread/shared_mutex.hpp>

#include "safe_ptr.h"
#include "XTConfig.h"
#include "EnumHelper.h"
#include "Util.h"
#include "PBUtil.h"


#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "TagDataWrapper.h"

#include "safe_ptr.h"

namespace XT {

	class DoubleFunction;
	//////typedef for DoubleFunction

#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<DoubleFunction> DoubleFunctionPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<DoubleFunction> DoubleFunctionPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<DoubleFunction> DoubleFunctionPtr;

#else

	typedef ::boost::shared_ptr<DoubleFunction> DoubleFunctionPtr;
#endif


	typedef ::sf::safe_ptr<DoubleFunction> DoubleFunctionSafePtr;

	typedef sf::contfree_safe_ptr<DoubleFunction> DoubleFunctionContFreePtr;
	//////end typedef for DoubleFunction

class XT_COMMON_API DoubleFunction {
public:

	/** 
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	DoubleFunction();


	/**
	* @brief default copy constructor
	*/
	DoubleFunction(const DoubleFunction& from)  ;

	/**
	* @brief default copy assignment
	*/
	DoubleFunction& operator=(const DoubleFunction& from)  ;


	/**
	* @brief destructor
	*/
	virtual ~DoubleFunction() {}

	///@}

	/** 
	* @name Calculation
	*/
	///@{
	/**
	* @brief function value
	*
	* @param x as input double vector
	*
	* @return value corresponding to x vector
	*/
	virtual double getValue(const std::vector<double> & x, int cpttype );

	/**
	* @brief gradient(first derivative)
	*
	* @param x as input double vector
	* @param y as output gradient double vector
	*/
	virtual void calcGradient(const std::vector<double> & x, std::vector<double> & y, int cpttype) ;

 

	///@}

	/** @name Setters and Getters
	*
	*/
	///@{

	/**
	* @brief params
	*
	* @return function parameters
	*/
	DoubleFunctionParamsPtr& funcParams();


	/**
	* @brief set epsilon value
	*
	* @param epislon as double
	*/
	virtual void setEpsilon(double epsilon);

	/**
	* @brief get epsilon value
	*
	* @return epsilon value
	*/
	virtual double getEpsilon() ;

	/**
	* @brief set integer parameter
	*/
	virtual void setIntParam(int idx, int i, int cpttype);

	/**
	* @brief get integer parameter
	*
	* @param idx as integer
	*
	* @return integer value
	*/
	virtual int getIntParam(int idx, int cpttype) ;

	/**
	* @brief add int parameter
	*
	* @param name
	* @param v
	*/
	virtual void addIntParam(const std::string& name, int v);

	/**
	* @brief get int parameter by name
	*
	* @param name
	*
	* @return int value
	*/
	virtual int getIntParamByName(const std::string& name,int cpttype);

	virtual void setIntParamByName(const std::string&name, int v, int cpttype);

	virtual std::vector<std::string> getIntParamNames();

	/**
	* @brief set double parameter
	*
	* @param idx as integer
	* @param d as double value
	*/
	virtual void setDoubleParam(int idx, double d, int cpttype) ;

	/**
	* @brief get double parameter
	*
	* @param idx as integer
	*
	* @return double value
	*/
	virtual double getDoubleParam(int idx, int cpttype) ;

	/**
	* @brief add double parameter
	*
	* @param name 
	* @param value
	*/
	virtual void addDoubleParam(const std::string& name, double v);

	/**
	* @brief get double parameter by name
	*
	* @param name
	*
	* @return double value
	*/
	virtual double getDoubleParamByName(const std::string& name, int cpttype);

	virtual void setDoubleParamByName(const std::string& name, double v, int cpttype);

	virtual std::vector<std::string> getDoubleParamNames();

 

	///@}


	/** @name Copy
	*
	*/
	///@{
	/**
	* @brief deep clone 
	*
	* @return cloned double function pointer
	*/
    virtual DoubleFunctionPtr deepClone();

	/**
	* @brief copy from another DoubleFunction instance
	*
	* @param other double function pointer
	*/
    virtual void copyFrom(DoubleFunctionPtr & other);

	/**
	* @brief copy curr parameters to prev
	*/
	virtual void copyCurrToPrevParams();

	/**
	* @brief copy curr parameters to temp
	*/
	virtual void copyCurrToTempParams();

	///@}


	/** @name String Functions
	*
	*/
	///@{
	/**
	* @brief string function
	*
	* @return string 
	*/
	virtual std::string str();

	virtual std::string getStr(int flag);

	virtual bool updateFromStr(const std::string& s, int flag);

	///@}

	/** 
	* @name Factory
	*/
	///@{
	/**
	* @brief factory function
	*
	* @return DoubleFunction pointer
	*/
	static DoubleFunctionPtr create() ;

	///@}
//protected:
//
//	std::map<int,int> m_intParams; ///< integer parameters
//	std::map<int,double> m_doubleParams; ///< double parameters
//	std::map<int,int> m_intParamsPrev; ///< previous integer parameters
//	std::map<int,double> m_doubleParamsPrev; ///< previous double parameters
//protected:
//	double m_epsilon; ///< default is 1e-6


protected:
	DoubleFunctionParamsPtr m_funcParams;

	sf::contfree_safe_ptr<std::unordered_map<int, std::string> > m_doubleParamIdxToNameMap;
	sf::contfree_safe_ptr<std::unordered_map<std::string, int> > m_doubleParamNameToIdxMap;

	sf::contfree_safe_ptr<std::unordered_map<int, std::string> > m_intParamIdxToNameMap;
	sf::contfree_safe_ptr<std::unordered_map<std::string, int> > m_intParamNameToIdxMap;
}; //end class DoubleFunction
  
} //end namespace XT

#endif
