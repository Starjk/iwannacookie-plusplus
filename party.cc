
#include <SDL.h>
#include <SDL_image.h>

#include "party.hh"

Party::Party(int	preset)
{
    partytype = preset / 100;
    hourglass = (preset / 10) % 10 * 1000;
    partysize = preset % 10;
    initsize = partysize;
}

Party::Party(int	inter, int	size)
{
    partytype = 1;
    partysize = size;
    initsize = size;
    hourglass = inter;
}

Party::Party(int	type, int	inter, int	size)
{
    partytype = type;
    partysize = size;
    initsize = size;
    hourglass = inter;
}

void	Party::Init()
{
    interval = hourglass;
    mob_control = MOB_CONTROL;
    tick = 5;
    score = 0;
}

void	Party::Cleanup()
{
    while (!party.empty())
	party.pop_back();
    party.clear();

    while (!fireworks.empty())
	fireworks.pop_back();
    fireworks.clear();
}

void	Party::HandleCollisions(Player	*player)
{
    for (unsigned i = 0, size = party.size(); i < size; i++)
	party[i]->HandleCollisions(player);
        // HandleCollisions: does any of my shots touch target rect?
	// if so, call Player->TakesDamages(value);

    player->HandleShooting(party);
    // for every foes, does any of my shots touch foe rect?
    // if so, call Foe/Boss->TakesDamages(value);
}

void	Party::Update(Player	*player)
{
    interval--;
    if ((interval <= 0) && (0 < partysize))
    {
	Foe	*foe = new Foe(partytype);
	foe->Init();
	party.push_back(foe);
	partysize--;

	std::cout << "New Foe?" << std::endl;

	interval = hourglass;
    }

    if (partysize < initsize)
    {
    // for (unsigned i = 0, size = party.size(); i < size; i++)
    // 	party[i]->Update();
	this->MobControl(player);

    // for (unsigned i = 0, size = fireworks.size(); i < size;i++)
    // 	fireworks[i]->Update();
	this->FireworksControl(player);
	if (this->Sanitize())
	    this->Cleanup();
    }
}

void	Party::Draw(CGameEngine	*game)
{
    for (unsigned i = 0, size = party.size(); i < size; i++)
	// draw if Exists, but vector is already sanitized
	party[i]->Draw(game);
    for (unsigned i = 0, size = fireworks.size(); i < size; i++)
	// draw if In Motion, but vector is already sanitized
	fireworks[i]->Draw(game);
}

bool	Party::Sanitize()
{
    int	nextf = this->GetNonExistent();
    int	nexts = this->GetStationary();

    while (nextf > 0)
    {
	party[nextf]->Cleanup();
	party.erase(party.begin() + nextf);
	nextf = this->GetNonExistent();
    }

    while (nexts > 0)
    {
	fireworks[nexts]->Cleanup();
	fireworks.erase(fireworks.begin() + nexts);
	nexts = this->GetStationary();
    }

    return (this->PartyOut());
}

int	Party::GetNonExistent()
{
    int	i = 0, size = party.size();

    while ((i < size) && (party[i]->DoesExists()))
	i++;

    if (i >= size)
	return (-1);
    return i;
}

int	Party::GetStationary(/* vector of Weaponry? would need the include */)
{
    int	i = 0, size = fireworks.size();

    while ((i < size) && (fireworks[i]->GetMotion()))
	i++;

    if (i >= size)
	return (-1);
    return i;
}

bool	Party::NoMoreFoes()
{
    bool	foes = false;	// assume there are no foes

    for (unsigned i = 0, size = party.size(); i < size; i++)
    {
	foes = party[i]->DoesExists();	// foe exists
	if (foes)
	    break;
    }

    return (!foes);
}

bool	Party::NoMoreShots()
{
    bool	shots = false;	// assume there are no shots

    for (unsigned i = 0, size = fireworks.size(); i < size; i++)
    {
	shots = fireworks[i]->GetMotion();	// shot exists
	if (shots)
	    break;
    }

    return (!shots);
}

void	Party::MobControl(Player	*player)
{
    mob_control -= tick;
    if (mob_control <= 1)
    {
	for (unsigned i = 0, size = party.size();
	     i < size; i++)
	    if (party[i]->KeepAlive() &&
		party[i]->DoesExists())
	    {
		party[i]->Mobility(/* toward &player? */);
		party[i]->Aggression(player, &fireworks); // player?
		party[i]->Update();
	    }
	    else if (party[i]->DoesExists())
	    { // meaning, party[i]->health <= 0
		score += party[i]->getPoint();
		party[i]->EndExistence();
	    }
	// if out of screen, doesn't exist already

	mob_control = MOB_CONTROL;
    }
}

void	Party::FireworksControl(Player	*player)
{
    for (unsigned i = 0, size = fireworks.size(); i < size; i++)
    {
	if (fireworks[i]->GetMotion())
	{
	    fireworks[i]->Update();
	    fireworks[i]->HandlePhysics();
	}

	if (PhysicEngine::Collide(fireworks[i]->getRect(),
				  player->getRect()))
	{
	    player->TakesDamages(fireworks[i]->getDamages());
	    fireworks[i]->EndMotion();
	}
    }
}

bool	Party::PartyOut()
{
    return ((partysize <= 0) &&
	    (this->NoMoreFoes() && this->NoMoreShots()));
}
