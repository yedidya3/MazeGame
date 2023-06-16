#include "TreasureBox.h"
#include <unordered_map>
#include "Line.h"
#include <cassert>
namespace experis
{


namespace treasure_boxs{
static constexpr int POINTS_ADD = 10;
static constexpr int POINTS_SUB = 6;


void DrawBox(Group& a_group, const ascii::ColoredCanvas::Color& a_color)
{
	a_group.Add<Line>(1,0,0).SetBrush('?').SetFg(a_color);
	a_group.Add<Line>(0,1,0).SetBrush('(').SetFg(a_color);
	a_group.Add<Line>(2,1,0).SetBrush(')').SetFg(a_color);
	a_group.Add<Line>(1,1,0).SetBrush('_').SetFg(a_color);
}

static std::unordered_map<TreasureBoxTypes, std::function<void(Player&)>> collectionActions
{
	{TreasureBoxTypes::EMPTY, [&](Player& a_player){ a_player.GetWriter()->operator<<("The box is empty\n");}},
	{TreasureBoxTypes::LIFE, [&](Player& a_player){ a_player.AddToLifePoints(POINTS_ADD); a_player.GetWriter()->operator<<("You received " + std::to_string(POINTS_ADD) + "\n");}},
	{TreasureBoxTypes::STRONG, [&](Player& a_player){ a_player.GetWriter()->operator<<("The box is empty\n");}},
	{TreasureBoxTypes::MINED, [&](Player& a_player){ a_player.GetWriter()->operator<<("The box is trapped, you lost " + std::to_string(POINTS_ADD) + " points\n");}}
};


static std::unordered_map<TreasureBoxTypes, std::function<void(Group&)>> drawingBoxes
{
	{TreasureBoxTypes::EMPTY, [&](Group& a_group){ DrawBox(a_group, ascii::ColoredCanvas::CYAN);}},
	{TreasureBoxTypes::LIFE, [&](Group& a_group){ DrawBox(a_group, ascii::ColoredCanvas::GREEN);}},
	{TreasureBoxTypes::STRONG, [&](Group& a_group){ DrawBox(a_group, ascii::ColoredCanvas::MAGENTA);}},
	{TreasureBoxTypes::MINED, [&](Group& a_group){ DrawBox(a_group, ascii::ColoredCanvas::RED);}}
};

void Collect(const TreasureBoxTypes& a_typeBox, Player& a_player)
{
	assert(collectionActions.find(a_typeBox) != collectionActions.end());
	collectionActions.at(a_typeBox)(a_player);
}

void Draw(const TreasureBoxTypes& a_typeBox, Group& a_draw)
{
	assert(drawingBoxes.find(a_typeBox) != drawingBoxes.end());
	drawingBoxes.at(a_typeBox)(a_draw);
}

} //treasure_box


} //experis