#pragma once
#include <unordered_map>
#include <functional>
#include <shared_mutex>
#include "Player.h"
#include "TreasureBox.h"
#include "Group.h"
#include <deque>
#include "Dragon.h"

namespace experis
{

class ContentRoom_mt
{
public:
	explicit ContentRoom_mt();
	ContentRoom_mt(const ContentRoom_mt& a_other) = delete;;
	ContentRoom_mt& operator=(const ContentRoom_mt a_other) = delete;
	~ContentRoom_mt() = default;

	bool Registration(Player& a_player);
	bool RemovePlayer(Player& a_player);
	void ActionOnRoomPlayers(std::function<void(Player&)> a_actionFunc);
	void ActionOnAnotherRandomPlayer(Player& a_player, std::function<void(std::optional<Player*>)> a_actionFunc);

	void BoxCollection(Player& a_player);
	void BoxDraw(Group& a_player) const;
	void DragonDraw(Group& a_player) const;

private:
	std::deque<Player*> m_players;
	mutable std::shared_timed_mutex m_playersMtx;
	std::optional<treasure_boxs::TreasureBoxTypes> m_treasureBox;
	std::optional<Dragon> m_dragon;
};





}