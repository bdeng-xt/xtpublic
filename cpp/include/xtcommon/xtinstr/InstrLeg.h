#pragma once
#ifndef XT_INSTRLEG_H
#define XT_INSTRLEG_H

/**
* \file InstrLeg.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for instrument leg.
*
* \description
*	Designed for definition information of a leg of an instrument.
*/


#include <stdint.h>
#include <string>
#include <sstream>
#include <math.h>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"
#include "EnumHelper.h"
#include "Instr.h"
//#include "InstrIndicator.h"

#include "StringMap.h"

namespace XT {

class XT_COMMON_API InstrLeg {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
		InstrLeg();

		/**
		* @brief default copy constructor
		*/
		InstrLeg(const InstrLeg& from);// = default;

		/**
		* @brief default copy assignment
		*/
		InstrLeg& operator=(const InstrLeg& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~InstrLeg();

	///@}

		/**
		* @brief initialization
		*
		* @param i as intrument
		* @param n as number
		*/
		void init(InstrPtr i, int n);

 
		/**
		* @brief get instrument
		*
		* @return InstrPtr
		*/
		InstrPtr& instr();
 
 
		/**
		* @brief get number
		*
		* @return number
		*/
		int getNum();

		/**
		* @brief set number
		*
		* @param i as number
		*/
		void setNum(int i);

		/**
		* @brief get weight
		*
		* @return weight
		*/
		double getWeight();

		/**
		* @brief set weight
		*
		* @param v as weight
		*/
		void setWeight(double v);

		/**
		* @brief specification string
		*
		* @return specification string
		*/
		std::string toSpecStr();

protected:
	InstrPtr m_instr; ///< instrument
 
	int m_num; ///< number of instrument
	double m_weight;///< weight for calculation
};

//////typedef for InstrLeg
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<InstrLeg> InstrLegPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<InstrLeg> InstrLegPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<InstrLeg> InstrLegPtr;

#else

typedef ::boost::shared_ptr<InstrLeg> InstrLegPtr;
#endif


typedef ::sf::safe_ptr<InstrLeg> InstrLegSafePtr;

typedef sf::contfree_safe_ptr<InstrLeg> InstrLegContFreePtr;
//////end typedef for InstrLeg


} //end namespace ht

#endif
