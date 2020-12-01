#ifndef SPARK_H
#define SPARK_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "IUpdatable.h"


class Spark : public sf::Sprite, public IUpdatable
{
private:
	// The random X and Y the particle will travel at
	float m_yDirection;
	float m_xDirection;

	// This is to store the original position for the next explosion
	float m_xOriginalPos;
	float m_yOriginalPos;

	// The const min / max values used in random aspect
	// The scalar range
	const float m_kMinScale		= 0.05f;
	const float m_kMaxScale		= 0.25f;

	// The random speed range
	const float m_kMinSpeed		= -5.0f;
	const float m_kMaxSpeed		= 10.0f;

	// The random direction
	// Negative: Down on Y Axis, Left on X axis
	// Positive: Up on Y Axis, Right on X axis
	const float m_kMinDirection = -100.0f;
	const float m_kMaxDirection = 100.0f;

	// Color range
	// 0 is white 255 is solid color
	const float m_kMinColor	    = 20.0f;
	const float m_kMaxColor		= 255.0f;

	// Alpha
	const float m_kMinAlpha		= 20.0f;
	const float	m_kMaxAlpha		= 255.0f;

	// Speed at which the particles start falling down
	const float m_kFallOffSpeed = 300.0f;

	// Time before particles start falling
	const float m_kFallOffDuration = 0.1f;
	// Lifetime of the spark
	const float m_kLifeDuration = 0.5f;	

	// This booleans is to stop updating/drawing 
	bool m_isActive;
	
	// Clock for movement
	sf::Clock m_clock;

	void initialise();

	// Randomizes the direction to which the particle will travel
	void randomiseDirection();

	//Randomizes the scale, color and alpha of the particle
	void randomiseScale();
	void randomiseColour();
	void randomiseAlpha();

	// Resets the particle properties
	// Called when going inactive to be used for next pos
	void resetParticle();


public:
	Spark();
	Spark(float x, float y);
	~Spark();

	// Inherited update
	virtual void update(float deltaTime) override;

	// Sets the position with fed-in values
	void setPos(float x, float y);

	// Re-arms the clock
	void restartTimer();

	// Get/Set
	bool getIsActive() const	    { return m_isActive;	 }
	void setIsActive(bool isActive) { m_isActive = isActive; };

};


#endif