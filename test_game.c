#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

#define NB_PIECES 3

/**
 * @brief test if pieces are well placed on a new game
 * @param 
 */
bool test_new (game g) {
  return (g->grid[3][0] == 0 && g->grid[3][1] && g->grid[2][2] == 1 && g->grid[1][2] == 1 && g->grid[1][4] == 3 && g->grid[1][5] == 3 && g->grid[5][5] == 2 && g->grid[4][5] == 2 && g->grid[3][5] == 2 && g->grid[2][5] == -1);
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
bool nbpiece_test (cgame g) {
  return (sizeof(g->pieces)*sizeof(struct piece_s)) + 1 == NB_PIECES + 1;
}


/**
 * @brief test the equality between two games
 */
bool equals (cgame g1, cgame g2) {
  for(int i = 0; i < 6; ++i)
    for(int j = 0; j < 6; ++j)
      if (g1->grid[i][j] != g2->grid[i][j])
	return false;
  
  if (g1->nbMoves != g2->nbMoves)
    return false;

  for (int i = 0; i < NB_PIECES; ++i)
    if (g1->pieces[i] != g2->pieces[i])
      return false;

  return true;
}

/**
 * @brief display different fields of a piece
 */
void display_piece (cpiece p) {
  printf ("Coord: x = %d, y = %d\n", p->x, p->y);
  if (p->small)
    printf("small\n");
  else
    printf("big\n");

  if (p->horizontal)
    printf("horizontal\n");
  else
    printf("vertical\n");
}

/**
 * @brief test if game_over_hr is working
 * @param fct should be the game_over_hr result with the same cgame than the one which should be entered in this function
 */
bool game_over_test (bool fct, cgame g) {
  return (fct && (g->grid[3][4] == 0));
}






// ************** MAIN ***************

int main (void) {

  // VARIABLES
  
  piece *pieces = malloc(sizeof(struct piece_s) * NB_PIECES);  //Allocation of an array of pieces (length = 3)
  pieces[0] = new_piece_rh(2, 2, true, false);        // piece coord (2,2) small, vertical
  pieces[1] = new_piece_rh(5, 5, false, false);       // piece coord (5,5) big, vertical
  pieces[2] = new_piece_rh(1, 4, true, true);         // piece coord (1,4) small, horizontal
  
  game g = new_game_hr (5, pieces);

  // NEW GAME TEST

  printf ("Test of new game : \n");

  if (!test_new(g)){
    fprintf(stderr, "pieces are not well placed on the board\n");
    exit(EXIT_FAILURE);
  }
   printf("pieces are well placed on the board\n");


  printf ("-- array display --\n");
  array_display (g->grid);


  // DELETE_GAME TEST


  // keskonmé ?????!

  // COPY_GAME TEST

  printf("Test copy game\n");
  game copy = malloc(sizeof(struct piece_s) * 3);
  copy_game (g, copy);
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
  cpiece p = malloc(sizeof(struct piece_s));
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


  return EXIT_SUCCESS;
}
