#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "weapon.hh"

Weaponry::Weaponry(int	type,
		   int	dmg,
		   int	velocity,
		   bool	is_foe)
{
    // FIXME: add switch for firetype and give out appropriate values
    firetype = type;
    damages = dmg;
    speed = velocity;

    motion = false;
    is_enemys = is_foe;
}

void Weaponry::Init(SDL_Rect	ship_rect)
{
    fire_rect.w = 8;
    fire_rect.h = 18;
    fire_rect.x = ship_rect.x + (ship_rect.w/2) - (fire_rect.w/2);

    if (is_enemys)
	fire_rect.y = ship_rect.y + ship_rect.h;
    else
	fire_rect.y = ship_rect.y;

    cycle = 100;
    clockwork = 5;

    std::cout << "Shoot Init" << std::endl;
}

void Weaponry::Cleanup()
{
    std::cout << "Shoot Cleanup" << std::endl;
}

void Weaponry::HandlePhysics()
{
    if ((motion) &&
	((fire_rect.y <= 0) || (fire_rect.y >= HEIGHT)))
	this->EndMotion();
}

void Weaponry::Update()
{
    cycle -= clockwork;
    if ((motion) && (cycle <= 0))
    {
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
	if (is_enemys)
	    SDL_BlitSurface(game->GraEng->GetFoeFire(firetype),
			    NULL, game->screen, &fire_rect);
	else
	    SDL_BlitSurface(game->GraEng->GetAllyFire(firetype),
			    NULL, game->screen, &fire_rect);
    }
}
