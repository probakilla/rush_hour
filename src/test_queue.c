#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define NB_PIECES 1

/**
 * @biref This function will free structures we use in test functions.
 * @param Différents structures used for testing queue.c
 **/

void clean_tests (piece *pieces1, piece *pieces2, game g1, game g2, queue q) {
  // Free the first array.
  delete_piece (pieces1[0]);
  free(pieces1);

  // Free the second array.
  delete_piece (pieces2[0]);
  free(pieces2);

  // Free games and queue.
  delete_game (g1);
  delete_game (g2);
  delete_queue (q);
}

bool test_push_pop () {

  // Initialization of the pieces.
  piece piece1 = new_piece_rh (0, 0, true, true);
  piece piece2 = new_piece_rh (1, 1, true, true);

  // Initialization of the two arrays.
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
  queue q = new_queue ();
  push (q, game1);
  push (q, game2);

  // Take the abscissa of the pop and the second game we put in the queue.
  game test_game = pop (q);
  rearrange_queue(q);
  int x1 = get_x (game_piece (test_game, 0));
  int x2 = get_x (game_piece (game1, 0));

  // Test if the abscissa are equals.
  if (x1 != x2){
    // Free the structures we used.
    clean_tests (p_array1, p_array2, game1, game2, q);
    fprintf (stderr, "The first pop has failed \n");
    return false;
  }

  // Same test, but for the other game.
  x1 = get_x (game_piece (pop (q), 0));
  rearrange_queue(q);
  x2 = get_x (game_piece (game2, 0));

  if (x1 != x2){
    // Free the structures we used.
    clean_tests (p_array1, p_array2, game1, game2, q);
    fprintf (stderr, "The second pop has failed\n");
    return false;
  }
  clean_tests (p_array1, p_array2, game1, game2, q);
  return true;
}

/**
 * @brief Fill the queue until it have to expend the array. If it dosn't works, it should cause a segmentation falt
 **/
bool test_push_overflow () {
  // Put a piece in the array.
  piece piece1 = new_piece_rh (0, 0, true, true);
  piece *p_array = malloc (sizeof (p_array) * NB_PIECES);
  p_array[0] = piece1;

  game game = new_game_hr (NB_PIECES, p_array);

  queue q = new_queue ();

  // Put more pieces that we cant put in a default queue.
  for (int i = 0; i < 60; ++i)
    push (q, game);
  return true;
}



int main (void) {

  if (!test_push_pop()){
    fprintf(stderr, "Error : push or pop problem");
    return 1;
  }

  test_push_overflow ();

  fprintf (stdout, "Youpi !\n");
  return 0;
}
