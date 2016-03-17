#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

#define NB_PIECES 6
#define DIMENSION 6



/**
 * @brief display different fields of a piece
 */
void display_piece (cpiece p) {
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
 * @brief test if pieces are well placed on a new game
 */
bool test_new (game g,piece *pieces) {
  if (game_nb_moves(g) == 0){
    for (int i = 0; i<NB_PIECES; ++i){
      display_piece(game_piece(g,i));
    }
    return true;
  }
  return false;
}

/**
 * @brief test if number of pieces is correct
 */
bool nbpiece_test (game g) {
  return (game_nb_pieces(g))  == NB_PIECES ;
}


/**
 * @brief test the equality between two games
 */
bool equals (game g1, game g2) {
  if (game_nb_moves(g1) != game_nb_moves(g2))
    return false;
  for (int i = 0; i<NB_PIECES; ++i){
    if ( get_x(game_piece(g1,i)) != get_x(game_piece(g2,i)) || get_y(game_piece(g1,i)) != get_y(game_piece(g2,i))){
      printf("%d %d", get_x(game_piece(g1,i)), get_x(game_piece(g2,i)));
      return false;
    }

    if ( is_horizontal(game_piece(g1,i)) != is_horizontal(game_piece(g2,i)) ) {
      return false;
    }
	
    if (is_horizontal(game_piece(g1,i))){
      if (get_width(game_piece(g1,i)) != get_width(game_piece(g2,i))){
	printf("if3");
	return false;
      }
    }

    if (!is_horizontal(game_piece(g1,i))){
      if (get_height(game_piece(g1,i)) != get_height(game_piece(g2,i))){
	return false;
      }
    }
  }
  return true;
}


/**
 * @brief test if game_over_hr is working
 * @param fct should be the game_over_hr result with the same cgame than the one which should be entered in this function
 */
bool game_over_test (bool fct, game g) {
  return fct && get_x(game_piece(g,0)) == 4 && get_y(game_piece(g,0)) == 3;
}

/**
 * @brief test if pieces are moved if they can  
 */
bool game_play (game g) {
  if (!play_move(g, 2, RIGHT, 1))
    return false;
  if (!play_move(g, 3, LEFT, 1))
    return false;
  if (!play_move(g, 1, UP, 1))
    return false;
  if (!play_move(g, 4, DOWN, 1))
    return false;
  if (play_move(g, 3, RIGHT, 2)) // test intersect
    return false;
  if (play_move(g, 5, DOWN, 1))
    return false;// test out of grid
  return true; 
}



// ************** MAIN ***************



int main (void) {

  // VARIABLES
  
  piece *pieces = malloc(sizeof(piece) * NB_PIECES);  //Allocation of an array of pieces
  pieces[0] = new_piece_rh (4, 3, true, true);        
  pieces[1] = new_piece_rh (0, 0, true, false);      
  pieces[2] = new_piece_rh (1, 1, true, true);         
  pieces[3] = new_piece_rh (2, 0, true, true);
  pieces[4] = new_piece_rh (2, 3, false, false);
  pieces[5] = new_piece_rh (4, 0, false, false);
  

  piece *pieces_copy = malloc(sizeof(piece) * NB_PIECES);  
  pieces_copy[0] = new_piece_rh (0, 3, true, true);
  pieces_copy[1] = new_piece_rh (0, 2, true, true);
  pieces_copy[2] = new_piece_rh (1, 0, true, false);
  pieces_copy[3] = new_piece_rh (3, 0, false, false);
  pieces_copy[4] = new_piece_rh (4, 1, true, true);
  pieces_copy[5] = new_piece_rh (5, 2, false, false);      
  
  game g = new_game_hr(NB_PIECES, pieces);
  printf("%d\n", game_nb_pieces(g));

  // NEW GAME TEST
  
  printf ("Test of new game : \n");
  
  if (!test_new(g,pieces)){
    fprintf(stderr, "Pieces not well placed on the board\n");
    exit(EXIT_FAILURE);
  }
  printf("Pieces well placed on the board\n");

  // DELETE_GAME TEST
  
  printf("Test delete game\n");
  game delete = new_game_hr (NB_PIECES, pieces);
  delete_game(delete);
  if(game_nb_moves(delete) != 0){
    fprintf(stderr, "Game not deleted");
    exit(EXIT_FAILURE);
  }
  else
    printf("Game deleted");
  
  // COPY_GAME TEST

  printf("\n\nTest copy game\n");
  game copy = new_game_hr(NB_PIECES, pieces_copy);
  if (copy == NULL){
    fprintf(stderr,"copy is not allocated");
    exit(EXIT_FAILURE);
  }
  copy_game(g, copy);
  for (int i = 0; i<NB_PIECES; ++i){
    display_piece(game_piece(g,i));
    display_piece(game_piece(copy,i));
    printf("\n");
  }
  if (!equals(g, copy)){
    fprintf(stderr, "copy failed\n");
    exit(EXIT_FAILURE);
  }
  printf("copy is successfully done\n");
  

  // GAME_NB_PIECES TEST

  printf("Test game_nb_pieces\n");
  game number = new_game_hr(NB_PIECES, pieces);
  if (nbpiece_test(number) != true){
    fprintf(stderr, "Error, function returns a bad amount of pieces\n");
    exit(EXIT_FAILURE);
  }
  printf ("Good amount of pieces\n");
  

  // GAME_PIECE TEST

  printf("Test game_piece\n");
  cpiece p = game_piece(g, 2);
  display_piece(p);


  // GAME_OVER TEST

  printf("Test game_over_hr\n");
  if (!game_over_test(game_over_hr(g), g)){
    fprintf (stderr, "Game is not well over\n");
    exit(EXIT_FAILURE);
  }
  printf ("Game well over\n");

  
  // PLAY_MOVE TEST
  
  game play_test = new_game_hr(NB_PIECES, pieces);
  if(!game_play(play_test)){
    fprintf (stderr, "pieces didn't moved well\n");
    exit(EXIT_FAILURE);
  }
  printf ("pieces moved correctly\n");
    
  
  //GAME_NB_MOVES TEST

  printf("Test game_nb_moves\n");
  int move = game_nb_moves(play_test);
  printf("%d\n",game_nb_moves(play_test)); 
  play_move(play_test,1, DOWN, 1);
  printf("%d\n",game_nb_moves(play_test)); 
  if (game_nb_moves(play_test) == move +1){
    printf("game_nb_moves works\n");
  }
  else
    fprintf(stderr,"game_nb_moves works\n");
  
  printf("Youpi!");
  return EXIT_SUCCESS;
}
