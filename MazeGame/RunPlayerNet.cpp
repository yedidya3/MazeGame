#include "RunPlayerNet.h"
#include "WriterNet.h"
#include "ReadNet.h"
namespace experis
{

RunPlayerNet::RunPlayerNet(CreatorPlayer_Base& a_creatorPlayers,  std::function<void(Player&, std::unique_ptr<Reader>)> a_funcRun)
	:m_creatorPlayers{a_creatorPlayers}
	,m_funcRun{a_funcRun}
{
}


struct DeleteRegister
{
	DeleteRegister(std::unique_ptr<Player> a_player, CreatorPlayer_Base& a_FuncFinish) 
		:m_player{a_player.release()} ,m_funcFinish{a_FuncFinish}{};
	~DeleteRegister(){m_funcFinish.DestroyPlayer(std::move(m_player));}
	std::unique_ptr<Player> m_player;
	CreatorPlayer_Base& m_funcFinish;
};


void RunPlayerNet::operator()(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection)
{
	std::unique_ptr<Reader> reader{std::make_unique<ReadNet>(a_connection)};
	std::unique_ptr<Player> player = m_creatorPlayers.CreatePlayer(std::make_unique<WriterNet>(a_connection), *reader);
	Player& playerRef = *player;
	DeleteRegister returnResources{std::move(player), m_creatorPlayers};
	try
	{
		m_funcRun(playerRef, std::make_unique<ReadNet>(a_connection));
	}
	catch(std::exception&)
	{
		int x = 42;
	}
}


} //experis