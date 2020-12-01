#ifndef SPARKEXPLOSION_H
#define SPARKEXPLOSION_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "IUpdatable.h"

// How many sparks the explosion contains
const int k_numberOfSparks = 51;

class Spark;

class SparkExplosion : public sf::Drawable, public IUpdatable
{
private:
	// The explosion
	Spark* m_pSpark;
	
	// The texture we feed to all sparks
	sf::Texture m_texture;

public:
	SparkExplosion();
	~SparkExplosion();

	// Feed the initial position into the spark array
	void setPos(float x, float y) const;
	   
	// Sets IsActive on all sparks
	void setIsActive() const;

	// Re-arm spark timer
	void restartTimer() const;

	// Inherited update
	virtual void update(float deltaTime) override;

	// Inherited function to draw the explosion
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;	
};
#endif