#pragma once
#include "Player.h"
#include <atomic>
#include "Group.h"

namespace experis
{

class Dragon
{
public:
	explicit Dragon(const int a_mountPoints) :m_pointsLife{a_mountPoints}{};
	Dragon(const Dragon& a_other) :m_pointsLife{a_other.m_pointsLife} {};
	Dragon& operator=(const Dragon& a_other) = delete;
	~Dragon() = default;

	size_t GetNumPointsLife() const { return m_pointsLife; }
	void AddToLifePoints(const int a_amountPoints) { m_pointsLife += a_amountPoints;};

private:
	int m_pointsLife;
};


void Draw(const Dragon& a_dragon, Group& a_group);

bool IsLife(Dragon& a_dargon);


} //experis