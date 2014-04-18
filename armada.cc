
#include <SDL.h>
#include <SDL_image.h>

#include "armada.hh"
//#include "player.hh"
//#include "foe.hh"

Armada::Armada(int	lvl, int	inter)
{
    level = lvl;
    hourglass = inter;
}

void	Armada::Init(int	lvl)
{
    level = lvl;
    //FIXME: time between party, but also time before first party :/
    hourglass = 10000;
    interval = hourglass;

    if (level == 1)
    {
	addPreset(123);
	addPreset(224);
    }
    if (level == 2)
    {
	addPreset(116);
	addPreset(224);
    }
}

void	Armada::Cleanup()
{
    while (!armada.empty())
	armada.pop_back();
    armada.clear();
}

void	Armada::HandleCollisions(Player	*player)
{
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	armada[i]->HandleCollisions(player);
}

void	Armada::Update(Player	*player)
{
    if (!this->Defeated())
    {

	// First: add new party as defined in Preset at inter.
	interval--;
	if ((interval <= 0) && (!preset.empty()))
	{
	    // Party	*newparty = new Party(1, 1500, 3);
	    Party	*newparty = new Party(this->popPreset());
	    newparty->Init();
	    armada.push_back(newparty);

	    std::cout << "New Party?" << std::endl;

	    interval = hourglass;
	}

	// Second: HandleCollisions with Player
	this->HandleCollisions(player);

	// Third: Update() all parties
	for (unsigned i = 0, size = armada.size(); i < size; i++)
	    armada[i]->Update(player);

	// Fourth: Clean vector of Party if some parties are defeated
	if (this->Sanitize())
	    this->Cleanup();

    }
    else
    {
        CallBoss(); // but once tho or... wotever
        // Boss is a Solo Party?
    }
}

void	Armada::Draw(CGameEngine	*game)
{
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	// draw if not Out, but vector is already sanitized
	armada[i]->Draw(game);
}
void	static Test() { std::cout << "'cause fuck you" << std::endl; }
bool	Armada::Sanitize()
{
    int	nexto = this->GetPartyOuted();

    while (nexto > 0)
    {
	armada[nexto]->Cleanup();
	armada.erase(armada.begin() + nexto);
	Test();
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
    std::cout << "And there shall be presented thy enemy."
	      << std::endl;
}
