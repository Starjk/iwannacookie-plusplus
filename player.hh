#ifndef PLAYER_HH_
# define PLAYER_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "foe.hh"

#define SHOT_FREQ	250	// 100

#define SHOT_TYPE_THRESHOLD_1	1
#define SHOT_TYPE_THRESHOLD_2	2
#define SHOT_TYPE_THRESHOLD_3	3
#define SHOT_TYPE_THRESHOLD_4	4
#define SHOT_TYPE_THRESHOLD_5	5
#define SHOT_TYPE_THRESHOLD_6	6

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

    void NewShot();
    void NewShotByType(int	firetype);
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
