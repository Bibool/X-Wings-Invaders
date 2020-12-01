#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics/Sprite.hpp>
#include "IUpdatable.h"

class Config;

class Star : public sf::Sprite, public IUpdatable
{
private:
	// Const values for tweaking
	// Position to which it resets to
	const float m_kUIPosition		= 65.0f;
	// Speed
	const float m_kMinSpeed			= 20.0f;
	const float m_kMaxSpeed			= 300.0f;
	// Scale
	const float m_kMinScale			= 0.03f;
	const float m_kMaxScale			= 0.15f;
	// Color
	const float m_kMinColorRange	= 20.0f;
	const float m_kMaxColorRange	= 255.0f;
	// Alpha
	//const int   m_kMinAlpha			= 20;
	const int	m_kMaxAlpha			= 255;
	
	Config*		m_pConfig;
	float		m_speed;

	// Set original values
	void initialise();

	// Functions that randomizes aspect of the stars
	void randomisePosition();
	void randomiseSpeed();
	void randomiseScale();
	void randomiseColour();

public:
	Star();
	~Star();

	// Derived update
	virtual void update( float deltaTime ) override;
};
#endif
