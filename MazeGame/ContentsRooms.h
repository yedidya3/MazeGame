#pragma once
#include "ContentRoom.h"
#include "SettingRooms.h"
namespace experis
{

class ContentsRooms
{
public:
	ContentsRooms(const std::vector<StateRoom>& a_roomsNumbers);
	ContentsRooms(const ContentsRooms& a_other) = delete;
	ContentsRooms& operator=(const ContentsRooms& a_other) = delete;
	~ContentsRooms() = default;

	ContentRoom_mt& Get(const size_t a_numRoom);
	const ContentRoom_mt& Get(const size_t a_numRoom) const;
	bool IsExsit(const size_t a_numRoom) const;

private:
	std::unordered_map<size_t ,ContentRoom_mt> m_rooms;
};

void MsgToRoom(ContentsRooms& a_contentsRooms, size_t a_numRoom, const std::string& a_msg);
void MsgEnter(ContentsRooms& a_contentsRooms, size_t a_numRoom, std::string a_namePlayer);

}