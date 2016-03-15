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
 * @brief this function create display a grid in terminal from a two dimension array. This array is created with parameters of a game of RushHour
 * @param the game you want to display, the array of pieces and the number of pieces
 */
void display_grid_rh (game g, piece* pieces, int nb_pieces, int x, int y);


/**
 * Same for ane rouge
 */
void display_grid_ar (game g, piece* pieces, int nb_pieces);


/**
 * @brief create a two dimension array and set place all pieces taken from an array of pieces
 * @param an array on pieces and the number of pieces
 */
int** init_grid (game g, int nb_pieces, int x, int y);


#endif
