#ifndef _GAME_TEXTE_H_
#define _GAME_TEXTE_H_

#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "piece.h"

#define DIMENSION 6
#define DIM_X_AR 4
#define DIM_Y_AR 5

#define SIZE_CHAR 5
#define INSTRUCTION_LINE 34
#define ERROR_LINE 32
#define PROMPT_LINE 35
#define PROMPT_RESET 50
#define CONDITION_CAR_SELECTION 0
#define CONDITION_CAR_DIRECTION 1
#define CONDITION_DIRECTION_VALUE 2
#define ASCII_CODE_U 85
#define ASCII_CODE_D 68
#define ASCII_CODE_R 82
#define ASCII_CODE_L 76


/**
 * @brief this function create and display a two dimensions array in the terminal. This array is created with parameters of a game of rush_hour
 * @param the game you want to display, an array of pieces, the number of pieces in the array, and dimensions of the game (width and height).
 */
void display_grid_rh(game g, int nb_pieces, int width, int heigth);



/**
 * @brief this function create, by calling init_grid, and display a two dimension array in terminal. This array is created with parameters of a game of ane_rouge
 * @param the game you want to display, an array of pieces, the number of pieces in the array, and dimensions of the game (width and height).
 */

void display_grid_ar(game g, int width, int height);


/**
 * @brief create a two dimension array and set place all pieces taken from an array of pieces
 * @param an array on pieces, the amount of pieces and dimensions of the grid.
 */
int** init_grid (game g, int x, int y);


/**
 * @brief Return a char in uppercase if it's lowercase, return the same if the the char is not a lowercase letter.
 **/
char to_upper (char c);


/**
 * @brief Clean the scanf buffer to avoid infinit loops.
 **/
void clear (void);


/**
 * @brief Set the terminal cursor to the begining of the line for a cleaner display.
 **/
void reset_cursor (void);

#endif
