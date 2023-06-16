#pragma once
#include "Player.h"
#include "StructureRooms.h"
#include "ContentsRooms.h"
namespace experis
{

class CommandDrawRoom
{
public:
	explicit CommandDrawRoom(const StructureRooms& a_rooms, const ContentsRooms& m_contentRooms, const size_t  a_lengthAxisX = 30, const size_t a_lengthAxisY = 15);
	CommandDrawRoom(const CommandDrawRoom& a_other);
	CommandDrawRoom& operator=(const CommandDrawRoom& a_other) = delete;
	~CommandDrawRoom() = default;

	void operator()(Player& a_player);

private:
	const StructureRooms& m_rooms;
	const ContentsRooms& m_contentRooms;
	const size_t  m_lengthAxisX;
	const size_t  m_lengthAxisY;

};

} //experis
