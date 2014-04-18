#ifndef SHIP_HH_
# define SHIP_HH_

#include <SDL.h>

#include "gameengine.hh"
#include "weapon.hh"

class Ship
{
public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Draw(CGameEngine	*game) = 0;

    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;

    virtual void TakesDamages(int	value) = 0;

    // virtual void HandleCollisions(Ship	*ship) = 0;

    virtual bool KeepAlive() { return ((health > 0)/* && OnScreen()*/); }

    virtual void StartExistence() { exists = true; }
    virtual void EndExistence()	{ exists = false; }
    virtual bool DoesExists() const { return exists; }

    // GettersxSetters
    virtual void setPower(int fire_power) = 0;
    virtual int getPower() const = 0;

    SDL_Rect *getRect() { return &ship_rect; }

protected:

    SDL_Surface		*spaceship;
    SDL_Rect		ship_rect;
    bool		exists;
    // ship fundamental stats
    int		health;
    int		speed;	// lateral move are 3 times speed
    int		firetype;	// could be player specific
    // manage spacing between shots
    int		frequency;
};

#endif /* SHIP_HH_ */
