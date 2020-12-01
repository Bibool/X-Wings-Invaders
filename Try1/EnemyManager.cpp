#include "Bullet.h"
#include "Config.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "EnemyManager.h"
#include "Helpers.h"
#include "RandomGenerator.h"
#include "UIManager.h"


EnemyManager::EnemyManager()
	: m_pConfig			(nullptr)
	, m_pRandomGenerator(nullptr)
	, m_pEnemyArray		(nullptr)
{
	m_fireClock.restart();
	m_isIntermission	= false;
	m_bulletFired		= false;
	m_movementSwitch    = false;
	m_isPastScreen	    = false;
	m_randomEnemy		= 0;
	m_speed				= -150.0f;
	m_arcadeSpeed		= -30.0f;
	m_waveCounter		= 20;
	m_pConfig			= new Config();
	m_pRandomGenerator  = new RandomGenerator();

	// Load texture once
	bool const loaded = m_texture.loadFromFile("Assets/Textures/XWing.png");
	ASSERT_CHECK(loaded);

	// Enemy Array
	m_pEnemyArray = new Enemy[m_kArraySize];

	// Set texture of all enemies here
	for( int i = 0; i < m_kArraySize; i++ )
	{
		m_pEnemyArray[i].setTexture(m_texture);
		m_pEnemyArray[i].setOrigin(sf::Vector2f(m_pEnemyArray[i].getTexture()->getSize().x * 0.5f, m_pEnemyArray[i].getTexture()->getSize().y * 0.5f));
		m_pEnemyArray[i].setScale(m_kScalar, m_kScalar);
		m_pEnemyArray[i].setRotation(m_kRotation);
	}
	
	m_originalPos = m_pEnemyArray[0].getPosition();
	setPos();

	waveMode = WaveMode::ModernMode;
	CONSOLE_OUT "Enemy Manager constructor ran. \n";
}

void EnemyManager::fireBullet(float deltaTime, EnemyBullet &enemyBullet, MusicManager &musicManager)
{
	// First checks if it's not firing
	if (m_bulletFired == false)
	{
		// Will get a random chance to fire
		if (Random::get01() >= m_kChanceToFire)
		{
			// Gets a random enemy
		    m_randomEnemy = static_cast<int>(Random::get(m_kArraySize));

			// Extra check to only use an active enemy
			if (m_pEnemyArray[m_randomEnemy].getActive())
			{
				CONSOLE_OUT("Enemy "); CONSOLE_OUT(m_randomEnemy); CONSOLE_OUT(" is firing.\n");
				// Sets the position of the enemy bullet, activates it, and plays the sound
				enemyBullet.setPosition(m_pEnemyArray[m_randomEnemy].getPosition());
				enemyBullet.setIsActive(true);
				enemyBullet.playSound(musicManager);
				m_bulletFired = true;
			}
		}
	}

	// If it's no longer active and not firing, reset
	if (enemyBullet.getIsActive() == false && m_bulletFired == true)
	{
		enemyBullet.setIsActive(false);
		m_bulletFired = false;
	}
}


bool EnemyManager::isWavePastScreen() const
{
	for (int n = 0; n < m_kArraySize; n++)
	{
		if ( m_pEnemyArray[n].getPosition().y >= static_cast<float>(m_pConfig->getHeight() ) )
		{
			return true;
		}
	}
	return false;
}


// Decreases the current enemy counter
void EnemyManager::incrementWave()
{
	m_waveCounter--;
}

void EnemyManager::lastAlive()
{
	// If there is one enemy left
	if( m_waveCounter == m_kEnemyLeftToIncreaseSpeed )
	{
		// Depending on which direction it's traveling, increase the speed
		if( m_movementSwitch == false )
		{
			m_speed -= m_kMovementIncrease;
			m_arcadeSpeed -= m_kMovementIncreaseArcade;
		}
		else
		{
			m_speed += m_kMovementIncrease;
			m_arcadeSpeed -= m_kMovementIncreaseArcade;
		}
	}
}


void EnemyManager::setPos() const
{
	CONSOLE_OUT "Wave position being set. \n";

	m_pEnemyArray[0].setPosition(m_originalPos);
	m_pEnemyArray[5].setPosition(m_pEnemyArray[0].getPosition().x, m_kDepthPosition * m_kRow2Multiplier);
	m_pEnemyArray[10].setPosition(m_pEnemyArray[0].getPosition().x, m_kDepthPosition * m_kRow3Multiplier);
	m_pEnemyArray[15].setPosition(m_pEnemyArray[0].getPosition().x, m_kDepthPosition * m_kRow4Multiplier);
	
	// Original enemy in top right is [0]
	// TODO: Replace with proper nested for loop (Rows/Cols)
	// Row 1
	for( unsigned int i = 1; i < 5; i++ )
	{
		m_pEnemyArray[i].setPosition(m_pEnemyArray[i - 1].getPosition().x - m_kGapDistance, m_kDepthPosition);
	}
	// Row 2
	for( unsigned int i = 6; i < 10; i++ )
	{
		m_pEnemyArray[i].setPosition(m_pEnemyArray[i - 1].getPosition().x - m_kGapDistance, m_kDepthPosition * m_kRow2Multiplier);
	}
	// Row 3
	for( unsigned int i = 11; i < 15; i++ )
	{
		m_pEnemyArray[i].setPosition(m_pEnemyArray[i - 1].getPosition().x - m_kGapDistance, m_kDepthPosition * m_kRow3Multiplier);
	}
	// Row 4
	for( unsigned int i = 16; i < 20; i++ )
	{
		m_pEnemyArray[i].setPosition(m_pEnemyArray[i - 1].getPosition().x - m_kGapDistance, m_kDepthPosition * m_kRow4Multiplier);
	}
	CONSOLE_OUT "Wave finished being set. \n";
}

