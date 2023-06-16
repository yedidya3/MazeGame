#pragma once
#include <memory>
#include <functional>
#include "Player.h"
#include "SimpleNetMT.h"
#include "CreatorPlayer_Base.h"
namespace experis
{
class RunPlayerNet
{
public:
	explicit RunPlayerNet(CreatorPlayer_Base& a_creatorPlayers, std::function<void(Player&, std::unique_ptr<Reader>)> a_funcRun);
	RunPlayerNet(const RunPlayerNet& a_other) = delete;
	RunPlayerNet& operator=(const RunPlayerNet& a_other) = delete;
	~RunPlayerNet() = default;

	void operator()(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection); //TODO: change to uniquePtr

private:
	CreatorPlayer_Base& m_creatorPlayers;
	std::function<void(Player&, std::unique_ptr<Reader>)> m_funcRun;
};

} //experis
