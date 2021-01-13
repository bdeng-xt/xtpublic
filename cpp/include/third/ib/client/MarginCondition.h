#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "OperatorCondition.h"

class XT_COMMON_API MarginCondition : public OperatorCondition {
	friend OrderCondition;

	int m_percent;

public:
	static const OrderConditionType conditionType = OrderConditionType::Margin;

protected:
	MarginCondition() { }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	virtual std::string toString();

	int percent();
	void percent(int percent);
};