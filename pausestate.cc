
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "gamestate.hh"
#include "pausestate.hh"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{

//     // Create "empty" surface with alpha property
// #if SDL_BYTEORDER == SDL_BIG_ENDIAN
//     background = SDL_CreateRGBSurface(SDL_SRCALPHA,WIDTH,HEIGHT,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
// #else
//     background = SDL_CreateRGBSurface(SDL_SRCALPHA,WIDTH,HEIGHT,32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
// #endif

//     // Fill with black pixels
//     // SDL_FillRect(background, NULL, SDL_MapRGB(background->format,
//     // 					      0, 0, 0));
//     // Make color "Black" transparent
//     SDL_SetColorKey(background, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 0, 0, 0));

//     alpha = 0;
//     // SDL_SetAlpha(background, SDL_SRCALPHA, alpha);

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

    // if (alpha < 150)
    // {
    // 	alpha += 5;
    // 	SDL_SetAlpha(background, SDL_SRCALPHA, alpha);
    // }

}

void CPauseState::Draw(GameEngine	*game)
{
    SDL_BlitSurface(game->GraEng->GetPauseBG(),
    		    NULL, game->screen, NULL);
    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
