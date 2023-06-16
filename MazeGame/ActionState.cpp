#include "ActionState.h"

namespace experis
{

	
ActionState::ActionState(const BaseParser& a_parserToCommand, const std::unordered_map<std::string, std::shared_ptr<InputModeState>>& a_mapNextState, CommandsMap& a_commandMap)
 	:InputModeState{}
	,m_parserToCommand{a_parserToCommand}
	,m_mapStatesNext{a_mapNextState}
	,m_commandsMang{a_commandMap}
{
}

std::shared_ptr<InputModeState> ActionState::Next(Player& a_player, const std::string& a_input)
{
	
	std::optional<std::string> actionOption = m_parserToCommand.Parse(a_input);
	if (actionOption.has_value())
	{
		m_commandsMang.Get(actionOption.value())(a_player);
	}
	else
	{
		a_player.GetWriter()->operator<<("Invalid command!!\n");
		return m_mapStatesNext.at("action");
	}
	if (m_mapStatesNext.find(actionOption.value()) != m_mapStatesNext.end())
	{
			return (*m_mapStatesNext.find(actionOption.value())).second;
	}
	
	return m_mapStatesNext.at("action");
}



} //experis