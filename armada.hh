#ifndef _ARMADA_HH_
# define _ARMADA_HH_

#include <SDL.h>
#include <vector>
#include <deque>

#include "player.hh"
#include "foe.hh"
#include "party.hh"

class Armada
{
public:

    Armada() // default is level one w/ interval of 100?
	{
	    interval = 1000;
	    level = 1;
	}
    Armada(int lvl, int inter); // level determines preset values

    void Init(int	lvl=1);
    void Cleanup(); // check if clean up to do, return bool?

    void HandleCollisions(Player *player); // manage c/ for each party
    // void HandleEvent(); ? Really?
    void Update(Player		*player);
    void Draw(CGameEngine	*game);

    // party quantity managment

    // preset managment
    void addPreset(int newPreset);
    int popPreset();

    // GettersxSetters
    std::vector<Party*> getArmada() const
	{ return armada; }
    void setArmada(std::vector<Party*> newArmada)
	{ armada = newArmada; }

    int getInterval() const
	{ return interval; }
    void setInterval(int inter)
	{ interval = inter; }

    std::deque<int> getPreset() const
	{ return preset; }
    void setPreset(std::deque<int> newPreset)
	{ preset = newPreset; }

private:
    std::vector<Party*>	armada;		// starts empty
    int			interval;
    int			hourglass;
    int			level;		// help to init preset
    std::deque<int>	preset;		// depends of lvl from Const
};

#endif /* _ARMADA_HH_ */
