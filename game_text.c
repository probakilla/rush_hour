#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "game_text.h"

void display_grid (game g, piece* pieces, int nb_pieces) {
  char num = 64 + DIMENSION;    // ascii code of A + DIMENSION.
  
  int ** grid = init_grid (g, nb_pieces);    // This grid will be use to display the game.

  for (int i = 0; i < DIMENSION; ++i){     // Vertical parcour.

    printf("  ");
    if (i == 2){   // Exception of the exit.
      for (int k = 0; k < DIMENSION; ++k)    // Display of top of the line.
	printf("|-------");
      printf("|\n  ");
      for (int k = 0; k < DIMENSION; ++k)    // Display the second line.
	printf("|       ");
      printf("------\n%c ", num - i);
      for (int k = 0; k < DIMENSION; ++k){    // Display the third line.
	int nb = grid[i][k];
	if (nb == -1)    // If square is empty (-1).
	  printf("|       ");
	else
	  printf("|   %d   ", grid[i][k]);
      }
      printf("  EXIT\n  ");
      for (int k = 0; k < DIMENSION; ++k) // Display the last line.
	printf("|       ");
      printf("------\n");
    }
  
    else {   // Rest of the grid.     
      for (int k = 0; k < DIMENSION; ++k)    // Display of top of the line.
	printf("|-------");
      printf("|\n  ");
      for (int k = 0; k < DIMENSION; ++k)    // Display the second line.
	printf("|       ");
      printf("|\n%c ", num - i);
      for (int k = 0; k < DIMENSION; ++k){    // Display the third line.
	int nb = grid[i][k];
	if (nb == -1)    // If square is empty (-1).
	  printf("|       ");
	else
	  printf("|   %d   ", grid[i][k]);
      }
      printf("|\n  ");
      for (int k = 0; k < DIMENSION; ++k) // Display the last line.
	printf("|       ");
      printf("|\n");
    }
  }
  printf("  ");   // Display the very last line.
  for (int i = 0; i < DIMENSION; ++i){
    printf("|-------");
  }
  printf("|\n  ");
  for (int i = 0; i < DIMENSION; ++i)
    printf("    %d   ", i);   // Display the number of the collunms.
  
  // Free of the grid.
  for (int i = 0; i < nb_pieces; ++i)
    free(grid[i]);
  free(grid);
}


int ** init_grid (game g, int nb_pieces) {

  // Initialisation of the grid, all indexes are set to -1.
  int ** grid = malloc (sizeof(int*) * (DIMENSION));
  if (grid == NULL)
    exit(EXIT_FAILURE);
  
  for (int i = 0; i < DIMENSION; ++i){
    grid[i] = malloc (sizeof(int)*DIMENSION + 1);
    if (grid[i] == NULL)
      exit(EXIT_FAILURE);
    for (int j = 0; j < DIMENSION; ++j){
      grid[i][j] = -1;
    }
  }
      
  // Fill of the grid.
  for (int i = 0; i < nb_pieces; ++i){

    grid[(DIMENSION - 1) - get_y(game_piece(g,i))][get_x(game_piece(g,i))] = i;
    if (!(is_horizontal(game_piece(g, i))) && get_height(game_piece(g, i)) == 2){  // Test if the piece is vertical and small.
      grid[((DIMENSION -1) - get_y(game_piece(g, i))) - 1][get_x(game_piece(g, i))] = i;
    }
    if ( !(is_horizontal(game_piece(g, i))) && get_height(game_piece(g, i)) == 3){ // Test if the piece is vertical and big.
      grid[((DIMENSION -1) - get_y(game_piece(g, i))) - 1][get_x(game_piece(g, i))] = i;
      grid[((DIMENSION -1) - get_y(game_piece(g, i))) - 2][get_x(game_piece(g, i))] = i;
    }

    if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 2){     // Test if the piece is horizontal and small.
      grid[((DIMENSION -1) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 1] = i;
    }
    if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 3){     // Test if the piece is horizontal big.
      grid[((DIMENSION -1) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 1] = i;
      grid[((DIMENSION -1) - get_y(game_piece(g, i)))][get_x(game_piece(g, i)) + 2] = i;
    }
  }
  return grid;
}
