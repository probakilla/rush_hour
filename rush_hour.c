#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "game.h"
#include "piece.h"
#include "game_texte.h"

#define NB_PIECES 6
#define DIMENSION 6




int main (void) {
  srand(time(NULL));

  // initialisation of different game configurations
  piece *pieces1 = malloc (sizeof(*pieces1) * NB_PIECES);
  if (pieces1 == NULL){
    fprintf(stderr,"Error : bad allocation");
    exit(EXIT_FAILURE);
  }

  // FIRST GAME
  pieces1[0] = new_piece_rh (0, 3, true,  true);// x, y , small , horizontal
  pieces1[1] = new_piece_rh (1, 0, false , false); 
  pieces1[2] = new_piece_rh (1, 4, false , true); 
  pieces1[3] = new_piece_rh (4, 0, true , false);
  pieces1[4] = new_piece_rh (4, 4, true , true);
  pieces1[5] = new_piece_rh (4, 2, true , true);
  
  piece *pieces2 = malloc (sizeof(*pieces2) * NB_PIECES);
  // SECOND GAME
  pieces2[0] = new_piece_rh (3, 0, true,  true);
  pieces2[1] = new_piece_rh (4, 0, false, true);
  pieces2[2] = new_piece_rh (2, 0, false, false);
  pieces2[3] = new_piece_rh (3, 4, true, false);
  pieces2[4] = new_piece_rh (5, 5, true, false);
  pieces2[5] = new_piece_rh (1, 3, true, true);
 
  piece *pieces3 = malloc (sizeof(*pieces3) * NB_PIECES);
  // THIRD GAME
  pieces3[0] = new_piece_rh (3, 0, true,  true);
  pieces3[1] = new_piece_rh (3, 4, false, true);
  pieces3[2] = new_piece_rh (5, 3, false, false);
  pieces3[3] = new_piece_rh (3, 2, true, false);
  pieces3[4] = new_piece_rh (4, 1, true, false);
  pieces3[5] = new_piece_rh (0, 5, true, true);

  
  

  // ARRAY OF DIFFERENT GAMES
  piece** games = malloc (sizeof(piece) * 3);
  games[0] = pieces1;
  games[1] = pieces2;
  games[2] = pieces3;

  // select a random game from the array of games
  game game = new_game_hr (NB_PIECES, pieces1);

  
  // RULES
  printf("\nYou have to move the 0 piece to the exit.\nTo move a piece, type it's number and a direction then the number of case you want to move.\n\n");
  
  
  // GAME START
  while (!(game_over_hr(game))){

       // COMMANDS
    printf("Directions commands : 1 = up, 2 = down, 3 = right, 4 = left\n");

    printf("\n\n%d %d\n\n", get_x(game_piece(game, 0)), get_y(game_piece(game,0)));

    // variables of command
    char car_number [10];
    int direction;
    char dir_num [10];

    // display the game
    display_grid(game, pieces1, NB_PIECES);
    printf("\n\npiece 0 : x = %d, y = %d\n\n", get_x(game_piece(game, 0)), get_y(game_piece(game,0)));

    // user choices & test if choices are correct
    printf("Select a piece :\n");
    scanf("%s", car_number);
    if (atoi(car_number) < 0 || atoi(car_number) > NB_PIECES - 1 ){ // if car number does not exists
      printf("\nMAUVAISE SAISIE ! Veuillez rentrer un numéro entre 0 et %d\n\n", NB_PIECES - 1);
      continue;
    }
    printf("Select a move :\n");
    scanf("%d", &direction);
    if (is_horizontal(game_piece(game, atoi(car_number))) && (direction < 3 || direction > 4)){
      printf("\nMAUVAISE SAISIE ! La voiture ne peut être déplacé que vers la droite (touche 3) ou vers la gauche (touche 4)\n\n");
      continue;
    }
    if ((!is_horizontal(game_piece(game, atoi(car_number)))) && (direction < 1 || direction > 2)){
      printf("\nMAUVAISE SAISIE ! La voiture ne peut être déplacé que vers le haut (touche 1) ou vers le bas (touche 2)\n\n");
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

    if (play_move(game, atoi(car_number), d, atoi(dir_num)))
      printf("Move possible and %d\n",d);
    else
      printf("Nope\n");
   
      
  
  }

  printf("Congratulation, you won ! You beat this level in %d moves !", game_nb_moves(game));
 
  return EXIT_SUCCESS;
}
