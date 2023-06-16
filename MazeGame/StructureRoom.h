#pragma once
#include <utility>
#include <optional>
#include <unordered_map>
#include "Facing.h"
namespace experis
{

class StructureRoom
{
public:
	using NumRoomOption = std::optional<size_t>;
	
	explicit StructureRoom(const NumRoomOption& a_north, const NumRoomOption& a_east, const NumRoomOption& a_south, const NumRoomOption& a_west);
	StructureRoom(const StructureRoom& a_other);
	StructureRoom& operator=(const StructureRoom& a_other) = delete;
	~StructureRoom() = default;

	
	NumRoomOption GetIdxRoomNext(const Directions& a_direction) const;

private:
	std::unordered_map<Directions ,NumRoomOption> m_direction2RoomNext;

};

} //experis
