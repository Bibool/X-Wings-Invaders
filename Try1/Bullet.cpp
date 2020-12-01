#include "Bullet.h"
#include "Config.h"
#include "GameSound.h"
#include "Helpers.h"
#include "PlayerController.h"
#include "MusicManager.h"

Bullet::Bullet()
	: GameSprite("Assets/Textures/Bullet.png")
	, m_pScreenBoundary(nullptr)
{
	m_pScreenBoundary = new Config();
	initialize();
}


// Overloaded ctor that sets position
Bullet::Bullet(float posX, float posY)
	: GameSprite("Assets/Textures/Bullet.png")
{
	setPosition(posX, posY - m_kPadding);
	m_pScreenBoundary = new Config();
	initialize();
}

// Initialize origin and scale
void Bullet::initialize()
{
	m_isActive = false;
	setOrigin(sf::Vector2f(getTexture()->getSize().x * 0.5f, getTexture()->getSize().y * 0.5f));
	setScale(0.1f, 0.1f);
}


// Checks if player is firing
 void Bullet::fireCheck(const PlayerController& player)
 {
	 if( player.getIsFiring() )
	 {
		 setIsActive(true);
	 }
 }

// Plays fire sound when pressed
void Bullet::playSound(const PlayerController& player, MusicManager& musicManager) const
{
	if( player.getIsFiring() && getIsActive() == false )
	{
		musicManager.m_pSoundHolder[3]->play();
	}
}

////////////////////////////////
// A set of overloaded function
// Used in multiple situations
// 1. Takes in player
// 2. Takes in float x, float y
// 3. Takes in an sf::Vector2f
////////////////////////////////

 void Bullet::resetPosition(PlayerController& player)
 {
	 if( getIsActive() == false )
	 {
		 setPosition(player.getPosition());
	 }
 }
 

void Bullet::resetPosition(float posX, float posY)
{
	setPosition(posX, posY);
}


void Bullet::resetPosition(sf::Vector2f vector2)
{
	setPosition(vector2);
}


// Sets to active to false if past screen.
// Moves the bullet up
void Bullet::bulletLogic(float deltaTime)
{
	if( getPosition().y <= m_kUIPosition )
	{
		m_isActive = false;
	}

	if( m_isActive == true )
	{
		move(0, -m_kVelocity * deltaTime);
	}
}


// Congregate all functions needed by the bullet into update
// To avoid multiple functions being called in game
void Bullet::update(float deltaTime, PlayerController& player, MusicManager& musicManager)
{
	resetPosition(player);
	playSound(player, musicManager);
	fireCheck(player);
	bulletLogic(deltaTime);
}

Bullet::~Bullet()
{
	safeDelete(m_pScreenBoundary);
}
