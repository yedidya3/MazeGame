#pragma once
#include "IoModeState.h"
#include <unordered_map>
#include <memory>
#include "CommandsMap.h"
#include "BaseParserCommand.h"
namespace experis
{
	
class ActionState : public InputModeState
{
public:
	explicit ActionState(const BaseParser& a_parserToCommand, const std::unordered_map<std::string, std::shared_ptr<InputModeState>>& a_mapNextState,
		CommandsMap& a_commandMap); 
	ActionState(const ActionState& a_other) = delete;
	ActionState& operator=(const ActionState& a_other) = delete;
	virtual ~ActionState() = default;

	virtual std::shared_ptr<InputModeState> Next(Player& a_player, const std::string& a_input) override;

private:
	const BaseParser& m_parserToCommand;
	const std::unordered_map<std::string, std::shared_ptr<InputModeState>>& m_mapStatesNext;
	CommandsMap& m_commandsMang;
};


	
} //experis