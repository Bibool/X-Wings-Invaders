#include "Helpers.h"
#include "Star.h"
#include "StarManager.h"

StarManager::StarManager()
	: m_pStar( nullptr )
{
	// Create an array of Stars
	m_pStar = new Star[ k_numberOfStars ];
	bool const loaded = m_texture.loadFromFile("Assets/Textures/star.tga");
	ASSERT_CHECK(loaded);

	for (int i = 0; i < k_numberOfStars; i++)
	{
		m_pStar[i].setTexture(m_texture);
	}
}

StarManager::~StarManager()
{
	safeDeleteArray( m_pStar );
}

// Cycles through the array  (amount of stars) and updates their logic
void StarManager::update( float deltaTime )
{
	for( int i = 0; i < k_numberOfStars; i++ )
	{
		m_pStar[ i ].update( deltaTime );
	}

}

// Cycles through the array  (amount of stars) and draws them
void StarManager::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{	
	for( int n = 0; n < k_numberOfStars; n++ )
	{
		target.draw( m_pStar[n] );
	}
}
