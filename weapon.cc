#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "weapon.hh"

Weaponery::Weaponery(int	type,
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

void Weaponery::Init(SDL_Rect	ship_rect)
{
    if (is_enemys)
	shoot = IMG_Load("media/img/fire_red.png");
    else
	shoot = SDL_LoadBMP("media/img/fire_blue.bmp");

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

void Weaponery::Cleanup()
{
    SDL_FreeSurface(shoot);

    std::cout << "Shoot Cleanup" << std::endl;
}

void Weaponery::SetMotion()
{
    motion = true;
}

bool Weaponery::GetMotion()
{
    return motion;
}

void Weaponery::EndMotion()
{
    motion = false;
}

void Weaponery::HandlePhysics()
{
    if ((motion) &&
	((fire_rect.y <= 0) || (fire_rect.y >= HEIGHT)))
	EndMotion();
}

void Weaponery::Update()
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

void Weaponery::Draw(CGameEngine	*game)
{
    if (motion)
	SDL_BlitSurface(shoot, NULL, game->screen, &fire_rect);
}
