#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "piece.h"
#include "game.h"
#include "game_text.h"


void display_grid_rh(game g, int nb_pieces, int x, int y) {
    char num = 64 + y;    // ascii code of A + y.

    int ** grid = init_grid (g, x, y);    // Create the grid we need to display the game on a terminal.

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
                else if (nb == -2)      // If the piece is blocked
		  printf("|   X   ");
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
		else if (nb == -2)     // If the piece is blocked
		  printf("|   X   ");
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



void display_grid_ar(game g, int x, int y) {

    char num = 64 + y;    // ascii code of A + y.

    int ** grid = init_grid (g, x, y);    // This grid will be use to display the game.
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
	    else if (nb == -2)     // If the piece is blocked
		  printf("|   X   ");
            else
                printf("|   %d   ", nb /*game_square_piece(g, k, i)grid[i][k]*/);
        }
        printf("|\n  ");
        for (int k = 0; k < x; ++k) // Display the last line.
            printf("|       ");
        printf("|\n");
    }
    printf("  ");
    for (int i = 0; i < x; ++i) {  // Display the very last line and the exit of the grid.
        if (i == 1 || i == 2){
            printf ("|       ");
        }
        else
            printf ("|-------");
    }
    printf("|\n\n");

    // Free of the grid
    for (int i = 0; i < y; ++ i)
        free(grid[i]);
    free(grid);

}





int ** init_grid (game g, int x, int y) {

  // Initialisation of the grid,
  int ** grid = malloc (sizeof(int*) * (y));
  assert(grid != NULL);

  // Fill the grid with pieces indexes.
  for (int i = 0; i < y; ++i){
    grid[i] = malloc (sizeof(int) * x + 1);
    assert (grid[i] != NULL);
    for (int j = 0; j < x; ++j){
      int number_piece = game_square_piece(g, j, i);
      if (number_piece != -1 && !(can_move_x(game_piece (g, number_piece))) && !(can_move_y(game_piece(g, number_piece))))
	grid[i][j] = -2;
      else
	grid[i][j] = number_piece;
    }
  }
  return grid;
}


char to_upper (char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}


void clear (void) {
    while (getchar() != '\n');
}


void reset_cursor (void) {
    printf("\033[%d;%dH%s\n", PROMPT_LINE, 0, "                                                             ");
    printf("\033[%d;%dH%s\n", INSTRUCTION_LINE, PROMPT_RESET, "");
}
