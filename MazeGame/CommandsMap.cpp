#include "CommandsMap.h"
#include <cassert>
namespace experis
{

CommandsMap::CommandsMap()
	:m_commands{}
{
}

void CommandsMap::Add(const std::string& a_codeCommand, Action a_commandHandler)
{
	m_commands.insert(std::make_pair(a_codeCommand, a_commandHandler));
}

CommandsMap::Action& CommandsMap::Get(const std::string& a_codeCommand)
{
	assert(IsExists(a_codeCommand));
	return m_commands[a_codeCommand];
}

bool CommandsMap::IsExists(const std::string& a_codeCommand) const
{
	return m_commands.find(a_codeCommand) != m_commands.end();
}

CommandsMap::Iterator CommandsMap::begin()
{
	return m_commands.begin();
}

CommandsMap::Iterator CommandsMap::end()
{
	return m_commands.end();
}

CommandsMap::ConstIterator CommandsMap::begin() const
{
	return m_commands.begin();
}

CommandsMap::ConstIterator CommandsMap::end() const
{
	return m_commands.end();
}

} //experis