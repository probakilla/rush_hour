#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "game_text.h"

#define DIMENSION 6

void display_grid (game g, piece* pieces, int nb_pieces) {
  char num = 102;    // ascii code of a.
  
  int ** grid = init_grid (g, nb_pieces);    // This grid will be use to display the game.

  
  // Create lines and place pieces number.
  for (int i = 0; i < DIMENSION; ++i){
    if (i != 2){
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       |\n");
      printf("%c ", num - i);
      for (int j = 0; j < DIMENSION; ++j){
	printf("|   ");
	if (grid[i][j] == -1)
	  printf ("    ");
	else
	  printf ("%d   ", grid[i][j]);
      }
      printf("|\n");
      printf("  |       |       |       |       |       |       |\n");      
    }

    
    // Exception of the third line, which one with the exit.
    else {
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       ------- \n");
      printf("%c ", num - i);
      for (int j = 0; j < DIMENSION; ++j){
	printf("|   ");
	if (grid[i][j] == -1)
	  printf ("    ");
	else
	  printf ("%d   ", grid[i][j]);
      }
      printf("  EXIT\n");
      printf("  |       |       |       |       |       |       ------- \n");
    }    
  }
  printf("  |-------|-------|-------|-------|-------|-------|\n");
  printf("      1       2       3       4       5       6\n");

  
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
