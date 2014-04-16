
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "gamestate.hh"
#include "firststate.hh"
#include "pausestate.hh"

FirstState FirstState::m_FirstState;

void	FirstState::Init()
{
    SDL_Surface	*temp = IMG_Load("media/img/background_1.jpg");

    background = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    std::cout << "FirstState Init" << std::endl;

    bg_focus.x = 0;
    bg_focus.y = 4400;
    bg_focus.w = WIDTH;
    bg_focus.h = HEIGHT;

    cycle = BACKGROUND_SCROLL;
    tick = 5;

    player.Init();
    armada.Init(1);

    score = 0;
}

void	FirstState::Cleanup()
{
    SDL_FreeSurface(background);

    std::cout << "FirstState Cleanup" << std::endl;

    // FIXME: if not cleanable, do something (player)
    player.Cleanup();
    // FIXME: if not cleanable, do something (armada)
    armada.Cleanup();
    // FIXME: when called, massive SEGFAULT & should free more stuff
}

void	FirstState::Pause()
{
    std::cout << "FirstState Pause" << std::endl;
}

void	FirstState::Resume()
{
    std::cout << "FirstState Resume" << std::endl;
}

void	FirstState::HandleEvents(CGameEngine	*game)
{
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

    }

    if (cycle <= tick)
	player.HandleEvents();

    // if ((!player.KeepAlive() && (!player.DoesExists())) || GameOver())
    // 	game->PopState();	FIXME: Bad Cleanup()?
}

void	FirstState::Update(CGameEngine	*game)
{
    // FIXME: compile flags
    game = game;

    ScrollBackground();

    // armada.HandleCollisions(&player);
    player.Update();
    armada.Update(&player);
}

void	FirstState::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(background, &bg_focus, game->screen, NULL);

    player.Draw(game);
    armada.Draw(game);

    // Always last function
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void	FirstState::ScrollBackground()
{
    cycle -= tick;
    if (cycle <= 0)
    {
	if (bg_focus.y <= 0)
	    bg_focus.y = 4400;
	else
	    bg_focus.y -= 1;
	cycle = BACKGROUND_SCROLL;
    }
}
