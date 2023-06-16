#pragma once
#include <string>
#include "Player.h"
namespace experis
{

class InputModeState
{
public:
	explicit InputModeState() = default;
	InputModeState(const InputModeState& a_other) = delete;
	InputModeState& operator=(const InputModeState& a_other) = delete;
	virtual ~InputModeState() = default;
	virtual std::shared_ptr<InputModeState> Next(Player& a_player, const std::string& a_input) = 0;

};

} //experis
