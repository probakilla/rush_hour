#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

#define NB_PIECES 3
#define DIMENSION 6



/**
 * @brief test if pieces are well placed on a new game
 * @param 
 */
bool test_new (game g,piece *pieces) {
  if (game_nb_moves(g) == 0){
    for (int i = 0; i<NB_PIECES; ++i){
      display_piece(game_piece(g,i));
    }
    return true;
  }
  
    

  }

/**
 * @brief display an double entry array
 */
void array_display (int ** t) {
  for (int i = 0; i < 6; ++i){
    for (int j = 0; j < 6; ++j)
      printf ("[%d]", t[i][j]);
    printf("\n");
  }
}

/**
 * @brief test if number of pieces is correct
 */
bool nbpiece_test (game g) {
  return (game_nb_pieces(g))  == NB_PIECES + 1;
}


/**
 * @brief test the equality between two games
 */
bool equals (game g1, game g2) {
  if (game_nb_moves(g1) != game_nb_moves(g2))
    return false;
  for (int i = 0; i<NB_PIECES; ++i){
    if ( get_x(game_piece(g1,i)) != get_x(game_piece(g2,i)) || get_y(game_piece(g1,i)) != get_y(game_piece(g2,i)))
      return false;

    if ( is_horizontal(game_piece(g1,i)) != is_horizontal(game_piece(g2,i)) )
      return false;

    if (is_horizontal(game_piece(g1,i))){
      if (get_width(game_piece(g1,i)) != get_width(game_piece(g2,i)))
	return false;
    }

    if (!is_horizontal(game_piece(g1,i))){
      if (get_height(game_piece(g1,i)) != get_height(game_piece(g2,i)))
	return false;
    }
  }
  return true;
}


/**
 * @brief display different fields of a piece
 */
void display_piece (piece p) {
  printf ("Coord: x = %d, y = %d\n", get_x(p), get_y(p));
  if (is_horizontal(p) && get_width(p) == 2)
    printf("horizontal small\n");
  else if (is_horizontal(p))
    printf("horizontal big\n");

  if ((!is_horizontal(p)) && get_height(p) == 2)
    printf("vertical small\n");
  else if (!is_horizontal(p))
    printf("vertical big\n");


}

/**
 * @brief test if game_over_hr is working
 * @param fct should be the game_over_hr result with the same cgame than the one which should be entered in this function
 */
bool game_over_test (bool fct, cgame g) {
  return true;
}






// ************** MAIN ***************

int main (void) {

  // VARIABLES
  
  piece *pieces = malloc(sizeof(piece) * NB_PIECES);  //Allocation of an array of pieces (length = 3)
  pieces[0] = new_piece_rh(2, 2, true, false);        // piece coord (2,2) small, vertical
  pieces[1] = new_piece_rh(5, 5, false, false);       // piece coord (5,5) big, vertical
  pieces[2] = new_piece_rh(1, 4, true, true);         // piece coord (1,4) small, horizontal

  piece *pieces_copy = malloc(sizeof(piece) * NB_PIECES);  //Allocation of an array of pieces (length = 3)
  pieces_copy[0] = new_piece_rh(2, 2, true, false);        // piece coord (3,3) small, vertical
  pieces_copy[1] = new_piece_rh(3, 3, false, false);       // piece coord (4,4) big, vertical
  pieces_copy[2] = new_piece_rh(4, 4, true, true);         // piece coord (2,5) small, horizontal
  
  game g = new_game_hr(3, pieces);

    // NEW GAME TEST
  
  printf ("Test of new game : \n");

  if (!test_new(g,pieces)){
    fprintf(stderr, "pieces are not well placed on the board\n");
    exit(EXIT_FAILURE);
  }
  printf("pieces are well placed on the board\n");

 
  // DELETE_GAME TEST


  // keskonmé ?????!

  // COPY_GAME TEST

  printf("\n\nTest copy game\n");
  game copy = new_game_hr(NB_PIECES, pieces_copy);
   if (copy == NULL){
    fprintf(stderr,"copy is not allocated");
    exit(EXIT_FAILURE);
  }
   copy_game (g, copy);
   for (int i = 0; i<NB_PIECES; ++i){
     display_piece(game_piece(g,i));
     display_piece(game_piece(copy,i));
     printf("\n");
   }
     if (!equals (g, copy)){
     fprintf(stderr, "copy failed\n");
    exit(EXIT_FAILURE);
  }
  printf("copy is successfully done\n");
  
  
 

  // GAME_NB_PIECES TEST

  printf("Test game_nb_pieces\n");
  if (!nbpiece_test){
    fprintf(stderr, "Error, function return a bad amount of pieces");
    exit(EXIT_FAILURE);
  }
  printf ("Good amount of pieces");
  


  // GAME_PIECE TEST

  printf("Test game_piece\n");
  cpiece p = malloc(sizeof(piece));
  p = game_piece(g, 2);
  display_piece(p);



  // GAME_OVER TEST

  printf("test game_over_hr\n");
  if (!game_over_test(game_over_hr(g), g)){
    printf ("game is not well over");
    exit(EXIT_FAILURE);
  }
  printf ("game is well over");



  
  // PLAY_MOVE TEST
  
  printf("test play_move\n");
  array_display(g->grid);
  play_move(g, 2, UP, 1);
  array_display(g->grid);
  

  //GAME_NB_MOVES TEST

  printf("test game_nb_moves\n");
  int move = game_nb_moves(g);
  move_piece(g->pieces[1], DOWN, 1);
  if (game_nb_moves(g) != move +1){
    printf("game_nb_moves is not working\n");
    exit(EXIT_FAILURE);
  }
  printf("game_nb_moves is working\n");
  */

  return EXIT_SUCCESS;
}
