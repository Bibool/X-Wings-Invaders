#ifndef BULLET_H
#define BULLET_H

#include "GameSprite.h"


class Config;
class MusicManager;
class PlayerController;

class Bullet : public GameSprite
{
private:
	// Const values that is used by the bullet
	// The velocity at which the bullet travels
	// 345 is defaulted value
	float const m_kVelocity = 545.0f;
	
	// A padding value for when setting the position
	float const m_kPadding = 10.0f;

	// And the location at which the UI lives at the top of the screen
	float const m_kUIPosition = 70.0f;

	// The booleans that is used to "reset" the bullet
	bool		m_isActive : 1;
	
	Config*	    m_pScreenBoundary;
	 
	// Initializing function called in ctors
	void initialize();

	// Plays a sound when firing
	void playSound(const PlayerController &player, MusicManager &musicManager) const;

	// Overloaded functions that takes in multiple Location types
	// 1. floats: x and y
	// 2. an sf::Vector2f
	// 3. A Player Controller
	void resetPosition(float posX, float posY);
	void resetPosition(sf::Vector2f vector2);
	void resetPosition(PlayerController &player);

	// Checks if player is firing
	void fireCheck(const PlayerController &player);

	// Main bullet logic
	void bulletLogic(float deltaTime);	
	
public:
	Bullet();

	Bullet(float posX, float posY);
	~Bullet();
	
	void update(float deltaTime, PlayerController &player, MusicManager &musicManager);
	
	// Getters & Setters
	bool getIsActive() const { return m_isActive; };
	void setIsActive(bool isActive) { m_isActive = isActive; };	
};

#endif
