#pragma once
#include "Writer.h"
#include "SimpleNetMT.h"
namespace experis
{

class WriterNet : public Writer 
{
public:
	WriterNet() = delete;
	WriterNet(const WriterNet& a_other) = delete;
	WriterNet& operator=(const WriterNet& a_other) = delete;
	~WriterNet() = default;

	explicit WriterNet(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connect);

	virtual WriterNet& operator<<(const std::string& a_val);

private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_connect;
};

} //experis
