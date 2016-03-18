#ifndef _GAME_TEXTE_H_
#define _GAME_TEXTE_H_

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "piece.h"

#define DIMENSION 6
#define DIM_X_AR 4
#define DIM_Y_AR 5


/**
 * @brief this function create, by calling init_grid, and display a two dimension array in terminal. This array is created with parameters of a game of rush_hour
 * @param the game you want to display, an array of pieces, the number of pieces in the array, and dimensions of the game (width and height).
 */
void display_grid_rh (game g, piece* pieces, int nb_pieces, int x, int y);



/**
 * @brief this function create, by calling init_grid, and display a two dimension array in terminal. This array is created with parameters of a game of ane_rouge
 * @param the game you want to display, an array of pieces, the number of pieces in the array, and dimensions of the game (width and height).
 */

void display_grid_ar (game g, piece* pieces, int nb_pieces, int x, int y);


/**
 * @brief create a two dimension array and set place all pieces taken from an array of pieces
 * @param an array on pieces, the amount of pieces and dimensions of the grid.
 */
int** init_grid (game g, int nb_pieces, int x, int y);


#endif
