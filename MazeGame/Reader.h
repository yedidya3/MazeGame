#pragma once
#include <string>
namespace experis
{

class Reader
{
public:
	explicit Reader() = default;
	Reader(const Reader& a_other) = delete;
	Reader& operator=(const Reader& a_other) = delete;
	virtual ~Reader() = default;

	virtual std::string ReadLine() = 0;
};

} //experis
