#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"

#define DIMENSION 6

void display_grid (int ** grid) {
  char num = 97;
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
}

int** init_grid (int x, int dim) {
  int ** grid = malloc (sizeof(int*) * (dim));
  for (int i = 0; i < dim; ++i){
    grid[i] = malloc (sizeof(int)*dim);
    for (int j = 0; j < dim; ++j)
      grid[i][j] = x;
  }
  return grid;
}

