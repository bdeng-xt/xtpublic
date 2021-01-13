#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "ContractCondition.h"
#include "Order.h"

class XT_COMMON_API PercentChangeCondition : public ContractCondition {
	friend OrderCondition;

	double m_changePercent;

protected:
	PercentChangeCondition()
	: m_changePercent(UNSET_DOUBLE)
	{ }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::PercentChange;

	double changePercent();
	void changePercent(double changePercent);
};