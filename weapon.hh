#ifndef WEAPON_HH_
# define WEAPON_HH_

#include <SDL.h>

#include "physengine.hh"

class Weaponery
{
public:
    Weaponery()
	{
	    firetype = 1;
	    damages = 50;
	    speed = 5;
	    motion = false;
	}
    Weaponery(int type, int dmg, int speed);

    void Init(SDL_Rect	ship_rect);
    void Cleanup();

    /* ... */
    void SetMotion();
    bool GetMotion();
    void EndMotion();
    /* ... */

    void HandlePhysics();
    void Update();
    void Draw(CGameEngine	*game);

private:
    SDL_Surface	*shoot;
    SDL_Rect	fire_rect;
    int		firetype;
    int		damages;
    int		speed;
    bool	motion;
    bool	is_enemys;

    int		cycle;
    int		clockwork;
};

#endif /* WEAPON_HH_ */
