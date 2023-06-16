#include "StructureRooms.h"
#include <cassert>


namespace experis
{

std::unordered_map<size_t, std::shared_ptr<StructureRoom>> CreateRooms(const std::vector<StateRoom>& a_vect, size_t a_lengthRow)
{
	assert(a_vect.size() > 0 && a_vect.size() % a_lengthRow == 0);
	std::unordered_map<size_t, std::shared_ptr<StructureRoom>> rooms{};
	size_t amountRooms = a_vect.size();
	size_t idx = 0;
	for (StateRoom isOpen : a_vect)
	{
		if (isOpen == StateRoom::OPEN)
		{
			size_t idxNorth = (idx + amountRooms - a_lengthRow) % amountRooms;
			size_t idxEast = (idx + 1) % amountRooms;
			size_t idxSouth = (idx + a_lengthRow) % amountRooms;
			size_t idxWest = (idx - 1) % amountRooms;
			std::optional<size_t> northOption = a_vect[idxNorth] == StateRoom::OPEN ? std::optional<size_t>{idxNorth} : std::optional<size_t>{};
			rooms.insert({idx, std::make_shared<StructureRoom>(StructureRoom{
				a_vect[idxNorth] == StateRoom::OPEN ? std::optional<size_t>{idxNorth} : std::optional<size_t>{},
				a_vect[idxEast] == StateRoom::OPEN ? std::optional<size_t>{idxEast} : std::optional<size_t>{},
				a_vect[idxSouth] == StateRoom::OPEN ? std::optional<size_t>{idxSouth} : std::optional<size_t>{},
				a_vect[idxWest] == StateRoom::OPEN ? std::optional<size_t>{idxWest} : std::optional<size_t>{}
					})});
		}
		++idx;
	}
	return rooms;
}


StructureRooms::StructureRooms(const std::vector<StateRoom>& a_vect, size_t a_lengthRow)
	:m_rooms{CreateRooms(a_vect, a_lengthRow)}
{
}


StructureRooms::StructureRooms()
	:m_rooms{}
{
	m_rooms.insert({0, std::make_shared<StructureRoom>(StructureRoom{{1}, {2}, {} ,{}})});
	m_rooms.insert({1, std::make_shared<StructureRoom>(StructureRoom{{}, {}, {0} ,{2}})});
	m_rooms.insert({1, std::make_shared<StructureRoom>(StructureRoom{{}, {1}, {} ,{0}})});
	/*
	m_rooms.insert({0, std::make_shared<Room>(Room{{1}, {}, {2} ,{}})});
	m_rooms.insert({1, std::make_shared<Room>(Room{{}, {}, {0} ,{2}})});
	m_rooms.insert({2, std::make_shared<Room>(Room{{0}, {1}, {} ,{3}})});
	m_rooms.insert({3, std::make_shared<Room>(Room{{}, {2}, {} ,{}})});
	*/											//north east south west
}

std::shared_ptr<StructureRoom> StructureRooms::Get(const size_t a_idxRoom)
{
	return m_rooms.at(a_idxRoom);
}

const std::shared_ptr<StructureRoom> StructureRooms::Get(const size_t a_idxRoom) const
{
	return m_rooms.at(a_idxRoom);
}


} //experis