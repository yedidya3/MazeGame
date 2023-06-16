#include "Facing.h"

namespace experis
{

Facing::Facing(const Directions& a_directory, unsigned char a_amountDirections)
	:m_directory{a_directory}
	,m_amountDirections{a_amountDirections}
{
}

Facing::Facing(const Facing& a_other)
	:m_directory{a_other.m_directory}
	,m_amountDirections{a_other.m_amountDirections}
{
}

Facing& Facing::operator=(const Facing& a_other)
{
	m_directory = a_other.m_directory;
	m_amountDirections = a_other.m_amountDirections;
	return *this;
}

void Facing::Right()
{
	m_directory = static_cast<Directions>((static_cast<int>(m_directory) + 1) % static_cast<int>(Directions::SUM));
}

void Facing::Left()
{
	m_directory = static_cast<Directions>(static_cast<int>(m_directory) == 0 ? (static_cast<int>(Directions::SUM) - 1) : (static_cast<int>(m_directory) - 1));
}

const Directions& Facing::GetDirection() const
{
	return m_directory;
}

} //experis