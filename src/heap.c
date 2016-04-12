#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "heap.h"

#define INIT_SIZE 100
#define INIT_TOP 1

struct heap_s {
  game * games;
  int size_heap;
  int top_index;
};

// Double the size of the array and initialize index to NULL.
void increase_array (heap h, game **game) {

  *game = realloc (*game, 2 * sizeof game);
  assert (*game != NULL);

  h->size_heap = h->size_heap << 1;

  for (int i = h->top_index + 1; i < h->size_heap; ++i)
    h->games = NULL;
}


/**
 * @brief Sort the heap and return 0 if it's successful.
 **/
int sort (heap h, int index) {

  if (index == 1)
    return 0;

  int i_above = index;
  if (index % 2 != 0)
    i_above = index - 1;
  i_above /= 2;

  // Test if the nb_moves is lesser than the one abouve.
  if (game_nb_moves(h->games[index]) < game_nb_moves(h->games[i_above])){

    // Exchange games.
    game tmp = new_game (0, 0, 0, NULL);
    copy_game(h->games[index], tmp);
    h->games[index] = h->games[i_above];
    h->games[i_above] = tmp;
  }

  return sort(h, i_above);
}


heap new_heap () {
  
  // Allocation of the structure.
  heap h = calloc (INIT_SIZE, sizeof (struct heap_s));
  assert (h != NULL);

  h->size_heap = INIT_SIZE;

  h->top_index = INIT_TOP;
  
  // Alloctation of the array.
  h->games = malloc (sizeof(game) * h->size_heap);
  assert (h->games != NULL);
  
  return h;
}

  
void heap_add (heap h, game g) {

  int top = h->top_index;
  int l_child = top * 2;
  int r_child = (top * 2) + 1;
    
  if (h->top_index == h->size_heap){
    increase_array(h, &h->games);
  }

  // If left child is empty, put the game.
  if (h->games[l_child] == NULL){
    h->games[l_child] = g;
    sort(h, h->top_index);
  }

  // If right child is empty, put the game and increase the top index.
  else if (h->games[r_child] == NULL) {
    h->games[r_child] = g;
    h->top_index++;
    sort(h, h->top_index);
  }

  else {
    top++;
    h->games[top * 2] = g;
    h->top_index++;
    sort(h, h->top_index);
  }
}

game game_search (heap h, game g) {

  for (int i = 1; i < ((h->top_index) * 2) + 1; ++i)
    if (h->games[i] == g)
      return g;
  return NULL;
}
