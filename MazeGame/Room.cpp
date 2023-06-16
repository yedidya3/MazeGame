#include "StructureRoom.h"
namespace experis
{

std::unordered_map<Directions ,StructureRoom::NumRoomOption> CreateMapDirection2Idx(const StructureRoom::NumRoomOption& a_north
	,const StructureRoom::NumRoomOption& a_east, const StructureRoom::NumRoomOption& a_south, const StructureRoom::NumRoomOption& a_west)
{
	std::unordered_map<Directions ,StructureRoom::NumRoomOption> mapDirections2Rooms
	{
		{Directions::NORTH , a_north}
		,{Directions::EAST , a_east}
		,{Directions::SOUTH , a_south}
		,{Directions::WEST , a_west}
	
	};
	return mapDirections2Rooms;
}

StructureRoom::StructureRoom(const NumRoomOption& a_north, const NumRoomOption& a_east, const NumRoomOption& a_south, const NumRoomOption& a_west)
	:m_direction2RoomNext{CreateMapDirection2Idx(a_north, a_east, a_south, a_west)}
{
}

StructureRoom::StructureRoom(const StructureRoom& a_other)
	:m_direction2RoomNext{a_other.m_direction2RoomNext}
{
}

StructureRoom::NumRoomOption StructureRoom::GetIdxRoomNext(const Directions& a_direction) const
{
	return m_direction2RoomNext.at(a_direction);
}

}