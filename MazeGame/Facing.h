#pragma once
#include <iomanip>

namespace experis
{

enum class Directions
{
	NORTH
	,EAST
	,SOUTH
	,WEST
	,SUM
};



class Facing
{
	
public:
	explicit Facing(const Directions& a_directory, unsigned char a_amountDirections = 4);
	Facing(const Facing& a_other);
	Facing& operator=(const Facing& a_other);
	~Facing() = default;

	bool operator==(const Facing& a_other) const = default;

	const Directions& GetDirection() const;

	void Right();
	void Left();

private:
	Directions m_directory;
	unsigned char m_amountDirections;
};

} //experis

