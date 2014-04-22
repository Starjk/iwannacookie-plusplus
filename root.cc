#include "root.hh"
#include "gameengine.hh"
#include "menustate.hh"

int	main(void)
{
    main_loop();

    return 0;
}

int	main_loop(void)
{
    GameEngine	game;

    // initialize the engine
    game.Init("CookieEngine Test v0.1");

    // QFIX: authorize continuous Kpress, yet an unbecoming solution
    if (SDL_EnableKeyRepeat(CUSTOM_REPEAT_DELAY,
			    SDL_DEFAULT_REPEAT_INTERVAL))
    {
	game.Cleanup();
	return 1;
    }

    // load the intro singleton
    game.ChangeState(CMenuState::Instance());

    // main loop
    while (game.Running())
    {
	game.HandleEvents();
	game.Update();
	game.Draw();
    }

    // cleanup the engine
    game.Cleanup();

    return 0;
}
