#ifndef GAMEENGINE_HH_
# define GAMEENGINE_HH_

#include <iostream>
#include <vector>

#include <SDL.h>

#define WIDTH	800
#define HEIGHT	600

// Forward declaration
class CGameState;

class CGameEngine
{
public:

    void Init(const char	*title,
	      int	width=WIDTH,
	      int	height=HEIGHT,
	      int	bpp=0,
	      bool	fullscreen=false);
    void Cleanup();

    void ChangeState(CGameState	*state);
    void PushState(CGameState	*state);
    void PopState();

    void HandleEvents();
    void Update();
    void Draw();

    bool Running() { return is_running; }
    void Quit() { is_running = false; }

    SDL_Surface	*screen;

private:
    // the stack of states
    std::vector<CGameState*>	states;

    bool	is_running;
    bool	is_fullscreen;
};

#endif /* GAMEENGINE_HH_ */
