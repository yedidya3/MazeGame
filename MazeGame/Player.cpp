#include "Player.h"
namespace experis
{

Player::Player(const std::string& a_name, const Facing& a_directory, size_t a_numRoom,
	std::unique_ptr<Writer> a_writer, const int a_amountPoints)
	:m_name{a_name}
	,m_facing{a_directory}
	,m_numRoom{a_numRoom}
	,m_writer{a_writer.release()}
	,m_lifePoints{a_amountPoints}
{
}

const Facing& Player::GetFacing() const
{
	return m_facing;
}
void Player::SetFacing(const Facing& a_directory)
{
	m_facing = a_directory;
}

size_t Player::GetNumRoom() const
{
	return m_numRoom;
}

void Player::SetNumRoom(const size_t a_numRoom)
{
	m_numRoom = a_numRoom;
}

Writer* Player::GetWriter()
{
	return m_writer.get();
}

const std::string& Player::GetName() const
{
	return m_name;
}

int Player::GetLifePoints() const
{
	return m_lifePoints;
}


void Player::AddToLifePoints(const int a_amountPoints )
{
	m_lifePoints += a_amountPoints;
}


bool IsLife(const Player& a_player)
{
	return a_player.GetLifePoints() > 0;
}


}