#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "OperatorCondition.h"

class XT_COMMON_API TimeCondition : public OperatorCondition {
	friend OrderCondition;

	std::string m_time;

protected:
	TimeCondition() { }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::Time;

	virtual std::string toString();

	std::string time();
	void time(const std::string &time);
};