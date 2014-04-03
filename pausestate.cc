
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "gamestate.hh"
#include "pausestate.hh"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{
    SDL_Surface *temp = IMG_Load("media/img/noir.jpg");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

//     Uint32 rmask, gmask, bmask, amask;
// #if SDL_BYTEORDER == SDL_BIG_ENDIAN
//     rmask = 0xff000000;
//     gmask = 0x00ff0000;
//     bmask = 0x0000ff00;
//     amask = 0x000000ff;
// #else
//     rmask = 0x000000ff;
//     gmask = 0x0000ff00;
//     bmask = 0x00ff0000;
//     amask = 0x00000000;
// #endif

//     create the background surface like the background with alpha
//     background = SDL_CreateRGBSurface(
//    SDL_SRCALPHA, WIDTH, HEIGHT, 32, rmask, gmask, bmask, amask);

    // fill the background surface with black
//     SDL_FillRect (background, NULL, SDL_MapRGB (background->format,
//    0, 0, 0));

//     SDL_SetAlpha(background, SDL_SRCALPHA, OPACITY);

    std::cout << "CPauseState Init" << std::endl;
}

void CPauseState::Cleanup()
{
    SDL_FreeSurface(background);

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
