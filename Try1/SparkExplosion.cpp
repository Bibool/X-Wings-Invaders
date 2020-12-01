#include "Helpers.h"
#include "Spark.h"
#include "SparkExplosion.h"

SparkExplosion::SparkExplosion()
	: m_pSpark(nullptr)
{
	m_pSpark = new Spark[k_numberOfSparks];
	
	bool const loaded = m_texture.loadFromFile("Assets/Textures/star.tga");
	ASSERT_CHECK(loaded);

	for (int i = 0 ; i < k_numberOfSparks; i++ )
	{
		m_pSpark[i].setTexture(m_texture);
	}
}


SparkExplosion::~SparkExplosion()
{
	safeDeleteArray(m_pSpark);
}

// Cycles through the array and updates
void SparkExplosion::update(float deltaTime)
{
	for( int n = 0; n < k_numberOfSparks; n++ )
	{
		m_pSpark[n].update(deltaTime);
	}
}

// Resets boolean here
void SparkExplosion::setIsActive() const
{
	for( int n = 0; n < k_numberOfSparks; n++ )
	{
		m_pSpark[n].setIsActive(true);
	}
}

// Re-arms the clock
void SparkExplosion::restartTimer() const
{
	for( int n = 0; n < k_numberOfSparks; n++ )
	{
		m_pSpark[n].restartTimer();
	}
}

// Sets the position of all sparks
void SparkExplosion::setPos(float x, float y) const
{
	for (int n= 0; n < k_numberOfSparks; n++ )
	{
		m_pSpark[n].setPos(x, y);
	}
}

//Cycles through the full array and draws them
void SparkExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for( int n = 0; n < k_numberOfSparks; n++ )
	{
		if( m_pSpark->getIsActive() == true )
		{
			target.draw(m_pSpark[n]);
		}
	}
}