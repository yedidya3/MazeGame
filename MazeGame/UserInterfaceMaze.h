#pragma once
#include <iostream>
#include <unordered_map>
#include "CommandsMap.h"
#include "Reader.h"
#include "Writer.h"
#include "BaseParserCommand.h"
#include "Player.h"
#include "IoModeState.h"
namespace experis
{

class UserInterfaceMaze
{
public:
	explicit UserInterfaceMaze(std::shared_ptr<InputModeState> a_state, CommandsMap& a_commandsMang);

	//explicit UserInterfaceMaze(BaseParserCommand& a_parserToCommand, CommandsMap& a_commandsMang );
	UserInterfaceMaze(const UserInterfaceMaze& a_other) = delete;
	UserInterfaceMaze& operator=(const UserInterfaceMaze& a_other) = delete;
	~UserInterfaceMaze() = default;

	void Run(Player& a_player, std::unique_ptr<Reader> a_reader);

private:
	std::shared_ptr<InputModeState> m_state;
	CommandsMap& m_commandsMang;
};

} //experis
