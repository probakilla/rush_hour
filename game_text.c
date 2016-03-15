#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "piece.h"
#include "game.h"
#include "game_text.h"

void display_array_ar (int ** grid) {

  for (int i = 0; i < DIM_Y_AR; ++i)
    for (int j = 0; j < DIM_X_AR; ++j){
      if (grid[i][j] == -1)
	printf ("[%d]", grid[i][j]);
      else
	printf ("[ %d]", grid[i][j]);
    }
  printf("\n");
}

void display_grid_rh (game g, piece* pieces, int nb_pieces, int x, int y) {
  char num = 64 + y;    // ascii code of A + DIMENSION.
  
  int ** grid = init_grid (g, nb_pieces, x, y);    // This grid will be use to display the game.

  for (int i = 0; i < y; ++i){     // Vertical parcour.

    printf("  ");
    if (i == 2){   // Exception of the exit.
      for (int k = 0; k < x; ++k)    // Display of top of the line.
	printf("|-------");
      printf("|\n  ");
      for (int k = 0; k < x; ++k)    // Display the second line.
	printf("|       ");
      printf("------\n%c ", num - i);
      for (int k = 0; k < x; ++k){    // Display the third line.
	int nb = grid[i][k];
	if (nb == -1)    // If square is empty (-1).
	  printf("|       ");
	else
	  printf("|   %d   ", grid[i][k]);
      }
      printf("  EXIT\n  ");
      for (int k = 0; k < x; ++k) // Display the last line.
	printf("|       ");
      printf("------\n");
    }
  
    else {   // Rest of the grid.     
      for (int k = 0; k < x; ++k)    // Display of top of the line.
	printf("|-------");
      printf("|\n  ");
      for (int k = 0; k < x; ++k)    // Display the second line.
	printf("|       ");
      printf("|\n%c ", num - i);
      for (int k = 0; k < x; ++k){    // Display the third line.
	int nb = grid[i][k];
	if (nb == -1)    // If square is empty (-1).
	  printf("|       ");
	else
	  printf("|   %d   ", grid[i][k]);
      }
      printf("|\n  ");
      for (int k = 0; k < x; ++k) // Display the last line.
	printf("|       ");
      printf("|\n");
    }
  }
  printf("  ");   // Display the very last line.
  for (int i = 0; i < x; ++i){
    printf("|-------");
  }
  printf("|\n  ");
  for (int i = 0; i < x; ++i)
    printf("    %d   ", i);   // Display the number of the collunms.
  
  // Free of the grid.
  for (int i = 0; i < nb_pieces; ++i)
    free(grid[i]);
  free(grid);
}



void display_grid_ar (game g, piece* pieces, int nb_pieces){
  int x = game_width(g);
  int y = game_height(g);
  char num = 64 + y;    // ascii code of A + DIMENSION.
  
  int ** grid = init_grid (g, nb_pieces, x, y);    // This grid will be use to display the game.
  init_grid(g, nb_pieces, x, y);

  for (int i = 0; i < y; ++i){     // Vertical parcour.

    printf("  ");
    for (int k = 0; k < x; ++k)    // Display of top of the line.
      printf("|-------");
    printf("|\n  ");
    for (int k = 0; k < x; ++k)    // Display the second line.
      printf("|       ");
    printf("|\n%c ", num - i);
    for (int k = 0; k < x; ++k){    // Display the third line.
      int nb = grid[i][k];
      if (nb == -1)    // If square is empty (-1).
	printf("|       ");
      else
	printf("|   %d   ", grid[i][k]);
    }
    printf("|\n  ");
    for (int k = 0; k < x; ++k) // Display the last line.
      printf("|       ");
    printf("|\n");
  }
  printf("  ");
  for (int i = 0; i < x; ++i) {
    if (i == 1 || i == 2){
      printf ("|       ");
	}
    else
      printf ("|-------");
  }
  printf("|\n\n");
}





int ** init_grid (game g, int nb_pieces, int x, int y) {

  // Initialisation of the grid, all indexes are set to -1.
  int ** grid = malloc (sizeof(int*) * (y));
  assert(grid != NULL);
  
  for (int i = 0; i < y; ++i){
    grid[i] = malloc (sizeof(int) * x + 1);
    assert (grid[i] != NULL);
    for (int j = 0; j < x; ++j){
      grid[i][j] = -1;
    }
  }

  // Fill the grid.
  for (int i = 0; i < nb_pieces; ++i) {
    piece tmp_piece = (piece) game_piece(g, i);
    int piece_x = get_x(tmp_piece);
    int piece_y = (y - 1) - get_y(tmp_piece);
    for (int ord = piece_y; ord > (piece_y - (get_height(tmp_piece) - 1)); --ord)
      for (int abs = piece_x; abs < (piece_x + (get_width(tmp_piece) - 1)); ++abs)
	grid[ord][abs] = i;
	
    
      
  }
  /*   
  // Fill of the grid. ATTENTION J'AI ENLEVER LES Y - 1
  for (int i = 0; i < nb_pieces; ++i){

  grid[(y - 1) - get_y(game_piece(g,i))][get_x(game_piece(g,i))] = i;
  if (!(is_horizontal(game_piece(g, i))) && get_height(game_piece(g, i)) == 2){  // Test if the piece is vertical and small.
  grid[((y) - get_y(game_piece(g, i))) - 1][get_x(game_piece(g, i))] = i;
  }
    if ( !(is_horizontal(game_piece(g, i))) && get_height(game_piece(g, i)) == 3){ // Test if the piece is vertical and big.
      grid[((y) - get_y(game_piece(g, i))) - 1][get_x(game_piece(g, i))] = i;
      grid[((y) - get_y(game_piece(g, i))) - 2][get_x(game_piece(g, i))] = i;
    }

    if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 2){     // Test if the piece is horizontal and small.
      grid[((y) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 1] = i;
    }
    if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 3){     // Test if the piece is horizontal big.
      grid[((y) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 1] = i;
      grid[((y) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 2] = i;
    }
  }
  */
  display_array_ar(grid);
  return grid;
}
