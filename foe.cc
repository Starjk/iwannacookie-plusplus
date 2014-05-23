#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh"
#include "foe.hh"

Foe::Foe(int	type)
{
    if ((type > 0) && (type <= FOE_TYPE_THRESHOLD_1))
    {
	health = 55;
	speed = 2;
	firetype = 1;
	point = 100;
    }
    else if (type <= FOE_TYPE_THRESHOLD_2)
    {
	health = 250;
	speed = 1;
	firetype = 1;
	point = 250;
    }
    else if (type <= FOE_TYPE_THRESHOLD_3)
    {
	health = 150;
	speed = 2;
	firetype = 2;
	point = 375;
    }
    else if (type <= FOE_TYPE_THRESHOLD_4)
    {
	health = 500;
	speed = 3;
	firetype = 1;
	point = 1500;
    }
    foe_type = type;
    EndExistence();
}

void	FirstThreshold(int	foe_type, SDL_Rect	*ship_rect)
{
    if ((foe_type > 0) && (foe_type <= FOE_TYPE_THRESHOLD_1))
    {
	ship_rect->w = 45;
	ship_rect->h = 57;

	switch (foe_type) {
	case (FOE_TYPE_THRESHOLD_1-4):
	    ship_rect->x = 180;
	    ship_rect->y = 74;
	    break;
	case (FOE_TYPE_THRESHOLD_1-3):
	    ship_rect->x = 680;
	    ship_rect->y = 49;
	    break;
	case (FOE_TYPE_THRESHOLD_1-2):
	    ship_rect->x = 75;
	    ship_rect->y = 0;
	    break;
	case (FOE_TYPE_THRESHOLD_1-1):
	    ship_rect->x = 600;
	    ship_rect->y = 25;
	    break;
	default:
	    ship_rect->x = 375;
	    ship_rect->y = 0;
	    break;
	}
    }
}

void	SecondThreshold(int	foe_type, SDL_Rect	*ship_rect)
{
    if (foe_type <= FOE_TYPE_THRESHOLD_2)
    {
	ship_rect->w = 60;
	ship_rect->h = 51;

	switch (foe_type) {
	case (FOE_TYPE_THRESHOLD_2-4):
	    ship_rect->x = 75;
	    ship_rect->y = 25;
	    break;
	case (FOE_TYPE_THRESHOLD_2-3):
	    ship_rect->x = 750;
	    ship_rect->y = 49;
	    break;
	case (FOE_TYPE_THRESHOLD_2-2):
	    ship_rect->x = 75;
	    ship_rect->y = 0;
	    break;
	case (FOE_TYPE_THRESHOLD_2-1):
	    ship_rect->x = 600;
	    ship_rect->y = 25;
	    break;
	default:
	    ship_rect->x = 375;
	    ship_rect->y = 0;
	    break;
	}
    }
}

void	ThirdThreshold(int	foe_type, SDL_Rect	*ship_rect)
{
    if (foe_type <= FOE_TYPE_THRESHOLD_3)
    {
	ship_rect->w = 47;
	ship_rect->h = 49;

	switch (foe_type) {
	case (FOE_TYPE_THRESHOLD_3-4):
	    ship_rect->x = 75;
	    ship_rect->y = 25;
	    break;
	case (FOE_TYPE_THRESHOLD_3-3):
	    ship_rect->x = 750;
	    ship_rect->y = 49;
	    break;
	case (FOE_TYPE_THRESHOLD_3-2):
	    ship_rect->x = 75;
	    ship_rect->y = 0;
	    break;
	case (FOE_TYPE_THRESHOLD_3-1):
	    ship_rect->x = 600;
	    ship_rect->y = 25;
	    break;
	default:
	    ship_rect->x = 375;
	    ship_rect->y = 0;
	    break;
	}
    }
}

void	FourthThreshold(int	foe_type, SDL_Rect	*ship_rect)
{
    // FIXME: still coding
    foe_type = foe_type;
    ship_rect = ship_rect;

    std::cout << "new type of foes: another new ship! "
	      << std::endl;
}

void Foe::Init()
{
    // FIXME: add private functions to manage all FoeType set
    if ((foe_type > 0) && (foe_type <= FOE_TYPE_THRESHOLD_1))
	FirstThreshold(foe_type, &ship_rect);
    else if (foe_type <= FOE_TYPE_THRESHOLD_2)
	SecondThreshold(foe_type, &ship_rect);
    else if (foe_type <= FOE_TYPE_THRESHOLD_3)
	ThirdThreshold(foe_type, &ship_rect);
    else if (foe_type <= FOE_TYPE_THRESHOLD_4)
	FourthThreshold(foe_type, &ship_rect);
    else
	// FIXME: are bosses negative foe_type value?
	std::cout << "Boss are negative value?" << std::endl;

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
    switch (foe_type) {
    case 1:
	MoveRight();
	MoveDown();
	break;
    case 2:
	MoveLeft();
	break;
    case 3:
	MoveDownRt();
	break;
    case 4:
	MoveDownLt();
	break;
    default:
	MoveDown();
	break;
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
	    Weaponry *shot = NULL;

	    // FIXME: handle every type of shots for Foe
	    if ((foe_type > 0) && (foe_type <= FOE_TYPE_THRESHOLD_2))
	    {
		shot = new Weaponry(firetype, true, 'r');
		shot->Init(ship_rect);
		shot->StartMotion();
		shots->push_back(shot);
		shot = new Weaponry(firetype, true, 'l');
	    }
	    else if (foe_type <= FOE_TYPE_THRESHOLD_3)
	    {
		shot = new Weaponry(firetype, true, 'c');
	    }
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

    if (PhysicEngine::OffScreen(this->getRect()))
	this->EndExistence();
}

void Foe::Draw(GameEngine	*game)
{
    if (this->DoesExists())
    {
	if ((ship_rect.x < 0) || (ship_rect.y < 0))
	{
	    // Copy position X&Y to circumvent BlitSurface
	    SDL_Rect tp;
	    tp.x = ship_rect.x;
	    tp.y = ship_rect.y;
	    SDL_BlitSurface(game->GraEng->GetFoe(foe_type),
			    NULL, game->screen, &tp);
	}
	else
	{
	    SDL_BlitSurface(game->GraEng->GetFoe(foe_type),
			    NULL, game->screen, &ship_rect);
	}
    }
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
