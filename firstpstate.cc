
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

    cycle = BACKGROUND_SCROLL;
    clockwork = 5;

    player.Init();

    score = 0;
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
	    player.NewShot();
	if (keys[SDLK_g])
	    NewChallenger();

    }

    HandleCollisions();
}

void CFirstPState::NewChallenger()
{

    if (encounters.empty())
	mob_control = MOB_CONTROL;

    Foe	*foe = new Foe(25, 2);
    foe->Init();
    encounters.push_back(foe);
}

void CFirstPState::MobControl()
{
    mob_control -= clockwork;
    if (mob_control <= 1)
    {
	for (unsigned i = 0, size = encounters.size();
	     i < size; i++)
	    if (encounters[i]->KeepAlive())
		encounters[i]->Update();
	    else
	    {
		score += encounters[i]->getPoint();
		// encounters[i]->Cleanup();
		encounters.erase(encounters.begin() + i);
	    }
	mob_control = MOB_CONTROL;
    }
}

void CFirstPState::Update(CGameEngine	*game)
{
    // FIXME: compile flags
    game = game;

    ScrollBackground();
    player.Update();
    MobControl();
}

void CFirstPState::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(background, &bg_focus, game->screen, NULL);
    player.Draw(game);

    for (unsigned i = 0, size = encounters.size(); i < size; i++)
	encounters[i]->Draw(game);

    // Always last function
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
	cycle = BACKGROUND_SCROLL;
    }
}

// if C, shot gets destroyed, target loses HP; targets manage own HP
void	CFirstPState::HandleCollisions()
{
    // FIXME: implemented HandleCollisions for class Ship
    for (unsigned i = 0, size = encounters.size(); i < size; i++)
	encounters[i]->HandleCollisions(&player);
	// HandleCollisions: does any of my shots touch target rect?
	// if so, call Player->TakesDamages(value);

    player.HandleShooting(encounters);
    // for every foes, does any of my shots touch foe rect?
    // if so, call Foe/Boss->TakesDamages(value);
}
