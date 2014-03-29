#ifndef PHYSENGINE_HH_
# define PHYSENGINE_HH_

#include <SDL.h>

#include "gameengine.hh"	// correspondence of WIDTH and HEIGHT

class PhysicEngine
{
public:

    // Movement
    bool ShiftUp(SDL_Rect	*object);
    bool ShiftDown(SDL_Rect	*object);
    bool ShiftLeft(SDL_Rect	*object);
    bool ShiftRight(SDL_Rect	*object);

    // Collision

    // Does the object collide with target:
    //   top? bottom? left? right?
    bool Collide(SDL_Rect	*object,
		 SDL_Rect	*target);

    static PhysicEngine	*Instance()
    {
	return &PhyEngine;
    }

protected:
    PhysicEngine() { }

private:
    static PhysicEngine	PhyEngine;
};

#endif /* PHYSENGINE_HH_ */
