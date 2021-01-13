#pragma once
#ifndef XT_INSTRCOMBO_H
#define XT_INSTRCOMBO_H

/**
* \file InstrCombo.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for instrument combo.
*
* \description
*	Designed for definition information of a combo of instrument legs.
*/


#include <stdint.h>
#include <string>
#include <sstream>
#include <math.h>

#include <boost/unordered_map.hpp>
#include <boost/smart_ptr.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"
#include "XTData.pb.h"

 

#include "LogUtil.h"
#include "EnumHelper.h"
#include "Instr.h"
#include "InstrLeg.h"
#include "StringMap.h"

namespace XT {

class XT_COMMON_API InstrCombo {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
		InstrCombo();

		/**
		* @brief default copy constructor
		*/
		InstrCombo(const InstrCombo& from);// = default;

		/**
		* @brief default copy assignment
		*/
		InstrCombo& operator=(const InstrCombo& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~InstrCombo();

	///@}

		/**
		* @brief set iid for InstrCombo
		*
		* @param iid as integer id
		*/
		void setComboIid(int iid);

		/**
		* @brief get iid for InstrCombo
		*
		* @return combo integer id
		*/
		int getComboIid();

		/**
		* @brief set name for InstrCombo
		*
		* @param s as name
		*/
		void setName(const std::string& s);

		/**
		* @brief get name for InstrCombo
		*
		* @return combo name
		*/
		const std::string& getName();

		/**
		* @brief add Instr
		*
		* @param instr as instrument
		* @param n as number of instrument
		*/
		void addInstr(InstrPtr instr, int n);
 
		/**
		* @brief add InstrLeg
		*
		* @param leg as InstrLeg
		*/
		void addInstrLeg(InstrLegPtr leg);

		/**
		* @brief get total number of legs
		*
		* @return number of legs
		*/
		int getNumOfInstrLegs();
 
		/**
		* @brief has Leg for iid
		*
		* @param iid as integer id
		*
		* @return if integer id exists
		*/
		bool hasInstrLegForIid(int iid);

		/**
		* @brief get Leg for iid
		*
		* @param iid as integer id
		*
		* @return InstrLegPtr
		*/
		InstrLegPtr& getInstrLegByIid(int iid);

		/**
		* @brief has Leg for instrid
		*
		* @param iid as integer id
		*
		* @return if instrument exists
		*/
		bool hasInstrLegForInstrID(const std::string& instrid);

		/**
		* @brief get Leg for instrid
		*
		* @param iid as integer id
		*
		* @return InstrLegPtr
		*/
		InstrLegPtr& getInstrLegByInstrID(const std::string& instrid);

		/**
		* @brief remove leg by iid
		*
		* @param iid as integer id
		*/
		void removeInstrLegByIid(int iid);

		/**
		* @brief remove leg by instrid
		*
		* @param instrid
		*/
		void removeInstrLegByInstrID(const std::string& instrid);

		/**
		* @brief get instrid vector
		*
		* @return vector of instrids
		*/
		std::vector<std::string> & getInstrIDs();

		/**
		* @brief get instrument iids
		*
		* @return vector of integer ids
		*/
		std::vector<int> & getIids();

		/**
		* @brief best mid price
		*
		* @return market mid price
		*/
		double getBestMktMidPx();

		/**
		* @brief best price on buy or sell side
		*
		* @param bs as buy sell type
		*
		* @return market price 
		*/
		double getBestMktPx(BuySellType::enumtype bs);

		/**
		* @brief best size on buy or sell side
		*
		* @param bs as buy sell type
		* 
		* @return market size
		*/
		int64_t getBestMktSz(BuySellType::enumtype bs);

		/*
		* @brief to string
		*
		* @return specification string
		*/
		std::string toSpecStr();

 

protected:
	int m_comboIid; ///< combo integer id
	std::string m_name; ///< combo name

	boost::unordered_map<int, InstrLegPtr > m_iidToInstrLegMap; ///< integer id to InstrLeg map
	boost::unordered_map<std::string, InstrLegPtr > m_instridToInstrLegMap; ///< instrid to InstrLeg map
	
	std::vector<int> m_iids; ///< vector of integer ids
	std::vector<std::string> m_instrumentIDs; ///< vector of instrids

	boost::unordered_map<int, std::string> m_iidToInstrIDMap; ///< integer id to instrid map
	boost::unordered_map<std::string, int> m_instrumentIDToIIDMap; ///< instrid to integer id map

	InstrLegPtr m_emptyLeg; ///< null empty instrleg
 
protected:
	/**
	* @brief udpate instruments
	*/
	void updateInstruments();
};

//////typedef for InstrCombo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<InstrCombo> InstrComboPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<InstrCombo> InstrComboPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<InstrCombo> InstrComboPtr;

#else

typedef ::boost::shared_ptr<InstrCombo> InstrComboPtr;
#endif


typedef ::sf::safe_ptr<InstrCombo> InstrComboSafePtr;

typedef sf::contfree_safe_ptr<InstrCombo> InstrComboContFreePtr;
//////end typedef for InstrCombo
} //end namespace ht

#endif