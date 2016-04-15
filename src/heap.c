#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"

#define INIT_SIZE 100
#define INIT_TOP 1

struct heap_s {
  game * games;
  int size_heap;
  int top_index;
};

// Double the size of the array and initialize index to NULL.
void increase_array (heap h, game **g, int i) {
  
  if (i == h->size_heap){

    int tmp = h->size_heap;
    h->size_heap = h->size_heap << 1;
    
    *g = (game*) realloc (*g, (h->size_heap * 2) * sizeof (game));
    assert (*g != NULL);

    for (int i = tmp; i < h->size_heap; ++i)
      h->games[i] = NULL;
  }
}


/**
 * @brief Sort the heap and return 0 if it's successful.
 **/

void sort (heap h, int index) {

  int i_above = index;
  
  while (index != 1) {
  
    if (i_above % 2 != 0)
      i_above = index - 1;
    i_above /= 2;

    // If the game of the current index have a lesser number of moves than the one above, exchange them.
    if (game_nb_moves(h->games[index]) < game_nb_moves(h->games[i_above])){
      
      // Exchange games.
      game tmp = new_game (0, 0, 0, NULL);
      copy_game(h->games[index], tmp);
      h->games[index] = h->games[i_above];
      h->games[i_above] = tmp;
    }
    index = i_above;
  }
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
    
  // Insert the first value.
  if (h->top_index == INIT_TOP && h->games[INIT_TOP] == NULL)
    h->games[INIT_TOP] = g;
  
  // If left child is empty, put the game.
  else if (h->games[l_child] == NULL){
    // Test if the array is full.
    increase_array(h, &h->games, l_child);
    h->games[l_child] = g;
    sort(h, l_child);
  }

  // If right child is empty, put the game and increase the top index.
  else if (h->games[r_child] == NULL) {
    // Test if the array is full
    increase_array(h, &h->games, r_child);
    h->games[r_child] = g;
    h->top_index++;
    sort(h, r_child);
  }
}


bool heap_game_search (heap h, game g) {

  for (int i = 1; i < h->size_heap; ++i) {
    for (int j = 0; j < game_nb_pieces(g); ++j) {
      if (get_x(game_piece(h->games[i],j)) != get_x(game_piece(g,j)) || get_y(game_piece(h->games[i],j)) != get_y (game_piece(g,j)))
        return false;
    }
  }
  return true;
}


game heap_index_search (heap h, int index) {

  if (index <= 0 || index > h->size_heap){
    fprintf (stderr, "ERROR : Index is incorrect");
    return NULL;
  }

  return h->games[index];
}


void heap_delete (heap h) {

  for (int i = 0; i < h->size_heap; ++i)
    delete_game(h->games[i]);
  free(h->games);
  free(h);
}
