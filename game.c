#include <stdio.h>
#include <stdlib.h>
 
#include "game.h"
#include "piece.h"
#include "game_texte.h"
 
#define DIMENSION 6

struct game_s{
  int nb_moves;
  piece *pieces;
};

game new_game_hr (int nb_pieces, piece *pieces){ //We suppose that the piece i = 0 is the "red one", the one we have to lead to exit).
  game  current = malloc(sizeof(struct game_s)); //Allocation of the structure
  current.nb_moves = 0;
   
  current->grid = malloc(DIMENSION * sizeof(int*));       // Creation of the game board
  for (int i = 0; i<DIMENSION; i++){
    current->grid[i] = malloc(DIMENSION * sizeof(int));
    for (int j = 1; j<DIMENSION; ++j){
      current->grid[i][j] = -1;
    }
  }
  
  int piece_name = 1;
  for (int i = 0; i< (sizeof(pieces) / sizeof(struct piece_s)); i++){    // search in the array of pieces DOESN'T WORK WITH THE PIECE IN THE CASE (0,x)
    if (is_horizontal(*pieces)){
      for (int j = get_x(*pieces); j <= get_width(*pieces); j++){ //j is the starting point to place the piece
	current->grid[get_y(*pieces)][j] = piece_name;
      }
    }
    else{
      for(int j = get_y(*pieces); j <= get_height(*pieces); j++){
	current->grid[j][get_x(*pieces)] = piece_name;
      }
    }
    ++piece_name;
    ++pieces;
  }
  return current;
}
void delete_game (game g) {
  g->nb_moves = -1;
  for (int i = 0; i < (sizeof(g->pieces) / sizeof(piece[0])); ++i)
    free(pieces[i]);
  free(pieces);
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
  int max = 0;                         // The number of pieces in the array. Its the maximum we should find in the grid + 1 (with the 0 piece)
  for (int i =0; i<DIMENSION; i++)
    for (int j = 0; j<DIMENSION; j++)
      if (g->grid[i][j] > max)
	max = g->grid[i][j];          // calcul du max
  
  return max + 1;
}
 
cpiece game_piece(cgame g, int piece_num) {
  cpiece res;
  for (int i =0; i<DIMENSION; i++)
    for (int j = 0; j<DIMENSION; j++)
      if (g->grid[i][j] == piece_num)
	for (int k = 0;k < (sizeof(g->pieces) / sizeof(g->pieces[0])); ++k)
	  if (i == get_x(g->pieces[k]) && j == get_y(g->pieces[k]))
	    res = g->pieces[k];
  return res;
}
 
bool game_over_hr(cgame g) {
  return g->grid[3][4] == 0;
}
 
bool play_move(game g, int piece_num, dir d, int distance) {

  if (distance < 0){
    return false;
  }

  if (piece_num <= 0 && piece_num >= game_nb_pieces(g) ){
    return false; 
  }
  
  piece move = game_piece(g,piece_num);
  int taille = 0;
  
  if (move_copy.small == true)
    taille = 2;
  else
    taille = 3;
   

  int taille = 0;
   
  if (is_horizontal(move)){ //LEFT or RIGHT
    if ( d == LEFT && get_x(move) - distance >= 0 ){ //LEFT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    return true;

    int extends_piece = get_width(move);
    if ( d == RIGHT  && get_x(move) + distance + extends_piece < DIMENSION ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    return true;
  }

  if (!is_horizontal(move)){ //UP or DOWN
    if ( d == DOWN && get_y(move) - distance >= 0 ){ //DOWN and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    return true;


    int extends_piece = get_height(move);
    if ( d == UP  && get_y(move) + distance + extends_piece < DIMENSION ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    return true;
  }
}

    
     
 
 
int game_nb_moves(cgame g) {

  return g->nbMoves;

}
