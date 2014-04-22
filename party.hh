#ifndef _PARTY_HH_
# define _PARTY_HH_

#include <SDL.h>
#include <vector>

#include "foe.hh"
#include "weapon.hh"

#define	MOB_CONTROL		350

class Party
{
public:

    Party() { partysize = 2; initsize = 2; hourglass = 100; }

    Party(int	preset);
    Party(int	inter, int	size);
    Party(int	type, int	inter, int	size);

    void Init();
    void Cleanup();

    // for all enemies, check all shots for C w/ player, also
    // for all player's shot, check all enemies for C
    unsigned HandleCollisions(Player *player);
    void Update(Player	*player);
    void Draw(GameEngine	*game);

    // Remove elements if Cease to exists or HP <= 0
    bool Sanitize();
    int	GetNonExistent();
    int	GetStationary();
    // Help check if Party can/should be Cleaned Up
    bool NoMoreFoes();
    bool NoMoreShots();

    // Manage enemies lifecycle: mvt, shooting, point, update
    void MobControl(Player	*player);
    // Manage vector of Weapon for enemies
    void FireworksControl(Player	*player);

    bool PartyOut();

    // GettersxSetters
    std::vector<Foe*> getParty() const
	{ return party; }
    void setParty(std::vector<Foe*> newParty)
	{ party = newParty; }

    int getInterval() const { return interval; }
    void setInterval(int inter) { interval = inter; }

    std::vector<Weaponry*> getFireworks() const
	{ return fireworks; }
    void setParty(std::vector<Weaponry*> newFireworks)
	{ fireworks = newFireworks; }

private:
    std::vector<Foe*>	party;
    int			partytype;
    int			partysize;
    int			hourglass;	// fixed value of interval
    int			initsize;
    int			interval;	// decreasing value
    std::vector<Weaponry*>	fireworks;

    int			mob_control;
    int			tick;
};

#endif /* _PARTY_HH_ */
