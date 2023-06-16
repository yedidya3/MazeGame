#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include "Writer.h"
#include "Player.h"
namespace experis
{

class CommandsMap
{
public:

	using Action = std::function<void(Player&)>;
	using Iterator = std::unordered_map<std::string, Action>::iterator;
	using ConstIterator = std::unordered_map<std::string, Action>::const_iterator;


	explicit CommandsMap();
	CommandsMap(const CommandsMap& a_other) = delete;
	CommandsMap& operator=(const CommandsMap& a_other) = delete;
	~CommandsMap() = default;

	void Add(const std::string& a_codeCommand, Action a_commandHandler);

	Action& Get(const std::string& a_codeCommand);

	bool IsExists(const std::string& a_codeCommand) const;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	std::unordered_map<std::string, Action> m_commands;

};

} //experis
