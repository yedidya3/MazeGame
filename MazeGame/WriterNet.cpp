#include "WriterNet.h"
namespace experis
{

WriterNet::WriterNet(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connect)
	:m_connect{a_connect}
{
}

WriterNet& WriterNet::operator<<(const std::string& a_val)
{
	try
	{
		m_connect->Write(a_val);
		return *this;
	}
	catch(const simplenet::SimpleNetMT::ConnectionClosed&)
	{
		return *this;
	}
}

} //experis