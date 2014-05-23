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
    firetype = 1;
    EndExistence();
}

void Player::Init()
{
    ship_rect.x = 380;
    ship_rect.y = 274;
    ship_rect.w = 39;
    ship_rect.h = 52;

    frequency = SHOT_FREQ;

    StartExistence();
}

void Player::Cleanup()
{
    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	if (firepower[i]->GetMotion())
	    firepower[i]->Cleanup();
}

void Player::HandleEvents()
{
    Uint8	*keys = SDL_GetKeyState(NULL);

    if (keys[SDLK_UP])
	MoveUp();
    if (keys[SDLK_DOWN])
	MoveDown();
    if (keys[SDLK_LEFT])
	MoveLeft();
    if (keys[SDLK_RIGHT])
	MoveRight();
    if (keys[SDLK_SPACE])
	NewShot();

    // test purpose
    if (keys[SDLK_k])
    {
	if (firetype < 6)
	    firetype++;
    }
    if (keys[SDLK_l])
    {
	if (firetype > 0)
	    firetype--;
    }
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

    if (this->Sanitize())
    {
	this->Cleanup();
	return;
    }
    if (health <= 0)
    {
	this->EndExistence();
	life--;
    }
    if (!DoesExists())
    {
	this->Sanitize();
	if (this->getLife() > 0)
	    std::cout << "Regenerate Player routine" << std::endl;
    }

    frequency--;
}

void Player::Draw(GameEngine	*game)
{
    if (KeepAlive() && DoesExists())
	SDL_BlitSurface(game->GraEng->GetPlayer(),
			NULL, game->screen, &ship_rect);

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
	if (firepower[i]->GetMotion())
	    firepower[i]->Draw(game);
}

bool Player::Sanitize()
{
    int	nexts = this->GetStationary();

    while (nexts > 0)
    {
	firepower[nexts]->Cleanup();
	firepower.erase(firepower.begin() + nexts);
	nexts = this->GetStationary();
    }

    return (NoMoreShots() &&
	    (!this->KeepAlive()) && (this->getLife() <= 0));
    // aka NoMoreShots and GameOver/LostGame();
}

int Player::GetStationary()
{
    int	i = 0, size = firepower.size();

    while ((i < size) && (firepower[i]->GetMotion()))
	i++;

    if (i >= size)
	return (-1);
    return i;
}

// NOTE: I am the exact same function as in class Party
bool Player::NoMoreShots()
{
    bool	shots = false;	// assume there are no shots

    for (unsigned i = 0, size = firepower.size(); i < size; i++)
    {
	shots = firepower[i]->GetMotion();	// shot exists
	if (shots)
	    break;
    }

    return (!shots);
}

void Player::MoveUp()
{
    if (ship_rect.y - speed > 0)
	ship_rect.y -= speed;
}

void Player::MoveDown()
{
    if (ship_rect.y + ship_rect.h + (speed*2) < HEIGHT)
	ship_rect.y += speed*2;
}

void Player::MoveLeft()
{
    if (ship_rect.x - (speed*3) > 0)
	ship_rect.x -= speed * 3;
}

void Player::MoveRight()
{
    if (ship_rect.x + ship_rect.w + (speed*3) < WIDTH)
	ship_rect.x += speed * 3;
}

void Player::NewShotByType(int	firetype)
{
    Weaponry *shot = NULL;

    if (firetype <= SHOT_TYPE_THRESHOLD_1)
	shot = new Weaponry(1, false, 'c');
    else if (firetype <= SHOT_TYPE_THRESHOLD_2)
    {
	shot = new Weaponry(1, false, 'r');
	shot->Init(ship_rect);
	shot->StartMotion();
	firepower.push_back(shot);
	shot = new Weaponry(1, false, 'l');
    }
    else if (firetype <= SHOT_TYPE_THRESHOLD_3)
    {
	shot = new Weaponry(1, false, 'r');
	shot->Init(ship_rect);
	shot->StartMotion();
	firepower.push_back(shot);
	shot = new Weaponry(1, false, 'c');
	shot->Init(ship_rect);
	shot->StartMotion();
	firepower.push_back(shot);
	shot = new Weaponry(1, false, 'l');
    }
    else if (firetype <= SHOT_TYPE_THRESHOLD_4)
    { // 'b' && 'd' && 'p' && 'q'
	shot = new Weaponry(3, false, 'r');
	shot->Init(ship_rect);
	shot->StartMotion();
	firepower.push_back(shot);
	shot = new Weaponry(3, false, 'l');
    }
    else if (firetype <= SHOT_TYPE_THRESHOLD_5)
    { // 'b' && 'd' && 'p' && 'q' && 'c'
	shot = new Weaponry(1, false, 'l');
    }
    else if (firetype <= SHOT_TYPE_THRESHOLD_6)
    { // 'b' && 'd' && 'p' && 'q' && 'a' && 'e'
	shot = new Weaponry(1, false, 'r');
    }
    else
	shot = new Weaponry(5, false, 'c');

    // At least one shot is generated
    shot->Init(ship_rect);
    shot->StartMotion();
    firepower.push_back(shot);
}

void Player::NewShot()
{
    // spacing out the shots
    frequency -= 5;
    if ((frequency <= 0) && this->KeepAlive())
    {
	// FIXME: handle every type of shots for Player
	if (firetype > 0)
	    this->NewShotByType(firetype);

	std::cout << "Player Shoot: Shot!" << std::endl;

	frequency = SHOT_FREQ;
    }
}

void Player::TakesDamages(int	value)
{
    health -= value;
    if ((health <= 0) && (this->DoesExists()))
	std::cout << "Argh! I'm Dead!" << std::endl;
}

unsigned Player::HandleShooting(std::vector<Foe*>	foes)
{
    unsigned score = 0;

    // for all player's shot, check all enemies for C
    for (unsigned i = 0, pshots = firepower.size(); i < pshots; i++)
	for (unsigned j = 0, size = foes.size(); j < size; j++)
	    if ((firepower[i]->GetMotion() && foes[j]->KeepAlive()) &&
		(PhysicEngine::Collide(firepower[i]->getRect(),
				       foes[j]->getRect())))
	    {
		score += foes[j]->TakesDamages(
		    firepower[i]->getDamages());
		firepower[i]->EndMotion();
	    }

    return score;
}
