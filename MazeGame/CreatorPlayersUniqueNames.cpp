#include "CreatorPlayersUniqueNames.h"
namespace experis
{

CreatorPlayersUniqueNames::CreatorPlayersUniqueNames(DbNames_mt& a_dbNames, ContentsRooms& a_secretariat)
	:m_dbNames{a_dbNames}
	,m_secretariat{a_secretariat}
{
}

std::unique_ptr<Player> CreatorPlayersUniqueNames::CreatePlayer(std::unique_ptr<Writer> a_writer, Reader& a_reader)
{
	(*a_writer) << "Please enter a name: \n";
	std::string untrusted_name = a_reader.ReadLine();
	while (m_dbNames.Add(untrusted_name) == false)
	{
		(*a_writer) << "The name already exists in the system, please enter a new name: \n";
		untrusted_name = a_reader.ReadLine();
	}
	std::unique_ptr<Player> player = std::make_unique<Player>(untrusted_name, Facing{Directions::NORTH}, 0, std::move(a_writer));
	m_secretariat.Get(player->GetNumRoom()).Registration(*player);
	return player;
}


void CreatorPlayersUniqueNames::DestroyPlayer(std::unique_ptr<Player> a_player)
{
	m_secretariat.Get(a_player->GetNumRoom()).RemovePlayer(*a_player);
	m_dbNames.Delete(a_player->GetName());
}



} //experis