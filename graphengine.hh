#ifndef GRAPHENGINE_HH_
# define GRAPHENGINE_HH_

#include <SDL.h>
#include <SDL_image.h>

#include <map>

class GraphEngine
{
public:

    void Init(int lvl=1);
    void Cleanup();
    void ChangeLevel();

    SDL_Surface	*GetGameTitle();
    SDL_Surface	*GetPlayer();
    SDL_Surface	*GetFoe(int	foetype);
    SDL_Surface	*GetAllyFire(int firetype);
    SDL_Surface	*GetFoeFire(int	firetype);
    SDL_Surface	*GetHeart();
    SDL_Surface	*GetPauseBG();
    SDL_Surface	*GetBackground();
    SDL_Surface	*GetDigit(char	digit);

private:
    std::map<char, SDL_Surface*>	preload;
    int	level;
};

#endif /* GRAPHENGINE_HH_ */
