#pragma once
#ifndef XT_TALIBFUNCINFO_H
#define XT_TALIBFUNCINFO_H

/**
* \file TALibFuncInfo.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide classes for TALibFuncInfo.
*
* \description
*	Designed for describing TALibFuncInfo.
*/

#include <cstdint>
#include <set>
#include <vector>
#include <map>

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

#include "XTConfig.h"
#include "LogUtil.h"
#include "Util.h"
#include "ta_libc.h"

namespace XT
{

class XT_COMMON_API TALibInputParameterInfo
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TALibInputParameterInfo();

	/**
	* @brief default copy constructor
	*/
	TALibInputParameterInfo(const TALibInputParameterInfo& from);// = default;

	/**
	* @brief default copy assignment
	*/
	TALibInputParameterInfo& operator=(const TALibInputParameterInfo& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TALibInputParameterInfo();

	///@}

	/**
	* @brief get flags
	*
	* @return flags as int
	*/
	int getFlags();

	/**
	* @brief set flags
	*
	* @param v as flags
	*/
	void setFlags(int v);

	/**
	* @brief get parameter name
	*
	* @return parameter name
	*/
	const std::string& getParamName();

	/**
	* @brief set parameter name
	*
	* @param v as parameter name
	*/
	void setParamName(const std::string& v);

	/**
	* @brief get type value
	*
	* @return type value
	*/
	int getType();

	/**
	* @brief set type value
	*
	* @param v as type value
	*/
	void setType(int v);
protected:
	int m_flags; ///< flags
	std::string m_paramName; ///< parameter name
	int m_type; ///< type value
};//class XT_COMMON_API TALibInputParameterInfo

  //////typedef for TALibInputParameterInfo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<TALibInputParameterInfo> TALibInputParameterInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<TALibInputParameterInfo> TALibInputParameterInfoPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<TALibInputParameterInfo> TALibInputParameterInfoPtr;

#else

typedef ::boost::shared_ptr<TALibInputParameterInfo> TALibInputParameterInfoPtr;
#endif


typedef ::sf::safe_ptr<TALibInputParameterInfo> TALibInputParameterInfoSafePtr;

typedef sf::contfree_safe_ptr<TALibInputParameterInfo> TALibInputParameterInfoContFreePtr;
//////end typedef for TALibInputParameterInfo

class XT_COMMON_API TALibOptInputParameterInfo
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TALibOptInputParameterInfo();

	/**
	* @brief default copy constructor
	*/
	TALibOptInputParameterInfo(const TALibOptInputParameterInfo& from);// = default;

	 /**
	 * @brief default copy assignment
	 */
	TALibOptInputParameterInfo& operator=(const TALibOptInputParameterInfo& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TALibOptInputParameterInfo();
	///@}

	/**
	* @brief get default value
	*
	* @return default value
	*/
	double getDefaultValue();

	/**
	* @brief set default value
	*
	* @param v as default value
	*/
	void setDefaultValue(double v);

	/**
	* @brief get type value
	*
	* @return type value
	*/
	int getType();

	/**
	* @brief set type value
	*
	* @param v as type value
	*/
	void setType(int v);

	/**
	* @brief get flags
	* 
	* @return flags value
	*/
	int getFlags();

	/**
	* @brief set flags
	*
	* @param v as flags
	*/
	void setFlags(int v);

	/**
	* @brief get parameter name
	*
	* @return parameter name
	*/
	const std::string& getParamName();

	/**
	* @brief set parameter name
	*
	* @param v as parameter name
	*/
	void setParamName(const std::string& v);

	/**
	* @brief get display name
	*
	* @return display name
	*/
	const std::string& getDisplayName();

	/**
	* @brief set display name
	*
	* @param v as display name
	*/
	void setDisplayName(const std::string& v);

	/**
	* @brief get hint string
	*
	* @return hint strng
	*/
	const std::string& getHint();

	/**
	* @brief set hint string
	*
	* @param v as hint
	*/
	void setHint(const std::string& v);

	/**
	* @brief get help file
	*
	* @return help file
	*/
	const std::string& getHelpFile();

	/**
	* @brief set help file
	*
	* @param v as help file
	*/
	void setHelpFile(const std::string& v);

protected:
	double m_defaultValue; ///< default value
	int m_type; ///< type value
	int m_flags; ///< flags value
	std::string m_paramName; ///< parameter name
	std::string m_displayName; ///< display name
	std::string m_hint; ///< hint information
	std::string m_helpFile; ///< help file


};//class XT_COMMON_API TALibOptInputParameterInfo

