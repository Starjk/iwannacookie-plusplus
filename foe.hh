#ifndef FOE_HH_
# define FOE_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "player.hh"

#define	SHOT_FREQ	75
#define	SHOT_SPEED	125
#define SHOT_DISTANCE	250

class Foe : public Ship
{
public:
    Foe()
	{
	    health = 25;
	    speed = 2;
	    foe_type = 1;	// FIXME: include moar enemy types
	    point = 100;	// FIXME: include moar enemy types
	    active = false;
	}
    Foe(int	hp, int actual_speed);

    void Init();
    void Cleanup();

    void HandleEvents();
    void Update();
    void Draw(CGameEngine	*game);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    // Manage movement
    void ActiveUnit(/* Ship *ship */);
    // Manage shots nearing Player
    void Aggression(Ship *ship, std::vector<Weaponery*> *shots);
    void TakesDamages(int	value);
    void HandleCollisions(Ship	*ship);
    // bool KeepAlive();

    // GettersxSetters
    void setPower(int fire_power) { firetype = fire_power; }
    int getPower() const { return firetype; }
    int getPoint() const { return point; }

private:
    int		point;
    int		foe_type;
    bool	active;
    // int		foe_freq;
    // spaceship, ship_rect, health, speed, firetype, firepower, frequency
};

#endif /* FOE_HH_ */
