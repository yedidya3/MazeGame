#include "UserInputParser.h"

namespace experis
{

UserInputParser::UserInputParser(CommandsMap& a_commands)
	:BaseParser{}
	,m_commands{a_commands}
{
}

std::optional<std::string> UserInputParser::Parse(const std::string& a_untrusted_text) const
{
	if (m_commands.IsExists(a_untrusted_text))
	{
		return a_untrusted_text;
	}
	else
	{
		return {};
	}
}

}//experis