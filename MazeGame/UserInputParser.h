#pragma once
#include "BaseParserCommand.h"
#include "CommandsMap.h"
namespace experis
{

class UserInputParser : public BaseParser
{
public:
	UserInputParser() = delete;
	UserInputParser(const UserInputParser& a_other) = delete;
	UserInputParser operator=(const UserInputParser& a_other) = delete;
	virtual ~UserInputParser() override = default;

	explicit UserInputParser(CommandsMap& a_commands);

	virtual std::optional<std::string> Parse(const std::string& a_untrusted_text) const override;
private:
	CommandsMap& m_commands;

};

} //experis
