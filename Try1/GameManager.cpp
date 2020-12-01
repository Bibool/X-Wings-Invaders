#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "Bullet.h"
#include "Config.h"
#include "CollisionManager.h"
#include "EnemyBullet.h"
#include "EnemyManager.h"
#include "FrontEndInput.h"
#include "GameIcon.h"
#include "GameManager.h"
#include "GameSound.h"
#include "GameStates.h"
#include "Helpers.h"
#include "MusicManager.h"
#include "PlayerController.h"
#include "RandomGenerator.h"
#include "SparkExplosion.h"
#include "StarManager.h"
#include "TextManager.h"
#include "UIManager.h"

GameManager::GameManager()
	: m_gameActive			(false)
	, m_pMainWindow			(nullptr)
	, m_pPlayerSprite		(nullptr)
	, m_pBullet				(nullptr)
	, m_pEnemyBullet		(nullptr)
	, m_pEnemyManager		(nullptr)
	, m_pConfigRes			(nullptr)
	, m_pMenuInput			(nullptr)
	, m_pGameStates			(nullptr)
	, m_pMusicManager		(nullptr)
	, m_pTextManager		(nullptr)
	, m_pUIManager			(nullptr)
	, m_pCollisionManager   (nullptr)
	, m_pSparkExplosion	    (nullptr)
	, m_pStarManager	    (nullptr)
{
	Random::initialiseSeed();
	// Initialize the screen resolution from Config
	m_pConfigRes	  = new Config();
	m_pMainWindow	  = new sf::RenderWindow(sf::VideoMode(m_pConfigRes->getWidth(), m_pConfigRes->getHeight()), "X-Wings Invader"); //sf::Style::Fullscreen);
	m_pMainWindow	  ->setIcon(game_icon.width, game_icon.height, game_icon.pixel_data);
	
	m_pPlayerSprite   = new PlayerController();
	m_pBullet		  = new Bullet(m_pPlayerSprite->getPosition().x, m_pPlayerSprite->getPosition().y);
	m_pEnemyManager   = new EnemyManager();
	m_pEnemyBullet    = new EnemyBullet();
	m_pMenuInput	  = new FrontEndInput();
	m_pGameStates     = new GameStates();
	m_pMusicManager   = new MusicManager();
	m_pTextManager    = new TextManager();
	m_pUIManager	  = new UIManager();
	m_pStarManager	  = new StarManager();
	m_pSparkExplosion = new SparkExplosion();

	CONSOLE_OUT "Game Manager constructor ran. \n";
}

////////////////////////////////////////////////////////////////////////
///// Draws the game here, depending on the current Game state	  //////
///// It will draw in order the things required from that state   //////
///// Menu::	    Will draw only the menu						  //////
///// Paused::      Will draw only the Pause menu				  //////
///// Playing::     Will draw the playable game					  //////
///// GameOver::    Will draw Game Over screen                    //////
///// Intermission: Will draw the intermission screen			  //////
////////////////////////////////////////////////////////////////////////
void GameManager::draw() const
{
	switch( m_pGameStates->m_eStates )
	{
	case GameStates::States::Menu:
	{
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[0]);
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[1]);
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[2]);
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[3]);
	}
		break;
		
	case GameStates::States::Paused:
	{
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[4]);
	}
		break;

	case GameStates::States::Playing:
	{
		m_pMainWindow->draw(*m_pStarManager);
		m_pMainWindow->draw(*m_pBullet);
		m_pMainWindow->draw(*m_pEnemyBullet);
		m_pMainWindow->draw(*m_pPlayerSprite);
		m_pMainWindow->draw(*m_pEnemyManager);
		m_pMainWindow->draw(*m_pSparkExplosion);
		m_pMainWindow->draw(*m_pUIManager);
	}
		break;

	case GameStates::States::GameOver:
	{
		m_pMainWindow->draw(*m_pStarManager);
		m_pMainWindow->draw(*m_pEnemyManager);
		m_pMainWindow->draw(*m_pSparkExplosion);
		m_pMainWindow->draw(*m_pUIManager);
		m_pMainWindow->draw(*m_pTextManager->m_pBackgroundFade);
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[5]);
	}
		break;

	case GameStates::States::Intermission:
	{
		m_pMainWindow->draw(*m_pStarManager);
		m_pMainWindow->draw(*m_pSparkExplosion);
		m_pMainWindow->draw(*m_pUIManager);
		m_pMainWindow->draw(*m_pTextManager->m_pBackgroundFade);
		m_pMainWindow->draw(m_pTextManager->m_pTextArray[6]);
	}
		break;
		
	default:
		break;
	}
}

// The loop of the game
void GameManager::run()
{
	sf::Clock clock;
	while( m_pMainWindow->isOpen() )
	{
		float deltaTime = clock.restart().asSeconds();
		
		// Game Logic
		update(deltaTime);

		// Clear screen
		m_pMainWindow->clear();

		// Draws things
		draw();

		// Switch buffers
		m_pMainWindow->display();
	}
}

