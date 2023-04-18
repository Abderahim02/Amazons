#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"


/* Computes next move
 * PARAM:
 * - previous_move: the move from the previous player. If this is the
 *                  first move of the game, `previous_move` is equal to
 *                  { UINT_MAX, UINT_MAX, UINT_MAX }
 * RETURNS: - the next move for the player.
 */
struct move_t play(struct move_t previous_move){
    
}

/* Announces the end of the game to the player, and cleans up the
   memory he may have been using.
 * POSTCOND:
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */
void finalize();

