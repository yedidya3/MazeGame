#pragma once
#include "Writer.h"
namespace experis
{

template<typename T>
class WriterStream : public Writer
{
public:
	WriterStream(T& a_stream)
		:Writer{}
		,m_stream{a_stream}
	{
	}
	virtual ~WriterStream() = default;

	virtual WriterStream& operator<<(const std::string& a_val) override
	{
		m_stream << a_val;
		return *this;
	}

private:
	T& m_stream;
};

} //experis


