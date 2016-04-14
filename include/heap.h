#ifndef _HEAP_H_
#define _HEAP_H_

#include "game.h"
#include "piece.h"

typedef struct heap_s* heap;

/**
 * @brief Init a new heap.
 * @param The first game you want to put in the heap.
 **/

heap new_heap ();


/**
 * @brief Add a value in the heap and sort it.
 **/

void heap_add (heap h, game g);


/**
 * @brief Search a game in the heap, return the game of NULL if the game is not is the heap.
 **/
game heap_game_search (heap h, game g);


/**
 * @biref This function returns the game at the index we wants. The heap begins with index 1 and not 0. If the index is incorrect, return NULL.
 **/
game heap_index_search (heap h, int index);


/**
 * @brief Free the structure of the heap.
 **/
void heap_delete (heap h);

#endif
