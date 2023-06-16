#include "ContentsRooms.h"
#include <cassert>
namespace experis
{


ContentsRooms::ContentsRooms(const std::vector<StateRoom>& a_roomsNumbers)
	:m_rooms{}
{
	size_t numRoom = 0;
	for (StateRoom isOpen : a_roomsNumbers)
	{
		if (isOpen == StateRoom::OPEN)
		{
			m_rooms[numRoom];
		}
		++numRoom;
	}
}


ContentRoom_mt& ContentsRooms::Get(const size_t a_numRoom)
{
	assert(IsExsit(a_numRoom));
	return m_rooms.at(a_numRoom);
}

const ContentRoom_mt& ContentsRooms::Get(const size_t a_numRoom) const
{
	assert(IsExsit(a_numRoom));
	return m_rooms.at(a_numRoom);
}

bool ContentsRooms::IsExsit(const size_t a_numRoom) const
{
	return m_rooms.find(a_numRoom) != m_rooms.end();
}


void MsgToRoom(ContentsRooms& a_contentsRooms, size_t a_numRoom, const std::string& a_msg)
{	
	a_contentsRooms.Get(a_numRoom).ActionOnRoomPlayers([&](Player& a_anotherPlayer)
		{
			a_anotherPlayer.GetWriter()->operator<<(a_msg);
		});
}

void MsgEnter(ContentsRooms& a_contentsRooms, size_t a_numRoom, std::string a_namePlayer)
{
	MsgToRoom(a_contentsRooms, a_numRoom, a_namePlayer + " enter to room\n");
}


} //experis