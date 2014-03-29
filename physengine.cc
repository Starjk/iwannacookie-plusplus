#include "physengine.hh"

PhysicEngine PhysicEngine::PhyEngine;

bool	PhysicEngine::ShiftUp(SDL_Rect		*object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftDown(SDL_Rect	*object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftLeft(SDL_Rect	*object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftRight(SDL_Rect	*object)
{
    object = object;
    return true;
}

static bool	CollideTop(SDL_Rect	*object,
			   SDL_Rect	*target)
{
    // This one looks wrong
    return ((target->y <= (object->y+object->h)) &&
	    (object->x >= (target->x+target->w)) &&
	    (object->x <= (target->x+target->w)));
}

static bool	CollideBottom(SDL_Rect	*object,
			      SDL_Rect	*target)
{
    // This one too
    return ((object->y >= (target->y+target->h)) &&
	    (object->x >= (target->x+target->w)) &&
	    (object->x <= (target->x+target->w)));
}

static bool	CollideLeft(SDL_Rect	*object,
			    SDL_Rect	*target)
{
    return ((target->x <= (object->x+object->w)) &&
	    (target->y <= (object->y+object->h)) &&
	    (object->y <= (target->y+target->h)));
}

static bool	CollideRight(SDL_Rect	*object,
			     SDL_Rect	*target)
{
    return ((object->x <= (target->x+target->w)) &&
	    (target->y <= (object->y+object->h)) &&
	    (object->y <= (target->y+target->h)));
}

bool	PhysicEngine::Collide(SDL_Rect	*object,
			      SDL_Rect	*target)
{
    return (CollideTop(object, target) ||
	    CollideBottom(object, target) ||
	    CollideLeft(object, target) ||
	    CollideRight(object, target));
}
