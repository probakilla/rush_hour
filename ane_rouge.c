#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_text.h"
#include "game.h"
#include "piece.h"

#define NB_PIECES 10

bool game_over_ar (game g) {
  return (get_x (game_piece(g, 0)) == 0 && get_y (game_piece(g, 0)) == 1);
}


int main(void){

  piece* pieces = malloc(sizeof(*pieces) * NB_PIECES); // Creation of the pieces array.

  // Filling of the array of pieces.
  pieces[0] = new_piece (1, 3, 2, 2, true, true);   // Red piece (x, y, height, width, can_move_x, can_move_y).
  pieces[1] = new_piece (0, 0, 1, 1, true, true);
  pieces[2] = new_piece (0, 1, 2, 1, true, false);
  pieces[3] = new_piece (0, 3, 2, 1, true, false);
  pieces[4] = new_piece (1, 1, 1, 1, true, true);
  pieces[5] = new_piece (1, 2, 1, 2, false, true);
  pieces[6] = new_piece (2, 1, 1, 1, true, true);
  pieces[7] = new_piece (3, 0, 1, 1, true, true);
  pieces[8] = new_piece (3, 1, 2, 1, true, false); 
  pieces[9] = new_piece (3, 3, 2, 1, true, false);


  game current_game = new_game (DIM_X_AR, DIM_Y_AR, NB_PIECES, pieces);

  display_grid_ar(current_game, pieces, NB_PIECES);
  
  return EXIT_SUCCESS;
}
