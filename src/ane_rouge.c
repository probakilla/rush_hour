#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game_text.h"

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


    game game = new_game (DIM_X_AR, DIM_Y_AR, NB_PIECES, pieces);



    while (!(game_over_ar(game))){

        system ("clear");

        printf("\n\n        ----- Ane Rouge ----- \n\n");

        // Display the game.
        display_grid_ar(game, DIM_X_AR, DIM_Y_AR);

        // Variables of command.
        int car_number = -1;
        char car_direction;
        int dir_num = -1;

        // The user select a piece.

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

        cpiece current_piece = game_piece(game, car_number);

        // Erase the error line.
        printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "                                                                                              ");

        // The user select a direction.

        printf ("\033[%d;%dH%s\n", INSTRUCTION_LINE, 0, "Chose a direction : Type the first letter of the direction (U, D, L or R).                 \n ");
        reset_cursor();
        int error_dir = scanf (" %c", &car_direction);
        car_direction = to_upper (car_direction);

        // Test if the choice is correct.
        if (car_direction == 'a' || (car_direction != ASCII_CODE_U && car_direction != ASCII_CODE_D && car_direction != ASCII_CODE_L && car_direction != ASCII_CODE_R) || error_dir != 1) {
            clear ();
            printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "----- Wrong argument ! Please select a correct direction ! (U, D, L or R) -----          \n ");
            reset_cursor();
            continue;
        }

        // Erase the error line.
        printf ("\033[%d;%dH%s\n", ERROR_LINE, 0, "                                                                                              ");

        // The user select a number of cases.

        printf ("\033[%d;%dH%s\n", INSTRUCTION_LINE, 0, "Chose a number of frame.                                                                    \n ");
        reset_cursor();
        int error_move = scanf ("%d", &dir_num);
        // We create some variables in order to make the code more clean.

        int move_up = (get_y(current_piece) + (get_height(current_piece) - 1) + dir_num);
        int move_down = (get_y(current_piece) - dir_num);
        int move_right = (get_x(current_piece) + (get_width(current_piece) - 1) + dir_num);
        int move_left = (get_x(current_piece) - dir_num);

        if (dir_num  < 1 || ((car_direction == ASCII_CODE_U) && move_up > (game_height(game) -1 + get_y(current_piece))) || ((car_direction == ASCII_CODE_D) && move_down < 0) || ((car_direction == ASCII_CODE_R) && move_right > (game_width(game) + 1 - get_x(current_piece))) || ((car_direction == ASCII_CODE_L) && move_left < 0) || error_move != 1) { // This condition test for each direction if what we enter is in the bounds.
            clear ();
            printf ("\033[%d;%dH%s\n", ERROR_LINE, 0,"-----  Wrong argument ! Enter a number that not cross the bounds of the grid -----          \n ");
            reset_cursor();
            continue;
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

        play_move (game, car_number, d, dir_num);
    }
    delete_game(game);

    for (int i = 0; i < NB_PIECES; ++i){
        free(pieces[i]);
    }
    free(pieces);

    return EXIT_SUCCESS;
}
