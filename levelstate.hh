
#ifndef LEVELSTATE_HH_
# define LEVELSTATE_HH_

#include <SDL.h>
#include <vector>
#include <queue>

#include "gamestate.hh"
#include "player.hh"
#include "armada.hh"

#define	BACKGROUND_SCROLL	150	// cycle
#define	MOB_CONTROL		350	// mob_control

class LevelState : public CGameState
{
public:

    LevelState(unsigned	level=1, unsigned score=0)
	{
	    this->level = level;
	    this->score = score;
	}

    void Init(); // bg s/r, player.Init, armada.Init, score, 'clocks'
    void Cleanup(); // clean to allow a new Init from scratch

    void Pause();
    void Resume();

    void HandleEvents(GameEngine *game); // manage keyboard mainly
    void Update(GameEngine	*game); // up all elts of vec/que + P1
    void Draw(GameEngine	*game); // draw "	"	"

    void ScrollBackground();

private:

    SDL_Rect		bg_focus;
    unsigned		score;
    unsigned		level;

    Player		player;
    Armada		armada;

    int			cycle;		// background freq
    int			mob_control;	// foe freq

    int			tick;
};

#endif /* LEVELSTATE_HH_ */
