#ifndef _PARTY_HH_
# define _PARTY_HH_

#include <SDL.h>
#include <vector>

#include "foe.hh"
#include "weapon.hh"

// #include "physengine.hh"
// #include "player.hh"

#define	MOB_CONTROL		350	// mob_control

class Party
{
public:

    Party() { partysize = 2; hourglass = 100; }

    Party(int	preset);
    Party(int	inter, int	size);
    Party(int	type, int	inter, int	size);

    void Init(); // hourglass = interval;
    void Cleanup(); // check if clean up to do, then clear

    // for all enemies, check all shots for C w/ player, also
    // for all player's shot, check all enemies for C
    void HandleCollisions(Player *player);
    // void HandleEvent(); ? Really?
    void Update(Player		*player);
    void Draw(CGameEngine	*game);

    // Check if Party can/should be Cleaned Up
    bool NoMoreFoes();
    bool NoMoreShots();

    // Manage enemies lifecycle: mvt, shooting, point, update
    void MobControl(Player	*player);
    // Manage vector of Weapon for enemies
    void FireworksControl(Player	*player);

    // GettersxSetters
    std::vector<Foe*> getParty() const
	{ return party; }
    void setParty(std::vector<Foe*> newParty)
	{ party = newParty; }

    int getInterval() const
	{ return interval; }
    void setInterval(int inter)
	{ interval = inter; }

    std::vector<Weaponry*> getFireworks() const
	{ return fireworks; }
    void setParty(std::vector<Weaponry*> newFireworks)
	{ fireworks = newFireworks; }

private:
    std::vector<Foe*>	party;
    int			partytype;
    int			partysize;
    int			hourglass;	// fixed value of interval
    int			interval;	// decreasing value
    std::vector<Weaponry*>	fireworks;

    int			score;		// add up score from all foes
    int			mob_control;
    int			tick;
};

/*
class Party
{
public:

    void HandleInterval(CGameEngine	*game); // FIXME: not sure
    void Update(CGameEngine	*game); // up conditions of enemies/shots/overall-party
    void Draw(CGameEngine	*game); // draw all legits enemies/shots

    // FIXME: dafuk?! from Party, get Party, for newRound?!
    //void NewRound(Party);

    bool Summon() { return (hourglass <= 0); }
    void TickDown() { hourglass--; }
    void TurnHourglass() { if (hourglass <= 0) hourglass = interval; }

    bool PartyDefeated(); // for all elts in party, 'no KeepAlive' or out of scope/screen
    void SummonBoss(int	bosstype, int health);

    void NewChallenger(); // push new Foe in party (?)
    void MobControl(); // check KeepAlive, ActiveUnit, Aggression, Update, Cleanup? (and return point?)
    void FireworksControl(); // manage Enemies' weapon

};
*/

#endif /* _PARTY_HH_ */
