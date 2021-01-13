#pragma once
#ifndef XT_MONGODBMGR_H
#define XT_MONGODBMGR_H

/**
* \file MongoDBMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for mongodb.
*
* \description
*	Designed for managing mongodb.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>			// 
#include <boost/bind.hpp>			// 
#include <boost/any.hpp>	// 
//#include <boost/lockfree/queue.hpp>
//#include <boost/lockfree/spsc_queue.hpp>
#include "Containers.h"

#include <boost/smart_ptr.hpp>

#ifndef XT_DISABLE_MONGO

#include "XTConfig.h"
#include "Util.h"
#include <InstrSpec.h>

//#include "Instr.h"
//#include <InstrBar.h>
//#include "InstrBarDataMap.h"

#include "Bar.h"

#include "LogUtil.h"


#include "SettingsMgr.h"

#include <XTTimer.h>

#include <bson.h>
#include <bcon.h>
#include <mongoc.h>

namespace XT
{

////////////////////////////////
class XT_COMMON_API MongoDBMgr
{

public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	MongoDBMgr();

	/**
	* @brief default copy constructor
	*/
	MongoDBMgr(const MongoDBMgr& from);// = default;

	/**
	* @brief default copy assignment
	*/
	MongoDBMgr& operator=(const MongoDBMgr& from);// = default;

	/**
	* @brief destructor
	*/
	~MongoDBMgr();
	///@}
public:

	/**
	* @brief release all resources
	*
	*/
	void release();

	/**
	* @brief is mongodb client is null or not
	*
	* @return if mongodb client is initialized successfully
	*/
	bool isNULL();
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static MongoDBMgr* getInstance();

	/**
	* @brief has instance
	*
	* @return if instance exists or not
	*/
	static bool hasInstance();

protected:
	static bool m_hasInstance;

public:
	/**
	* @brief get InstrSpec by instrid
	*
	* @param instrid
	*
	* @return InstrSpec
	*/
	InstrSpecPtr getInstrSpecByInstrID(const std::string& instrid);
//	InstrPtr getInstrByInstrID(const std::string& instrid, int booklevels);
	 

	/**
	* @brief get barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	* @param spanseconds as bar seconds
	* 
	* @return barlist
	*/
	BarListPtr getBarListForInstrID(const std::string& exch, const std::string& instrid, int64_t startdt, int64_t enddt, int spanseconds);

	/**
	* @brief get barlist for instrid with number limit
	*
	* @param exch as exchange id
	* @param instrid
	* @param enddt as end timestamp
	* @param numlimit as maximum number of entries to pull
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarListPtr getBarListForInstrIDWithLimit(const std::string& exch, const std::string& instrid, int64_t enddt,  int numlimit, int spanseconds);

	/**
	* @brief get 60 seconds barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstrID(const std::string& exch, const std::string& instrid, int64_t startdt, int64_t enddt);

	/**
	* @brief get day barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param startintdate as start int date
	* @param endintdate as end int date
	*
	* @return barlist
	*/
	BarListPtr getDayBarListForInstrID(const std::string& exch, const std::string& instrid, int startintdate, int endintdate);

	/**
	* @brief get 60 seconds barlist for instrid with number limit
	*
	* @param exch as exchange id
	* @param instrid
	* @param enddt as end timestamp
	* @param numlimt as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr get60sBarListForInstrIDWithLimit(const std::string& exch, const std::string& instrid, int64_t enddt, int numlimit );

	/**
	* @brief get day barlist for instrid with number limit
	*
	* @param exch as exchange id
	* @param instrid
	* @param enddt as end timestamp
	* @param numlimt as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr getDayBarListForInstrIDWithLimit(const std::string& exch, const std::string& instrid, int  enddate, int numlimit );

	/**
	* @brief get latest barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param dt as end timestamp
	* @param spanseconds as bar seconds
	*
	* @return barlist
	*/
	BarPtr getLatestBarForInstrID(const std::string& exch, const std::string& instrid, int64_t dt, int spanseconds);

	/**
	* @brief get latest 60 seconds barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param dt as end timestamp
	*
	* @return barlist
	*/
	BarPtr getLatest60sBarForInstrID(const std::string& exch, const std::string& instrid, int64_t dt);

	/**
	* @brief get latest day barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param intdate as int date
	*
	* @return barlist
	*/
	BarPtr getLatestDayBarForInstrID(const std::string& exch, const std::string& instrid, int intdate);


	//
 

public:
	/**
	* @brief add document to queue for inserting
	*
	* @param doc as mongodb document
	* @param colname as collection name
	*/
	void addInsertDocument(const std::string& doc, const std::string& colname);
