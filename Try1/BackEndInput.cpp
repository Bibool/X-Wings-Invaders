#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "BackEndInput.h"
#include "Helpers.h"




BackEndInput::BackEndInput()
	:	m_pKeyboard(nullptr)
{
	// Initialize the booleans to a default value of false
	m_isKeyLeftPressed = false;
	m_isKeyLeftReleased = false;
	m_isKeyRightPressed = false;
	m_isKeyRightReleased = false;
	m_isKeyFirePressed = false;
	m_isKeyFireReleased = false;
	m_pKeyboard = new sf::Keyboard();
	CONSOLE_OUT "Front End Input constructor ran. \n";
}

///////////////////////////////////////////////
// Reads the input of the player
// This is a workaround for not using a window
// event for the key release function.
// TODO: Use File stream to allow user choice?
// 
// Overview: Space/F for fire
//			 Left/A to move left
//			 Right/D to move right
///////////////////////////////////////////////
void BackEndInput::getInput()
{
	// Checks if m_pKeyBoard is healthy
	ASSERT_CHECK(m_pKeyboard);
	
	//// LEFT INPUT
	if ( m_pKeyboard->isKeyPressed(sf::Keyboard::Left) || m_pKeyboard->isKeyPressed(sf::Keyboard::A) )
	{
		m_isKeyLeftPressed = true;
		m_isKeyLeftReleased = false;
		//CONSOLE_OUT("Left has been pressed.\n");
	}
	else
	{
		m_isKeyLeftPressed = false;
		m_isKeyLeftReleased = true;
		//CONSOLE_OUT("Left has been released.\n");
	}
	///// RIGHT INPUT
	if( m_pKeyboard->isKeyPressed(sf::Keyboard::Right) || m_pKeyboard->isKeyPressed(sf::Keyboard::D) )
	{
		m_isKeyRightPressed = true;
		m_isKeyRightReleased = false;
		//CONSOLE_OUT("Right has been pressed.\n");
	}
	else
	{
		m_isKeyRightPressed = false;
		m_isKeyRightReleased = true;
		//CONSOLE_OUT( "Right has been released.\n");
	}
	///// FIRE INPUT
	if( m_pKeyboard->isKeyPressed(sf::Keyboard::Space) || m_pKeyboard->isKeyPressed(sf::Keyboard::F) )
	{
		m_isKeyFirePressed = true;
		m_isKeyFireReleased = false;
		//CONSOLE_OUT("Fire has been pressed.\n");
	}
	else
	{
		m_isKeyFirePressed = false;
		m_isKeyFireReleased = true;
		//CONSOLE_OUT( "Fire has been released.\n" );
	}
}

BackEndInput::~BackEndInput()
{
	safeDelete(m_pKeyboard);
}