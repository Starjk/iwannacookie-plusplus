#include <iostream>
#include "SDL.h"
#include "root.hh"

int	main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    	std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    	return 1;
    }

    /* create window */
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, 0);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    SDL_Quit();

    open_window();

    return 0;
}

int	open_window()
{
    std::cout << "Open a Window" << std::endl;
    return 0;
}
