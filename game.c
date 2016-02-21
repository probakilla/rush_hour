#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

#define DIMENSION 6


game new_game_hr (int nb_pieces, piece *pieces){ //On suppose que dans le taleau de piece, la piece à i = 0 est la piece a faire sortir pour gagner (voiture rouge)
    game  current = malloc(sizeof(struct game_s)); //Allocation de la structure
    current->nbMoves = 0;

    current->grid = malloc(DIMENSION * sizeof(int*));       // Création de la grille de jeu
    for (int i = 0; i<DIMENSION; i++){
        current->grid[i] = malloc(DIMENSION * sizeof(int));
    }
    return current;
}
void delete_game (game g) {
    for (int i = 0; i<DIMENSION; i++){ //free des sous tableaux
        free(g->grid[i]);
    }
    free(g->grid); //free du tableau restant
    free(g);    //free de la structure

}

void copy_game (cgame src, game dst) {
}

int game_nb_pieces(cgame g) {
  return g;
}

cpiece game_piece(cgame g, int piece_num) {
  cpiece piece;
  return piece;
}

bool game_over_hr(cgame g) {
  return true;
}
