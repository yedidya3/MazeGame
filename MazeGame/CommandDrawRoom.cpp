#include "CommandDrawRoom.h"
#include "Group.h"
#include "ProducesRoomsGroup.h"
namespace experis
{




CommandDrawRoom::CommandDrawRoom(const StructureRooms& a_rooms, const ContentsRooms& m_contentRooms, const size_t  a_lengthAxisX, const size_t a_lengthAxisY)
	:m_rooms{a_rooms}
    ,m_contentRooms{m_contentRooms}
    ,m_lengthAxisX{a_lengthAxisX}
    ,m_lengthAxisY{a_lengthAxisY}
{
}

CommandDrawRoom::CommandDrawRoom(const CommandDrawRoom& a_other)
    :m_rooms{a_other.m_rooms}
    ,m_contentRooms{a_other.m_contentRooms}
    ,m_lengthAxisX{a_other.m_lengthAxisX}
    ,m_lengthAxisY{a_other.m_lengthAxisY}
{
}


void CommandDrawRoom::operator()(Player& a_player)
{
    static constexpr short COORD_ROOM_X = 4;
    static constexpr short COORD_ROOM_Y = 2;
	std::unique_ptr<Group> draw = ProducesRoomStructureGroup(*(m_rooms.Get(a_player.GetNumRoom())),
        a_player.GetFacing().GetDirection());

    m_contentRooms.Get(a_player.GetNumRoom()).BoxDraw(draw->Add<Group>(COORD_ROOM_X,COORD_ROOM_Y));
     m_contentRooms.Get(a_player.GetNumRoom()).DragonDraw(draw->Add<Group>(COORD_ROOM_X + 12 ,COORD_ROOM_Y + 1));
    ascii::ColoredCanvas canvas{m_lengthAxisX, m_lengthAxisY};
           
    draw->Draw(canvas);
    std::stringstream ss{};
    canvas.Print(ss, ascii::ColoredCanvas::OutputPosition::CURRENT_LINE);
           
    a_player.GetWriter()->operator<<(ss.str());
}


}