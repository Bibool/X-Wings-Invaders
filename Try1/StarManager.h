#ifndef STARMANAGER_H
#define STARMANAGER_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "IUpdatable.h"

// Amount of stars
const int k_numberOfStars = 1001;

class Star;

class StarManager : public sf::Drawable, public IUpdatable
{
private:
	//The stars
	Star*		m_pStar;
	
	// The texture we feed to all stars
	sf::Texture m_texture;

public:
	StarManager();
	~StarManager();
	
	// Derived update
	virtual void update(float deltaTime) override;

	// Derived draw
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;
};
#endif
