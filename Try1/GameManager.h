#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/System/Clock.hpp>
#include "IUpdatable.h"

namespace sf
{
	class RenderWindow;
}

class BackEndInput;
class Bullet;
class Config;
class CollisionManager;
class Enemy;
class EnemyBullet;
class EnemyManager;
class FrontEndInput;
class GameStates;
class GameText;
class MusicManager;
class PlayerController;
class SparkExplosion;
class StarManager;
class TextManager;
class UIManager;

const float m_kIntermissionTimer = 3.0f;

class GameManager : public IUpdatable
{
private:
	bool m_gameActive : 1;
	sf::RenderWindow*	m_pMainWindow;
	// Game Objects
	PlayerController*	m_pPlayerSprite;
	Bullet*				m_pBullet;
	EnemyBullet*		m_pEnemyBullet;
	EnemyManager*		m_pEnemyManager;
	// Systems
	Config*				m_pConfigRes;
	FrontEndInput*		m_pMenuInput;
	GameStates*			m_pGameStates;
	MusicManager*		m_pMusicManager;
	TextManager*		m_pTextManager;
	UIManager*			m_pUIManager;
	CollisionManager*	m_pCollisionManager;
	SparkExplosion*		m_pSparkExplosion;
	StarManager*		m_pStarManager;

	sf::Clock m_clock;
	
	virtual void update(float deltaTime) override;
	void draw()			const;
	void eventCheck();
	
public:
	GameManager();
	~GameManager();
	
	void run();
};
#endif
