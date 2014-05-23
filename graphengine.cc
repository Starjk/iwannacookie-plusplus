#include "graphengine.hh"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

void GraphEngine::Init(int	lvl)
{
    SDL_Surface	*tmp = NULL;
    level = lvl;

    if (level != 1)
	std::cout << "No can do. Yet." << std::endl;

    preload['a']=IMG_Load("media/img/titre.jpg");
    preload['b']=IMG_Load("media/img/noir.jpg");

    tmp = IMG_Load("media/img/background_1.jpg");
    preload['c']= SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);

    preload['d']=IMG_Load("media/img/red_ship.png");
    preload['e']=IMG_Load("media/img/ship_e1.png");
    preload['f']=IMG_Load("media/img/ship_e2.png");
    preload['g']=SDL_LoadBMP("media/img/fire_blue.bmp");
    preload['h']=IMG_Load("media/img/fire_red.png");
    preload['i']=IMG_Load("media/img/heart.png");

    preload['0']=IMG_Load("media/num/0p.png");
    preload['1']=IMG_Load("media/num/1p.png");
    preload['2']=IMG_Load("media/num/2p.png");
    preload['3']=IMG_Load("media/num/3p.png");
    preload['4']=IMG_Load("media/num/4p.png");
    preload['5']=IMG_Load("media/num/5p.png");
    preload['6']=IMG_Load("media/num/6p.png");
    preload['7']=IMG_Load("media/num/7p.png");
    preload['8']=IMG_Load("media/num/8p.png");
    preload['9']=IMG_Load("media/num/9p.png");
}

void GraphEngine::Cleanup()
{
    SDL_FreeSurface(preload['a']);
    SDL_FreeSurface(preload['b']);
    SDL_FreeSurface(preload['c']);
    SDL_FreeSurface(preload['d']);
    SDL_FreeSurface(preload['e']);
    SDL_FreeSurface(preload['f']);
    SDL_FreeSurface(preload['g']);
    SDL_FreeSurface(preload['h']);
    SDL_FreeSurface(preload['i']);
    preload.clear();
}

void	GraphEngine::ChangeLevel()
{
    this->Cleanup();
    this->Init(level + 1);
}

SDL_Surface	*GraphEngine::GetGameTitle()
{
    return (preload['a']);
}

SDL_Surface	*GraphEngine::GetPlayer()
{
    return (preload['d']);
}

SDL_Surface	*GraphEngine::GetFoe(int	foetype)
{
    if ((foetype > 0) && (foetype <= 5))
	return (preload['e']);
    else if (foetype <= 10)
	return (preload['f']);
    else if (foetype <= 15)
	return (preload['f']);
    return (preload['e']);
}

SDL_Surface	*GraphEngine::GetAllyFire(int	firetype)
{
    if ((firetype < 1) && (firetype > 5))
	std::cout << "what is wrong w/ you?" << std::endl;
    return (preload['g']);
}

SDL_Surface	*GraphEngine::GetFoeFire(int	firetype)
{
    if (firetype != 1)
	std::cout << "what is wrong w/ you?" << std::endl;
    return (preload['h']);
}

SDL_Surface	*GraphEngine::GetHeart()
{
    return (preload['i']);
}

SDL_Surface	*GraphEngine::GetPauseBG()
{
    return (preload['b']);
}

SDL_Surface	*GraphEngine::GetBackground()
{
    if (level != 1)
	std::cout << "Are you sure it's defined yet?"
		  << std::endl;
    return (preload['c']);
}

SDL_Surface	*GraphEngine::GetDigit(char	digit)
{
    if ((digit > 47) && (digit < 58))	// '0' = 48 | '9' = 57
	return preload[digit];

    return preload['0'];
}
