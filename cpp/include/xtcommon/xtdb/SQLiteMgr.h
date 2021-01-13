#pragma once
#ifndef XT_SQLITEMGR_H
#define XT_SQLITEMGR_H

/**
* \file SQLiteMgr.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for sqlite databases.
*
* \description
*	Designed for managing sqlite databases.
*/

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>

#include "XTConfig.h"

#include "Util.h"
#include "FileUtil.h"
#include "InstrSpec.h"
#include "Instr.h"

#include "Bar.h"

#include "LogUtil.h"
 

#include "SettingsMgr.h"

#include <SQLiteCpp/Backup.h>
#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/SQLiteException.h>


namespace XT
{

class XT_COMMON_API MainDBMgr
{
public:
	/**
	* @name constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	MainDBMgr();

	/**
	* @brief default copy constructor
	*/
	MainDBMgr(const MainDBMgr& from);// = default;

	/**
	* @brief default copy assignment
	*/
	MainDBMgr& operator=(const MainDBMgr& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~MainDBMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static MainDBMgr* getInstance();
protected:
	std::string m_mainDbFile; ///< main db file
	boost::shared_ptr<SQLite::Database > m_db; ///< main db
//	SQLite::Database* m_db;
public:
	/**
	* @brief get main db file
	*
	* @return main db file
	*/
	const std::string& getMainDbFile();

	/**
	* @brief set main db file
	*
	* @param s as main db file
	*/
	void setMainDbFile(const std::string& s);

	/**
	* @brief if client is null or not
	*
	* @return if client is created successfully
	*/
	bool isNULL();

	/**
	* @brief execuate sql
	*
	* @sql as sql string
	*/
	void execSql(const std::string& sql);

	/**
	* @brief get query results
	*
	* @param sql
	*
	* @return vector of query results
	*/
	std::vector<std::string> getQueryResults(const std::string& sql );

	/**
	* @brief get instrspec by instrid
	*
	* @param instrid
	*
	* @return InstrSpecPtr
	*/
	InstrSpecPtr getInstrSpecByInstrID(const std::string& instrid );
	
	/**
	* @ if instrid exists
	*
	*/
	bool hasInstrID(const std::string& instrid);

	/**
	* @brief get instr by instrid and booklevels
	*
	* @param instrid
	* @param booklevels
	*
	* @return InstrPtr
	*/
	InstrPtr getInstrByInstrID(const std::string& instrid, int booklevels );

	/**
	* @brief get instrs by sql and booklevels
	*
	* @param sql for query
	* @param booklevels
	*
	* @return vector of InstrPtr
	*/
	std::vector<InstrPtr > getInstrsBySql(const std::string& sql, int booklevels);

	/**
	* @brief get instrspecs by sql and booklevels
	*
	* @param sql for query
	* @param booklevels
	*
	* @return vector of InstrSpecPtr
	*/
	std::vector<InstrSpecPtr > getInstrSpecsBySql(const std::string& sql );

protected:

};

class XT_COMMON_API TrdDBMgr
{
public:
	/**
	* @name constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TrdDBMgr();

	/**
	* @brief default copy constructor
	*/
	TrdDBMgr(const TrdDBMgr& from);// = default;

									 /**
									 * @brief default copy assignment
									 */
	TrdDBMgr& operator=(const TrdDBMgr& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TrdDBMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static TrdDBMgr* getInstance();
protected:
	std::string m_trdDbFile; ///< trade database file
//	boost::shared_ptr<SQLite::Database > m_db;
	SQLite::Database* m_db; ///< trade sqlite client
public:
	/**
	* @brief get trade database file
	*
	* @return trade database file
	*/
	const std::string& getTrdDbFile();

	/**
	* @brief set trade database file
	*
	* @param s as trade database file name
	*/
	void setTrdDbFile(const std::string& s);

	/**
	* @brief check if client is null
	*
	* @return if client is created successfully
	*/
	bool isNULL();

	/**
	* @brief create ohlcv table for exchange
	*
	* @param exch as exchange id
	*/
	void create_dt_ohlcv_exch(const std::string& exch);
	
	/**
	* @brief get barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param startdt as start timestamp
	* @param enddt as end timestamp
	*
	* @return barlist
	*/
	BarListPtr  getBarListForInstrID(const std::string& exch, const std::string& instrid, int64_t startdt, int64_t enddt );

	/**
	* @brief get barlist for instrid
	*
	* @param exch as exchange id
	* @param instrid
	* @param enddt as end timestamp
	* @param num as maximum number of entries
	*
	* @return barlist
	*/
	BarListPtr  getBarListForInstrIDWithLimit(const std::string& exch, const std::string& instrid, int64_t enddt , int num);

	 
public:
	/**
	* @brief execute sql command
	*
	* @param sql
	*/
	void execSql(const std::string& sql);

	/**
	* @brief get query results
	*
	* @param sql as query string
	*
	* @return vector of query results
	*/
	std::vector<std::string> getQueryResults(const std::string& sql);

 
protected:
	std::string m_sql_sqlite_create_dt_ohlcv_exch; ///< sql for creating ohlcv table
};


class XT_COMMON_API SQLiteMgr
{
public:
	/**
	* @name constructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	SQLiteMgr();

	/**
	* @brief destructor
	*/
	virtual ~SQLiteMgr();

	///@}
public:
	/**
	* @brief get singleton instance
	*
	* @return singleton instance
	*/
	static SQLiteMgr* getInstance();

	/**
	* @brief get main database file
	*
	* @return main database file
	*/
	std::string getMainDbFile();

	/**
	* @brief set main database file
	*
	* @param s as main database file
	*/
	void setMainDbFile(const std::string& s);

	/**
	* @brief get trade database file
	*
	* @return trade database file
	*/
	std::string getTrdDbFile();

	/**
	* @brief set trade database file
	*
	* @param s as trade database file
	*/
	void setTrdDbFile(const std::string& s);

	/**
	* @brief get base directory
	*
	* @return base directory
	*/
	std::string getBaseDir();

	/**
	* @brief set base directory
	*
	* @param s as base directory
	*/
	void setBaseDir(const std::string& s);

	///@}


	/** @name Query and Insert Functions
	*
	*/
	///@{

	/**
	* @brief execute sql command
	*
	* @param sql
	* @param dbfile as database file name
	*/
	void execSql(const std::string& sql, const std::string& dbfile);

	/**
	* @brief get query results
	*
	* @param sql as query string
	* @param dbfile as database file name
	*
	* @return vector of query results
	*/
	std::vector<std::string> getQueryResults(const std::string& sql, const std::string& dbfile);

	///@}

protected:
	std::string m_baseDir; ///< base directory
};//class

}//namespace XT


#endif