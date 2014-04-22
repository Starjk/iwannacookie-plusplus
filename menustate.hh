
#ifndef MENUSTATE_HH_
# define MENUSTATE_HH_

#include "SDL.h"
#include "gamestate.hh"

class CMenuState : public CGameState
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
    static CMenuState* Instance() { return &m_MenuState; }

protected:
    CMenuState() { }

private:
    static CMenuState	m_MenuState;
    // End singleton B

    SDL_Surface	*background;
    SDL_Surface	*fader;
    int		alpha;
};

#endif /* MENUSTATE_HH_ */
