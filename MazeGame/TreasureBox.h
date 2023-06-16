#pragma once
#include "Group.h"
#include "Player.h"

namespace experis
{

namespace treasure_boxs
{

enum class TreasureBoxTypes
{
	EMPTY,
	LIFE,
	STRONG,
	MINED,
	SUM,
};

void Collect(const TreasureBoxTypes& a_typeBox, Player& a_player);

void Draw(const TreasureBoxTypes& a_typeBox, Group& a_draw);



} //treasure_box

} //experis
