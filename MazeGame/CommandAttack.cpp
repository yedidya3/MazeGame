#include "CommandAttack.h"


namespace experis
{
CommandAttack::CommandAttack(ContentsRooms& a_contentsRooms, const int a_subPoints)
	:m_contentsRooms{a_contentsRooms}
    ,m_subPoints{a_subPoints}
{
}

void CommandAttack::operator()(Player& a_player)
{
    m_contentsRooms.Get(a_player.GetNumRoom()).ActionOnAnotherRandomPlayer(a_player, [&](std::optional<Player*> a_playerOption)
    {
        if (a_playerOption.has_value())
        {
            Player& rival = *a_playerOption.value();
            rival.AddToLifePoints(-m_subPoints);
		    std::string msg = "You were attacked by " + a_player.GetName() + "\nyou have left: " + 
			    std::to_string(rival.GetLifePoints()) + " points\n"; 
		    rival.GetWriter()->operator<<(msg);
		    a_player.GetWriter()->operator<<("You attacked " + rival.GetName() + " Successfully\n");
		    return;
        }
        else
        {
                a_player.GetWriter()->operator<<("No opponents found in the room\n");
        }
    });
}


} //experis
