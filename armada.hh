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

    Armada()
	{
	    interval = 1000;
	    level = 1;
	}
    Armada(int lvl, int inter); // level determines preset values

    void Init(int	lvl=1);
    void Cleanup();

    unsigned Update(Player	*player);
    void Draw(GameEngine	*game);

    bool Sanitize();
    int	GetPartyOuted();

    // party quantity managment

    // preset managment
    void addPreset(int newPreset);
    int popPreset();

    bool Defeated();	// if preset empty and all parties "out"
    void CallBoss();	// all parties out, add solo party of Boss

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
