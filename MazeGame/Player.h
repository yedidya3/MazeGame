#pragma once
#include "Facing.h"
#include "StructureRoom.h"
#include "Reader.h"
#include "Writer.h"
#include <atomic>
namespace experis
{

static constexpr int DEFAULT_POINTS = 100;
class Player
{
public:
	Player() = delete;
	Player(const Player& a_other) = delete;
	Player& operator=(const Player& a_other) = delete;
	~Player() = default;

	explicit Player(const std::string& a_name, const Facing& a_directory,  size_t a_numRoom, std::unique_ptr<Writer> a_writer
		, const int a_amountPoints = DEFAULT_POINTS);


	const std::string& GetName() const;
	const Facing& GetFacing() const;
	void SetFacing(const Facing& a_directory);
	size_t GetNumRoom() const;
	void SetNumRoom(const size_t a_numRoom);

	Writer* GetWriter();

	int GetLifePoints() const;
	void AddToLifePoints(const int a_amountPoints);

private:
	std::string m_name;
	Facing m_facing;
	size_t m_numRoom;
	std::unique_ptr<Writer> m_writer;
	std::atomic<int> m_lifePoints;   
};

bool IsLife(const Player& a_player);



} //experis
