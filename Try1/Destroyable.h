#ifndef DESTROYABLE_H
#define DESTROYABLE_H

// Abstract class that was ment to be inherited from when it comes to taking damage
// However as everything is a one shot, it's unnecessary.

class Destroyable
{
private:

public:
	int health;
	Destroyable() { health = 0; };
	virtual void takeDamage(){};
	virtual void giveDamage(){};
	virtual void die(){};

};
#endif