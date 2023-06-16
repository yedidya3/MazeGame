#include "ShoutState.h"
#include "TalkState.h"
namespace experis
{
    
ShoutState::ShoutState(ContentsRooms& a_roomSecretariat, std::shared_ptr<InputModeState> a_nextState, StructureRooms& a_rooms)
	:InputModeState{}
	,m_roomSecretariat{a_roomSecretariat}
	,m_nextState{a_nextState}
    ,m_rooms{a_rooms}
{
}

std::shared_ptr<InputModeState> ShoutState::Next(Player& a_player, const std::string& a_input)
{
        const std::string msg = "Shout from " + a_player.GetName() + ": \"" + a_input + "\"\n";
        m_roomSecretariat.Get(a_player.GetNumRoom()).ActionOnRoomPlayers([&](Player& a_playerAnother)
		{
			a_playerAnother.GetWriter()->operator<<(msg);
		});
        std::shared_ptr<StructureRoom> thisRoom = m_rooms.Get(a_player.GetNumRoom());
        std::vector<Directions> directions{Directions::EAST, Directions::WEST, Directions::SOUTH, Directions::NORTH};
        for (const Directions& direction : directions)
        {
            StructureRoom::NumRoomOption numRoomOption = thisRoom->GetIdxRoomNext(direction);
            if (numRoomOption.has_value())
            {
                m_roomSecretariat.Get(numRoomOption.value()).ActionOnRoomPlayers([&](Player& a_playerAnother)
		        {
			        a_playerAnother.GetWriter()->operator<<(msg);
		        });
            }
        }
        return m_nextState;
}


    


} //experis