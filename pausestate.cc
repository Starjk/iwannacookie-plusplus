
#include <stdio.h>

#include "SDL.h"
#include "gameengine.hh"
#include "gamestate.hh"
#include "pausestate.hh"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{
    SDL_Surface *temp = SDL_LoadBMP("media/img/pause.bmp");

    background = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    printf("CPauseState Init\n");
}

void CPauseState::Cleanup()
{
    SDL_FreeSurface(background);

    printf("CPauseState Cleanup\n");
}

void CPauseState::Pause()
{
    printf("CPauseState Pause\n");
}

void CPauseState::Resume()
{
    printf("CPauseState Resume\n");
}

void CPauseState::HandleEvents(CGameEngine	*game)
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

void CPauseState::Update(CGameEngine	*game)
{
    // FIXME: compile flags
    game = game;
}

void CPauseState::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(background, NULL, game->screen, NULL);
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