// Draws every object
void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for( int i = 0; i < m_kArraySize; i++ )
	{
		if( m_pEnemyArray[i].getActive() )
		{
			target.draw(m_pEnemyArray[i]);
		}
	}
}

// Movement logic for enemies
void EnemyManager::movement(float deltaTime)
{
	for(  int i = 0; i < m_kArraySize; i++ )
	{
		m_pEnemyArray[i].move(m_speed * deltaTime, 0.0f);
	}
	
	for(  int i = 0; i < m_kArraySize; i++ )
	{
		// Only collides with wall if they aren't dead
		if( m_pEnemyArray[i].getDead() == false )
		{
			if( m_movementSwitch == false )
			{
				// Check for collision with left wall here
				if( m_pEnemyArray[i].getPosition().x <= m_kPaddingAndPosition )
				{
					// Wave drops down then switch direction
					for( int j = 0; j < m_kArraySize; j++ )
					{
						m_pEnemyArray[j].move(0.0f, m_kDepthIncrement * deltaTime);
					}
					m_movementSwitch = true;
					switchDirection();
				}
			}

			if( m_movementSwitch == true )
			{
				if( m_pEnemyArray[i].getPosition().x >= static_cast<float>( m_pConfig->getWidth() ) - m_kPaddingAndPosition )
				{
					for( int j = 0; j < m_kArraySize; j++ )
					{
						m_pEnemyArray[j].move(0.0f, m_kDepthIncrement * deltaTime);
					}
					m_movementSwitch = false;
					switchDirection();
				}
			}
		}
	}
}

// Prototype arcade style movement
void EnemyManager::movementArcade()
{
	////////////////////////////////////////////////
	//// This is not fully functional at the time
	//// Needs work on collision and behaviour
	////////////////////////////////////////////////
	sf::Time localDeltaTime = sf::seconds(1);
	m_timer += m_clock.restart();
	while( m_timer >= localDeltaTime )
	{
		for(  int i = 0; i < m_kArraySize; i++ )
		{
			m_pEnemyArray[i].move(m_arcadeSpeed, 0.0f);
		}
		
		for(  int i = 0; i < m_kArraySize; i++ )
		{
			if( m_pEnemyArray[i].getDead() == false )
			{
				if( m_movementSwitch == false )
				{
					if( m_pEnemyArray[i].getPosition().x <= m_kPaddingAndPosition )
					{
						for(  int j = 0; j < m_kArraySize; j++ )
						{
							m_pEnemyArray[j].move(0.0f, m_kDepthIncrementArcade);
						}
						m_movementSwitch = true;
						switchDirectionArcade();
					}
				}

				if( m_movementSwitch == true )
				{
					if( m_pEnemyArray[i].getPosition().x >= static_cast<float>( m_pConfig->getWidth() ) - m_kPaddingAndPosition )
					{
						for(  int j = 0; j < m_kArraySize; j++ )
						{
							m_pEnemyArray[j].move(0.0f, m_kDepthIncrementArcade);
						}
						m_movementSwitch = false;
						switchDirectionArcade();
					}
				}
			}
		}
		m_timer -= localDeltaTime;
	}
}

// Switches movement type depending on Wave mode chosen
void EnemyManager::checkMovementMode(float deltaTime)
{
	switch ( waveMode )
	{
		case WaveMode::ModernMode:
		{
			movement(deltaTime);
		}
			break;
			
		case WaveMode::OldSkoolMode:
		{
			movementArcade();
		}
			break;
	}
}

void EnemyManager::update(float deltaTime, UIManager &uiManager, EnemyBullet &enemyBullet, MusicManager &musicManager)
{
	checkMovementMode(deltaTime);
	fireBullet(deltaTime, enemyBullet, musicManager);
}

// Resets wave counter and increments wave and score
void EnemyManager::updateWaveAndScore(UIManager& uiManager)
{
	m_waveCounter = 20;
	int score = uiManager.getScore();
	int lives = uiManager.getLives();
	uiManager.setScore(score += score);
	uiManager.setLives(lives += 1);
	uiManager.addWaveUI();
	uiManager.updateLifeNumber();
	uiManager.updateWaveNumber();
}

// Resets the flag of every enemy
void EnemyManager::resetEnemyStatus() const
{
	for( int i = 0; i < m_kArraySize; i++ )
	{
		m_pEnemyArray[i].setActive(true);
		m_pEnemyArray[i].setDead(false);
	}
}

void EnemyManager::waveIntermission()
{
	m_isIntermission = true;
}


// When wave is dead, resets position, updates UI, and reset enemy flags
void EnemyManager::respawnWave(UIManager &uiManager)
{
	if( m_waveCounter <= 0 )
	{
		CONSOLE_OUT "Wave resetting. \n";
		setPos();
		updateWaveAndScore(uiManager);
		resetEnemyStatus();
		waveIntermission();
	}
}

// Simple function to switch the direction upon hitting a wall
void EnemyManager::switchDirection()
{
	m_speed = -m_speed;
}
void EnemyManager::switchDirectionArcade()
{
	m_arcadeSpeed = -m_arcadeSpeed;
}

EnemyManager::~EnemyManager()
{
	safeDelete(m_pConfig);
	safeDelete(m_pRandomGenerator);
	safeDeleteArray(m_pEnemyArray);
}