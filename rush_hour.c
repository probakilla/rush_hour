#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "game.h"
#include "piece.h"
#include "game_text.h"

#define NB_PIECES 6
#define NB_GAMES 3


void delete_piece_array (piece* pieces){
  for (int i = 0; i < NB_PIECES; ++i)
    delete_piece(pieces[i]);
  free(pieces);
}


int main (void) {

  // initialisation of different game configurations
  piece *pieces1 = malloc (sizeof(*pieces1) * NB_PIECES);
  if (pieces1 == NULL){
    fprintf(stderr,"Error : bad allocation of pieces1, please restart the game.\n");
    exit(EXIT_FAILURE);
  }
  // FIRST GAME
  pieces1[0] = new_piece_rh (0, 3, true,  true);   // x, y , small , horizontal
  pieces1[1] = new_piece_rh (2, 3, false , false);
  pieces1[2] = new_piece_rh (0, 0, true , false); 
  pieces1[3] = new_piece_rh (1, 1, true , true);
  pieces1[4] = new_piece_rh (2, 0, true , true);
  pieces1[5] = new_piece_rh (4, 0, false , false);
  
  piece *pieces2 = malloc (sizeof(*pieces2) * NB_PIECES);
  if (pieces2 == NULL){
    fprintf(stderr, "Error : bad allocation of pieces2, please restart the game.\n");
    exit(EXIT_FAILURE);
  }
  // SECOND GAME
  pieces2[0] = new_piece_rh (0, 3, true,  true);
  pieces2[1] = new_piece_rh (1, 0, true, false);
  pieces2[2] = new_piece_rh (2, 1, true, true);
  pieces2[3] = new_piece_rh (3, 3, false, false);
  pieces2[4] = new_piece_rh (4, 1, true, false);
  pieces2[5] = new_piece_rh (5, 0, false, false);
 
  piece *pieces3 = malloc (sizeof(*pieces3) * NB_PIECES);
  if (pieces3 == NULL){
    fprintf(stderr, "Error : bad allocation of pieces3, please restart the game.\n");
    exit(EXIT_FAILURE);
  }
  // THIRD GAME
  pieces3[0] = new_piece_rh (0, 3, true, true);
  pieces3[1] = new_piece_rh (0, 2, true, true);
  pieces3[2] = new_piece_rh (1, 0, true, false);
  pieces3[3] = new_piece_rh (3, 0, false, false);
  pieces3[4] = new_piece_rh (4, 1, true, true);
  pieces3[5] = new_piece_rh (5, 2, false, false);

  
  // ARRAY OF DIFFERENT GAMES
  piece** games = malloc (sizeof(piece) * 3);
  games[0] = pieces1;
  games[1] = pieces2;
  games[2] = pieces3;
  
  // RULES
  printf("\nYou have to move the 0 piece to the exit.\nTo move a piece, type it's number and a direction then the number of case you want to move.\n\n");
  
  for (int k = 0; k < NB_GAMES; ++k){
    game game = new_game_hr (NB_PIECES, games[k]);

    printf("\n\n ------ LEVEL %d ------ \n\n", k + 1);
    
    
    // GAME START
    while (!(game_over_hr(game))){
    
      // COMMANDS
      printf("Directions commands : 1 = up, 2 = down, 3 = right, 4 = left\n");

      // Variables of command.
      char car_number [10];
      int direction;
      char dir_num [10];

      // Display the game.
      display_grid(game, pieces1, NB_PIECES);
      printf("\n\npiece 0 : x = %d, y = %d\n\n", get_x(game_piece(game, 0)), get_y(game_piece(game,0)));

      // Check if user choices & test if choices are correct.
      printf("Select a piece :\n");
      scanf("%s", car_number);
      if (atoi(car_number) < 0 || atoi(car_number) > NB_PIECES - 1 ){ // if car number does not exists
        printf("\nWrong number! Pleas type a number between 0 and %d\n\n", NB_PIECES - 1);
	continue;
      }
      printf("Select a move :\n");
      scanf("%d", &direction);
      if (is_horizontal(game_piece(game, atoi(car_number))) && (direction < 3 || direction > 4)){
        printf("\nWrong number! The car can only be moved to the left (number 4) or the right (number 3)\n\n");
	continue;
      }
      if ((!is_horizontal(game_piece(game, atoi(car_number)))) && (direction < 1 || direction > 2)){
	printf("\nWrong number! The car can only be moved up (number 1) or down (number 2)\n\n");
	continue;
      }    
      printf("How many cases ?\n");
      scanf("%s", dir_num);
    
      // direction convertion
      dir d;
      switch (direction){
      case 1:
	d = UP;
	break;
      case 2 :
	d = DOWN;
	break;
      case 3:
	d = RIGHT;
	break;
      case 4:
	d = LEFT;
	break;
      }
      play_move (game, atoi(car_number), d, atoi(dir_num));
    }
    printf("\n\nCongratulation, you  beat this level in %d moves !\n\n", game_nb_moves(game));
    delete_game(game);
  }

  printf("\n\nCONGRATULATION, YOU BEAT THE GAME !! THANKS FOR PLAYING !\n\n");


  // Free of the game.
  for (int i = 0; i < NB_GAMES; ++i)
    delete_piece_array(games[i]);
  free(games);

  return EXIT_SUCCESS;
}
