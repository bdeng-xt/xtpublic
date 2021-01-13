#pragma once
#ifndef XT_XTMSG_H
#define XT_XTMSG_H

/**
* \file XTMsg.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for xt message.
*
* \description
*	Designed for xt message.
*/

#include <stdint.h>
#include <string>
#include <sstream>
#include <math.h>

#include <set>

#include <boost/unordered_set.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "safe_ptr.h"

#include "XTConfig.h"

#include "Util.h"
#include "PBUtil.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"
//#include "TagDataWrapper.h"
#include "EnumUtil.h"
#include "EnumHelper.h"

namespace XT
{
	class XTMsg;

	//////typedef for XTMsg
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<XTMsg> XTMsgPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<XTMsg> XTMsgPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<XTMsg> XTMsgPtr;

#else

	typedef ::boost::shared_ptr<XTMsg> XTMsgPtr;
#endif


	typedef ::sf::safe_ptr<XTMsg> XTMsgSafePtr;

	typedef sf::contfree_safe_ptr<XTMsg> XTMsgContFreePtr;
	//////end typedef for XTMsg

	class XT_COMMON_API XTMsg
	{

	public:


		/**
		* @name Constructor and Initialization
		*/
		///@{
		/**
		* @brief constructor
		*/
		XTMsg();

		/**
		* @brief default copy constructor
		*/
		XTMsg(const XTMsg& from);// = default;

		/**
		* @brief default copy assignment
		*/
		XTMsg& operator=(const XTMsg& from);// = default;

		/**
		* @brief destructor
		*/
		virtual ~XTMsg();


		///@}

		/**
		* @methods
		*/
		///@{

		/**
		* @brief data
		*
		* @return data
		*/
		XTMsgDataPtr& data();

		/**
		* @brief get name
		*
		* @return name
		*/
		const std::string& getName();

		/**
		* @brief set name
		*
		* @param name
		*/
		void setName(const std::string& s);

		/**
		* @brief get double
		*
		* @return double
		*/
		double getDouble();

		/**
		* @brief set double
		*
		* @param double
		*/
		void setDouble(double d);

		/**
		* @brief get integer
		*
		* @return integer
		*/
		int getInt();

		/**
		* @brief set integer
		*
		* @param integer
		*/
		void setInt(int i);

		/**
		* @brief get 64bit integer
		*
		* @return 64bit integer
		*/
		int64_t getInt64();

		/**
		* @brief set 64bit integer
		*
		* @param 64bit integer
		*/
		void setInt64(int64_t i);

		/**
		* @brief get string
		*
		* @return string
		*/
		const std::string& getStr();

		/**
		* @brief set string
		*
		* @param string
		*/
		void setStr(const std::string& s);

		/**
		* @brief add string pair to map
		*
		* @param key
		* @param valuestr
		*/
		void addKeyValueStr(const std::string& key, const std::string& valuestr);

		/**
		* @brief exists key or not
		*
		* @param key
		*
		* @return if a key exists
		*/
		bool hasKey(const std::string& key);

		/**
		* @brief get value str by key
		* 
		* @param key
		*
		* @return valuestr 
		*/
		const std::string& getValueStr(const std::string& key);


		///@}

		
		/**
		* @name String Functions
		*/
		///@{
		/**
		* @brief to json string
		*
		* @return json string
		*/
		std::string toJsonStr();

		///**
		//* @brief to pretty json string
		//*
		//* @return pretty json string
		//*/
		//std::string toPrettyJsonStr();

		/**
		* @brief from json string
		*
		* @param s as json string
		*/
		void fromJsonStr(const std::string& s);


		/**
		* @brief to pb string
		*
		* @return pb string
		*/
		std::string toPBStr();

		/**
		* @brief from pb string
		*
		* @param s as pb string
		*/
		void fromPBStr(const std::string& s);

		/**
		* @brief to csv string
		*
		* @return csv string
		*/
		std::string toCsvStr();

		/**
		* @brief from csv string
		*
		* @param s as csv string
		*/
		void fromCsvStr(const std::string& s);

		/**
		* @brief to plain csv string
		*
		* @return plain csv string
		*/
		std::string toPlainCsvStr();

		/**
		* @brief from plain csv string
		*
		* @param s as plain csv string
		*/
		void fromPlainCsvStr(const std::string& s);


		///@}

		/**
		* @name Static Factory
		*/
		///@{

		/**
		* @brief factory function
		*
		* @return InstrSpec
		*/
		static XTMsgPtr create();


		///@}

	protected:
		XTMsgDataPtr m_data;
		
	 
		
	}; //end class InstrSpec


} //end namespace XT


#endif
