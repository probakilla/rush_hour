#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_text.h"
#include "game.h"
#include "piece.h"

#define NB_PIECES 10

bool game_over_ar (game g) {
  return (get_x (game_piece(g, 0)) == 1 && get_y (game_piece(g, 0)) == 0);
}


int main(void){

  piece* pieces = malloc(sizeof(*pieces) * NB_PIECES); // Creation of the pieces array.

  // Filling of the array of pieces.
  pieces[0] = new_piece (1, 3, 2, 2, true, true);   // Red piece (x, y, height, width, can_move_x, can_move_y).
  pieces[1] = new_piece (0, 0, 1, 1, true, true);
  pieces[2] = new_piece (0, 1, 1, 2, true, true);
  pieces[3] = new_piece (0, 3, 1, 2, true, true);
  pieces[4] = new_piece (1, 1, 1, 1, true, true);
  pieces[5] = new_piece (1, 2, 2, 1, true, true);
  pieces[6] = new_piece (2, 1, 1, 1, true, true);
  pieces[7] = new_piece (3, 0, 1, 1, true, true);
  pieces[8] = new_piece (3, 1, 1, 2, true, true); 
  pieces[9] = new_piece (3, 3, 1, 2, true, true);


  game current_game = new_game (DIM_X_AR, DIM_Y_AR, NB_PIECES, pieces);



  while (!(game_over_ar(current_game))){
    
    // COMMANDS
    printf("Directions commands : 1 = up, 2 = down, 3 = right, 4 = left\n\n");

    // Variables of command.
    int car_number;
    int direction;
    int dir_num;

    // Display the game.
    display_grid_ar(current_game, pieces, NB_PIECES, DIM_X_AR, DIM_Y_AR);
    printf("\n\npiece 0 : x = %d, y = %d\n\n", get_x(game_piece(current_game, 0)), get_y(game_piece(current_game,0)));

    // Check if user choices & test if choices are correct.
    printf("Select a piece :\n");
    scanf("%d", &car_number);

    printf("Select a move :\n");
    scanf("%d", &direction);

    printf("How many cases ?\n");
    scanf("%d", &dir_num);
    
    // direction conversion
    dir d = UP;
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
    play_move (current_game, car_number, d, dir_num);
  }
  printf("\n\nCongratulation, you  beat this level in %d moves !\n\n", game_nb_moves(current_game));
  delete_game(current_game);

  for (int i = 0; i < NB_PIECES; ++i){
    free(pieces[i]);
  }
  free(*pieces);
  
  return EXIT_SUCCESS;
}
