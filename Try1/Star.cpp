#include "Config.h"
#include "Helpers.h"
#include "RandomGenerator.h"
#include "Star.h"


Star::Star()
	: m_pConfig(nullptr)
{
	m_pConfig = new Config();
	m_speed = 0.0f;
	initialise();
}


Star::~Star()
{
	safeDelete(m_pConfig);
}

void Star::initialise()
{
	randomisePosition();
	randomiseSpeed();
	randomiseScale();
	//randomiseColour();
}


void Star::randomisePosition()
{
	const float randomX = Random::get(static_cast<float>(m_pConfig->getWidth()));
	const float randomY = Random::get(static_cast<float>(m_pConfig->getHeight()));
	setPosition( randomX, randomY );
}

void Star::randomiseSpeed()
{

	m_speed = Random::get(m_kMinSpeed, m_kMaxSpeed );
}

void Star::randomiseScale()
{
	const float scalar = Random::get( m_kMinScale, m_kMaxScale );
	setScale( scalar, scalar );
}

void Star::randomiseColour()
{
	sf::Color color;

	color.r = static_cast<sf::Uint8>( Random::get( m_kMinColorRange, m_kMaxColorRange ) );
	color.g = static_cast<sf::Uint8>( Random::get( m_kMinColorRange, m_kMaxColorRange ) );
	color.b = static_cast<sf::Uint8>( Random::get( m_kMinColorRange, m_kMaxColorRange ) );
	color.a = m_kMaxAlpha;
	setColor( color );
}

void Star::update( float deltaTime )
{
	sf::Vector2f pos = getPosition();

	pos.y += m_speed * deltaTime;

	if( pos.y > static_cast<float>( m_pConfig->getHeight() ) )
	{
		pos.y = m_kUIPosition;
	}

	setPosition( pos );
}

