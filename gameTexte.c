#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"

#define DIMENSION 6

/*
void display_grid (){
  printf("\n");
   printf("      1       2       3       4       5       6 \n");
  for (int i = 0; i < 6; ++i){
    if (i == 2) {
      
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       ---------\n");
      printf("%d |       |       |       |       |       |           EXIT\n", i+1);
      printf("  |       |       |       |       |       |       ---------\n");
      continue;
    }
    else if (i != 2){
     
      printf("  |-------|-------|-------|-------|-------|-------|\n");
      printf("  |       |       |       |       |       |       |\n");
      printf("%d |       |       |       |       |       |       |\n", i+1);
      printf("  |       |       |       |       |       |       |\n");
    }
  }
   printf("  |-------|-------|-------|-------|-------|-------|\n");
}
*/


void display_grid (int ** grid) {

  for (int i = 0; i < DIMENSION; ++i){
     printf("|-------|-------|-------|-------|-------|-------|\n");
     printf("|       |       |       |       |       |       |\n");
     for (int j = 0; j < DIMENSION; ++j){
       printf("|   ");
      if (grid[i][j] == -1)
	printf ("    ");
      else
	printf ("%d   ", grid[i][j]);
       }
    printf("|\n");
    printf("|       |       |       |       |       |       |\n");
    
  }
   printf("|-------|-------|-------|-------|-------|-------|\n");
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

int main(void){
  int ** grid = init_grid(1, DIMENSION);
  //grid [1][1] = 1;
  display_grid (grid);
  return 0;  
}
