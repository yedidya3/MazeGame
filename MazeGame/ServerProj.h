#pragma once

#include "CyclinBlockingQueue.h"
#include "UrlPathReader.h"
#include "SimpleNetMT.h"
#include <thread>
namespace experis
{
static const size_t MAX_QUEUE = 1000; 
template<typename TFunc>
class ServerProj
{
public:
	ServerProj() = delete;
	ServerProj(const ServerProj& a_other) = delete;
	ServerProj& operator=(const ServerProj& a_other) = delete;
	~ServerProj() = default;

	explicit ServerProj(TFunc& a_funcEx, const unsigned short a_port, size_t a_amountHandlers);

private:
	void PorterHandler();
	void RequestHandler();
	std::list<std::unique_ptr<std::thread>> CreateHandlersRequests(size_t a_amountHandlers);

	TFunc& m_funcEx;
	simplenet::SimpleNetMT m_net;
	CyclinBlockingQueue_mt<std::shared_ptr<simplenet::SimpleNetMT::Connection>, MAX_QUEUE> m_Requests;
	std::thread m_porter;
	std::list<std::unique_ptr<std::thread>> m_handlingRequests;
};


template<typename TFunc>
ServerProj<TFunc>::ServerProj(TFunc& a_funcEx, const unsigned short a_port, size_t a_amountHandlers)
	:m_funcEx{a_funcEx}
	,m_net{a_port}
	,m_porter{&ServerProj::PorterHandler , this}
	,m_Requests{}
	,m_handlingRequests{CreateHandlersRequests(a_amountHandlers)}
{
}

template<typename TFunc>
void ServerProj<TFunc>::PorterHandler()
{
	while (true)
	{
		std::shared_ptr<simplenet::SimpleNetMT::Connection> c = std::make_unique<simplenet::SimpleNetMT::Connection> //TODO: shared
			(simplenet::SimpleNetMT::Connection(m_net.WaitForConnection()));
		m_Requests.Push(c);
	}
}

template<typename TFunc>
std::list<std::unique_ptr<std::thread>> ServerProj<TFunc>::CreateHandlersRequests(size_t a_amountHandlers)
{
	std::list<std::unique_ptr<std::thread>> toRet;
	for (size_t idx = 0 ; idx < a_amountHandlers ; ++idx)
	{
		toRet.push_back(std::make_unique<std::thread>(&ServerProj::RequestHandler, this));
	}
	return toRet;
}


template<typename TFunc>
void ServerProj<TFunc>::RequestHandler()
{
	while (true)
	{
		std::shared_ptr<simplenet::SimpleNetMT::Connection> c;
		m_Requests.Pop(c);
		try
		{
			m_funcEx.operator()(c);
		}
		catch (const simplenet::SimpleNetMT::ConnectionClosed&)
		{
			//std::cout << "CLOSED\n";
		}
	}
}






}//experis
