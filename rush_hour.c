#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "piece.h"
#include "game_texte.h"




int main (void) {
  srand(time(NULL));

  // initialisation of different game configurations
  piece* pieces1 = malloc (sizeof(struct piece_s) * 6);
  piece* pieces2 = malloc (sizeof(struct piece_s) * 6);
  piece* pieces3 = malloc (sizeof(struct piece_s) * 6);
  
  // FIRST GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces1[1] = new_piece_rh (2, 4, false, false);
  pieces1[2] = new_piece_rh (1, 5, true, false);
  pieces1[3] = new_piece_rh (4, 3, true, false);
  pieces1[4] = new_piece_rh (4, 5, true, true);
  pieces1[5] = new_piece_rh (1, 0, false, true);

  // SECOND GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces2[1] = new_piece_rh (2, 2, false, true);
  pieces2[2] = new_piece_rh (1, 2, false, false);
  pieces2[3] = new_piece_rh (3, 4, true, false);
  pieces2[4] = new_piece_rh (5, 1, true, false);
  pieces2[5] = new_piece_rh (1, 5, true, true);

  // THIRD GAME
  pieces1[0] = new_piece_rh (3, 0, true,  true);
  pieces3[1] = new_piece_rh (3, 4, false, true);
  pieces3[2] = new_piece_rh (5, 3, false, false);
  pieces3[3] = new_piece_rh (3, 2, true, false);
  pieces3[4] = new_piece_rh (4, 1, true, false);
  pieces3[5] = new_piece_rh (0, 5, true, true);

  // ARRAY OF DIFFERENT GAMES
  piece** games = malloc (sizeof(struct piece_s*) * 3);
  games[0] = pieces1;
  games[1] = pieces2;
  games[2] = pieces3;

  // select a random game from the array of games
  game game = new_game_hr (6, pieces2); 
  
  // GAME START
  while (!game_over_hr(game)){

    // variables of command
    char car_number [10];
    char direction [10];
    char dir_num [10];

    // RULES
    printf("You have to move the 0 piece to the exit.\nTo move a piece, type it's number and a direction then the number of case you want to move.\n\n");
    // COMMANDS
    printf("Directions commands : 1 = up, 2 = down, 3 = right, 4 = left\n");

    // display the game
    display_grid(game->grid);

    // user choices
    printf("Select a piece :\n");
    scanf("%s", car_number);
    printf("Select a move :\n");
    scanf("%s", direction);
    printf("How many cases ?\n");
    scanf("%s", dir_num);

    
    dir d;
    switch (atoi(direction)){
    case 1:
      d = UP;
      break;
    case 2:
      d = DOWN;
      break;
    case 3:
      d = RIGHT;
      break;
    case 4:
      d = LEFT;
      break;

    }

        
    if (play_move(game, atoi(car_number), d, atoi(dir_num)))
      //refresh grid
      printf(" ");
    else
      printf("Wrong arguments !!");
      
    
  }

  printf("Congratulation, you won ! You beat this level in %d moves !", game_nb_moves(game));
  return EXIT_SUCCESS;
}
