#pragma once
#include <string>
namespace experis
{

class Writer
{
public:
	explicit Writer() = default;
	Writer(const Writer& a_other) = delete;
	Writer& operator=(const Writer& a_other) = delete;
	virtual ~Writer() = default;

	virtual Writer& operator<<(const std::string& a_val) = 0;
};


} //experis