
#ifndef FIRSTPSTATE_HH_
# define FIRSTPSTATE_HH_

#include <SDL.h>
#include "gamestate.hh"
#include "player.hh"

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

    int			cycle;
    int			clockwork;
};

#endif /* FIRSTPSTATE_HH_ */
