#pragma once
#ifndef XT_SESSION_H
#define XT_SESSION_H

#include <cstdint>
#include <set>
#include <string>
#include <iostream>

#include <memory>

#include "XTConfig.h"
#include "safe_ptr.h"

#include "Util.h"
#include "PBUtil.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "StringUtil.h"
#include "TimeUtil.h"

namespace XT
{


	class Session;
	//////typedef for Session
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Session> SessionPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Session> SessionPtr;
	//	typedef sf::contfree_safe_ptr<Session> SessionPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Session> SessionPtr;

#else

	typedef ::std::shared_ptr<Session> SessionPtr;
#endif


	typedef ::sf::safe_ptr<Session> SessionSafePtr;

	typedef sf::contfree_safe_ptr<Session> SessionContFreePtr;
	//////end typedef for Session


///////

	class Sessions;
	//////typedef for Sessions
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Sessions> SessionsPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Sessions> SessionsPtr;
	//	typedef sf::contfree_safe_ptr<Session> SessionPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Sessions> SessionsPtr;

#else

	typedef ::std::shared_ptr<Sessions> SessionsPtr;
#endif


	typedef ::sf::safe_ptr<Sessions> SessionsSafePtr;

	typedef sf::contfree_safe_ptr<Sessions> SessionsContFreePtr;
	//////end typedef for Sessions

//////
	class ExchSessions;
	//////typedef for ExchSessions
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<ExchSessions> ExchSessionsPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<ExchSessions> ExchSessionsPtr;
	//	typedef sf::contfree_safe_ptr<ExchSessions> ExchSessionsPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<ExchSessions> ExchSessionsPtr;

#else

	typedef ::std::shared_ptr<ExchSessions> ExchSessionsPtr;
#endif


	typedef ::sf::safe_ptr<ExchSessions> ExchSessionsSafePtr;

	typedef sf::contfree_safe_ptr<ExchSessions> ExchSessionsContFreePtr;
	//////end typedef for ExchSessions

	class XT_COMMON_API Session
	{
	public:

		/**
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		Session();

		/**
		* @brief default copy constructor
		*/
		Session(const Session& from) = default;

		/**
		* @brief default copy assignment
		*/
		Session& operator=(const Session& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~Session();

	public:
		void init(const std::string& cfgstr, int tradingday, int prevtradingday);

		void updateCfgStr(const std::string& s);

		/**
		* @brief data info
		*/
		SessionDataPtr& data();

		bool isValid();

		const std::string& cfgStr();

		const std::string& getName();
		const std::string& getBeginDt();
		const std::string& getEndDt();
		int64_t getBeginTs();
		int64_t getEndTs();

		int getSecondsTotal();
		int getSecondsElapsed();
		int getSecondsLeft();

		std::string getStr(int flag = 0);

		static const std::string& cfgStrPattern();

	protected:
		SessionDataPtr m_data;
	//	std::string m_cfgStr;

		//	SessionPtr m_next;
		static std::string m_cfgStrPattern;

	};//class XT_COMMON_API Session

	class XT_COMMON_API Sessions
	{
	public:

		/**
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		Sessions();

		/**
		* @brief default copy constructor
		*/
		Sessions(const Sessions& from) = default;

		/**
		* @brief default copy assignment
		*/
		Sessions& operator=(const Sessions& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~Sessions();

	public:
		void init(const std::string& cfgstr, int tradingday, int prevtradingday);

		void updateCfgStr(const std::string& s);

		int updateTs(int64_t ts);

		int currIdx();

		const SessionPtr& currSession();

		int getSecondsTotal();
		int getSecondsLeft();
		int getSecondsElapsed();

		std::string getStr(int flag = 0);

	protected:
		int m_currIdx;
		sf::contfree_safe_ptr<std::vector<SessionPtr> >  m_data;

		SessionPtr m_emptySession;
		std::string m_cfgStr;
		SessionPtr m_currSession;

		int m_tradingday;
		int m_prevtradingday;

		int m_secondsTotal;
		int m_secondsElapsed;
		int m_secondsLeft;


	};//class XT_COMMON_API Sessions

	class XT_COMMON_API ExchSessions
	{
	public:

		/**
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		ExchSessions();

		/**
		* @brief default copy constructor
		*/
		ExchSessions(const ExchSessions& from) = default;

		/**
		* @brief default copy assignment
		*/
		ExchSessions& operator=(const ExchSessions& from) = default;

		/**
		* @brief destructor
		*/
		virtual ~ExchSessions();

	public:
		/**
		* @brief initialization
		*
		*/
		void init(const std::string& exchid, int tradingday,int prevtradingday);

		/**
		* @brief initialize with string parameters
		*
		* @param string parameters
		*/
		void updateStrParams(const StringMapPtr& smp);

		StringMapPtr& strParams();
		SessionsPtr& sessions();
		sf::contfree_safe_ptr<std::unordered_map<std::string, SessionsPtr> >& productSessions();

		const std::string& exchID();
		int getTradingDay();
		int getPrevTradingDay();

		int updateTs(int64_t ts);

		const SessionPtr& currSession(const std::string& productid);

		const SessionsPtr& currSessions(const std::string& productid);

		std::string getStr(int flag);

	protected:
		StringMapPtr m_strParams;
		SessionsPtr m_sessions;
		SessionsPtr m_emptySessions;
		sf::contfree_safe_ptr<std::unordered_map<std::string, SessionsPtr> > m_productSessions;
		sf::contfree_safe_ptr<std::unordered_map<std::string, std::string> > m_productToSessionNameMap;
		
		std::string m_exchid;
		int m_tradingday;
		int m_prevtradingday;


	public:
		static StringMapPtr getDefaultStrParams(const std::string& exchid);

		static std::string getSessionsCfgStr(const std::string& exchid, const std::string& productid);

		static std::string getSessionsStr(const std::string& exchid, const std::string& productid, int tradingday,int prevtradingday);

	protected:
		static StringMapPtr getDefaultStrParamsForCFFEX();
		static StringMapPtr getDefaultStrParamsForCZCE();
		static StringMapPtr getDefaultStrParamsForDCE();
		static StringMapPtr getDefaultStrParamsForSHFE();
		static StringMapPtr getDefaultStrParamsForINE();
		static StringMapPtr getDefaultStrParamsForSSE();
		static StringMapPtr getDefaultStrParamsForSZSE();

		static StringMapPtr getDefaultStrParamsForDERIBIT();
		static StringMapPtr getDefaultStrParamsForBINANCE();

	};//class XT_COMMON_API ExchSessions

}//namespace XT



#endif