
#ifndef FIRSTPSTATE_HH_
# define FIRSTPSTATE_HH_

#include "SDL.h"
#include "gamestate.hh"

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
};

#endif /* FIRSTPSTATE_HH_ */
