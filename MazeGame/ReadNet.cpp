#include "ReadNet.h"

namespace experis
{
ReadNet::ReadNet(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connect)
	:Reader{}
	,m_connect{a_connect}
{
}

std::string ReadNet::ReadLine()
{
	return m_connect->ReadLine();
}

}//experis