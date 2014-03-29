
#include <iostream>

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

    std::cout << "CFirstPState Init" << std::endl;

    bg_focus.x = 0;
    bg_focus.y = 4400;
    bg_focus.w = WIDTH;
    bg_focus.h = HEIGHT;

    cycle = 100;
    clockwork = 5;

    player.Init();
}

void CFirstPState::Cleanup()
{
    SDL_FreeSurface(background);

    std::cout << "CFirstPState Cleanup" << std::endl;

    player.Cleanup();
}

void CFirstPState::Pause()
{
    std::cout << "CFirstPState Pause" << std::endl;
}

void CFirstPState::Resume()
{
    std::cout << "CFirstPState Resume" << std::endl;
}

void CFirstPState::HandleEvents(CGameEngine	*game)
{
    Uint8	*keys = SDL_GetKeyState(NULL);
    SDL_Event	event;

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

	if (keys[SDLK_UP])
	    player.MoveUp();
	if (keys[SDLK_DOWN])
	    player.MoveDown();
	if (keys[SDLK_LEFT])
	    player.MoveLeft();
	if (keys[SDLK_RIGHT])
	    player.MoveRight();
	if (keys[SDLK_SPACE])
//	    player.MainWeapon();
	    player.NewShot();

    }
}

void CFirstPState::Update(CGameEngine	*game)
{
    // FIXME: compile flags
    game = game;

    ScrollBackground();
    player.Update();
}

void CFirstPState::Draw(CGameEngine	*game)
{
    // FIXME: add increment/+loop in bg_focus/background
    SDL_BlitSurface(background, &bg_focus, game->screen, NULL);
    player.Draw(game);
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void CFirstPState::ScrollBackground()
{
    cycle -= clockwork;
    if (cycle <= 0)
    {
	if (bg_focus.y <= 0)
	    bg_focus.y = 4400;
	else
	    bg_focus.y -= 1;
	cycle = 100;
    }
}
