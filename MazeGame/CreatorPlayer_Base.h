#pragma once
#include <memory>
#include "Player.h"
#include "Writer.h"
#include "Reader.h"
namespace experis
{

class CreatorPlayer_Base
{
public:
	CreatorPlayer_Base() = default;
	CreatorPlayer_Base(const CreatorPlayer_Base& a_other) = delete;
	CreatorPlayer_Base& operator=(const CreatorPlayer_Base& a_other) = delete;
	virtual ~CreatorPlayer_Base() = default;

	virtual std::unique_ptr<Player> CreatePlayer(std::unique_ptr<Writer> a_writer, Reader& a_reader) = 0;
	virtual void DestroyPlayer(std::unique_ptr<Player> a_player) = 0;

};


} //experis