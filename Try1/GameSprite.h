#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class GameSprite : public sf::Sprite
{
private:
	sf::Texture m_texture;

public:
	//GameSprite();
	GameSprite( const char* textureName );
	~GameSprite();
};

#endif