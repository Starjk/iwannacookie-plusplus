#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include "gameengine.hh"
#include "player.hh"

Player::Player(int	hp,
	       int	remaining_life,
	       int	actual_speed)
{
    health = hp;
    life = remaining_life;
    speed = actual_speed;
}

void Player::Init()
{
    spaceship = IMG_Load("media/img/red_ship.png");
    ship_rect.x = 380;
    ship_rect.y = 274;
    ship_rect.w = 39;
    ship_rect.h = 52;

    frequency = 100;

    std::cout << "Player Init" << std::endl;
}

void Player::Cleanup()
{
    SDL_FreeSurface(spaceship);
    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	firepower[i]->Cleanup();

    std::cout << "Player Cleanup" << std::endl;
}

void Player::MoveUp()
{
    ship_rect.y -= speed;
}

void Player::MoveDown()
{
    ship_rect.y += speed;
}

void Player::MoveLeft()
{
    ship_rect.x -= speed * 3;
}

void Player::MoveRight()
{
    ship_rect.x += speed * 3;
}

void Player::NewShot(bool	is_foe)
{
    // spacing out the shots
    frequency -= 5;
    if (frequency <= 0)
    {

	Weaponery *shot = new Weaponery(firetype, 50, 5, is_foe);
	shot->Init(ship_rect);
	shot->SetMotion();
	firepower.push_back(shot);

	std::cout << "Player Shoot: Shot!" << std::endl;

	frequency = 100;
    }
}

void Player::HandleEvents()
{
    if (health <= 0)
	std::cout << "Boom. Out." << std::endl;
}

void Player::Update()
{

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
    {
	if (firepower[i]->GetMotion())
	{
	    firepower[i]->Update();
	    firepower[i]->HandlePhysics();
	}
    }

    frequency--;
}

void Player::Draw(CGameEngine	*game)
{
    if (KeepAlive())
	SDL_BlitSurface(spaceship, NULL, game->screen, &ship_rect);

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	if (firepower[i]->GetMotion())
	    firepower[i]->Draw(game);
}

void Player::TakesDamages(int	value)
{
    health -= value;
    if (health <= 0)
	std::cout << "Argh! I'm Dead!" << std::endl;
}

void Player::HandleCollisions(Ship	*ship)
{
    // FIXME: still coding
    ship = ship;
}

void Player::HandleShooting(std::vector<Foe*>	foes)
{
    // for all player's shot, check all enemies for C
    for (unsigned i = 0, pshots = firepower.size(); i < pshots; i++)
	for (unsigned j = 0, size = foes.size(); j < size; j++)
	    if (PhysicEngine::Collide(firepower[i]->getRect(),
				      foes[j]->getRect()))
	    {
		foes[j]->TakesDamages(firepower[i]->getDamages());
		firepower[i]->EndMotion();
	    }

    // FIXME: redo vector after a pass to REALLY cleanup the mess
}
