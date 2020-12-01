#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IUpdatable.h"
#include "Destroyable.h"
#include "GameSprite.h"


// Forward declared classes
class BackEndInput;
class Bullet;
class Config;

//////////////////////////////////////
//  This class holds all the values	//
//  as well as functions that has   //
//  things to do with the player	//
//////////////////////////////////////
class PlayerController : public GameSprite, public Destroyable, public IUpdatable
{
private:
	// Const values required by logic
	// Speed Variables
	float const   m_kMoveSpeed       = 500.0f;
	float const   m_kNullSpeed	     = 0.0f;
	
	// Positioning and Boundaries
	float const   m_kBoundaryPadding = 30.0f;
	float const   m_kPositionPadding = 50.0f;

	// Screen anchor multiplier
	float const   m_kHookMultiplier  = 0.5f;

	// Model scale values
	float const   m_kXScale		     = 0.1f;
	float const   m_kYScale		     = 0.1f;
	
	// This bool in relation to the bullet
	// To avoid multi sound shots
	// TODO: Move more logic into here
	bool	      m_isFiring;
	bool	      m_isAtLeftWall;
	bool	      m_isAtRightWall;
	bool	      m_isDead;
	
	// The player input needed for movement/fire
	// And config to appropriate place of the player
	// Independent of magic numbers
	BackEndInput* m_pPlayerInput;
	Config*		  m_pScreenBoundary;
	
	// Checks the boundary to stop player from stepping outside of bounds
	void boundaryCheck(float timeDelta);

	// Inherited functions
	// TODO: Fully implement these functions
	void takeDamage() override{};
	void giveDamage() override{};
	void die()        override{};

public:
	PlayerController();
	~PlayerController();
	
	// Frame compensated update that handles all the logic/input
	virtual void update(float timeDelta) override;
	
	// Get/Set
	bool getIsFiring() const		{ return m_isFiring;     };
	void setIsFiring(bool isFiring) { m_isFiring = isFiring; };

	bool getIsDead() const			{ return m_isDead;		 };
	void setIsDead(bool isDead)		{ m_isDead = isDead;	 };

	int getLife() const				{ return health;		 };
	void setLife(int healthPoint)	{ health = healthPoint;  };
};

#endif