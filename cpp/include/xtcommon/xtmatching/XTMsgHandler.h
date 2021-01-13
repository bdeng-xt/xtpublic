#pragma once
#ifndef XT_MSG_HANDLER_H
#define XT_MSG_HANDLER_H

/**
* \file XTMsgHandler.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide class for XTMsg handler.
*
* \description
*	Designed for use for XTMsg handler.
*/

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "PBUtil.h"
#include "XTMsg.h"

#include "XTConfig.h"

namespace XT
{

class XT_COMMON_API XTMsgHandler
{
public:
	XTMsgHandler() :
		m_count(0)
	{  }
	XTMsgHandler(const XTMsgHandler&) {} // = delete;
	XTMsgHandler(XTMsgHandler&&) {} // = delete;
	virtual ~XTMsgHandler() {} // = default;

	XTMsgHandler& operator=(const XTMsgHandler&) { return *this; } // = delete;
	XTMsgHandler& operator=(XTMsgHandler&&) { return *this; } // = delete;

	void processMsgData(XTMsgData& msg);

	int count();
protected:
	int m_count;

};//class XTMsgHandler

}//namespace XT

#endif