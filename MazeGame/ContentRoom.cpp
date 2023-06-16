#include "ContentRoom.h"
#include <Random>
#include "RandomMy.h"

namespace experis
{

treasure_boxs::TreasureBoxTypes RandomBox()
{
   return static_cast<treasure_boxs::TreasureBoxTypes>(detail::random::Rand() % static_cast<int>(treasure_boxs::TreasureBoxTypes::SUM));
}

std::optional<treasure_boxs::TreasureBoxTypes> RandomBoxOption()
{
	if (detail::random::Rand() % 2)
	{
		return RandomBox();
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<Dragon> RandomDragon()
{
	if (detail::random::Rand() % 2)
	{
		return Dragon{50};
	}
	else
	{
		return std::nullopt;
	}
}


ContentRoom_mt::ContentRoom_mt()
	:m_players{}
	,m_playersMtx{}
	,m_treasureBox{RandomBoxOption()}
	,m_dragon{RandomDragon()}
{
}


bool ContentRoom_mt::Registration(Player& a_player)
{
	std::lock_guard<std::shared_timed_mutex> writerLock{m_playersMtx};
	m_players.push_back(&a_player);	
	return true;
}

bool ContentRoom_mt::RemovePlayer(Player& a_player)
{
	std::lock_guard<std::shared_timed_mutex> writerLock{m_playersMtx};
	/*
	m_players.remove_if([&](Player* a_playerRow)
		{ return a_playerRow->GetName() == a_player.GetName();});
	*/

	// Erase all even numbers
    for (std::deque<Player*>::iterator it = m_players.begin(); it != m_players.end();)
    {
        if ((*it)->GetName() == a_player.GetName())
            it = m_players.erase(it);
        else
            ++it;
    }



	return true;
}

void ContentRoom_mt::ActionOnRoomPlayers(std::function<void(Player&)> a_actionFunc)
{
	std::lock_guard<std::shared_timed_mutex> writerLock{m_playersMtx};
	for (Player*& rival : m_players)
	{
		a_actionFunc(*rival);
	}
}

void ContentRoom_mt::ActionOnAnotherRandomPlayer(Player& a_player, std::function<void(std::optional<Player*>)> a_actionFunc)
{
	std::lock_guard<std::shared_timed_mutex> writerLock{m_playersMtx};
	std::mt19937 gen(detail::random::Rand());
	std::shuffle(m_players.begin(), m_players.end(), gen);
	for (Player* rival : m_players) //ToDo: random
	{
		if (IsLife(*rival) && rival->GetName() != a_player.GetName())
		{
			a_actionFunc(rival);
			return;
		}
	}
	a_actionFunc({});
}


void ContentRoom_mt::BoxCollection(Player& a_player)
{
	std::lock_guard<std::shared_timed_mutex> writerLock{m_playersMtx};
	if (m_treasureBox.has_value())
	{
		treasure_boxs::Collect(m_treasureBox.value(), a_player);
	}
	else
	{
		a_player.GetWriter()->operator<<("There is no treasure box in this room");
	}
}

void ContentRoom_mt::BoxDraw(Group& a_group) const
{
	std::shared_lock<std::shared_timed_mutex> readerLock{m_playersMtx};
	if (m_treasureBox.has_value())
	{
		treasure_boxs::Draw(m_treasureBox.value(), a_group);
	}
}

void ContentRoom_mt::DragonDraw(Group& a_group) const
{
	std::shared_lock<std::shared_timed_mutex> readerLock{m_playersMtx};
	if (m_dragon.has_value())
	{
		Draw(m_dragon.value(), a_group);
	}
}

} //experis
