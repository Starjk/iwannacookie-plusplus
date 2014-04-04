#ifndef PLAYER_HH_
# define PLAYER_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "foe.hh"

class Foe;

class Player : public Ship
{
public:
    Player()
	{
	    health = 100;
	    life = 3;
	    speed = 4;
	}
    Player(int	hp, int	remaining_life, int actual_speed);

    void Init();
    void Cleanup();

    void HandleEvents();
    void Update();
    void Draw(CGameEngine	*game);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void NewShot(bool		is_foe=false);
    void UpgradeWeapon(/* Weaponery player_weapon */);
    void DownWeapon(/* Weaponery player_weapon */);

    void TakesDamages(int	value);

    void HandleCollisions(Ship	*ship);
    void HandleShooting(std::vector<Foe*> foes);

    // GettersxSetters
    void setPower(int fire_power) { firetype = fire_power; }
    int getPower() const { return firetype; }

private:

    // player fundamental stats
    int		life;
    /**
    int		speed;	// lateral move are 3 times speed
    int		firetype;
    */

    // aim to keep all visible shoot on screen
    std::vector<Weaponery*>	firepower;
    /**
    // manage spacing between shots
    int		frequency;
    */
};

#endif /* PLAYER_HH_ */
