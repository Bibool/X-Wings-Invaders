#include "GameSprite.h"
#include "Helpers.h"


GameSprite::GameSprite( const char* textureName )
{
	bool const loaded = m_texture.loadFromFile( textureName );
	ASSERT_CHECK(loaded);
	setTexture( m_texture );
}

GameSprite::~GameSprite()
{

}
