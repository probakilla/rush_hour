#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "game_texte.h"

#define DIMENSION 6

void display_grid (game g, piece* pieces, int nb_pieces) {
  char num = 97;
  int ** grid = init_grid (pieces, nb_pieces);
  printf("      1       2       3       4       5       6\n");
  for (int i = 0; i < DIMENSION; ++i){
    if (i != 3){
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       |\n");
      printf("%c ", num+i);
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
  for (int i = 0; i < nb_pieces; ++i)
    free(grid[i]);
  free(grid);
}

int** init_grid (piece* pieces, int nb_pieces) {
  // Initialisation of grid with the value -1
  int ** grid = malloc (sizeof(int*) * (nb_pieces));
  for (int i = 0; i < nb_pieces; ++i){
    grid[i] = malloc (sizeof(int)*nb_pieces);
    for (int j = 0; j < nb_pieces; ++j)
      grid[i][j] = -1;
  }
  for (int i = 0; i < nb_pieces; ++i) {
    grid[get_y(pieces[i])][get_x(pieces[i])] = i;

  return grid;
  }
}

