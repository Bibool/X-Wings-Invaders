#include "RandomGenerator.h"
#include "Spark.h"

Spark::Spark()
	: m_yDirection	(0.0f)
	, m_xDirection	(0.0f)
	, m_xOriginalPos(0.0f)
	, m_yOriginalPos(0.0f)
	, m_isActive	(false)
{
	initialise();	
}

Spark::Spark(float x, float y)
	: m_yDirection	(0.0f)
	, m_xDirection	(0.0f)
	, m_xOriginalPos(0.0f)
	, m_yOriginalPos(0.0f)
	, m_isActive	(false)
{
	initialise();
	setPosition(x, y);
}

Spark::~Spark()
{
	
}

void Spark::initialise()
{
	restartTimer();
	randomiseScale();
	randomiseDirection();
	m_xOriginalPos = getPosition().x;
	m_yOriginalPos = getPosition().y;
}

void Spark::randomiseColour()
{
	sf::Color color;
	color.r = static_cast<sf::Uint8>( Random::get(m_kMinColor, m_kMaxColor) );
	color.g = static_cast<sf::Uint8>( Random::get(m_kMinColor, m_kMaxColor) );
	color.b = static_cast<sf::Uint8>( Random::get(m_kMinColor, m_kMaxColor) );
	color.a = static_cast<sf::Uint8>( m_kMaxColor );
	setColor(color);
}

void Spark::randomiseAlpha()
{
	sf::Color color;
	color.a = static_cast<sf::Uint8>(Random::get(m_kMinAlpha, m_kMaxAlpha));
	setColor(color);
}


void Spark::randomiseDirection()
{
	m_xDirection = Random::get( m_kMinDirection, m_kMaxDirection );
	m_yDirection = Random::get( m_kMinDirection, m_kMaxDirection );
}

void Spark::restartTimer()
{
	m_clock.restart();
}


void Spark::setPos(float x, float y)
{
	setPosition( x, y );
	m_xOriginalPos = x;
	m_yOriginalPos = y;
}

void Spark::randomiseScale()
{
	float scalarX = Random::get(m_kMinScale, m_kMaxScale);
	float scalarY = Random::get(m_kMinScale, m_kMaxScale);
	setScale(scalarX, scalarY);
}


void Spark::resetParticle()
{
	setIsActive(false);
	setPosition(m_xOriginalPos, m_yOriginalPos);
	randomiseDirection();
	randomiseScale();
	restartTimer();
}

// Stores the current position then adds to it the random speed multipliers
// Then after a second has elapsed, turns off.
void Spark::update(float deltaTime)
{
	float posX = getPosition().x;
	float posY = getPosition().y;	
	
	posX += m_xDirection * deltaTime * Random::get(m_kMinSpeed, m_kMaxSpeed);
	posY += m_yDirection * deltaTime * Random::get(m_kMinSpeed, m_kMaxSpeed);

	// Only move while object is active
	if( m_isActive == true )
	{
		setPosition(posX, posY);
	}

	// Particles fall off
	if (m_clock.getElapsedTime().asSeconds() >= m_kFallOffDuration)
	{
		move(0, m_kFallOffSpeed * deltaTime);
	}

	// Reset properties after kill switch
	if ( m_clock.getElapsedTime().asSeconds() >= m_kLifeDuration )
	{
		resetParticle();
	}
}