
#ifndef PAUSESTATE_HH_
# define PAUSESTATE_HH_

#include "SDL.h"
#include "gamestate.hh"

class CPauseState : public CGameState
{
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(CGameEngine	*game);
    void Update(CGameEngine	*game);
    void Draw(CGameEngine	*game);

    // Singleton B
    static CPauseState	*Instance()
    {
	return &m_PauseState;
    }

protected:
    CPauseState() { }

private:
    static CPauseState	m_PauseState;
    // End singleton B

    SDL_Surface		*background;
};

#endif /* PAUSESTATE_HH_ */
