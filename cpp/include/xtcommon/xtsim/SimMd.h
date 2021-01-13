#pragma once
#ifndef XT_SIM_MD_H
#define XT_SIM_MD_H

#include <string>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>

#include <memory>

#include <boost/unordered_map.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>		 
#include <boost/bind.hpp>			 
#include <boost/any.hpp>	 
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

#include "XTConfig.h"
#include "XTEnum.pb.h"
#include "XTData.pb.h"
#include "typedef_XTData.pb.h"

#include "SimMdGateway.h"
#include "SimUtil.h"

namespace XT
{

class XT_COMMON_API SimMd: public SimMdGateway
{

public:
	SimMd();
	virtual ~SimMd();

public:
	virtual void start();

public:

	/**
	* @brief update daydata
	*/
	virtual void onDayData(DayDataPtr& daydata);


	/**
	* @brief update mktdataquote
	*/
	virtual void onMktQuoteData(MktQuoteDataPtr& mktdata);

	/**
	* @brief update on data str
	*/
	virtual void onDataStr(const std::string& line, const std::string& datatype);
protected:
	void processTask();
//////////////////////////

};

typedef std::shared_ptr<SimMd> SimMdPtr;

}//namespace

#endif