#ifndef FOE_HH_
# define FOE_HH_

#include <SDL.h>
#include <vector>

#include "ship.hh"
#include "physengine.hh"
#include "weapon.hh"
#include "player.hh"

#define	FOE_SHOT_FREQ		75	// 50 == fucking hard
#define	FOE_SHOT_SPEED		125
#define FOE_SHOT_DISTANCE	250

#define FOE_TYPE_THRESHOLD_1	5
#define FOE_TYPE_THRESHOLD_2	10
#define FOE_TYPE_THRESHOLD_3	15
#define FOE_TYPE_THRESHOLD_4	20

class Foe : public Ship
{
public:
    Foe()
	{
	    health = 25;
	    speed = 2;
	    firetype = 1;
	    foe_type = 1;
	    point = 50;
	    EndExistence();
	}
    Foe(int	type);

    void Init();
    void Cleanup();

    void HandleEvents();
    void Update();
    void Draw(GameEngine	*game);

    void MoveUp() { ship_rect.y -= speed; }
    void MoveDown() { ship_rect.y += speed; }
    void MoveLeft() { ship_rect.x -= speed * 3; }
    void MoveRight() { ship_rect.x += speed * 3; }
    void MoveDownLt() { ship_rect.y+=speed*3; ship_rect.x-=speed; }
    void MoveDownRt() { ship_rect.y+=speed*3; ship_rect.x+=speed; }

    // Manage movement
    void Mobility(/* Ship *ship */);
    // Manage shots nearing Player
    void Aggression(Ship *ship, std::vector<Weaponry*> *shots);
    unsigned TakesDamages(int	value);

    // GettersxSetters
    void setPower(int fire_power) { firetype = fire_power; }
    int getPower() const { return firetype; }
    void setPoint(int pt) { point = pt; }
    int getPoint() const { return point; }

private:
    int		point;
    // FIXME: unsigned or else, technically, -1 fucks everything!
    int		foe_type;

};

#endif /* FOE_HH_ */