void GameManager::eventCheck()
{
	ASSERT_CHECK(m_pMainWindow);

	sf::Event event;

	while (m_pMainWindow->pollEvent(event))
	{
		switch (event.type) // creates a switch case on events
		{
			// close the window/app when here
		case sf::Event::Closed:
			m_pMainWindow->close();
			break;

		default:
			break;
		}
	}

	
	// TODO: Incorporate this into a proper state machine with exit states
	// Input feeds in into the game state
	// Ideally only called on key input rather that in update.
	m_pMenuInput->getInput();

	// Enter
	if (m_pMenuInput->getKeyEnterPressed() == true )
	{
		m_pGameStates->m_eStates = GameStates::States::Playing;
		m_pMusicManager->m_pSoundHolder[0]->pause();
		if (m_gameActive == false )
		{
			m_pMusicManager->m_pSoundHolder[1]->play();
			m_gameActive = true;
		}
		
		if (m_pMusicManager->m_pSoundHolder[1]->getStatus() == m_pMusicManager->m_pSoundHolder[1]->Paused)
		{
			m_pMusicManager->m_pSoundHolder[1]->play();
		}
	}

	// Escape
	if(m_pMenuInput->getKeyEscapePressed() == true )
	{
		m_pMainWindow->close();
	}

	// Tab
	if( m_pMenuInput->getKeyTabPressed() == true )
	{
		m_pMusicManager->m_pSoundHolder[1]->pause();
		m_pGameStates->m_eStates = GameStates::States::Paused;
	}

	// V
	if( m_pMenuInput->getKeyVPressed() == true )
	{
		if (m_pGameStates->m_eStates == GameStates::States::Menu)
		{
			m_pEnemyManager->waveMode = EnemyManager::WaveMode::OldSkoolMode;

			if (m_pMusicManager->getIsPlayingSound() == false)
			{
				m_pMusicManager->m_pSoundHolder[8]->play();
				m_pMusicManager->setIsPlayingSound(true);
			}
		}
	}

	// Checks if it's game over
	if (m_pUIManager->checkLifeLeft() || m_pEnemyManager->isWavePastScreen())
	{
		m_pMusicManager->m_pSoundHolder[1]->pause();
		static bool playOnce = true;
		if (playOnce) 
		{
			m_pMusicManager->m_pSoundHolder[11]->play();
			playOnce = false;
		}
		m_pGameStates->m_eStates = GameStates::States::GameOver;
	}

	// Checks if its a wave intermission
	if (m_pEnemyManager->getIsIntermission())
	{
		static bool doOnce = true;
		if (doOnce)
		{
			m_clock.restart();
			doOnce = false;
		}
		m_pGameStates->m_eStates = GameStates::States::Intermission;

		if (m_clock.getElapsedTime().asSeconds() >= m_kIntermissionTimer)
		{
			m_pTextManager->resetIntermissionEffect();
			m_pEnemyManager->setIsIntermission(false);
			m_pGameStates->m_eStates = GameStates::States::Playing;
			doOnce = true;
		}
	}
}

// Game Update
// Feed deltaTime into other updates
void GameManager::update(float deltaTime)
{
	eventCheck();

	// Optimization checks to update only during states
	// Check if game is paused so player cannot move
	switch ( m_pGameStates->m_eStates )
	{
		case GameStates::States::Playing:
		{
			m_pStarManager		->update(deltaTime);
			m_pBullet			->update(deltaTime, *m_pPlayerSprite, *m_pMusicManager);
			m_pEnemyBullet		->update(deltaTime, *m_pMusicManager, *m_pEnemyManager);
			m_pCollisionManager ->update(*m_pBullet, *m_pMusicManager, *m_pEnemyManager, *m_pUIManager, *m_pSparkExplosion, *m_pEnemyBullet, *m_pPlayerSprite);
			m_pSparkExplosion	->update(deltaTime);
			m_pPlayerSprite		->update(deltaTime);
			m_pEnemyManager		->update(deltaTime, *m_pUIManager, *m_pEnemyBullet, *m_pMusicManager);
		}
			break;

		case GameStates::States::Paused:
		{
				
		}
			break;
		
		case GameStates::States::Menu:
		{
				
		}
			break;

		case GameStates::States::GameOver:
		{
			m_pStarManager		->update(deltaTime);
			m_pEnemyManager		->update(deltaTime, *m_pUIManager, *m_pEnemyBullet, *m_pMusicManager);
			m_pTextManager		->update();
		}
			break;

		case GameStates::States::Intermission:
		{
			m_pSparkExplosion	->update(deltaTime);
			m_pTextManager		->intermissionEffect();
		}
			break;
		
		default:
			break;
	}
}

GameManager::~GameManager()
{
	// Deletes pointers
	safeDelete(m_pConfigRes);
	safeDelete(m_pPlayerSprite);
	safeDelete(m_pMainWindow);
	safeDelete(m_pTextManager);
	safeDelete(m_pGameStates);
	safeDelete(m_pMenuInput);
	safeDelete(m_pMusicManager);
	safeDelete(m_pBullet);
	safeDelete(m_pUIManager);
	safeDelete(m_pEnemyBullet);
	safeDelete(m_pEnemyManager);
	safeDelete(m_pCollisionManager);
	safeDelete(m_pSparkExplosion);
	safeDelete(m_pStarManager);
}