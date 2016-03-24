#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "piece.h"
#include "game.h"

/**
 * @queue queue.h
 *
 * @brief A queue will be used in our game solver.
 *
 **/

/**
 * @struct queue_s
 * @brief This queue will use an array on games.
 *
 **/

typedef struct queue_s* queue;


/**
 * @brief Create a new queue, the field index_top is set automatically to 0.
 **/

queue new_queue ();

/**
 * @brief Push a game in the queue. If the queue is full, the size of the array will double.
 * @param The game you want to stock, and the queue.
 **/

void push (queue q, game g);

/**
 * @brief Returns the first game of the array. All others games will be shifted.
 * @param The queue where you want to push a game.
 **/

game pop (queue q);

/**
 * @brief Free the array of the queue.
 **/

void delete_queue (queue q);

#endif
