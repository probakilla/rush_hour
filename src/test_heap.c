#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "game.h"
#include "piece.h"
#include "heap.h"

#define NB_PIECES 1
#define OVERFLOW_TEST 150
#define FIRST_PIECE 0
#define DIRECTION_VALUE 2
#define FIRST_HEAP_INDEX 1

/**
 * @biref This function will free structures we use in test functions.
 * @param Différents structures used for testing queue.c
 **/

void clean_tests (piece *pieces1, piece *pieces2, game g1, game g2, heap h) {
  // Free the first array.
  delete_piece (pieces1[0]);
  free(pieces1);

  // Free the second array.
  delete_piece (pieces2[0]);
  free(pieces2);

  // Free games and queue.
  delete_game (g1);
  delete_game (g2);
  heap_delete (h);
}

bool test_heap_add () {

  // Initialization of the pieces.
  piece piece1 = new_piece_rh (0, 0, true, true);
  piece piece2 = new_piece_rh (1, 1, true, true);

  // Initialization of the two arrays of pieces.
  piece *p_array1 = malloc (sizeof (p_array1) * NB_PIECES);
  assert (p_array1 != NULL);
  p_array1[0] = piece1;
  
  piece *p_array2 = malloc (sizeof (p_array2) * NB_PIECES);
  assert (p_array2 != NULL);
  p_array2[0] = piece2;

  // Creation of two games
  game game1 = new_game_hr (NB_PIECES, p_array1);
  game game2 = new_game_hr (NB_PIECES, p_array2);

  // We create a queue and push the two games in it.
  heap h = new_heap ();

  // Move a piece of the game to change his number of movement.
  play_move (game2, FIRST_PIECE, UP, DIRECTION_VALUE);
  play_move (game2, FIRST_PIECE, RIGHT, DIRECTION_VALUE);
  
  // Try to overflow the heap.
  for (int i = 0; i < OVERFLOW_TEST; ++i)
    heap_add (h, game2);

  heap_add (h, game1);

  if (game_nb_moves(heap_index_search(h, FIRST_HEAP_INDEX)) != game_nb_moves(game1)){
    fprintf (stderr, "ERROR : The heap is not sorted");
    clean_tests (p_array1, p_array2, game1, game2, h);
    return false;
  }

  return true;
}

int main (void) {

  if (!test_heap_add())
    return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}
