#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/Sprite.hpp>

class Config;

class Enemy : public sf::Sprite
{
private:
	// Used to set the position relative to the screen resolution
	Config*		m_pScreenRes;
	
	// Used for positioning the first enemy
	const float m_kPaddingAndPosition = 100.0f;

	// Booleans used for the different logic used in the Enemy Manager
	bool		m_isActive;
	bool		m_isDead;

	// Initializes the base values
	void initialize();
	   	 	
public:
	Enemy();
	Enemy(float posX, float posY);
	~Enemy();

	// To be removed, serves the same purpose as setActive(false)
	void die();
	
	// Getters and Setts
	bool getActive() const		  { return m_isActive;     };
	bool getDead() const		  { return m_isDead;	   };
	void setActive(bool isActive) { m_isActive = isActive; };
	void setDead(bool isDead)	  { m_isDead = isDead;	   };
};

#endif