#ifndef WEAPON_HH_
# define WEAPON_HH_

#include <SDL.h>

#include "physengine.hh"

class Weaponry
{
public:
    Weaponry()
	{
	    firetype = 1;
	    position_x = 'c';
	    damages = 50;
	    speed = 5;
	    motion = false;
	}
    Weaponry(int type, bool is_foe, char posx='c');

    void Init(SDL_Rect	ship_rect);
    void InitSpec();
    void InitPosition(SDL_Rect	ship_rect);
    void Cleanup();

    void HandlePhysics();
    void Update();
    void Draw(GameEngine	*game);

    void StartMotion() { motion = true; }
    void EndMotion() { motion = false; }
    bool GetMotion() const { return motion; }

    // GettersxSetters
    void setDamages(int		value) { damages = value; }
    int	getDamages() const { return damages; }

    SDL_Rect	*getRect() { return &fire_rect; }

private:
    SDL_Rect	fire_rect;
    int		firetype;
    int		damages;
    int		speed;

    bool	motion;
    bool	is_enemys;
    char	position_x;

    int		cycle;
    int		clockwork;

};

#endif /* WEAPON_HH_ */
