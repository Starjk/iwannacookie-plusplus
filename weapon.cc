#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "weapon.hh"

Weaponry::Weaponry(int	type, bool	is_foe, char posx)
{
    firetype = type;
    position_x = posx;
    is_enemys = is_foe;
    // FIXME: manage dmg and speed in Constructor
    this->InitSpec();

    motion = false;
}

void Weaponry::InitSpec()
{

    // Weapon Characteristics
    if (is_enemys)
    {
	switch (firetype) {
	case 1:
	    damages = 20;
	    speed = 4;
	    break;
	case 2:
	    damages = 50;
	    speed = 6;
	    break;
	default:
	    damages = 100;
	    speed = 8;
	    break;
	}

    }
    else
    {
	switch (firetype) {
	case 1:
	    damages = 50;
	    speed = 5;
	    break;
	case 2:
	    damages = 60;
	    speed = 7;
	    break;
	case 3:
	    damages = 75;
	    speed = 9;
	    break;
	case 4:
	    damages = 100;
	    speed = 10;
	    break;
	default:
	    damages = 250;
	    speed = 14;
	    break;
	}

    }
}

void Weaponry::InitPosition(SDL_Rect ship_rect)
{
    // MANAGE X
    if (position_x == 'r')
	fire_rect.x = ship_rect.x + (ship_rect.w / 8) - (fire_rect.w/2);
    else if (position_x == 'l')
	fire_rect.x = ship_rect.x + (ship_rect.w*7/8) - (fire_rect.w/2);
    else // if ((position_x == 'c') and error case)
	fire_rect.x = ship_rect.x + (ship_rect.w/2) - (fire_rect.w/2);

    // MANAGE Y
    if (is_enemys)
    {
	fire_rect.y = ship_rect.y + ship_rect.h;
	if (position_x != 'c')
	    fire_rect.y -= fire_rect.h * 8 / 9;
    }
    else
    {
	fire_rect.y = ship_rect.y - fire_rect.h;
	if (position_x != 'c')
	    fire_rect.y += fire_rect.h * 8 / 9;
    }

    // FIXME: handle different origin of shots, given the type (sides?)
}

void Weaponry::Init(SDL_Rect	ship_rect)
{
    // FIXME: only one type of shots red/blue, no variance for boss?
    fire_rect.w = 8;
    fire_rect.h = 18;

    // FIXME: manage position of each type of posx in Init
    this->InitPosition(ship_rect);

    cycle = 100;
    clockwork = 5;
}

void Weaponry::Cleanup()
{
    std::cout << "Shoot Cleanup" << std::endl;
}

void Weaponry::HandlePhysics()
{
    // FIXME: use PhysicEngine to handle out of screen for shots
    if ((motion) && (PhysicEngine::LeaveScreen(&fire_rect)))
//	((fire_rect.y <= 0) || (fire_rect.y >= HEIGHT)))
	this->EndMotion();
}

void Weaponry::Update()
{
    cycle -= clockwork;
    if ((motion) && (cycle <= 0))
    {
	// FIXME: if (guided)... pseudo-code below
	/**
	   if ((guided) && (is_enemy) && (fire_rect.y <= player_rect.y))
	     if (ship_rect.x < player_rect.x)
	       fire_rect.x += 5;
	     else if (ship_rect.x > player_rect.x)
	       fire_rect.x -= 5;
	 */
	if (is_enemys)
	    fire_rect.y += speed;
	else
	    fire_rect.y -= speed;
	cycle = 100;
    }
}

void Weaponry::Draw(GameEngine	*game)
{
    if (motion)
    {
	SDL_Rect tp;
	tp.x = fire_rect.x;
	tp.y = fire_rect.y;
	if (is_enemys)
	    SDL_BlitSurface(game->GraEng->GetFoeFire(firetype),
			    NULL, game->screen, &tp);
	else
	    SDL_BlitSurface(game->GraEng->GetAllyFire(firetype),
			    NULL, game->screen, &tp);
    }
}
