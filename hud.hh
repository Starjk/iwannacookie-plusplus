#ifndef HUD_HH_
# define HUD_HH_

#include <SDL.h>
#include <SDL_image.h>

#include "gameengine.hh" // correspondence of WIDTH and HEIGHT
#include "player.hh"

#define	SZ_SBOARD	10
#define	SZ_DIGITS	12

namespace HUD
{

    // Display ALL
    void DisplayHUD(Player	*player, int	score,
		    GameEngine	*game);

    // Display Current Health / bar w/ 'health' segments top right
    void DisplayHealth(Player	*player, GameEngine	*game);

    // Display Remaining Life / 'life' hearts top right corner
    void DisplayHearts(Player	*player, GameEngine	*game);

    // Display Score / top left corner X zeros until...
    void DisplayScore(int	score, GameEngine	*game);

} /* HUD */

#endif /* HUD_HH_ */
