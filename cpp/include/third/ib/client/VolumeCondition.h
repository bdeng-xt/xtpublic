#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "ContractCondition.h"

class XT_COMMON_API VolumeCondition : public ContractCondition {
	friend OrderCondition;

	int m_volume;

protected:
	VolumeCondition() { }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::Volume;

	int volume();
	void volume(int volume);
};