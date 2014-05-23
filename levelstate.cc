
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "hud.hh"
#include "gamestate.hh"
#include "levelstate.hh"
#include "menustate.hh"
#include "pausestate.hh"

void	LevelState::Init()
{
    bg_focus.x = 0;
    bg_focus.y = 4400;
    bg_focus.w = WIDTH;
    bg_focus.h = HEIGHT;

    cycle = BACKGROUND_SCROLL;
    tick = 5;

    player.Init();
    armada.Init(level);

    std::cout << "LevelState Init" << std::endl;
}

void	LevelState::Cleanup()
{
    std::cout << "LevelState Cleanup" << std::endl;

    player.Cleanup();
    armada.Cleanup();
}

void	LevelState::Pause()
{
    std::cout << "LevelState Pause" << std::endl;
}

void	LevelState::Resume()
{
    std::cout << "LevelState Resume" << std::endl;
}

void	LevelState::HandleEvents(GameEngine	*game)
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

    // FIXME: MY LIVES HAVE VALUE, I'M NOT GONNA TAKE IT ANYMORE
    if ((!player.KeepAlive() && (!player.DoesExists()))/* || GameOver()*/)
    {	// game over
    	game->PopState();
	game->GraEng->Cleanup();
    }
    // else if Boss Defeated
    // {
    // 	game->ChangeState(new LevelState(level + 1, score));
    // }
}

void	LevelState::Update(GameEngine	*game)
{
    // FIXME: compile flags
    game = game;

    ScrollBackground();

    player.Update();
    score += armada.Update(&player);
}

void	LevelState::Draw(GameEngine	*game)
{
    SDL_BlitSurface(game->GraEng->GetBackground(),
		    &bg_focus, game->screen, NULL);

    player.Draw(game);
    armada.Draw(game);

    HUD::DisplayHUD(&player, score, game);

    // Always last function
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

void	LevelState::ScrollBackground()
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
