#include <iostream>
#include "GameText.h"
#include "Helpers.h"

GameText::GameText(const char* fontName)
{
	bool const loaded = m_font.loadFromFile(fontName);
	ASSERT_CHECK( loaded );
	setFont(m_font);
	
	// Initialize booleans and values
	m_alpha = 255;
	m_colorG = 255;
	m_colorB = 255;
	m_colorR = 255;
	m_multiplier = 1.0f;
	m_hasReachedAlpha0	 = false;
	m_hasReachedAlpha255 = true;
	m_hasReachedR0		 = false;
	m_hasReachedR255	 = true;
	m_hasReachedG0		 = false;
	m_hasReachedG255	 = true;
	m_hasReachedB0		 = false;
	m_hasReachedB255	 = true;	
}

void GameText::glowEffect(float deltaTime)
{
	//////////////////////////////////////////////
	// A little function that enables text to glow
	// Alpha starts at 255, goes all the way to 0
	// Flips booleans to avoid infinite loop
	// Goes all the way up to 255, ect.
	// TODO: Use a recursive function here?
	// TODO: Use frame rate compensation
	// 255 = white
	// 0 = black
	//////////////////////////////////////////////

	if (m_alpha <= 255 && m_hasReachedAlpha255 == true )
	{
		setFillColor(sf::Color(255, 255, 255, m_alpha));
		m_alpha--;
	}
	
	if (m_alpha == 0 )
	{
		m_hasReachedAlpha255 = false;
		m_hasReachedAlpha0 = true;
	}
	
	if (m_alpha >= 0 && m_hasReachedAlpha0 == true )
	{
		setFillColor(sf::Color(255, 255, 255, m_alpha));
		m_alpha++;
	}
	
	if (m_alpha == 255 )
	{
		m_hasReachedAlpha255 = true;
	    m_hasReachedAlpha0 = false;
	}
}

void GameText::glowEffect(sf::Text &text)
{
	if (m_alpha <= 255 && m_hasReachedAlpha255 == true)
	{
		text.setFillColor(sf::Color(255, 255, 255, m_alpha));
		m_alpha--;
	}

	if (m_alpha == 0)
	{
		m_hasReachedAlpha255 = false;
		m_hasReachedAlpha0 = true;
	}

	if (m_alpha >= 0 && m_hasReachedAlpha0 == true)
	{
		text.setFillColor(sf::Color(255, 255, 255, m_alpha));
		m_alpha++;
	}

	if (m_alpha == 255)
	{
		m_hasReachedAlpha255 = true;
		m_hasReachedAlpha0 = false;
	}
}

void GameText::glowRGB()
{
	if( m_colorG <= 255 && m_hasReachedG255 == true )
	{
		setFillColor(sf::Color(m_colorR, m_colorG, m_colorB, 255));
		m_colorR--;
		m_colorG--;
		m_colorB--;
	}

	if( m_colorG == 0 )
	{
		m_hasReachedG255 = false;
		m_hasReachedG0 = true;
	}

	if( m_colorG >= 0 && m_hasReachedG0 == true )
	{
		setFillColor(sf::Color(m_colorR, m_colorG, m_colorB, 255));
		m_colorR++;
		m_colorG++;
		m_colorB++;
	}

	if( m_colorG == 255 )
	{
		m_hasReachedG255 = true;
		m_hasReachedG0 = false;
	}
}

void GameText::glowRed()
{
	if( m_colorR <= 255 && m_hasReachedR255 == true )
	{
		setFillColor(sf::Color(m_colorR, 255, 255, 255));
		m_colorR--;
	}

	if( m_colorR == 0 )
	{
		m_hasReachedR255 = false;
		m_hasReachedR0 = true;
	}

	if( m_colorR >= 0 && m_hasReachedR0 == true )
	{
		setFillColor(sf::Color(m_colorR, 255, 255, 255));
		m_colorR++;
	}

	if( m_colorR == 255 )
	{
		m_hasReachedR255 = true;
		m_hasReachedR0 = false;
	}
}

void GameText::glowBlue()
{
	if( m_colorB <= 255 && m_hasReachedB255 == true )
	{
		setFillColor(sf::Color(255, 255, m_colorB, 255));
		m_colorB--;
	}

	if( m_colorB == 0 )
	{
		m_hasReachedB255 = false;
		m_hasReachedB0 = true;
	}

	if( m_colorB >= 0 && m_hasReachedB0 == true )
	{
		setFillColor(sf::Color(255, 255, m_colorB, 255));
		m_colorB++;
	}

	if( m_colorB == 255 )
	{
		m_hasReachedB255 = true;
		m_hasReachedB0 = false;
	}
}

void GameText::glowGreen()
{
	if( m_colorG <= 255 && m_hasReachedG255 == true )
	{
		setFillColor(sf::Color(255, m_colorG, 255, 255));
		m_colorG--;
	}

	if( m_colorG == 0 )
	{
		m_hasReachedG255 = false;
		m_hasReachedG0 = true;
	}

	if( m_colorG >= 0 && m_hasReachedG0 == true )
	{
		setFillColor(sf::Color(255, m_colorG, 255, 255));
		m_colorG++;
	}

	if( m_colorG == 255 )
	{
		m_hasReachedG255 = true;
		m_hasReachedG0 = false;
	}
}



