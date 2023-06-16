#pragma once
#include "IoModeState.h"
#include "ActionState.h"
#include "ContentsRooms.h"
namespace experis
{
	
class TalkState : public InputModeState
{
public:
	TalkState(ContentsRooms& a_roomSecretariat, std::shared_ptr<InputModeState> a_nextState);
	TalkState(const ActionState& a_other) = delete;
	TalkState& operator=(const ActionState& a_other) = delete;
	virtual ~TalkState() = default;

	virtual std::shared_ptr<InputModeState> Next(Player& a_player, const std::string& a_input) override;

private:
	std::shared_ptr<InputModeState> m_nextState;
	ContentsRooms& m_roomSecretariat;

};
	


} //experis