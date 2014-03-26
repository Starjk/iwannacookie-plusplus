#include "root.hh"
#include "gameengine.hh"
#include "menustate.hh"

int	main(void)
{
    // SDL_Surface		*screen = NULL;

    // if (SDL_Init(SDL_INIT_VIDEO) != 0)
    // {
    // 	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    // 	return 1;
    // }

    // /* create window */
    // screen = SDL_SetVideoMode(640, 480, 0, 0);

    // /* update the screen */
    // SDL_UpdateRect(screen, 0, 0, 0, 0);

    // /* sleep for proof */
    // SDL_Delay(1000);

    // SDL_Quit();

    // std::cout << "This is were it all g..." << std::endl;
    main_loop();

    return 0;
}

int	main_loop(void)
{
    CGameEngine	game;

    // initialize the engine
    game.Init("GameEngine Test v0.1");

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
