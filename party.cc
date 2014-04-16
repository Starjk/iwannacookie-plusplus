
#include <SDL.h>
#include <SDL_image.h>

#include "party.hh"

Party::Party(int	preset)
{
    partytype = preset / 100;
    hourglass = (preset / 10) % 10;
    partysize = preset % 10;
}

Party::Party(int	inter, int	size)
{
    partytype = 1;
    partysize = size;
    hourglass = inter;
}

Party::Party(int	type, int	inter, int	size)
{
    partytype = type;
    partysize = size;
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
    // FIXME: check working value
    for (unsigned i = 0, size = party.size(); i < size; i++)
	party[i]->Cleanup();
        // delete (party.back());

    while (!party.empty())
	party.pop_back();
    party.clear();
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
	party.push_back(new Foe(partytype));
	partysize--;
	interval = hourglass;
    }

    MobControl(player);
    FireworksControl(player);

    // for (unsigned i = 0, size = party.size(); i < size; i++)
    // 	party[i]->Update();
    // for (unsigned i = 0, size = fireworks.size(); i < size; i++)
    // 	fireworks[i]->Update();
}

void	Party::Draw(CGameEngine	*game)
{
    for (unsigned i = 0, size = party.size(); i < size; i++)
	party[i]->Draw(game);
    for (unsigned i = 0, size = fireworks.size(); i < size; i++)
	fireworks[i]->Draw(game);
}

bool	Party::NoMoreFoes()
{
    return false;
}

bool	Party::NoMoreShots()
{
    return false;
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
		party[i]->ActiveUnit(/* &player */);
		party[i]->Aggression(player, &fireworks);
		party[i]->Update();
	    }
	    else
	    {
		score += party[i]->getPoint();
		party[i]->Cleanup();
		party.clear();
	    }
	// FIXME: redo vector after a pass to REALLY cleanup the mess
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
    // FIXME: redo vector after a pass to REALLY cleanup the mess
}
