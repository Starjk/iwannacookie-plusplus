
#ifndef FIRSTPSTATE_HH_
# define FIRSTPSTATE_HH_

#include <SDL.h>
#include <vector>

#include "gamestate.hh"
#include "player.hh"
#include "foe.hh"

#define	BACKGROUND_SCROLL	100	// cycle
#define	MOB_CONTROL		350	// mob_control

class CFirstPState : public CGameState
{
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(CGameEngine	*game);
    void Update(CGameEngine	*game);
    void Draw(CGameEngine	*game);

    // TODO: add this properly
    void ScrollBackground();

    // FIXME: del/rename/call-in-the-right-way after TEST
    void NewChallenger();
    void MobControl();

    // for all enemies, check all shots for C w/ player, also
    // for all player's shot, check all enemies for C
    void HandleCollisions();

    // Singleton B
    static CFirstPState	*Instance()
    {
	return &m_FirstPState;
    }

protected:
    CFirstPState() { }

private:
    static CFirstPState	m_FirstPState;
    // End singleton B

    SDL_Surface		*background;
    SDL_Rect		bg_focus;
    Player		player;
    unsigned		score;

    std::vector<Foe*>	encounters;

    int			cycle;		// background freq
    int			mob_control;	// foe freq
    int			clockwork;
};

#endif /* FIRSTPSTATE_HH_ */
