#include "DbNames_mt.h"

namespace experis
{

DbNames_mt::DbNames_mt()
	:m_names{}
	,m_namesMtx{}
{
}

bool DbNames_mt::Add(const std::string& a_val)
{
	std::unique_lock<std::mutex> lockName{m_namesMtx};
	if (m_names.count(a_val))
	{
		return false;
	}
	else
	{
		m_names[a_val] = true;
		return true;
	}
}
bool DbNames_mt::Delete(const std::string& a_val)
{
	std::unique_lock<std::mutex> lockName{m_namesMtx};
	if (m_names.count(a_val))
	{
		return false;
	}
	else
	{
		m_names.erase(a_val);
		return true;
	}
}



}
