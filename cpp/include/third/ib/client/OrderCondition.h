#pragma once
#include "XTConfig.h"
#include "StdAfx.h"
#include "IExternalizable.h"
#include "shared_ptr.h"

class XT_COMMON_API OrderCondition : public IExternalizable {
public:
	enum OrderConditionType {
		Price = 1,
		Time = 3,
		Margin = 4,
		Execution = 5,
		Volume = 6,
		PercentChange = 7
	};

private:
	OrderConditionType m_type;
	bool m_isConjunctionConnection;

public:
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual void writeExternal(std::ostream &out) const;

	std::string toString();
	bool conjunctionConnection() const;
	void conjunctionConnection(bool isConjunctionConnection);	
	OrderConditionType type();
	
	void set_type(OrderConditionType t);
	void set_isConjuctionConnection(bool b);
	
	static OrderCondition *create(OrderConditionType type);
};