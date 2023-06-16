#pragma once
#include "StructureRooms.h"
#include "ContentsRooms.h"
#include "Player.h"
#include "CommandDrawRoom.h"
namespace experis
{

class CommandWalk
{
public:
	explicit CommandWalk(const StructureRooms& a_structureRooms, ContentsRooms& a_contentsRooms, CommandDrawRoom& a_commandDrawRoom);
	CommandWalk(const ContentsRooms& a_other) = delete;
	CommandWalk& operator=(const ContentsRooms& a_other) = delete;
	~CommandWalk() = default;

	void operator()(Player& a_player);


private:
	const StructureRooms& m_structureRooms;
	ContentsRooms& m_contentsRooms;
	CommandDrawRoom& m_commandDrawRoom;

};


}