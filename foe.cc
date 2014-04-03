#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "foe.hh"

Foe::Foe(int	hp,
	 int	actual_speed)
{
    health = hp;
    speed = actual_speed;
    foe_type = 1;	// FIXME: include moar enemy types
    point = 100;	// FIXME: include moar enemy types
}

void Foe::Init()
{
    if (foe_type == 1)
	spaceship = IMG_Load("media/img/ship_e1.png");

    ship_rect.x = 180;
    ship_rect.y = 74;
    ship_rect.w = 45;
    ship_rect.h = 57;

    frequency = SHOT_SPEED;

    std::cout << "Foe Init" << std::endl;
}

void Foe::Cleanup()
{
    SDL_FreeSurface(spaceship);
    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	firepower[i]->Cleanup();

    std::cout << "Foe Cleanup" << std::endl;
}

// FIXME: physic engine not implemented/able?
//     => ShiftUp(class Ship);

void Foe::MoveUp()
{
    ship_rect.y -= speed;
}

void Foe::MoveDown()
{
    ship_rect.y += speed;
}

void Foe::MoveLeft()
{
    ship_rect.x -= speed * 3;
}

void Foe::MoveRight()
{
    ship_rect.x += speed * 3;
}

void Foe::NewShot()
{
    frequency -= 5;
    if (frequency <= 0)
    {

	Weaponery	*shot = new Weaponery(firetype, 50, 5);
	shot->Init(ship_rect);
	shot->SetMotion();
	firepower.push_back(shot);

	std::cout << "Foe Shoot: Shot!" << std::endl;

	frequency = SHOT_SPEED;
    }
}

void Foe::HandleEvents()
{
    if (health <= 0)
	std::cout << "Boom. Out." << std::endl;
}

void Foe::Update()
{

    MoveRight();
    MoveDown();

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
    {
	if (!firepower[i]->GetMotion())
	{
	    firepower[i]->Cleanup();
	    firepower.erase(firepower.begin() + i);
	}
	firepower[i]->Update();
	firepower[i]->HandlePhysics();
    }

    frequency--;
}

void Foe::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(spaceship, NULL, game->screen, &ship_rect);

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	firepower[i]->Draw(game);
}

void Foe::TakesDamages(int	value)
{
    health -= value;
    if (health <= 0)
	std::cout << "Die, rebel scum." << std::endl;
}

void Foe::HandleCollisions(Ship		*ship)
{
    // FIXME: still coding
    ship = ship;
}
