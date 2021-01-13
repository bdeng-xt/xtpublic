#pragma once
#ifndef XT_INSTR_EVENT_MGR_H
#define XT_INSTR_EVENT_MGR_H

/**
* \file InstrEventMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for market data and order events manager.
*
* \description
*	This component provides a class for market data and order events manager.
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>

#include <boost/signals2.hpp>
#include "XTConfig.h"
#include "log4z.h"

#include "Util.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "InstrEventHandler.h"

namespace XT
{

class XT_COMMON_API InstrEventMgr {
public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		InstrEventMgr();

		/**
		* @brief default copy constructor
		*/
		InstrEventMgr(const InstrEventMgr& from);  

		/**
		* @brief default copy assignment
		*/
		InstrEventMgr& operator=(const InstrEventMgr& from);//  

		/**
		* @brief destructor
		*/
		virtual ~InstrEventMgr();

		///@}

	public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static InstrEventMgr* getInstance();

 

public:
	/**
	* @brief signal
	*/
	std::shared_ptr< boost::signals2::signal<void(int,int,int,int)> >& signal();

	/**
	* @brief publish event
	*
	* @param iid
	* @param oid
	* @param qid
	* @param flag
	*/
	void publish(int iid, int oid, int qid, int eventtype);
protected:
	std::shared_ptr< boost::signals2::signal<void(int,int,int,int)> > m_signal;

protected:
	void onTimer(int inttime);
	boost::signals2::connection m_connectionTimer; ///< connection

};//class

}//namespace


#endif