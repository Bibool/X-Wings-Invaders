#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

#include "Config.h"
#include "GameSprite.h"
#include "Helpers.h"
#include "UIManager.h"

UIManager::UIManager()
	: m_pScreenBoundary	(nullptr)
	, m_pFont			(nullptr)
	, m_pTextArray		(nullptr)
	, m_pUIBar			(nullptr)
	, m_score	(0)
	, m_wave	(1)
	, m_lives	(10)
{
	// Load the screen res
	m_pScreenBoundary = new Config();
	
	// Set the font used by the UI Text
	m_pFont = new sf::Font();
	m_pFont->loadFromFile("Assets/Fonts/8bitFont.ttf");

	// Load up the array with sf::Texts
	m_pTextArray = new sf::Text[m_k_NumberOfTexts];

	// Initialize style settings shared by all elements
	initializeStyle();
	
	// Score Text
	m_pTextArray[0].setFont(*m_pFont);
	m_pTextArray[0].setString(" Score ");
	m_pTextArray[0].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[0].setPosition(
		static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.09f,
		static_cast<float>( m_pScreenBoundary->getHeight() ) * 0.03f);

	// Score Number
	std::ostringstream scoreToString;
	scoreToString << m_score;
	m_pTextArray[1].setFont(*m_pFont);
	m_pTextArray[1].setString(scoreToString.str());
	m_pTextArray[1].setOutlineColor(sf::Color::White);
	m_pTextArray[1].setPosition(
		static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.3f,
		static_cast<float>( m_pScreenBoundary->getHeight() ) * 0.03f);
	
	// Life Text
	m_pTextArray[2].setFont(*m_pFont);
	m_pTextArray[2].setString(" Lives ");
	m_pTextArray[2].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[2].setPosition(
		static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.09f,
		static_cast<float>( m_pScreenBoundary->getHeight() ) * 0.9f);
	
	// Life Number
	std::ostringstream livesToString;
	livesToString << m_lives;
	m_pTextArray[3].setFont(*m_pFont);
	m_pTextArray[3].setString(livesToString.str());
	m_pTextArray[3].setOutlineColor(sf::Color::White);
	m_pTextArray[3].setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.25f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.9f);
	
	// Wave Text
	m_pTextArray[4].setFont(*m_pFont);
	m_pTextArray[4].setString(" Wave ");
	m_pTextArray[4].setOutlineColor(sf::Color::Yellow);
	m_pTextArray[4].setPosition(
		static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.7f,
		static_cast<float>( m_pScreenBoundary->getHeight() ) * 0.03f);

	// Wave Number
	std::ostringstream waveToString;
	waveToString << m_wave;
	m_pTextArray[5].setFont(*m_pFont);
	m_pTextArray[5].setString(waveToString.str());
	m_pTextArray[5].setOutlineColor(sf::Color::White);
	m_pTextArray[5].setPosition(
		static_cast<float>( m_pScreenBoundary->getWidth() ) * 0.9f,
		static_cast<float>( m_pScreenBoundary->getHeight() ) * 0.03f);
	
	// Create the UI Bar that resides at the top of the screen to mask unwanted effects
	m_pUIBar = new GameSprite("Assets/Textures/UIBar.png");
	m_pUIBar->setOrigin(
		m_pUIBar->getGlobalBounds().width * 0.5f,
		m_pUIBar->getGlobalBounds().height * 0.5f);
	m_pUIBar->setScale(1.0f, 0.2f);
	m_pUIBar->setPosition(
		static_cast<float>(m_pScreenBoundary->getWidth()) * 0.5f,
		static_cast<float>(m_pScreenBoundary->getHeight()) * 0.07f);

	CONSOLE_OUT "UI Manager constructor ran. \n";
}


void UIManager::initializeStyle() const
{
	for (int i = 0; i < m_k_NumberOfTexts; i++)
	{
		m_pTextArray[i].setFont(*m_pFont);
		m_pTextArray[i].setOutlineThickness(1);
		m_pTextArray[i].setFillColor(sf::Color::Black);
		m_pTextArray[i].setCharacterSize(20);
		m_pTextArray[i].setOrigin(m_pTextArray[i].getGlobalBounds().width * 0.5f,	m_pTextArray[i].getGlobalBounds().height * 0.5f);
	}
}


void UIManager::updateScoreNumber() const
{
	std::ostringstream scoreToString;
	scoreToString << m_score;
	m_pTextArray[1].setString(scoreToString.str());
}

void UIManager::updateWaveNumber() const
{
	std::ostringstream waveToString;
	waveToString << m_wave;
	m_pTextArray[5].setString(waveToString.str());
}

void UIManager::updateLifeNumber() const
{
	std::ostringstream livesToString;
	livesToString << m_lives;
	m_pTextArray[3].setString(livesToString.str());
}

void UIManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_pUIBar);
	for (int i = 0; i < m_k_NumberOfTexts; i++)
	{
		target.draw(m_pTextArray[i]);
	}
}

void UIManager::addScoreUI()
{
	m_score += m_kScoreIncrease;
}

void UIManager::addWaveUI()
{
	m_wave += 1;
}

void UIManager::minusLife()
{
	m_lives -= 1;
}

bool UIManager::checkLifeLeft() const
{
	return getLives() == 0;
}


UIManager::~UIManager()
{
	safeDelete(m_pScreenBoundary);
	safeDelete(m_pFont);
	safeDelete(m_pUIBar);
	safeDeleteArray(m_pTextArray);
}

