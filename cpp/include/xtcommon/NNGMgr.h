#pragma once
#ifndef XT_NNG_MGR_H
#define XT_NNG_MGR_H

/**
* \file NNGMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class for managing nanomsg next generation messaging.
*
* \description
*	Designed for nanomsg next generation.
*/

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


#include "XTConfig.h"

#include "LogUtil.h"


#include "nng.h" 
#include "compat/nanomsg/nn.h"
#include "compat/nanomsg/nn_pubsub.h"
#include "compat/nanomsg/nn_reqrep.h"
#include "compat/nanomsg/nn_pipeline.h"
#include "compat/nanomsg/nn_bus.h"

namespace XT {

	class XT_COMMON_API NNGMgr
	{

	public:
		/**
		* @name Constructor and Destructor
		*/
		///@{

		/**
		* @brief constructor
		*/
		NNGMgr();

		/**
		* @brief default copy constructor
		*/
		NNGMgr(const NNGMgr& from) {}// = delete;

		/**
		* @brief default copy assignment
		*/
		NNGMgr& operator=(const NNGMgr& from) { return *this; } //= delete;

		/**
		* @brief destructor
		*/
		~NNGMgr();

		///@}
	public:
		/**
		* @brief get singleton instance
		*
		* @return singleton instance
		*/
		static NNGMgr* getInstance();

		/**
		* @brief has instance
		*
		* @return if instance exists or not
		*/
		static bool hasInstance();

	protected:
		static bool m_hasInstance;

	public:

 
	};// NNGMgr



}//namespace XT




#endif