  //////typedef for TALibOptInputParameterInfo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoPtr;

#else

typedef ::boost::shared_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoPtr;
#endif


typedef ::sf::safe_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoSafePtr;

typedef sf::contfree_safe_ptr<TALibOptInputParameterInfo> TALibOptInputParameterInfoContFreePtr;
//////end typedef for TALibOptInputParameterInfo

class XT_COMMON_API TALibOutputParameterInfo
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TALibOutputParameterInfo();

	/**
	* @brief default copy constructor
	*/
	TALibOutputParameterInfo(const TALibOutputParameterInfo& from);// = default;

	/**
	* @brief default copy assignment
	*/
	TALibOutputParameterInfo& operator=(const TALibOutputParameterInfo& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TALibOutputParameterInfo();

	///@}

	/**
	* @brief get flags
	*
	* @return flags value
	*/
	int getFlags();

	/**
	* @brief set flags
	*
	* @param v as flags
	*/
	void setFlags(int v);

	/**
	* @brief get parameter name
	*
	* @return parameter name
	*/
	const std::string& getParamName();

	/**
	* @brief set parameter name
	*
	* @param v as parameter name
	*/
	void setParamName(const std::string& v);

	/**
	* @brief get type value
	*
	* @return type value
	*/
	int getType();

	/**
	* @brief set type value
	*
	* @param v as type value
	*/
	void setType(int v);
protected:
	int m_flags;///< flags value
	std::string m_paramName; ///< parameter name
	int m_type; ///< type value
};//class XT_COMMON_API TALibOutputParameterInfo

  //////typedef for TALibOutputParameterInfo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoPtr;

#else

typedef ::boost::shared_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoPtr;
#endif


typedef ::sf::safe_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoSafePtr;

typedef sf::contfree_safe_ptr<TALibOutputParameterInfo> TALibOutputParameterInfoContFreePtr;
//////end typedef for TALibOutputParameterInfo

class XT_COMMON_API TALibFuncInfo
{
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	TALibFuncInfo();

	/**
	* @brief default copy constructor
	*/
	TALibFuncInfo(const TALibFuncInfo& from);// = default;

	/**
	* @brief default copy assignment
	 */
	TALibFuncInfo& operator=(const TALibFuncInfo& from);// = default;

	/**
	* @brief destructor
	*/
	virtual ~TALibFuncInfo();

	///@}

	/**
	* @brief intialization
	*
	* @param name as function name
	*/
	void init(const std::string& name);

	/**
	* @brief get name
	*
	* @return name
	*/
	const std::string& getName();

	/**
	* @brief set name
	*
	* @param v as name
	*/
	void setName(const std::string& v);
	 
	/**
	* @brief get camel case name
	*
	* @return camel case name
	*/
	const std::string& getCamelCaseName();

	/**
	* @brief set camel case name
	*
	* @param v as camel case name
	*/
	void setCamelCaseName(const std::string& v);
	 
	/**
	* @brief get group name
	*
	* @return group name
	*/
	const std::string& getGroup();

	/**
	* @brief set group name
	*
	* @param v as group name
	*/
	void setGroup(const std::string& v);
	 
	/**
	* @brief get hint
	* 
	* @return hint
	*/
	const std::string& getHint();

	/**
	* @brief set hint
	*
	* @param v as hint
	*/
	void setHint(const std::string& v);
	 
	/**
	* @brief get flags value
	*
	* @return flags value
	*/
	int getFlags();

