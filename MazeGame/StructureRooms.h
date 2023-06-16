#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "StructureRoom.h"
#include "SettingRooms.h"
namespace experis
{

class StructureRooms
{
	
public:
	explicit StructureRooms(const std::vector<StateRoom>& a_vect, size_t a_lengthRow);
	StructureRooms(const StructureRooms& a_other) = delete;
	StructureRooms& operator=(const StructureRooms& a_other) = delete;
	~StructureRooms() = default;
	explicit StructureRooms();
	std::shared_ptr<StructureRoom> Get(const size_t a_idxRoom);
	const std::shared_ptr<StructureRoom> Get(const size_t a_idxRoom) const;

private:
	std::unordered_map<size_t, std::shared_ptr<StructureRoom>> m_rooms;

};


} //experis