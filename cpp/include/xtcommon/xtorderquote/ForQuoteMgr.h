#pragma once
#ifndef XT_FORQUOTE_MGR_H
#define XT_FORQUOTE_MGR_H

/**
* * \file ForQuoteMgr.h
* *
* * \author Bin Deng (bdeng@xtal-tech.com)
* *
* * \brief  Provide a manager for all forquotes.
* *
* * \description
* *       Designed for managing forquotes.
* */

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "log4z.h"
#include "safe_ptr.h"


#include "Util.h"
#include "TimeUtil.h"
#include "DataUtil.h"

namespace XT {

class XT_COMMON_API ForQuoteMgr {
public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		ForQuoteMgr();

		/**
		* @brief default copy constructor
		*/
		ForQuoteMgr(const ForQuoteMgr& from);// {}// = delete;

		/**
		* @brief default copy assignment
		*/
		ForQuoteMgr& operator=(const ForQuoteMgr& from);// { return *this; } // = delete;

		/**
		* @brief destructor
		*/
		virtual ~ForQuoteMgr();

		///@}

public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static ForQuoteMgr* getInstance();

public:
	/**
	* queue for recieved ForQuoteInfo
	*/
	sf::contfree_safe_ptr<std::deque<ForQuoteInfoPtr > >& forquotes();

	/**
	* add ForQuoteInfo
	*/
	void addForQuoteInfo(const ForQuoteInfoPtr& p);

	/**
	* remove ForQuoteInfos which are too long
	*/
	int removeForQuoteInfoTooLong(int64_t nowts, int seconds);

public:
	/**
	* add forquoteref forquotesysid pair
	*/
	void addForQuoteRefForQuoteSysID(const std::string& forquoteref, const std::string& forquotesysid);

	/**
	* has ForQuoteRef for ForQuoteSysID
	*/
	bool hasForQuoteRefForForQuoteSysID(const std::string& forquotesysid);

	/**
	* get ForQuoteRef for ForQuoteSysID
	*/
	const std::string& getForQuoteRefForForQuoteSysID(const std::string& forquotesysid);

	/**
	* if it has ForQuoteSysID for ForQuoteRef
	*/
	bool hasForQuoteSysIDForForQuoteRef(const std::string& forquoteref);

	/**
	* get ForQuoteSysID for ForQuoteRef
	*/
	const std::string& getForQuoteSysIDForForQuoteRef(const std::string& forquoteref);

protected:
	std::string m_emptyString;

	ForQuoteMgrCfgDataPtr m_cfgData;
//	ForQuoteInfoPtr m_nullForQuoteInfoPtr;
	sf::contfree_safe_ptr<std::deque<ForQuoteInfoPtr > > m_forquotes;

protected:
	sf::contfree_safe_ptr<std::map<std::string, std::string> > m_forQuoteRefToForQuoteSysIDMap; ///< map for ForQuoteRef to ForQuoteSysID
	sf::contfree_safe_ptr<std::map<std::string, std::string> > m_forQuoteSysIDToForQuoteRefMap; ///< map for ForQuoteSysID to ForQuoteRef

};//class

}//namespace

#endif