#include <stdio.h>
#include <stdlib.h>

#include "game.h"

struct game {
  int x;
  int y;
  int nbMoves;


game new_game_hr (int nb_pieces, piece *pieces){
  game game;
  return game;
}

void delete_game (game g) {

}

void copy_game (cgame src, game dst) {
}

int game_nb_pieces(cgame g) {
  return;
}

cpiece game_piece(cgame g, int piece_num) {
  cpiece piece;
  return piece; 
}

bool game_over_hr(cgame g) {
  return true;
}
