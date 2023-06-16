#pragma once
#include "Reader.h"
namespace experis
{

template<typename T>
class ReaderStream : public Reader
{
public:
	ReaderStream(T& a_stream)
		:Reader{}
		,m_stream{a_stream}
	{
	}
	virtual ~ReaderStream() = default;


	virtual std::string ReadLine() override
	{
		std::string input{};
		std::getline(m_stream, input);
		return input;
	}

private:
	T& m_stream;
};

} //experis
