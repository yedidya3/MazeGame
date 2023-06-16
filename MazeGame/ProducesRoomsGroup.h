#pragma once
#include "Group.h"
#include <memory>
#include "StructureRoom.h"
#include "Facing.h"
#include "Line.h"
namespace experis
{

std::unique_ptr<Group> ProducesRoomStructureGroup(const StructureRoom& a_room, const Directions a_directory);

} //experis