public:
	/**
	* @brief execute command
	*
	* @param s as commond string
	* @colname as collection name
	*/
	void execCommand(const std::string& s, const std::string& colname);

	/**
	* @brief get query results
	* 
	* @param s as query string
	* @param colname as collection name
	*
	* @return vector of query results
	*/
	std::vector<std::string> getQueryResults(const std::string& s, const std::string& colname);

	/**
	* @brief get query results
	*
	* @param smp as query stringmap 
	* @param colname as collection name
	*
	* @return query result as StringMapLst
	*/
	StringMapListPtr getQueryStringMapList(const std::string& s, const std::string& colname);

	/**
	* @brief get query results with optional string
	*
	* @param s as query string
	* @param optsstr as optional string
	* @param colname as collection name
	*
	* @return vector of query results
	*/
	std::vector<std::string> getQueryResultsWithOpts(const std::string& s, const std::string& optsstr, const std::string& colname);

	/**
	* @brief insert mongodb document
	*
	* @param s as document string
	* @param colname as collection name
	*
	* @return status
	*/
	int insertDocument(const std::string& s, const std::string& colname);

	/**
	* @brief insert mongodb documents
	*
	* @param docs as vector of document string
	* @param colname as collection name
	*
	* @return status
	*/
	int insertDocuments(std::vector<std::string>& docs, const std::string& colname);

	/**
	* @brief get max int value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return maximum int value
	*/
	int getMaxInt32ValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);

	/**
	* @brief get min int value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return minimum int value
	*/
	int getMinInt32ValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);

	/**
	* @brief get max double value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return maximum double value
	*/
	double getMaxDoubleValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);

	/**
	* @brief get min double value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return minimum double value
	*/
	double getMinDoubleValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);

	/**
	* @brief get max int64_t value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return maximum int64_t value
	*/
	int64_t getMaxInt64ValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);

	/**
	* @brief get min int64_t value
	*
	* @param fieldname
	* @param collectionname
	*
	* @return minimum int64_t value
	*/
	int64_t getMinInt64ValueForFieldInCollection(const std::string& fieldname, const std::string& collectionname);


public:
	/**
	* @brief set username
	*
	* @param s as username
	*/
	void setUsername(const std::string& s);

	/**
	* @brief get username
	*
	* @return username
	*/
	std::string getUsername();

	/**
	* @brief set password
	*
	* @param s as password
	*/
	void setPassword(const std::string& s);
	//	static std::string getPassword();

	/**
	* @brief set host name
	*
	* @param s as host name
	*/
	void setHostname(const std::string& s);

	/**
	* @brief get host name
	*
	* @return host name
	*/
	std::string getHostname();

	/**
	* @brief set port
	*
	* @param port
	*/
	void setPort(int port);

	/**
	* @brief get port
	*
	* @return port
	*/
	int getPort();

	/**
	* @brief set database name
	* 
	* @s as database name
	*/
	void setDbname(const std::string & s);

	/**
	* @brief get database name
	*
	* @return database name
	*/
	std::string getDbname();

	/**
	* @brief set default to xt
	*/
	void setDefault2XT();

	/**
	* @brief set default to xt local
	*/
	void setDefault2XTLocal();

	/**
	* @brief set default to txjh
	*/
	void setDefault2TXJH();

	/**
	* @brief set default to txjh local
	*/
	void setDefault2TXJHLocal();

	/**
	* @brief set connection
	*/
	void setConnection(const std::string& hostname, int port, const std::string& username, const std::string& password, const std::string& dbname);


	/**
	* @brief create client database
	*/
	void createClientDatabase();

	/**
	* @brief destroy client database
	*/
	void destroyClientDatabase();

protected:
	/**
	* @brief generate connection string
	*/
	void generateConnectionStr();

	/**
	* @brief get int value from bson_value
	* 
	* @return int value
	*/
	int getInt32FromValue(const bson_value_t *value);

	/**
	* @brief get int64_t value from bson_value
	*
	* @return int64_t value
	*/
	int64_t getInt64FromValue(const bson_value_t * value);

	/**
	* @brief get double value from bson_value
	*
	* @return double value
	*/
	double getDoubleFromValue(const bson_value_t * value);

	/**
	* @brief get string value from bson_value
	*
	* @return string value
	*/
	std::string getStringFromValue(const bson_value_t * value);

	/**
	* @brief intialize
	*/
	void init();

	/**
	* @brief on timer event
	*/
	void onTimer();
protected:
	std::string m_connection_str; ///< connection string
	std::string m_connection_str_template; ///< connection string template

	std::string m_username; ///< username
	std::string m_password; ///< password
	std::string m_hostname; ///< host name
	int m_port; ///< port

	std::string m_dbname; ///< database name
	std::string m_c_name_instruments; ///< collection name

	mongoc_client_t * m_client; ///< client
	mongoc_database_t * m_database; ///< database
protected:
	std::map<std::string, std::queue<std::string> > m_insertdoc_queue_map; ///< documents queue

	int m_max_insert_count; ///< maximum count for inserting

	boost::signals2::connection m_connectionTimer; ///< signal connection

};//class XT_COMMON_API MongoDbMgr


}//namespace XT

#endif //#ifndef XT_DISABLE_MONGO

#endif