#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

int main void (void) {
	
  piece pieces = malloc(sizeof(struct piece_s) * 3);  //Allocation of an array of pieces (length = 3)
  pieces[0] = new_piece_rh(2, 2, true, false);        // piece coord (2,2) small, vertical
  pieces[1] = new_piece_rh(5, 5, false, false);       // piece coord (5,5) big, vertical
  pieces[2] = new_piece_rh(1, 4, true, true);         // piece coord (1,4) small, horizontal
  
  game g = new_game_hr (5, pieces);

  printf ("Test of new game : ");

  if (g[3][0] == 0 && g[3][1] && g[2][2] == 1 && g[1][2] == 1 && g[1][4] == 3 && 
}
