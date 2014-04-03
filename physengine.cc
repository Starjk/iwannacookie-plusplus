#include "physengine.hh"

// Movement management

bool	PhysicEngine::ShiftUp(SDL_Rect		&object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftDown(SDL_Rect	&object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftLeft(SDL_Rect	&object)
{
    object = object;
    return true;
}

bool	PhysicEngine::ShiftRight(SDL_Rect	&object)
{
    object = object;
    return true;
}

// Collision management

static bool	CollideTop(SDL_Rect	*object,
			   SDL_Rect	*target)
{
    return ((object->y + object->h >= target->y) &&
	    (object->y < target->y) &&
	    (object->x < target->x + target->w) &&	// <= ?
	    (object->x + object->w > target->x));	// >= ?
}

static bool	CollideBottom(SDL_Rect	*object,
			      SDL_Rect	*target)
{
    return ((target->y + target->h >= object->y) &&
	    (target->y < object->y) &&
	    (object->x < target->x + target->w) &&	// <= ?
	    (object->x + object->w > target->x));	// >= ?
}

static bool	CollideLeft(SDL_Rect	*object,
			    SDL_Rect	*target)
{
    return ((target->x + target->w >= object->x) &&
	    (target->x < object->x) &&
	    (object->y < target->y + target->h) &&	// <= ?
	    (object->y + object->h > target->y));	// >= ?
}

static bool	CollideRight(SDL_Rect	*object,
			     SDL_Rect	*target)
{
    return ((object->x + object->w >= target->x) &&
	    (object->x < target->x) &&
	    (object->y < target->y + target->h) &&	// <= ?
	    (object->y + object->h > target->y));	// >= ?
}

bool	PhysicEngine::Collide(SDL_Rect	*object,
			      SDL_Rect	*target)
{
    return (CollideTop(object, target) ||
	    CollideBottom(object, target) ||
	    CollideLeft(object, target) ||
	    CollideRight(object, target));
}
