
#ifndef PAUSESTATE_HH_
# define PAUSESTATE_HH_

#include "SDL.h"
#include "gamestate.hh"

#define	OPACITY	155

class CPauseState : public CGameState
{
public:
    void Init();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents(GameEngine	*game);
    void Update(GameEngine	*game);
    void Draw(GameEngine	*game);

    // Singleton B
    static CPauseState	*Instance() { return &m_PauseState; }

protected:
    CPauseState() { }

private:
    static CPauseState	m_PauseState;
    // End singleton B

    // FIXME: wait for 'alpha fix'
    // SDL_Surface		*background;
};

#endif /* PAUSESTATE_HH_ */
