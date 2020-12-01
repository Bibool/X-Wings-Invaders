#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include "IUpdatable.h"

// Const values
// Amount of enemy in wave
const int   m_kArraySize = 20; 

class Bullet;
class Config;
class Enemy;
class EnemyBullet;
class RandomGenerator;
class UIManager;

class EnemyManager : public sf::Drawable
{
private:	
	// Bool for bullet
	bool  m_bulletFired;
	
	// Safety check for movement
	bool  m_movementSwitch;

	// Wave intermission
	bool  m_isIntermission;

	// Enemy reached bottom of screen
	bool  m_isPastScreen;
	
	// For controlling speed of wave
	float m_speed;
	
	// For controlling arcade mode speed of wave
	float m_arcadeSpeed;
	
	// To keep track of how many enemies are alive
	int   m_waveCounter;

	// variable used to hold the random enemy
	int   m_randomEnemy;
	
	// Const values
	// Y increment values
	const float m_kDepthIncrement		    = 20000.0f;
	const float m_kDepthIncrementArcade	    = 50.0f;
	
	// X increment values
	const float m_kMovementIncrease		    = 80.0f;
	const float m_kMovementIncreaseArcade   = 50.0f;
	
	// Positioning and Collision
	const float m_kPaddingAndPosition	    = 50.0f;
	const float m_kDepthPosition	        = 100.0f;
	const float m_kGapDistance			    = 70.0f;
	const float m_kRow2Multiplier		    = 1.5f;
	const float m_kRow3Multiplier		    = 2.0f;
	const float m_kRow4Multiplier		    = 2.5f;
	
	// Enemies needed before speed boost
	const int   m_kEnemyLeftToIncreaseSpeed = 1;

	// Chance for enemy to fire
	const float m_kChanceToFire			    = 0.95f;

	// Positioning/Scale value
	const float m_kRotation					= 180.0f;
	const float m_kScalar					= 0.1f; 
	
	// Stores original position that feeds into every other enemy
	sf::Vector2f m_originalPos;

	// Config for screen bounds
	Config* m_pConfig;
	RandomGenerator* m_pRandomGenerator;

	// Timer and clock for step movement
	sf::Clock m_clock;
	sf::Clock m_intermissionClock;
	sf::Clock m_fireClock;
	sf::Time m_timer;

	// Sets the position both at beginning and wave reset
	void setPos() const;

	// Switches the direction of movement
	void switchDirection();
	void switchDirectionArcade();


	// Movement logic
	void movement(float deltaTime);
	void movementArcade();

	// Check which movement to use
	void checkMovementMode(float deltaTime);

	// Fire logic
	void fireBullet(float deltaTime, EnemyBullet &enemyBullet, MusicManager &musicManager);

	// Pause between wave
	void waveIntermission();

	// Holds the texture shared by all enemies
	sf::Texture m_texture;
	   
public:
	EnemyManager();
	~EnemyManager();
	void update(float deltaTime, UIManager& uiManager, EnemyBullet &enemyBullet, MusicManager &musicManager);
	void updateWaveAndScore(UIManager& uiManager);
	void resetEnemyStatus() const;
	void incrementWave();
	void lastAlive();


	// Resets the wave
	void respawnWave(UIManager& uiManager);

	// Overriden draw function
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Enum for movement mode
	enum class WaveMode { OldSkoolMode = 0, ModernMode } waveMode;

	// Array holding enemies
	Enemy* m_pEnemyArray;

	// Get/Set
	bool getIsFiring() const		{ return m_bulletFired; };
	void setIsFiring(bool isFiring) { m_bulletFired = isFiring; };

	bool getIsIntermission() const				{ return m_isIntermission; };
	void setIsIntermission(bool isIntermission) { m_isIntermission = isIntermission; };

	bool isWavePastScreen() const;
};

#endif