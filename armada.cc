
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
    //FIXME: NOW!
    hourglass = 1000;
    interval = hourglass;

    if (level == 1)
    {
	preset.push_back(115);
	preset.push_back(115);
    }
    if (level == 2)
    {
	preset.push_back(116);
	preset.push_back(224);
    }
}

void	Armada::Cleanup()
{
    // FIXME: check working value
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	if (armada[i]->NoMoreShots() && armada[i]->NoMoreFoes())
	    armada[i]->Cleanup();
            // delete (armada[i]);

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
    // FIXME: do something for end of enemy cycle

    // First: add new party has defined in Preset at inter.
    interval--;
    if (interval <= 0)
    {
	// int pre = preset.front();
	// int type = pre / 100, inter = (pre / 10) % 10, size = pre % 10;

	Party	*newparty = new Party(1, 250, 3);
	newparty->Init();
	armada.push_back(newparty);

	interval = hourglass;
    }

    // Second: Update() all parties
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	armada[i]->Update(player);

    // Third: Clean vector of Party if some parties are defeated
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	if (armada[i]->NoMoreShots() && armada[i]->NoMoreFoes())
	    armada[i]->Cleanup();
}

void	Armada::Draw(CGameEngine	*game)
{
    for (unsigned i = 0, size = armada.size(); i < size; i++)
	armada[i]->Draw(game);
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
