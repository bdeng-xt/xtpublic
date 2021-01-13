#include "StdAfx.h"
#include "SoftDollarTier.h"

SoftDollarTier::SoftDollarTier(const std::string& name, const std::string& val, const std::string& displayName) :
	m_name(name), m_val(val), m_displayName(displayName)
{
}

std::string SoftDollarTier::name() const
{
	return m_name;
}

std::string SoftDollarTier::val() const
{
	return m_val;
}

std::string SoftDollarTier::displayName() const
{
	return m_displayName;
}

void SoftDollarTier::set_name(const std::string& s) { m_name = s; }
void SoftDollarTier::set_val(const std::string& s) { m_val = s; }
void SoftDollarTier::set_displayname(const std::string& s) { m_displayName = s; }