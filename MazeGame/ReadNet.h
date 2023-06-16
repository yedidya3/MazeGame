#pragma once
#include "SimpleNetMT.h"
#include "Reader.h"
namespace experis
{
class ReadNet : public Reader
{
public:
	explicit ReadNet() = delete;
	ReadNet(const ReadNet& a_other) = delete;
	ReadNet& operator=(const ReadNet& a_other) = delete;
	virtual ~ReadNet() = default;

	explicit ReadNet(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connect);

	virtual std::string ReadLine() override;

private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_connect;
};

} //experis
