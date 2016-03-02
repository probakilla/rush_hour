#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "piece.h"
#include "gameTexte.h"




int main (void) {
  srand(time(NULL));

  piece* pieces1 = malloc (sizeof(struct piece_s) * 5);
  piece* pieces2 = malloc (sizeof(struct piece_s) * 5);
  piece* pieces3 = malloc (sizeof(struct piece_s) * 4);

  // FIRST GAME
  piece1[0] = new_piece_rh (1, 0, false, true);
  piece1[1] = new_piece_rh (2, 4, false, false);
  piece1[2] = new_piece_rh (1, 5, true, false);
  piece1[3] = new_piece_rh (4, 3, true, false);
  piece1[4] = new_piece_rh (4, 5, true, true);

  // SECOND GAME
  piece2[0] = new_piece_rh (2, 2, false, true);
  piece2[1] = new_piece_rh (1, 2, false, false);
  piece2[2] = new_piece_rh (3, 4, true, false);
  piece2[3] = new_piece_rh (5, 1, true, false);
  piece2[4] = new_piece_rh (1, 5, true, true);

  // THIRD GAME
  piece3[0] = new_piece_rh (3, 4, false, true);
  piece3[1] = new_piece_rh (5, 3, false, false);
  piece3[2] = new_piece_rh (3, 2, true, false);
  piece3[3] = new_piece_rh (4, 1, true, false);
  piece3[4] = new_piece_rh (0, 5, true, true);

  // ARRAY OF DIFFERENT GAMES
  piece** games = malloc (sizeof(struct piece_s*) * 3);
  games[0] = pieces1;
  games[1] = pieces2;
  games[2] = pieces3;

  cgame game = games[rand() % 2];
    
  while (!game_over_hr(g)){

  
  return EXIT_SUCCESS;
}
