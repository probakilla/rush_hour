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
game game_search (heap h, game g);


#endif
