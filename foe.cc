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
    firetype = 1;
    foe_type = 1;	// TODO: include moar enemy types
    point = 100;	// TODO: include moar enemy types
    this->EndExistence();
}

void Foe::Init()
{
    ship_rect.x = 180;
    ship_rect.y = 74;
    ship_rect.w = 45;
    ship_rect.h = 57;

    if (foe_type == 2)
    {
	ship_rect.x += 500;
	ship_rect.y -= 25;
    }

    frequency = FOE_SHOT_FREQ;
    this->StartExistence();

    std::cout << "Foe Init" << std::endl;
}

void Foe::Cleanup()
{
    std::cout << "Foe Cleanup" << std::endl;
}

void Foe::Mobility(/* Ship *ship */)
{
    if (foe_type == 1)
    {
	MoveRight();
	MoveDown();
    }
    else if (foe_type == 2)
    {
	MoveLeft();
    }
}

void Foe::Aggression(Ship *ship, std::vector<Weaponry*> *shots)
{
    if ((ship->DoesExists()) &&
	(abs(ship->getRect()->x - ship_rect.x) < FOE_SHOT_DISTANCE))
    {
	// spacing out the shots
	frequency -= 5;
	if (frequency <= 0)
	{
	    Weaponry *shot = new Weaponry(firetype, 50, 5, true);
	    shot->Init(ship_rect);
	    shot->StartMotion();
	    shots->push_back(shot);

	    std::cout << "Foe Shoot: Shot!" << std::endl;

	    frequency = FOE_SHOT_FREQ;
	}
    }
}

void Foe::HandleEvents()
{
    if (health <= 0)
    {
	this->EndExistence();
	std::cout << "Boom. Out." << std::endl;
    }
}

void Foe::Update()
{
    frequency--;

    // FIXME: check if rect x and y are/should be negative or not
    if (PhysicEngine::OffScreen(this->getRect()))
	this->EndExistence();
}

void Foe::Draw(GameEngine	*game)
{
    if (this->DoesExists())
	SDL_BlitSurface(game->GraEng->GetFoe(foe_type),
			NULL, game->screen, &ship_rect);
}

unsigned Foe::TakesDamages(int	value)
{
    health -= value;
    if (health <= 0)
    {
	this->EndExistence();
        return (this->getPoint());
    }
    return 0;
}

void Foe::HandleCollisions(Ship		*ship)
{
    // FIXME: still coding
    ship = ship;
}
