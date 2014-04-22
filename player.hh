#ifndef PLAYER_HH_
# define PLAYER_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "foe.hh"

#define SHOT_FREQ	100

class Foe;

class Player : public Ship
{
public:
    Player()
	{
	    health = 100;
	    life = 3;
	    speed = 4;
	    firetype = 1;
	    EndExistence();
	}
    Player(int	hp, int	remaining_life, int actual_speed);

    void Init();
    void Cleanup();

    void HandleEvents();	// manage keyboard input for ship
    void Update();
    void Draw(GameEngine	*game);

    bool Sanitize();		// manage cleaning of All Shots
    int	 GetStationary();
    bool NoMoreShots();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void NewShot(bool		is_foe=false);
    void UpgradeWeapon(/* Weaponry player_weapon */);
    void DownWeapon(/* Weaponry player_weapon */);

    void TakesDamages(int	value);
    unsigned HandleShooting(std::vector<Foe*> foes);

    // GettersxSetters
    void setPower(int fire_power) { firetype = fire_power; }
    int getPower() const { return firetype; }

    void setLife(int heart) { life = heart; }
    int getLife() const { return life; }

    std::vector<Weaponry*> *getFireworks() { return &firepower; }

private:

    // player fundamental stats
    int		life;
    // aim to keep all visible shoot on screen
    std::vector<Weaponry*>	firepower;
};

#endif /* PLAYER_HH_ */
