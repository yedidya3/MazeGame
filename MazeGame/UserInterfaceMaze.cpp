#include "UserInterfaceMaze.h"
#include <string>
#include <iostream>
#include <cassert>
namespace experis
{

UserInterfaceMaze::UserInterfaceMaze(std::shared_ptr<InputModeState> a_state, CommandsMap& a_commandsMang)
	:m_state{a_state}
	,m_commandsMang{a_commandsMang}
{
}


void UserInterfaceMaze::Run(Player& a_player, std::unique_ptr<Reader> a_reader)
{
	Player& player = a_player;
	
	assert(m_commandsMang.IsExists("start"));
	m_commandsMang.Get("start")(a_player);
	//assert(m_parserToCommand.Parse("directory").has_value());
	//m_parserToCommand.Parse("directory").value()(player);

	std::shared_ptr<InputModeState> state = m_state;
	while (IsLife(a_player))
	{
		player.GetWriter()->operator<<(">");
		std::string untrust_input = a_reader->ReadLine();
		if (!IsLife(a_player))
		{
			player.GetWriter()->operator<<("You lost the game\nBye Bye...\n");
			return;
		}
		state = state->Next(a_player, untrust_input);
	}
}

} //experis