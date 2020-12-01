#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <SFML/System/Vector2.hpp>
#include "GameSprite.h"

class Config;
class Enemy;
class EnemyManager;
class MusicManager;

class EnemyBullet : public GameSprite
{
	float const m_kVelocity   = 350.0f;
	float const m_kPadding	  = 10.0f;
	bool		m_isActive : 1;

	Config*	    m_pScreenBoundary;

	// Initialize values shared by constructors
	void initialize();

	// Overloaded function for positioning
	void resetPosition(float posX, float posY);
	void resetPosition(sf::Vector2f vector2);
	void resetPosition(Enemy &enemy);

	// The bullet logic
	void bulletLogic(float deltaTime);

public:
	EnemyBullet();
	EnemyBullet(float posX, float posY);
	~EnemyBullet();

	void fireCheck(EnemyManager &enemyManager);
	void playSound(MusicManager &musicManager) const;

	// Hides bullet offscreen till used again
	void hideBullet();

	void update(float deltaTime);
	void update(float deltaTime, MusicManager &musicManager, EnemyManager &enemyManager);
	

	// Getters & Setters
	bool getIsActive() const { return m_isActive; };
	void setIsActive(bool isActive) { m_isActive = isActive; };	
};

#endif