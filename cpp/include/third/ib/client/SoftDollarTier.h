#pragma once
#include "XTConfig.h"
#include "StdAfx.h"

class XT_COMMON_API SoftDollarTier
{
	std::string m_name, m_val, m_displayName;

public:
	SoftDollarTier(const std::string& name = "", const std::string& val = "", const std::string& displayName = "");

	std::string name() const;
	std::string val() const;
	std::string displayName() const;
	
	void set_name(const std::string& s);
	void set_val(const std::string& s);
	void set_displayname(const std::string& s);
};

