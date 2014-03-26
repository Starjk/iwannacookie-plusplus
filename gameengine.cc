#include "gameengine.hh"
#include "gamestate.hh"

void CGameEngine::Init(const char	*title,
		       int	width,
		       int	height,
		       int	bpp,
		       bool	fullscreen)
{
    int flags = 0;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    	std::cout << "SDL_Init Error: " << SDL_GetError()
		  << std::endl;
    	return;
    }

    // set the title bar text
    SDL_WM_SetCaption(title, title);

    if (fullscreen)
	flags = SDL_FULLSCREEN;

    // create the screen surface
    screen = SDL_SetVideoMode(width, height, bpp, flags);

    is_fullscreen = fullscreen;
    is_running = true;

    printf("CGameEngine Init\n");
}

void CGameEngine::Cleanup()
{
    // cleanup the all states
    while (!states.empty())
    {
	states.back()->Cleanup();
	states.pop_back();
    }

    // switch back to windowed mode so other
    // programs won't get accidentally resized
    if (is_fullscreen)
	screen = SDL_SetVideoMode(800, 600, 0, 0);

    printf("CGameEngine Cleanup\n");

    // $ kill -9 SDL
    SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state)
{
    // cleanup the current state
    if (!states.empty())
    {
	states.back()->Cleanup();
	states.pop_back();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init();
}

void CGameEngine::PushState(CGameState* state)
{
    // pause current state
    if (!states.empty())
	states.back()->Pause();

    // store and init the new state
    states.push_back(state);
    states.back()->Init();
}

void CGameEngine::PopState()
{
    // cleanup the current state
    if (!states.empty())
    {
	states.back()->Cleanup();
	states.pop_back();
    }

    // resume previous state
    if (!states.empty())
	states.back()->Resume();
}

void CGameEngine::HandleEvents()
{
    // let the current (topmost) state handle events
    states.back()->HandleEvents(this);
}

void CGameEngine::Update()
{
    // let the current (topmost) state update the game
    states.back()->Update(this);
}

void CGameEngine::Draw()
{
    // let the current (topmost) state draw the screen
    states.back()->Draw(this);
}
