#ifndef IUPDATABLE_H
#define IUPDATABLE_H

// Any class that can be updated can be derived from this
class IUpdatable
{
	// Any derived class needs to fill in this
	virtual void update(float deltaTime) = 0;
};

#endif