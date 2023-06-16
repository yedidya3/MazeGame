#pragma once
#include "CreatorPlayer_Base.h"
#include "DbNames_mt.h"
#include "ContentsRooms.h"
namespace experis
{

class CreatorPlayersUniqueNames : public CreatorPlayer_Base
{
public:
	explicit CreatorPlayersUniqueNames(DbNames_mt& a_dbNames, ContentsRooms& a_secretariat);
	CreatorPlayersUniqueNames (const CreatorPlayersUniqueNames& a_other) = delete;
	CreatorPlayersUniqueNames& operator=(const CreatorPlayersUniqueNames& a_other) = delete;
	virtual ~CreatorPlayersUniqueNames() override = default;

	virtual std::unique_ptr<Player> CreatePlayer(std::unique_ptr<Writer> a_writer, Reader& a_reader) override;
	virtual void DestroyPlayer(std::unique_ptr<Player> a_player) override;


private:
	DbNames_mt& m_dbNames;
	ContentsRooms& m_secretariat;
};


} //experis