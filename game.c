#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

#define DIMENSION 6


game new_game_hr (int nb_pieces, piece *pieces){ //On suppose que dans le taleau de piece, la piece � i = 0 est la piece a faire sortir pour gagner (voiture rouge)
    game  current = malloc(sizeof(struct game_s)); //Allocation de la structure
    current->nbMoves = 0;

    current->grid = malloc(DIMENSION * sizeof(int*));       // Cr�ation de la grille de jeu
    for (int i = 0; i<DIMENSION; i++){
        current->grid[i] = malloc(DIMENSION * sizeof(int));
    }
    
    int nomPiece = 1;
    for (int i = 0; i< sizeof(g->pieces / sizeof(struct piece); i++){    //Parcours du tableau de pieces NE FONCTIONNE PAS POUR UNE PIECE de coordonn�es (0,x)
        if (is_horizontal(pieces)){
            for (int j = get_x(pieces); j <= get_width(pieces); j++){ //j sert de point de d�part pour placer la piece
                current->grid[get_y(pieces)][j] = nomPiece;     //abscisse fixe ordonn�e variable
            }
        }
        else{
           for(int j = get_y(pieces); j <= get_height(pieces); j++){
               current->grid[j][get_x(pieces)] = nomPiece;
           } 
        }
        ++nomPiece;
        ++pieces;
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
    dst->nbMoves = src ->nbMoves;
    for (int i =0; i<DIMENSION; i++){
        for (int j = 0; j<DIMENSION; j++){
            dst->grid[i][j] = src->grid[i][j];
        }
    }
}

int game_nb_pieces(cgame g) {
  int max = 0;                         // Le nombre de pi�ces du tableau est le nombre maximum qu'on trouvera dans la grille +1 (en comptant la pi�ce 0)
  for (int i =0; i<DIMENSION; i++)     // Parcours du tableau
    for (int j = 0; j<DIMENSION; j++)
      if (g->grid[i][j] > max)
	max = g->grid[i][j];          // calcul du max
        
  return max + 1;
}

cpiece game_piece(cgame g, int piece_num) {
  cpiece res;
  for (int i =0; i<DIMENSION; i++)     // Parcours du tableau
    for (int j = 0; j<DIMENSION; j++)
      if (g->grid[i][j] == piece_num)
	for (int k = 0;k < sizeof(g->pieces / sizeof(struct piece); ++k)
	       if (i == g->pieces[k]-> y && j == g->pieces[k]-> x)
		 res = g->pieces[k];
  return res;
}

bool game_over_hr(cgame g) {
  return g->grid[3][4] == 0;
}


int game_nb_moves(cgame g) {
  return g->nbMoves;
}
