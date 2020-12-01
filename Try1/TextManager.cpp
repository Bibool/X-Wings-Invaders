#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <SFML/System/Clock.hpp>

#include "Config.h"
#include "GameSprite.h"
#include "Helpers.h"
#include "TextManager.h"



TextManager::TextManager()
	: m_alpha			(0)
	, m_fadeAlpha		(0)
	, m_red				(255)
	, m_blue			(0)
	, m_green			(0)
	, m_pScreenBoundary (nullptr)
	, m_pFontArray		(nullptr)
	, m_pTextArray		(nullptr)
	, m_pBackgroundFade (nullptr)
{
	// Init config
	m_pScreenBoundary = new Config();

	// Loads the blank image
	m_pBackgroundFade = new GameSprite("Assets/Textures/FadeToBlack.png");
	// Sets some values
	m_pBackgroundFade->setOrigin(sf::Vector2f(m_pBackgroundFade->getTexture()->getSize().x * 0.5f, m_pBackgroundFade->getTexture()->getSize().y * 0.5f));
	m_pBackgroundFade->setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f, 
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.5f);
	m_blackFade.a = m_fadeAlpha;
	m_pBackgroundFade->setColor(m_blackFade);
	
	// Arrays
	m_pTextArray = new sf::Text[k_numberOfTexts];
	m_pFontArray = new sf::Font[k_numberOfFonts];

	// Load the only two needed fonts here to avoid repetition
	m_pFontArray[0].loadFromFile("Assets/Fonts/8bitFont.ttf");
	m_pFontArray[1].loadFromFile("Assets/Fonts/SoloChromeFont.ttf");
	m_pFontArray[2].loadFromFile("Assets/Fonts/OptimusPrinceps.ttf");
	
	// Load the Texts
	// The Big Bold Menu Star Wars Text
	m_pTextArray[0].setFont(m_pFontArray[1]);
	m_pTextArray[0].setString(" STAR \nWARS");
	m_pTextArray[0].setOutlineThickness(2);
	m_pTextArray[0].setCharacterSize(100);
	m_pTextArray[0].setFillColor(sf::Color::Black);
	m_pTextArray[0].setOutlineColor(sf::Color::White);
	m_pTextArray[0].setOrigin(
		m_pTextArray[0].getGlobalBounds().width * 0.5f,
		m_pTextArray[0].getGlobalBounds().height * 0.5f);
	m_pTextArray[0].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.3f);

	// The X-Wings Invader Title Text
	m_pTextArray[1].setFont(m_pFontArray[0]);
	m_pTextArray[1].setString("X Wings Invader");
	m_pTextArray[1].setOutlineThickness(1);
	m_pTextArray[1].setCharacterSize(15);
	m_pTextArray[1].setFillColor(sf::Color::Black);
	m_pTextArray[1].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[1].setOrigin(
		m_pTextArray[1].getGlobalBounds().width * 0.5f, 
		m_pTextArray[1].getGlobalBounds().height * 0.5f);
	m_pTextArray[1].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.5f);

	// The Prompt text to begin the game
	m_pTextArray[2].setFont(m_pFontArray[0]);
	m_pTextArray[2].setString(" Insert Coin ");
	m_pTextArray[2].setOutlineThickness(2);
	m_pTextArray[2].setCharacterSize(30);
	m_pTextArray[2].setFillColor(sf::Color::Black);
	m_pTextArray[2].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[2].setOrigin(
		m_pTextArray[2].getGlobalBounds().width * 0.5f, 
		m_pTextArray[2].getGlobalBounds().height * 0.5f);
	m_pTextArray[2].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.6f);


	// Mode select text
	m_pTextArray[3].setFont(m_pFontArray[0]);
	m_pTextArray[3].setString("                     BETA MODE\nPress V to enable Old Skool mode ");
	m_pTextArray[3].setOutlineThickness(1);
	m_pTextArray[3].setCharacterSize(20);
	m_pTextArray[3].setOutlineColor(sf::Color::White);
	m_pTextArray[3].setFillColor(sf::Color::Blue);
	m_pTextArray[3].setOrigin(
		m_pTextArray[3].getGlobalBounds().width * 0.5f, 
		m_pTextArray[3].getGlobalBounds().height * 0.5f);
	m_pTextArray[3].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.8f);
	
	// The Pause Text
	m_pTextArray[4].setFont(m_pFontArray[0]);
	m_pTextArray[4].setString("Press Enter to resume");
	m_pTextArray[4].setOutlineThickness(2);
	m_pTextArray[4].setCharacterSize(30);
	m_pTextArray[4].setFillColor(sf::Color::Black);
	m_pTextArray[4].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[4].setOrigin(
		m_pTextArray[4].getGlobalBounds().width * 0.5f,
		m_pTextArray[4].getGlobalBounds().height * 0.5f);
	m_pTextArray[4].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.5f);

	// The Game Over Text
	m_pTextArray[5].setFont(m_pFontArray[2]);
	m_pTextArray[5].setString("YOU DIED");
	m_pTextArray[5].setOutlineThickness(2);
	m_pTextArray[5].setCharacterSize(80);
	m_pTextArray[5].setFillColor(sf::Color::Red);
	m_pTextArray[5].setOutlineColor(sf::Color::Black);
	m_pTextArray[5].setOrigin(
		m_pTextArray[5].getGlobalBounds().width * 0.5f,
		m_pTextArray[5].getGlobalBounds().height * 0.5f);
	m_pTextArray[5].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.5f);

	// The Intermission Text
	m_pTextArray[6].setFont(m_pFontArray[2]);
	m_pTextArray[6].setString("Intermission");
	m_pTextArray[6].setOutlineThickness(2);
	m_pTextArray[6].setCharacterSize(80);
	m_pTextArray[6].setFillColor(sf::Color::Red);
	m_pTextArray[6].setOutlineColor(sf::Color::Black);
	m_pTextArray[6].setOrigin(
		m_pTextArray[6].getGlobalBounds().width * 0.5f,
		m_pTextArray[6].getGlobalBounds().height * 0.5f);
	m_pTextArray[6].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.5f);

	// Set color values here
	m_colorFade.a = m_alpha;
	m_colorFade.b = m_blue;
	m_colorFade.g = m_green;
	m_colorFade.r = m_red;
	m_clock.restart();
	
	CONSOLE_OUT "Text Manager constructor ran. \n";
}

void TextManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < k_numberOfTexts - 2; i++)
	{
		target.draw(m_pTextArray[i]);
	}
}

// This is the logic for the dark souls effect
// As it shares the same logic and call as the text
// I implemented the blank picture in here instead of UI manager

void TextManager::transitionEffect()
{
	// Picture
	// Increases alpha every interval if alpha hasn't reached 255
	if (m_clock.getElapsedTime().asSeconds() >= m_kImageFadeTimer && m_fadeAlpha < 255)
	{
		m_fadeAlpha++;
	}

	// Text
	// Increases alpha at a slower interval if alpha hasn't reached 255
	// Then resets the timer
	if (m_clock.getElapsedTime().asSeconds() >= m_kFadeInTimer && m_alpha < 255)
	{
		m_alpha++;
		
		m_clock.restart();
	}

	// Proceed to set the color values;
	m_blackFade.a = m_fadeAlpha;
	m_colorFade.a = m_alpha;
	m_pBackgroundFade->setColor(m_blackFade);
	m_pTextArray[5].setFillColor(m_colorFade);
}

void TextManager::intermissionEffect()
{
	// Picture
	// Increases alpha every interval if alpha hasn't reached 255
	if (m_clock.getElapsedTime().asSeconds() >= m_kImageFadeTimer && m_fadeAlpha < 255)
	{
		m_fadeAlpha++;
	}

	// Text
	// Increases alpha at a slower interval if alpha hasn't reached 255
	// Then resets the timer
	if (m_clock.getElapsedTime().asSeconds() >= m_kFadeInTimer && m_alpha < 255)
	{
		m_alpha++;

		m_clock.restart();
	}


	// Proceed to set the color values;
	m_blackFade.a = m_fadeAlpha;
	m_colorFade.a = m_alpha;
	m_pBackgroundFade->setColor(m_blackFade);
	m_pTextArray[6].setFillColor(m_colorFade);
}

void TextManager::resetIntermissionEffect()
{
	m_alpha = 0;
	m_fadeAlpha = 0;
}


void TextManager::update()
{
	transitionEffect();
}



TextManager::~TextManager()
{
	safeDelete(m_pScreenBoundary);
	safeDelete(m_pBackgroundFade); 
	safeDeleteArray(m_pFontArray);
	safeDeleteArray(m_pTextArray);
}

