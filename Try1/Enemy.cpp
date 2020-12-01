#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Enemy.h"
#include "Helpers.h"

Enemy::Enemy()
	: m_pScreenRes(nullptr)
{
	m_pScreenRes = new Config();
	initialize();

	// Sets the position to the top right corner of the screen
	setPosition(static_cast<float>(m_pScreenRes->getWidth()) - m_kPaddingAndPosition, m_kPaddingAndPosition);
}


// Overloaded ctor that specifies position
Enemy::Enemy(float posX, float posY)
	: m_pScreenRes(nullptr)
{
	m_pScreenRes = new Config();
	initialize();

	// Sets the position to where wanted
	setPosition(posX, posY);
}

Enemy::~Enemy()
{
	safeDelete(m_pScreenRes);
}

// Initialize the values used in both ctors
void Enemy::initialize()
{
	m_isActive = true;
	m_isDead = false;
}

// To be removed as setActive(false) is essentially the same
void Enemy::die()
{
	m_isActive = false;
}