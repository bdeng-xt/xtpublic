#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "OperatorCondition.h"

class XT_COMMON_API ContractCondition : public OperatorCondition {
	int m_conId;
	std::string m_exchange;

public:
	virtual std::string toString();
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual void writeExternal(std::ostream &out) const;

	int conId();
	void conId(int conId);
	std::string exchange();
	void exchange(const std::string &exchange);
};
