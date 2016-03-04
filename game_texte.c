#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "game_texte.h"

#define DIMENSION 6

void display_grid (game g, piece* pieces, int nb_pieces) {
  char num = 97; // ascii code of a.
  
  int ** grid = init_grid (g, nb_pieces);
  printf("\npd\n");
  display_array(grid);
  printf("      1       2       3       4       5       6\n"); // Display of collumn's numbers

  // Create lines and place pieces number
  for (int i = 0; i < DIMENSION; ++i){
    if (i != 3){
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       |\n");
      printf("%c ", num + i);
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
  
    // Exception of the fourth line, which one with the exit
    else {
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       ------- \n");
      printf("%c ", num+i);
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

  // free of the grid
  for (int i = 0; i < nb_pieces; ++i)
    free(grid[i]);
  free(grid);

}



int** init_grid (game g, int nb_pieces) {
  // Initialisation of grid with the value -1
  int ** grid = malloc (sizeof(int*) * (DIMENSION));
  if (grid == NULL)
    exit(EXIT_FAILURE);
  
  for (int i = 0; i < DIMENSION; ++i){
    grid[i] = malloc (sizeof(int)*DIMENSION + 1);
    if (grid[i] == NULL)
      exit(EXIT_FAILURE);
    for (int j = 0; j < DIMENSION; ++j)
      grid[i][j] = -1;
  }
  // Place the piece
  for (int i = 0; i < DIMENSION; ++i) {
    grid[get_x(game_piece(g, i))][get_y(game_piece(g, i))] = i;
    
    if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 2) // small horizontal
      grid[get_x(game_piece(g, i))][get_y(game_piece(g, i))+1] = i;
    else if (is_horizontal(game_piece(g, i)) && get_width(game_piece(g, i)) == 3){ // big horizontal
      grid[get_x(game_piece(g, i))][get_y(game_piece(g, i))+1] = i;
      grid[get_x(game_piece(g, i))][get_y(game_piece(g, i))+2] = i;
    }

    else if (!is_horizontal(game_piece(g, i)) && get_height(game_piece(g, i)) == 2){ // small vertical
      grid[get_x(game_piece(g, i))-1][get_y(game_piece(g, i))] = i;
    }
    else if (!is_horizontal(game_piece(g, i)) && get_height(game_piece(g, i)) == 3){ // big vertical
      grid[get_x(game_piece(g, i))-1][get_y(game_piece(g, i))] = i;
      grid[get_x(game_piece(g, i))-2][get_y(game_piece(g, i))] = i;  
    }
  }
  return grid;
}

void display_array (int ** grid) {
  for (int i = 0; i < DIMENSION; ++i){
    for (int j = 0; j < DIMENSION; ++j)
      printf("%d ", grid[i][j]);
    printf("\n");
  }
}
