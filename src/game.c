#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#define DIMENSION 6

struct game_s { //Structure of game with the number of moves, the number pieces, the width, the height and a array containing the pieces of the game.
    int nb_moves;
    int nb_pieces;
    int width;
    int height;
    piece *pieces;
};

game new_game_hr(int nb_pieces,
                 piece *pieces) { //We suppose that the piece i = 0 is the "red one", the one we have to lead to exit).
    game current = malloc(sizeof(struct game_s)); //Allocation of the structure
    current->nb_pieces = nb_pieces;
    current->nb_moves = 0;
    current->width = DIMENSION;
    current->height = DIMENSION;


    current->pieces = malloc(sizeof(piece) * nb_pieces);
    if (current->pieces == NULL)
        printf("ERREUR D'ALLOCATION");

    for (int i = 0; i < nb_pieces; i++) {
        current->pieces[i] = new_piece_rh(0, 0, false, false);
        copy_piece(pieces[i], current->pieces[i]);
    }
    return current;

}

void delete_game(game g) { //Freeing subarrays and the main array
    for (int i = 0; i < game_nb_pieces(g); ++i)
        free(g->pieces[i]);
    free(g->pieces);
    free(g);
}

void copy_game(cgame src, game dst) { // Copying fileds, and copying each piece
    //Test if the arrays of pieces are equals. If not, freeing the dst array and realloc it of the right size.

    if (dst->nb_pieces != src->nb_pieces) {
        for (int i = 0; i < dst->nb_pieces; ++i) {
            delete_piece(dst->pieces[i]);

        }
        free(dst->pieces);

        dst->pieces = malloc(sizeof(piece) * src->nb_pieces);
        for (int i = 0; i < src->nb_pieces; ++i){
            dst->pieces[i] = new_piece_rh(0,0,false,false);
            copy_piece(src->pieces[i], dst->pieces[i]);
        }
    }
    else {
        for (int i = 0; i < src->nb_pieces; ++i){
            copy_piece(src->pieces[i], dst->pieces[i]);
        }
    }

    dst->nb_moves = src->nb_moves;
    dst->nb_pieces = src->nb_pieces;
    dst->width = src->width;
    dst->height = src->height;

}

int game_nb_pieces(cgame g) {
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num) {
    return g->pieces[piece_num];

}

bool game_over_hr(cgame g) {
    return get_y(g->pieces[0]) == 3 && get_x(g->pieces[0]) == (game_width(g) - 2);
}

bool test_move (game g, int piece_num, dir d, int distance){ //Create a copy of a piece to calculate later if the move don't intersect and so don't change the real piece.

    piece move_copy = new_piece_rh(0, 0, true,true);
    copy_piece(game_piece(g, piece_num), move_copy);

    for (int test_distance = 0; test_distance < distance; ++test_distance) {    //This loop test the move 1 by 1 to be sure the piece don't transperce and exceed another piece.
        move_piece(move_copy, d, 1);
        for (int i = 0; i < piece_num; ++i) {    //Double loop to skip the intersect test with the piece itself.
            if (intersect(move_copy, g->pieces[i])){
                free(move_copy);
                return false;
            }
        }
        for (int i = piece_num + 1; i < game_nb_pieces(g); i++) {
            if (intersect(move_copy, g->pieces[i])){
                free(move_copy);
                return false;
            }
        }
    }
    free(move_copy);
    return true;

}


/* --------------------- 

This is the main fonction of the game. The fonction test if the piece stays is the board and if the move is correct.

------------------------ */

bool play_move(game g, int piece_num, dir d, int distance) {

    // The two first test eliminates two easy cases.

    if (distance < 0) {
        return false;
    }

    if (piece_num < 0 || piece_num >= game_nb_pieces(g)) {
        return false;
    }

    if (can_move_x((piece) game_piece(g, piece_num))) {    //Check if the piece is horizontal

        if (d == LEFT && get_x((piece) game_piece(g, piece_num)) - distance >=0) {    // Piece is horizontal and check if the piece is still in the grid after the move.
            if (test_move(g,piece_num,d,distance)){
                move_piece((piece) game_piece(g, piece_num), d, distance); //Move the real piece, increase the number of moves and free the copy.
                g->nb_moves += distance;
                return true;
            }
        }

        int extends_piece = get_width((piece) game_piece(g, piece_num)) - 1;    //The piece is supposed to move right. Adding the "extension" to the piece for checking if the move is correct.

        if (d == RIGHT && get_x((piece) game_piece(g, piece_num)) + distance + extends_piece < game_width(g)) {    //Same for RIGHT direction.
            if (test_move(g,piece_num,d,distance)){
                move_piece((piece) game_piece(g, piece_num), d, distance);
                g->nb_moves += distance;
                return true;
            }
        }
    }

    if (can_move_y((piece) game_piece(g, piece_num))) {    //Check if the piece is vertical

        if (d == DOWN && get_y((piece) game_piece(g, piece_num)) - distance >= 0) {    //Same for DOWN direction
            if (test_move(g,piece_num,d,distance)){
                move_piece((piece) game_piece(g, piece_num), d, distance);
                g->nb_moves += distance;
                return true;
            }
        }

        int extends_piece = get_height((piece) game_piece(g, piece_num)) - 1;

        if (d == UP && get_y((piece) game_piece(g, piece_num)) + distance + extends_piece < game_height(g)) {    //Same for UP direction
            if (test_move(g,piece_num,d,distance)){
                move_piece((piece) game_piece(g, piece_num), d, distance);
                g->nb_moves += distance;
                return true;
            }
        }
    }

    return false;
}

int game_nb_moves(cgame g) {
    return g->nb_moves;
}


game new_game(int width, int height, int nb_pieces, piece *pieces) {
    game current = malloc(sizeof(struct game_s)); //Allocation of the structure

    current->nb_pieces = nb_pieces;
    current->nb_moves = 0;
    current->width = width;
    current->height = height;

    current->pieces = malloc(sizeof(piece) * nb_pieces);
    if (current->pieces == NULL)
        printf("ERREUR D'ALLOCATION");

    for (int i = 0; i < nb_pieces; i++) {
        current->pieces[i] = new_piece_rh(0, 0, false, false);
        copy_piece(pieces[i], current->pieces[i]);
    }
    return current;
}


int game_width(cgame g) {
    return g->width;
}


int game_height(cgame g) {
    return g->height;
}


int game_square_piece(game g, int x, int y) {

    piece tmp_p = new_piece(x, y, 1, 1, true, true);  // Create a piece with coordonates (x, y) in order to test if another piece intersect this one.

    for (int i = 0; i < g->nb_pieces; ++i)
        if (intersect((cpiece)tmp_p, (cpiece)g->pieces[i])){
            free(tmp_p);
            return i;
        }
    free(tmp_p);
    return -1;
}
