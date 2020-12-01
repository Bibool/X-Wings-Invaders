#include "BackEndInput.h"
#include "Config.h"
#include "Helpers.h"
#include "PlayerController.h"

PlayerController::PlayerController()
	: GameSprite	   ("Assets/Textures/Player.png") 
	, m_pPlayerInput   (nullptr)
	, m_pScreenBoundary(nullptr)
{
	health			  = 10;
	m_isFiring		  = false;
	m_isAtLeftWall    = false;
	m_isAtRightWall   = false;
	m_isDead		  = false;
	m_pPlayerInput	  = new BackEndInput();
	m_pScreenBoundary = new Config();
	
	// Set the Origin to be in the center of the player regardless of size/scale
	// Then set the scale to be more appropriate
	// TODO: Use a math equation to scale appropriate to the screen?
	// Then set it to the bottom of the screen calculated per screen resolution
	setOrigin(sf::Vector2f(getTexture()->getSize().x * m_kHookMultiplier, getTexture()->getSize().y * m_kHookMultiplier));
	setScale(m_kXScale, m_kYScale);
	setPosition(static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.5f, static_cast<float>( m_pScreenBoundary->getHeight() ) - m_kPositionPadding);

	CONSOLE_OUT "Player Controller constructor ran. \n";
}

//Stops player from going past screen edges
void PlayerController::boundaryCheck(float timeDelta)
{
	// Check Left boundary
	if ( getPosition().x <= m_kBoundaryPadding )
	{
		m_isAtLeftWall = true;
		m_isAtRightWall = false;
	}
	else
	{
		m_isAtLeftWall = false;
	}
	// Check Right boundary
	if (getPosition().x >= static_cast<float>(m_pScreenBoundary->getWidth()) - m_kBoundaryPadding )
	{
		m_isAtLeftWall = false;
		m_isAtRightWall = true;
	}
	else
	{
		m_isAtRightWall = false;
	}
}


void PlayerController::update(float timeDelta)
{
	// Safety checks before usage
	ASSERT_CHECK(m_pPlayerInput);
	ASSERT_CHECK(m_pScreenBoundary);
	
	m_pPlayerInput->getInput();
	boundaryCheck(timeDelta);
	// Movement input
	// Feeds deltaTime into speed equation for frame rate compensation
	if ( m_pPlayerInput->getKeyLeftPressed())
	{
		if( m_isAtLeftWall == false )
		{
			move(-m_kMoveSpeed * timeDelta, m_kNullSpeed);
		}
	}
	if( m_pPlayerInput->getKeyRightPressed())
	{
		if( m_isAtRightWall == false )
		{
			move(m_kMoveSpeed * timeDelta, m_kNullSpeed);
		}
	}
	// Used to read when player fires
	if (m_pPlayerInput->getKeyFirePressed())
	{
		
		m_isFiring = true;
	}
	else
	{
		m_isFiring = false;
	}
}

// Safely removes the pointers
PlayerController::~PlayerController()
{
	safeDelete(m_pPlayerInput);
	safeDelete(m_pScreenBoundary);
}