
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include "gameengine.hh"
#include "gamestate.hh"
#include "menustate.hh"
#include "firstpstate.hh"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init()
{
    SDL_Surface	*temp = IMG_Load("media/img/titre.jpg");

    background = SDL_DisplayFormat(temp);

    SDL_FreeSurface(temp);

    // create the fader surface like the background with alpha
    fader = SDL_CreateRGBSurface(SDL_SRCALPHA, background->w, background->h,
				 background->format->BitsPerPixel,
				 background->format->Rmask,
				 background->format->Gmask,
				 background->format->Bmask,
				 background->format->Amask);

    // fill the fader surface with black
    SDL_FillRect (fader, NULL, SDL_MapRGB (background->format, 0, 0, 0));

    // start off opaque
    alpha = 255;

    SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);

    printf("CMenuState Init\n");
}

void CMenuState::Cleanup()
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(fader);

    printf("CMenuState Cleanup\n");
}

void CMenuState::Pause()
{
    printf("CMenuState Pause\n");
}

void CMenuState::Resume()
{
    printf("CMenuState Resume\n");
}

void CMenuState::HandleEvents(CGameEngine	*game)
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT:
	    game->Quit();
	    break;

	case SDL_KEYDOWN:
	    switch (event.key.keysym.sym) {
	    case SDLK_RETURN:
		game->ChangeState(CFirstPState::Instance());
		break;

	    case SDLK_ESCAPE:
		game->Quit();
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

void CMenuState::Update(CGameEngine		*game)
{
    // FIXME: compile
    game = game;

    alpha--;

    if (alpha < 0)
	alpha = 0;

    SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);
}

void CMenuState::Draw(CGameEngine		*game)
{
    SDL_BlitSurface(background, NULL, game->screen, NULL);

    // No need to blit if it's a transparent surface
    if (alpha != 0)
	SDL_BlitSurface(fader, NULL, game->screen, NULL);

    SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}