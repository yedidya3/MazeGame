#pragma once
#include <functional>
#include "CreatorPlayer_Base.h"
#include "ReaderStream.h"
#include "WriterStream.h"

namespace experis
{

class RunPlayerStream
{
public:
	explicit RunPlayerStream(CreatorPlayer_Base& a_creatorPlayers, std::function<void(Player&, std::unique_ptr<Reader>)> a_funcRun);
	RunPlayerStream(const RunPlayerStream& a_other) = delete;
	RunPlayerStream& operator=(const RunPlayerStream& a_other) = delete;
	~RunPlayerStream() = default;

	template<typename TInput, typename TOutput>
	void operator()(TInput& a_inputStream, TOutput& a_outputStream);

private:
	CreatorPlayer_Base& m_creatorPlayers;
	std::function<void(Player&, std::unique_ptr<Reader>)> m_funcRun;
};

struct DeleteRegister
{
	DeleteRegister(std::unique_ptr<Player> a_player, CreatorPlayer_Base& a_FuncFinish) 
		:m_player{a_player.release()} ,m_funcFinish{a_FuncFinish}{};
	~DeleteRegister(){m_funcFinish.DestroyPlayer(std::move(m_player));}
	std::unique_ptr<Player> m_player;
	CreatorPlayer_Base& m_funcFinish;
};

template<typename TInput, typename TOutput>
void RunPlayerStream::operator()(TInput& a_inputStream, TOutput& a_outputStream)
{
	try
	{
		std::unique_ptr<Reader> reader = std::make_unique<ReaderStream<TInput>>(a_inputStream);
		Reader& ReaderRef = *reader;
		std::unique_ptr<Player> player = m_creatorPlayers.CreatePlayer(std::make_unique<WriterStream<TOutput>>(a_outputStream), *reader);
		Player& playerRef = *player;
		DeleteRegister returnResources{std::move(player), m_creatorPlayers};
		m_funcRun(playerRef, std::make_unique<ReaderStream<TInput>>(a_inputStream));
	}
	catch(const std::exception&)
	{
		int x = 42;
	}
}


} //experis

