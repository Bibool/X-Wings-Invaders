#include <SFML/Window/Keyboard.hpp>
#include "FrontEndInput.h"
#include "Helpers.h"

FrontEndInput::FrontEndInput()
	: m_pKeyboard(nullptr)
{
	// Initialize the booleans as well as keyboard
	m_pKeyboard = new sf::Keyboard();
	m_isEnterPressed = false;
	m_isEnterReleased = false;
	m_isEscapePressed = false;
	m_isEscapeReleased = false;
	m_isTabPressed = false;
	m_isTabReleased = false;
	m_isVPressed = false;
	CONSOLE_OUT "Front End Input constructor ran. \n";
}
///////////////////////////////////////////////
// Reads the input of the player
// This is a workaround for not using a window
// event for the key release function.
// TODO: Use File stream to allow user choice?
// 
// Overview: Enter to begin game
//			 Escape to exit game / or pause?
//			 Tab to pauseWA
///////////////////////////////////////////////
void FrontEndInput::getInput()
{
	// Check if m_pKeyboard is healthy
	ASSERT_CHECK(m_pKeyboard);
	// Enter input 
	if( m_pKeyboard->isKeyPressed(sf::Keyboard::Enter) )
	{
		m_isEnterPressed = true;
		m_isEnterReleased = false;
	}
	else
	{
		m_isEnterPressed = false;
		m_isEnterReleased = true;
	}

	// Escape input
	if( m_pKeyboard->isKeyPressed(sf::Keyboard::Escape) )
	{
		m_isEscapePressed = true;
		m_isEscapeReleased = false;
	}
	else
	{
		m_isEscapePressed = false;
		m_isEscapeReleased = true;
	}

	// Tab input
	if( m_pKeyboard->isKeyPressed(sf::Keyboard::Tab) )
	{
		m_isTabPressed = true;
		m_isTabReleased = false;
	}
	else
	{
		m_isTabPressed = false;
		m_isTabReleased = true;
	}
	// V input
	if (m_pKeyboard->isKeyPressed(sf::Keyboard::V) )
	{
		m_isVPressed = true;
	}
	else
	{
		m_isVPressed = false;
	}
}

FrontEndInput::~FrontEndInput()
{
	safeDelete(m_pKeyboard);
}