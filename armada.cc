
#include <SDL.h>
#include <SDL_image.h>

#include "armada.hh"

Armada::Armada(int	lvl, int	inter)
{
    level = lvl;
    hourglass = inter;
}

void	Armada::Init(int	lvl)
{
    level = lvl;
    //FIXME: time between party == time before first party (:/)
    hourglass = 7500;
    interval = hourglass;

    if (level == 1)
    {
	addPreset(42503);	// fourth
	addPreset(33003);	// fourth
	addPreset(12003);
	addPreset(22004);
	addPreset(11006);
	addPreset(21003);

	addPreset(12003);
	addPreset(22004);
	addPreset(11006);
	addPreset(21003);
	addPreset(12003);
	addPreset(22004);
	addPreset(11006);
	addPreset(21003);
    }
    if (level == 2)
    {
	addPreset(12006);
	addPreset(22004);
	addPreset(11006);
    }
}

void	Armada::Cleanup()
{
    while (!armada.empty())
	armada.pop_back();
    armada.clear();
}

unsigned Armada::Update(Player	*player)
{
    if (!this->Defeated())
    {
	unsigned score = 0;
	// First: add new party as defined in Preset at inter.
	interval--;
	if ((interval <= 0) && (!preset.empty()))
	{
	    Party	*newparty = new Party(this->popPreset());
	    newparty->Init();
	    armada.push_back(newparty);

	    std::cout << "New Party?" << std::endl;
	    interval = hourglass;
	}

	for (unsigned i = 0, size = armada.size(); i < size; i++)
	{
	    // Second: HandleCollisions with Player
	    score += armada[i]->HandleCollisions(player);
	    // Third: Update() all parties mvt/shooting
	    armada[i]->Update(player);
	}

	// Fourth: Clean vector of Party when parties are defeated
	if (this->Sanitize())
	    this->Cleanup();

	return score;
    }
    else
    {
        CallBoss(); // but once tho or... wotever
    }
    return 0;
}

void	Armada::Draw(GameEngine	*game)
{
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	armada[i]->Draw(game);
}

bool	Armada::Sanitize()
{
    int	nexto = this->GetPartyOuted();

    while (nexto > 0)
    {
	armada[nexto]->Cleanup();
	armada.erase(armada.begin() + nexto);
	nexto = this->GetPartyOuted();
    }

    return (this->Defeated());
}

int	Armada::GetPartyOuted()
{
    int	i = 0, size = armada.size();

    while ((i < size) && (!armada[i]->PartyOut())) // shouldn't exists anymore
	i++;

    if (i >= size)
	return (-1);
    return i;
}

void	Armada::addPreset(int	newPreset)
{
    preset.push_back(newPreset);
}

int	Armada::popPreset()
{
    int tmp = preset.front();
    preset.pop_front();
    return tmp;
}

bool	Armada::Defeated()
{
    return false;
}

void	Armada::CallBoss()
{
    // FIXME: no boss?! This is Sacrilege!
    std::cout << "And there shall be presented thy enemy."
	      << std::endl;
}
