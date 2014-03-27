#ifndef PLAYER_HH_
# define PLAYER_HH_

#include <SDL.h>

#include "physengine.hh"

class Player
{
public:
    Player()
	{
	    health = 100;
	    life = 3;
	    speed = 4;
	    has_spawn = true;
	}
    Player(int	hp, int	remaining_life, int actual_speed);

    void Init();
    void Cleanup();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void MainWeapon();

    void HandleEvents();
    void Update();
    void Draw(CGameEngine	*game);

private:
    SDL_Surface	*spaceship;
    SDL_Rect	ship_rect;
    int		health;
    int		life;
    int		speed;	// lateral move are * 2/3
    bool	has_spawn;
};

#endif /* PLAYER_HH_ */
