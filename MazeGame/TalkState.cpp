#include "TalkState.h"
namespace experis
{

TalkState::TalkState(ContentsRooms& a_roomSecretariat, std::shared_ptr<InputModeState> a_nextState)
	:InputModeState{}
	,m_roomSecretariat{a_roomSecretariat}
	,m_nextState{a_nextState}
{
}

std::shared_ptr<InputModeState> TalkState::Next(Player& a_player, const std::string& a_input)
{
	const std::string msg = "Talk from " + a_player.GetName() + ": \"" + a_input + "\"\n";     
	m_roomSecretariat.Get(a_player.GetNumRoom()).ActionOnRoomPlayers([&](Player& a_playerAnother)
		{
			a_playerAnother.GetWriter()->operator<<(msg);
		});


	//m_roomSecretariat.MessageToRoom(a_player.GetNumRoom(), msg);
	return m_nextState;
}




} //experis