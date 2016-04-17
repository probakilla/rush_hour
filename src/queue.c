#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "game.h"
#include "queue.h"

#define INIT_QUEUE_SIZE 100000

struct queue_s {
    int array_size;
    int index_top;
    game *game_array;
    int fill_multiple;
};

/**
 * @brief Test if the queue is full.
 * @param The queue you want to test.
 **/

bool is_full (queue q) {

  // If the array size (-1) is equals the the top index, the queue is full.
  return (q->array_size - 1) == q->index_top;
}

/**
 * @brief This function will be used to double the size of the array when it's full.
 * @param The array we need to increase it size.
 **/
game* increase_queue (game *array, int fill_multiple) {

  array = realloc (array, sizeof (game) * (INIT_QUEUE_SIZE * fill_multiple + 1));
  assert (array != NULL);
  return array;
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
  q->fill_multiple = 1;

  return q;
}

void push (queue q, game g) {

  // Test if the queue is full, if it is, double the size of the array.
  if (is_full(q)) {
    q->game_array = increase_queue (q->game_array, q->fill_multiple);
    q->array_size = q->array_size << 1;
  }
  // Place the game in the array and increase the top index.
  q->game_array[q->index_top] = g;
  q->index_top += 1;
  q->fill_multiple += 1;
}

game pop (queue q) {

  // If the queue is empty, this function does nothing.
  if (q->index_top == 0){
    printf("-1");
    exit(EXIT_FAILURE);
  }

  return q->game_array[0];
}

void rearrange_queue(queue q){
  int n = q->index_top;

  // Shift all games stocked in the array.
  for (int i = 0; i < n; ++i)
    q->game_array[i] = q->game_array[i + 1];

  q->index_top -= 1;
}

void delete_queue (queue q) {

  int n = q->index_top;

  for (int i = 0; i < n; ++i)
    delete_game (q->game_array[i]);
  free (q->game_array);
  free (q);
}
