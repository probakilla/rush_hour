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

	// initialization of different game configurations
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
		game game = new_game_hr(NB_PIECES, games[k]);

		// GAME START
		while (!(game_over_hr(game))){

			system ("clear");

			printf("\n ------ LEVEL %d ------ \n\n", k + 1);

			// Variables of command.
			int car_number = -1;
			char car_direction;
			int dir_num = -1;
			int condition = -1;

			// Display the game.
			display_grid_rh (game, pieces1, NB_PIECES, DIMENSION, DIMENSION);

			// The user select a piece.
			while (condition != CONDITION_CAR_SELECTION) {

				printf ("\033[%d;%dH%s\n", INSTRUCTION_LINE, 0, "Chose a piece : Type the number of the piece.                                             \n  ");
				reset_cursor ();
				int error = scanf ("%d", &car_number);

				// Test if the choice is correct.
				if (car_number == -1 || (car_number < 0 || car_number > (NB_PIECES - 1)) || error != 1){  // Enter if the choice is a digit and is in bounds.
					clear();
					printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, " ----- Wrong argument ! Please select a number between 0 and 5 -----                     \n ");
					reset_cursor ();
					continue;
				}
				condition = CONDITION_CAR_SELECTION;
			}

			cpiece current_piece = game_piece(game, car_number);

			// Erase the error line.
			printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "                                                                                              ");

			// The user select a direction.
			while (condition != CONDITION_CAR_DIRECTION) {

				printf ("\033[%d;%dH%s\n", INSTRUCTION_LINE, 0, "Chose a direction : Type the first letter of the direction (U, D, L or R).                 \n ");
				reset_cursor();
				int error_dir = scanf (" %c", &car_direction);
				car_direction = to_upper (car_direction);

				// Test if the choice is correct.
				if (car_direction == 'a' || (car_direction != ASCII_CODE_U && car_direction != ASCII_CODE_D && car_direction != ASCII_CODE_L && car_direction != ASCII_CODE_R) || error_dir != 1 || ((car_direction == ASCII_CODE_U || car_direction == ASCII_CODE_D) && is_horizontal(current_piece)) || ((car_direction == ASCII_CODE_R || car_direction == ASCII_CODE_L) && !(is_horizontal(current_piece)))) {
					clear ();
					printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "----- Wrong argument ! Please select a correct direction ! (U, D, L or R) -----          \n ");
					reset_cursor();
					continue;
				}
				condition = CONDITION_CAR_DIRECTION;
			}

			// Erase the error line.
			printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "                                                                                              ");

			// The user select a number of cases.

			while (condition != CONDITION_DIRECTION_VALUE) {
				printf ("\033[%d;%dH%s\n", INSTRUCTION_LINE, 0, "Chose a number of frame.                                                                    \n ");
				reset_cursor();
				int error_move = scanf ("%d", &dir_num);
				// We create some variables in order to make the code more clean.

				int move_up = (get_y(current_piece) + (get_height(current_piece) - 1) + dir_num);
				int move_down = (get_y(current_piece) - dir_num);
				int move_right = (get_x(current_piece) + (get_width(current_piece) - 1) + dir_num);
				int move_left = (get_x(current_piece) - dir_num);

				if (dir_num  == -1 || ((car_direction == ASCII_CODE_U) && move_up > (game_height(game) -1 + get_y(current_piece))) || ((car_direction == ASCII_CODE_D) && move_down < 0) || ((car_direction == ASCII_CODE_R) && move_right > (game_width(game) - get_x(current_piece))) || ((car_direction == ASCII_CODE_L) && move_left < 0) || error_move != 1) { // This condition test for each direction if what we enter is in the bounds.
					clear ();
					printf ("\033[%d;%dH%s\n", ERROR_LINE, 0,"-----  Wrong argument ! Enter a number that not cross the bounds of the grid -----          \n ");
					reset_cursor();
					continue;
				}
				condition = CONDITION_DIRECTION_VALUE;
			}

			// Erase the error line.
			printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "                                                                                              ");


			//direction conversion
			dir d = UP;

			switch (car_direction){
				case (ASCII_CODE_U):
					d = UP;
					break;
				case (ASCII_CODE_D):
					d = DOWN;
					break;
				case (ASCII_CODE_L):
					d = LEFT;
					break;
				case (ASCII_CODE_R):
					d = RIGHT;
					break;
			}
			// Play the move.
			play_move (game, car_number, d, dir_num);
		}
		printf("\n\nCongratulation, you  beat this level in %d moves !\n\n", game_nb_moves(game));
		delete_game(game);
	}


	printf("\n\nCONGRATULATION, YOU BEAT THE GAME !! THANKS FOR PLAYING !\n\n");


	// Free of the game.
	for (int i = 0; i < NB_PIECES; ++i){
		free(pieces1[i]);
		free(pieces2[i]);
		free(pieces3[i]);

		free(pieces1);
		free(pieces2);
		free(pieces3);

		free(games);

		return EXIT_SUCCESS;
	}
}
