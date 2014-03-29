#ifndef PLAYER_HH_
# define PLAYER_HH_

#include <SDL.h>
#include <vector>

#include "physengine.hh"
#include "weapon.hh"

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

    // FIXME: should be NewShot() and act according to name
    void MainWeapon(/* Weaponery player_weapon */);
    void NewShot(/* Weaponery player_weapon */);
    void UpgradeWeapon(/* Weaponery player_weapon */);
    void DownWeapon(/* Weaponery player_weapon */);

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

    // FIXME: use list container to keep all visible shoot
    std::vector<Weaponery*>	firepower;
    Weaponery	pewpewpew;
    int		frequency;
};

#endif /* PLAYER_HH_ */
