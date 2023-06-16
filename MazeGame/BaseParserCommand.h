#pragma once
#include <functional>
#include <string>
#include <optional>
#include "Player.h"
namespace experis
{

class BaseParser
{
public:
	using Action = std::function<void(Player&)>;
	BaseParser() = default;
	BaseParser(const BaseParser& a_other) = delete;
	BaseParser& operator=(const BaseParser& a_other) = delete;
	virtual ~BaseParser() = default;
	
	//virtual std::optional<Action> Parse(const std::string& a_untrusted_text) = 0;
	virtual std::optional<std::string> Parse(const std::string& a_untrusted_text) const = 0;
};

} //experis