	/**
	* @brief set flags value
	*
	* @param v as flags value
	*/
	void setFlags(int v);
	 

	/**
	* @brief get number of inputs
	*
	* @return number of inputs
	*/
	unsigned int getNbInput();

	/**
	* @brief set number of inputs
	*
	* @param v as number of inputs
	*/
	void setNbInput(unsigned int v);
	 
	/**
	* @brief get number of optional inputs
	*
	* @return number of optional inputs
	*/
	unsigned int getNbOptInput();

	/**
	* @brief set number of optional inputs
	*
	* @param v as number of optional inputs
	*/
	void setNbOptInput(unsigned int v);
	 
	/**
	* @brief get number of outputs
	*
	* @return number of outputs
	*/
	unsigned int getNbOutput();

	/**
	* @brief set number of outputs
	*
	* @param v as number of outputs
	*/
	void setNbOutput(unsigned int v);
	 
	/**
	* @brief get number of integer outputs
	*
	* @return number of integer outputs
	*/
	unsigned int getNbIntOutput();

	/**
	* @brief get output name by output index
	*
	* @param idx as output index
	*
	* @return output name
	*/
	const std::string& getOutputNameByIdx(int idx);

	/**
	* @brief get output index by output name
	*
	* @param outputname as output name
	* 
	* @return output index
	*/
	int getIdxByOutputName(const std::string& outputname);

	/**
	* @brief input parameter informations
	*
	* @return vector of input parameter informations
	*/
	std::vector<TALibInputParameterInfoPtr >& inputParameterInfos();

	/**
	* @brief optional input parameter informations
	*
	* @return vector of optional input parameter informations
	*/
	std::vector<TALibOptInputParameterInfoPtr >& optInputParameterInfos();

	/**
	* @brief output parameter informations
	*
	* @return vector of output parameter informations
	*/
	std::vector<TALibOutputParameterInfoPtr >& outputParameterInfos();
 
	/**
	* @brief output names
	*
	* @return vector of output names
	*/
	std::vector<std::string>& outputNames();
protected:
 
	std::string m_emptyString; ///< empty string

	std::string m_name; ///< function name
	std::string m_camelCaseName; ///< camel case name
	std::string m_group; ///< group name
	std::string m_hint; ///< hint information

	int m_flags; ///< flags value
 
	unsigned int m_nbInput; ///< number of inputs
	unsigned int m_nbOptInput; ///< number of optional inputs
	unsigned int m_nbOutput; ///< number of outputs

	unsigned int m_nbIntOutput;
 
	std::vector<TALibInputParameterInfoPtr > m_inputParameterInfos; ///< input parameters
	std::vector<TALibOptInputParameterInfoPtr > m_optInputParameterInfos; ///< optional input parameters
	std::vector<TALibOutputParameterInfoPtr > m_outputParameterInfos; ///< output parameters
 
	std::map<std::string, int> m_outputNameToIdxMap; ///< output name to index map
	std::map<int, std::string> m_idxToOutputNameMap; ///< output index to name map
	std::vector<std::string> m_outputNames; ///< output names

};//class XT_COMMON_API TALibFuncInfo

  //////typedef for TALibFuncInfo
#if defined(USE_BOOST_SHARED_PTR)

typedef ::boost::shared_ptr<TALibFuncInfo> TALibFuncInfoPtr;

#elif defined(USE_STD_SHARED_PTR)

typedef ::std::shared_ptr<TALibFuncInfo> TALibFuncInfoPtr;

#elif defined(USE_SAFE_PTR)

typedef ::sf::safe_ptr<TALibFuncInfo> TALibFuncInfoPtr;

#else

typedef ::boost::shared_ptr<TALibFuncInfo> TALibFuncInfoPtr;
#endif


typedef ::sf::safe_ptr<TALibFuncInfo> TALibFuncInfoSafePtr;

typedef sf::contfree_safe_ptr<TALibFuncInfo> TALibFuncInfoContFreePtr;
//////end typedef for TALibFuncInfo

 

}//namespace XT

#endif