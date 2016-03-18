#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "piece.h"
#include "game.h"
#include "game_text.h"


void display_grid_rh (game g, piece* pieces, int nb_pieces, int x, int y) {
  char num = 64 + y;    // ascii code of A + y.
  
  int ** grid = init_grid (g, nb_pieces, x, y);    // Create the grid we need to display the game on a terminal.

  for (int i = 0; i < y; ++i){     // Vertical parcour.

    printf("  ");
    if (i == 2){   // Exception of the exit line.
      for (int k = 0; k < x; ++k)    // Display of top of the line.
	printf("|-------");
      printf("|\n  ");
      for (int k = 0; k < x; ++k)    // Display the second line.
	printf("|       ");
      printf("------\n%c ", num - i);
      for (int k = 0; k < x; ++k){    // Display the third line.
	int nb = grid[(y - 1) - i][k];
	
	if (nb == -1)    // If square is empty (-1), it will be empty.
	  printf("|       ");
	else
	  printf("|   %d   ", nb);
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
	int nb = grid[(y - 1) - i][k];
	if (nb == -1)    // If square is empty (-1).
	  printf("|       ");
	else
	  printf("|   %d   ", nb);
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
  char num = 64 + y;    // ascii code of A + y.
  
  int ** grid = init_grid (g, nb_pieces, x, y);    // This grid will be use to display the game.
  //init_grid(g, nb_pieces, x, y);

  for (int i = 0; i < y; ++i){     // Vertical parcour.

    printf("  ");
    for (int k = 0; k < x; ++k)    // Display of top of the line.
      printf("|-------");
    printf("|\n  ");
    for (int k = 0; k < x; ++k)    // Display the second line.
      printf("|       ");
    printf("|\n%c ", num - i);
    for (int k = 0; k < x; ++k){    // Display the third line.
      int nb = grid[(y - 1) - i][k];
      if (nb == -1)    // If square is empty (-1).
	printf("|       ");
	      else
	printf("|   %d   ", nb /*game_square_piece(g, k, i)grid[i][k]*/);
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
  
  // Free of the grid
  for (int i = 0; i < x; ++ i)
    free(grid[i]);
  free(grid);
  
}





int ** init_grid (game g, int nb_pieces, int x, int y) {

  // Initialisation of the grid, all values are set to -1.
  int ** grid = malloc (sizeof(int*) * (y));
  assert(grid != NULL);
  
  for (int i = 0; i < y; ++i){
    grid[i] = malloc (sizeof(int) * x + 1);
    assert (grid[i] != NULL);
    for (int j = 0; j < x; ++j){
      grid[i][j] = game_square_piece(g, j, i);
    }
  }
  return grid;
}
