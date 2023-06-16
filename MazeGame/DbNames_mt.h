#pragma once
#include <unordered_map>
#include <string>
#include <mutex>

namespace experis
{

class DbNames_mt
{
public:
	explicit DbNames_mt();
	DbNames_mt(const DbNames_mt& a_other) = delete;
	DbNames_mt& operator=(const DbNames_mt& a_other) = delete;
	~DbNames_mt() = default;
	
	bool Add(const std::string& a_val);
	bool Delete(const std::string& a_val);

private:
	std::unordered_map<std::string, bool> m_names;
	mutable std::mutex m_namesMtx;
};

}
