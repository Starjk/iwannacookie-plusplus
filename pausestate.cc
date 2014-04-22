
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "gamestate.hh"
#include "pausestate.hh"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{
    std::cout << "CPauseState Init" << std::endl;
}

void CPauseState::Cleanup()
{
    std::cout << "CPauseState Cleanup" << std::endl;
}

void CPauseState::Pause()
{
    std::cout << "CPauseState Pause" << std::endl;
}

void CPauseState::Resume()
{
    std::cout << "CPauseState Resume" << std::endl;
}

void CPauseState::HandleEvents(GameEngine	*game)
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT:
	    game->Quit();
	    break;

	case SDL_KEYDOWN:
	    switch (event.key.keysym.sym) {
	    case SDLK_ESCAPE:
		game->PopState();
		break;
	    default:
		break;
	    }
	    break;
	default:
	    break;
	}
    }
}

void CPauseState::Update(GameEngine	*game)
{
    // FIXME: compile flags
    game = game;
}

void CPauseState::Draw(GameEngine	*game)
{
    SDL_BlitSurface(game->GraEng->GetPauseBG(),
		    NULL, game->screen, NULL);
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
