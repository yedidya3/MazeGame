#pragma once
#include "IoModeState.h"
#include "ActionState.h"
#include "StructureRooms.h"
#include "ContentsRooms.h"
namespace experis
{
	

class ShoutState : public InputModeState
{
public:
	explicit ShoutState(ContentsRooms& a_roomSecretariat, std::shared_ptr<InputModeState> a_nextState, StructureRooms& a_rooms);
	ShoutState(const ShoutState& a_other) = delete;
	ShoutState& operator=(const ShoutState& a_other) = delete;
	virtual ~ShoutState() = default;

	virtual std::shared_ptr<InputModeState> Next(Player& a_player, const std::string& a_input) override;


private:
	std::shared_ptr<InputModeState> m_nextState;
	ContentsRooms& m_roomSecretariat;
	StructureRooms& m_rooms; 

};

	

} //experis