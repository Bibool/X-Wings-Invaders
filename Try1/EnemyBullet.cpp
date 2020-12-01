#include "EnemyBullet.h"

#include "Bullet.h"
#include "Config.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "GameSound.h"
#include "Helpers.h"
#include "MusicManager.h"

EnemyBullet::EnemyBullet()
	: GameSprite("Assets/Textures/EnemyBullet.png")
	, m_pScreenBoundary(nullptr)
{
	initialize();
}

void EnemyBullet::initialize()
{
	m_isActive = false;
	m_pScreenBoundary = new Config();
	setOrigin(sf::Vector2f(getTexture()->getSize().x * 0.5f, getTexture()->getSize().y * 0.5f));
	setScale(0.1f, 0.2f);
}

// Overloaded ctor that sets position
EnemyBullet::EnemyBullet(float posX, float posY)
	: GameSprite("Assets/Textures/EnemyBullet.png")
	, m_pScreenBoundary(nullptr)
{
	setPosition(posX, posY - m_kPadding);
	initialize();
}

// Plays fire sound when pressed
void EnemyBullet::playSound(MusicManager& musicManager) const
{
	musicManager.m_pSoundHolder[9]->play();
}

void EnemyBullet::fireCheck(EnemyManager &enemyManager)
{
	if (enemyManager.getIsFiring())
	{
		setIsActive(true);
	}
}

////////////////////////////////
// A set of overloaded function
// Used in multiple situations
// 1. Takes in player
// 2. Takes in float x, float y
// 3. Takes in an sf::Vector2f
////////////////////////////////

void EnemyBullet::resetPosition(Enemy& enemy)
{
	if( getIsActive() == false )
	{
		setPosition(enemy.getPosition());
	}
}


void EnemyBullet::resetPosition(float posX, float posY)
{
	setPosition(posX, posY);
}


void EnemyBullet::resetPosition(sf::Vector2f vector2)
{
	setPosition(vector2);
}


// Sets to active to false if past screen.
// Moves the bullet up
void EnemyBullet::bulletLogic(float deltaTime)
{
	if( getPosition().y >= static_cast<float>(m_pScreenBoundary->getHeight()) + m_kPadding )
	{
		m_isActive = false;
	}

	if( m_isActive == true )
	{
		move(0, m_kVelocity * deltaTime);
	}
}


// Congregate all functions needed by the bullet into update
// To avoid multiple functions being called in game
void EnemyBullet::update(float deltaTime, MusicManager& musicManager, EnemyManager &enemyManager)
{
	bulletLogic(deltaTime);
}

void EnemyBullet::update(float deltaTime)
{
	bulletLogic(deltaTime);
}

void EnemyBullet::hideBullet()
{
	setPosition(-10.0f, -10.0f);
}



EnemyBullet::~EnemyBullet()
{
	safeDelete(m_pScreenBoundary);
}
