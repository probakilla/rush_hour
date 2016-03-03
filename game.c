#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "game_texte.h"

#define DIMENSION 6


game new_game_hr (int nb_pieces, piece *pieces){ //On suppose que dans le tableau de piece, la piece � i = 0 est la piece a faire sortir pour gagner (voiture rouge)
    game  current = malloc(sizeof(struct game_s)); //Allocation de la structure
    current->nbMoves = 0;

    current->grid = malloc(DIMENSION * sizeof(int*));       // Cr�ation de la grille de jeu
    for (int i = 0; i<DIMENSION; i++){
        current->grid[i] = malloc(DIMENSION * sizeof(int));
	for (int j = 1; j<DIMENSION; ++j){
	  current->grid[i][j] = -1;
	}
    }

    int nomPiece = 1;
    for (int i = 0; i< (sizeof(pieces) / sizeof(struct piece_s)); i++){    //Parcours du tableau de pieces NE FONCTIONNE PAS POUR UNE PIECE de coordonn�es (0,x)
        if (is_horizontal(*pieces)){
            for (int j = get_x(*pieces); j <= get_width(*pieces); j++){ //j sert de point de d�part pour placer la piece
                current->grid[get_y(*pieces)][j] = nomPiece;     //abscisse fixe ordonn�e variable
            }
        }
        else{
           for(int j = get_y(*pieces); j <= get_height(*pieces); j++){
               current->grid[j][get_x(*pieces)] = nomPiece;
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
	for (int k = 0;k < (sizeof(g->pieces) / sizeof(struct piece_s)); ++k)
	       if (i == g->pieces[k]-> y && j == g->pieces[k]-> x)
		 res = g->pieces[k];
  return res;
}

bool game_over_hr(cgame g) {
  return g->grid[3][4] == 0;
}

bool play_move(game g, int piece_num, dir d, int distance) {
  piece move = game_piece(g,piece_num);
  piece moveCp = move;
  
if (move->horizontal){ //LEFT or RIGHT
    
    if ( d == 1 && move->x - distance >= 0 ){ //LEFT
      moveCp->x -= distance;
      for (int i = 0; i<DIMENSION; i++){
	for (int j = 0; j<DIMENSION; j++){
	  if ( grid[i][j] != -1){
	    if (intersect(game_piece(g,grid[i][j]), moveCp)
		return false;
	  }
	}
      }
    move->x -= distance;
    return true;
    }

    if ( d == 1 && move->x - distance >= 0 ){ //RIGHT
      moveCp->x += distance;
      for (int i = 0; i<DIMENSION; i++){
	for (int j = 0; j<DIMENSION; j++){
	  if ( grid[i][j] != -1){
	    if (intersect(game_piece(g,grid[i][j]), moveCp)
		return false;
	  }
	}
      }
    move->x -= distance;
    return true;
    }

if (move->horizontal != true){ //UP or DOWN
    
    if ( d == 1 && move->x - distance >= 0 ){ //DOWN
      moveCp->y -= distance;
      for (int i = 0; i<DIMENSION; i++){
	for (int j = 0; j<DIMENSION; j++){
	  if ( grid[i][j] != -1){
	    if (intersect(game_piece(g,grid[i][j]), moveCp)
		return false;
	  }
	}
      }
    move->y -= distance;
    return true;
    }

    if ( d == 1 && move->x - distance >= 0 ){ //UP
      moveCp->x -= distance;
      for (int i = 0; i<DIMENSION; i++){
	for (int j = 0; j<DIMENSION; j++){
	  if ( grid[i][j] != -1){
	    if (intersect(game_piece(g,grid[i][j]), moveCp)
		return false;
	  }
	}
      }
    move->x -= distance;
    return true;
    }
	 
	    	      
	 
       
     
    
 
}


int game_nb_moves(cgame g) {
  return g->nbMoves;
}

