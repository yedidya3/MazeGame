#include "CommandWalk.h"
namespace experis
{

CommandWalk::CommandWalk(const StructureRooms& a_structureRooms, ContentsRooms& a_contentsRooms, CommandDrawRoom& a_commandDrawRoom)
	:m_structureRooms{a_structureRooms}
	,m_contentsRooms{a_contentsRooms}
    ,m_commandDrawRoom{a_commandDrawRoom}
{
}

void CommandWalk::operator()(Player& a_player)
{
	size_t numRoom = a_player.GetNumRoom();
    Directions directory = a_player.GetFacing().GetDirection();
    std::shared_ptr<StructureRoom> room = m_structureRooms.Get(numRoom);
    StructureRoom::NumRoomOption optionRoomNum = room->GetIdxRoomNext(directory);
    if (optionRoomNum.has_value())
    {
        m_contentsRooms.Get(a_player.GetNumRoom()).RemovePlayer(a_player);
        MsgToRoom(m_contentsRooms, a_player.GetNumRoom(), a_player.GetName() + " left\n");
        a_player.SetNumRoom(optionRoomNum.value());

        MsgEnter(m_contentsRooms, a_player.GetNumRoom(), a_player.GetName());
        m_contentsRooms.Get(a_player.GetNumRoom()).Registration(a_player);
        a_player.GetWriter()->operator<<("Room transfer\n");
        m_commandDrawRoom.operator()(a_player);
    }
    else
    {
            a_player.GetWriter()->operator<<("Direction blocked\n");
    }
}



} //experis