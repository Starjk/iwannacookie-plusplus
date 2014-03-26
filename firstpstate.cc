
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include "gameengine.hh"
#include "gamestate.hh"
#include "firstpstate.hh"
#include "pausestate.hh"

CFirstPState CFirstPState::m_FirstPState;

void CFirstPState::Init()
{
    SDL_Surface	*temp = IMG_Load("media/img/background_1.jpg");

    background = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    printf("CFirstPState Init\n");
}

void CFirstPState::Cleanup()
{
    SDL_FreeSurface(background);

    printf("CFirstPState Cleanup\n");
}

void CFirstPState::Pause()
{
    printf("CFirstPState Pause\n");
}

void CFirstPState::Resume()
{
    printf("CFirstPState Resume\n");
}

void CFirstPState::HandleEvents(CGameEngine	*game)
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
		game->Quit();
		break;
	    case SDLK_p:
		game->PushState(CPauseState::Instance());
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

void CFirstPState::Update(CGameEngine	*game)
{
    // FIXME: compile flags
    game = game;
}

void CFirstPState::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(background, NULL, game->screen, NULL);
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

