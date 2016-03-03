#ifndef _GAME_TEXTE_H_
#define _GAME_TEXTE_H_

#include <stdlib.h>
#include <stdio.h>


/**
 * @brief this function display a grid in terminal from a two dimension array 
 * @param a two dimension array
 */
void display_grid (int ** grid);


/**
 * @brief create a two dimension array and set all indexes of this array with a value
 * @param the value you want to put in all indexes of the array and the dimension of the array (the array will be "square")
 */
int** init_grid (int x, int dim);


#endif
