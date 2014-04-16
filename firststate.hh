
#ifndef FIRSTSTATE_HH_
# define FIRSTSTATE_HH_

#include <SDL.h>
#include <vector>
#include <queue>

#include "gamestate.hh"
#include "player.hh"
#include "armada.hh"

#define	BACKGROUND_SCROLL	150	// cycle
#define	MOB_CONTROL		350	// mob_control

class FirstState : public CGameState
{
public:
    void Init(); // bg s/r, player.Init, armada.Init, score, 'clocks'
    void Cleanup(); // clean and clear vector and queue

    void Pause();
    void Resume();

    void HandleEvents(CGameEngine *game); // manage keyboard mainly
    void Update(CGameEngine	*game); // up all elts of vec/que + P1
    void Draw(CGameEngine	*game); // draw "	"	"

    // TODO: add this properly
    void ScrollBackground();



    // Manage enemies lifecycle: mvt, shooting, point, update
    // void MobControl();
    // Manage vector of Weapon for enemies
    // void FireworksControl();

    // void InitParty(int partysize, int interval); // push_back parties
    // void NewRound(Party	*faceoff); // if summon, pop Foe : TickDown()
    // void PlayOutRound(); // for all foes, ...

    // Singleton B
    static FirstState	*Instance() { return &m_FirstState; }

protected:
    FirstState() { }

private:
    static FirstState	m_FirstState;
    // End singleton B

    SDL_Surface		*background;
    SDL_Rect		bg_focus;
    unsigned		score;

    Player		player;
    Armada		armada;

    int			cycle;		// background freq
    int			mob_control;	// foe freq

    int			tick;
};

#endif /* FIRSTSTATE_HH_ */
