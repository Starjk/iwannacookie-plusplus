#include <SDL.h>
#include <SDL_image.h>

#include "hud.hh"

void HUD::DisplayHUD(Player	*player, int	score,
		     GameEngine	*game)
{
    HUD::DisplayHearts(player, game);
    HUD::DisplayHealth(player, game);
    HUD::DisplayScore(score, game);
}

void HUD::DisplayHealth(Player	*player, GameEngine	*game)
{
    // INIT
    SDL_Surface	*health = IMG_Load("media/img/healthbar-re.png");
    SDL_Rect	*health_rect = new SDL_Rect;
    unsigned	hp = player->getHealth() / 5;

    health_rect->y = 10;
    health_rect->w = 5;
    health_rect->h = 29;

    // Right End
    health_rect->x = WIDTH - 10;
    SDL_BlitSurface(health, NULL, game->screen, health_rect);

    // Middle Bars
    SDL_FreeSurface(health);
    health = IMG_Load("media/img/greenbar.png");
    for (unsigned i = 2; i < hp; i++)
    {
	health_rect->x = WIDTH - (5 + (i * 5));
	SDL_BlitSurface(health, NULL, game->screen, health_rect);
    }

    // Left End
    SDL_FreeSurface(health);
    health = IMG_Load("media/img/healthbar-le.png");
    health_rect->x = WIDTH - (5 + (hp * 5));
    SDL_BlitSurface(health, NULL, game->screen, health_rect);

    // FREE
    delete (health_rect);
    SDL_FreeSurface(health);
}

void HUD::DisplayHearts(Player	*player, GameEngine	*game)
{
    // INIT
    SDL_Surface	*heart = IMG_Load("media/img/heart.png");
    SDL_Rect	*heart_rect = new SDL_Rect;
    unsigned	hearts = player->getLife();

    heart_rect->y = 45;
    heart_rect->w = 28;
    heart_rect->h = 31;

    for (unsigned i = 1; i <= hearts; i++)
    {
	heart_rect->x = WIDTH - (i * 33);
	SDL_BlitSurface(game->GraEng->GetHeart(),
			NULL, game->screen, heart_rect);
    }

    // FREE
    delete (heart_rect);
    SDL_FreeSurface(heart);
}

void HUD::DisplayScore(int	score, GameEngine	*game)
{
    // INIT
    SDL_Rect	*score_rect = new SDL_Rect;
    int		position = 5 + ((SZ_SBOARD - 1) * SZ_DIGITS);
    char	digit = '0';
    int		ttrap = 0;

    score_rect->y = 10;
    score_rect->w = 20;
    score_rect->h = 20;

    for (unsigned i = 0; i < SZ_SBOARD; i++)
    {
	score_rect->x = position - (i * SZ_DIGITS);
	if (score > 0)
	{
	    ttrap = score % 10;
	    digit = ttrap + 48;
	    score /= 10;
	}
	else
	    digit = '0';
	SDL_BlitSurface(game->GraEng->GetDigit(digit),
			NULL, game->screen, score_rect);
    }

    // FREE
    delete(score_rect);
}
