#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "piece.h"
#include "game_texte.h"




int main (void) {
  srand(time(NULL));

  piece* pieces1 = malloc (sizeof(struct piece_s) * 5);
  piece* pieces2 = malloc (sizeof(struct piece_s) * 5);
  piece* pieces3 = malloc (sizeof(struct piece_s) * 4);

  // FIRST GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces1[1] = new_piece_rh (2, 4, false, false);
  pieces1[2] = new_piece_rh (1, 5, true, false);
  pieces1[3] = new_piece_rh (4, 3, true, false);
  pieces1[4] = new_piece_rh (4, 5, true, true);
  pieces1[5] = new_piece_rh (1, 0, false, true);

  // SECOND GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces2[1] = new_piece_rh (2, 2, false, true);
  pieces2[2] = new_piece_rh (1, 2, false, false);
  pieces2[3] = new_piece_rh (3, 4, true, false);
  pieces2[4] = new_piece_rh (5, 1, true, false);
  pieces2[5] = new_piece_rh (1, 5, true, true);

  // THIRD GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces3[1] = new_piece_rh (3, 4, false, true);
  pieces3[2] = new_piece_rh (5, 3, false, false);
  pieces3[3] = new_piece_rh (3, 2, true, false);
  pieces3[4] = new_piece_rh (4, 1, true, false);
  pieces3[5] = new_piece_rh (0, 5, true, true);

  // ARRAY OF DIFFERENT GAMES
  piece** games = malloc (sizeof(struct piece_s*) * 3);
  games[0] = pieces1;
  games[1] = pieces2;
  games[2] = pieces3;

  cgame game = new_game_hr (6, games[rand() % 2]);
    
  while (!game_over_hr(game)){

  
    return EXIT_SUCCESS;
  }
}
