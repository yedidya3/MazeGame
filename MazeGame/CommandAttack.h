#pragma once
#include "ContentsRooms.h"
#include "Player.h"
namespace experis
{

class CommandAttack
{
public:
	explicit CommandAttack(ContentsRooms& a_contentsRooms, const int a_subPoints = 35);
	CommandAttack(const ContentsRooms& a_other) = delete;
	CommandAttack operator=(const ContentsRooms& a_other) = delete;
	~CommandAttack() = default;

	void operator()(Player& a_player);

private:
	ContentsRooms& m_contentsRooms;
	int m_subPoints;
};


}