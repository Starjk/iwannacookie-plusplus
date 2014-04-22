
#ifndef GAMESTATE_HH_
# define GAMESTATE_HH_

#include "gameengine.hh"

class CGameState
{
public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents(GameEngine	*game) = 0;
    virtual void Update(GameEngine	*game) = 0;
    virtual void Draw(GameEngine	*game) = 0;

    void ChangeState(GameEngine	*game, CGameState	*state)
    {
	game->ChangeState(state);
    }

protected:
    // States are Singleton
    CGameState() { }
};

#endif /* GAMESTATE_HH_ */
