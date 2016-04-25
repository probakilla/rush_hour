#include "game.h"
#include "utils.h"


bool pieces_equality(cpiece p, cpiece p2){
    return get_x(p) != get_x(p2) || get_y(p) != get_y (p2);
}

bool games_equality(game g, game g2){
    for (int i = 0 ; i < game_nb_pieces(g); ++i){
        if (pieces_equality(game_piece(g, i), game_piece(g2, i)) == true){
            return false;
        }
    }
    return true;
}