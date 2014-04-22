#ifndef PHYSENGINE_HH_
# define PHYSENGINE_HH_

#include <SDL.h>

#include "gameengine.hh" // correspondence of WIDTH and HEIGHT

namespace PhysicEngine
{

    // Movement
    bool ShiftUp(SDL_Rect	&object);
    bool ShiftDown(SDL_Rect	&object);
    bool ShiftLeft(SDL_Rect	&object);
    bool ShiftRight(SDL_Rect	&object);

    // Boundaries
    bool OnScreen(SDL_Rect	*object);
    bool OffScreen(SDL_Rect	*object);
    bool LeaveScreen(SDL_Rect	*object);

    // Collision

    // Does the object collide with target:
    bool Collide(SDL_Rect	*object,
		 SDL_Rect	*target);

} /* PhysicEngine */

#endif /* PHYSENGINE_HH_ */
