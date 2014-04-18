#ifndef FOE_HH_
# define FOE_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "player.hh"

#define	FOE_SHOT_FREQ		75
#define	FOE_SHOT_SPEED		125
#define FOE_SHOT_DISTANCE	250

class Foe : public Ship
{
public:
    Foe()
	{
	    health = 55;
	    speed = 2;
	    foe_type = 1;	// TODO: include moar enemy types
	    point = 100;	// TODO: include moar enemy types
	    EndExistence();
	}
    Foe(int	type)
	{
	    health = 55;
	    speed = 2;
	    foe_type = type;	// TODO: include moar enemy types
	    point = 100;	// TODO: include moar enemy types
	    EndExistence();
	}
    Foe(int	hp, int actual_speed);

    void Init();
    void Cleanup();

    void HandleEvents();
    void Update();
    void Draw(CGameEngine	*game);

    void MoveUp() { ship_rect.y -= speed; }
    void MoveDown() { ship_rect.y += speed; }
    void MoveLeft() { ship_rect.x -= speed * 3; }
    void MoveRight() { ship_rect.x += speed * 3; }

    // Manage movement
    void Mobility(/* Ship *ship */);
    // Manage shots nearing Player
    void Aggression(Ship *ship, std::vector<Weaponry*> *shots);
    void TakesDamages(int	value);
    void HandleCollisions(Ship	*ship);

    // GettersxSetters
    void setPower(int fire_power) { firetype = fire_power; }
    int getPower() const { return firetype; }
    void setPoint(int pt) { point = pt; }
    int getPoint() const { return point; }

private:
    int		point;
    int		foe_type;

    // int		foe_freq;
    // spaceship, ship_rect, health, speed, firetype, firepower, frequency
};

#endif /* FOE_HH_ */
