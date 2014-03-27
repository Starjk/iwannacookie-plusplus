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
    has_spawn = true;
}

void Player::Init()
{
    spaceship = IMG_Load("media/img/red_ship.png");
    ship_rect.x = 380;
    ship_rect.y = 274;
    ship_rect.w = 39;
    ship_rect.h = 52;

    std::cout << "Player Init" << std::endl;
}

void Player::Cleanup()
{
    SDL_FreeSurface(spaceship);

    std::cout << "Player Cleanup" << std::endl;
}

void Player::MoveUp()
{
    ship_rect.y -= speed;
    // FIXME: physic engine not implemented/able?
    // FIXME: ShiftUp(&ship_rect);
}

void Player::MoveDown()
{
    ship_rect.y += speed;
}

void Player::MoveLeft()
{
    ship_rect.x -= speed * 2;
}

void Player::MoveRight()
{
    ship_rect.x += speed * 2;
}

void Player::MainWeapon()
{
    std::cout << "Player Shoot: Pew Pew Pew"
	      << std::endl;
}

void Player::HandleEvents()
{
}

void Player::Update()
{
}

void Player::Draw(CGameEngine	*game)
{
    SDL_BlitSurface(spaceship, NULL, game->screen, &ship_rect);
    //SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}

