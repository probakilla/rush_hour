#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "queue.h"

#define INIT_QUEUE_SIZE 50

struct queue_s {
  int array_size;
  int index_top;
  game *game_array;
};

/**
 * @brief Test if the queue is full.
 * @param The queue you want to test.
 **/

bool is_full (queue q) {

  // If the array size (-1) is equals the the top index, the queue is full.
  return (q->array_size - 1) == q->index_top;
}

queue new_queue () {

  // Allocate the structure
  queue q = malloc (sizeof(struct queue_s));
  assert (q != NULL);
  q->array_size = INIT_QUEUE_SIZE;

  // Allocate the game array
  q->game_array = malloc(sizeof(game) * q->array_size);
  assert ((q->game_array) != NULL);

  q-> index_top = 0;

  return q;
}

void push (queue q, game g) {

  // Test if the queue is full, if it is, double the size of the array.
  if (is_full(q)) {
    q->game_array = realloc (q->game_array, (q->array_size * (sizeof(game))) * 2);
    assert (q->game_array == NULL);
    q->array_size *= 2;
  }
  // Place the game in the array and increase the top index.
  q->game_array[q->index_top] = g;
  q->index_top += 1;
}

game pop (queue q) {

  // We need to save the game we want to return.
  game result = q->game_array[0];
  int n = q->index_top;

  // Shift all games stocked in the array.
  for (int i = 0; i < n; ++i) 
    q->game_array[i] = q->game_array[i + 1];

  q->index_top -= 1;
  return result;
}

void delete_queue (queue q) {

  int n = q->index_top;
  
  for (int i = 0; i < n; ++i)
    delete_game (q->game_array[i]);
  free (q->game_array);
  free (q);  
}
