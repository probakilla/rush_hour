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
  current->nb_moves = 0;

  current->pieces = malloc(sizeof(piece) * nb_pieces);
  if (current->pieces == NULL)
    printf("ERREUR D'ALLOCATION");

  for (int i = 0; i<nb_pieces;i++){
    current->pieces[i] = new_piece_rh(0,0,false,false);
    copy_piece(pieces[i],current->pieces[i]); 
  }
  return current;
  
}
void delete_game (game g) {
  g->nb_moves = -1;
  for (int i = 0; i < game_nb_pieces(g); ++i)
    free(g->pieces[i]);
  free(g->pieces);
}
 
void copy_game (cgame src, game dst) {
  dst->nb_moves = src ->nb_moves;
  for (int i = 0; i<game_nb_pieces(src) + 2;i++){
    copy_piece(src->pieces[i],dst->pieces[i]);
  }
}
  
  
 
 
int game_nb_pieces(cgame g) {
  return sizeof(g->pieces) / sizeof(g->pieces[0]);
}
 
cpiece game_piece(cgame g, int piece_num) {
  return g->pieces[piece_num];
    
}
 
bool game_over_hr(cgame g) {
  return get_x(g->pieces[0] ) == 4 && get_y(g->pieces[0]) == 3;
}
 
bool play_move(game g, int piece_num, dir d, int distance) {

  if (distance < 0){
    return false;
  }

  if (piece_num <= 0 && piece_num >= game_nb_pieces(g) ){
    return false; 
  }
  
  piece move = (piece)game_piece(g,piece_num);
   
  if (is_horizontal(move)){ //LEFT or RIGHT
    if ( d == LEFT && get_x(move) - distance >= 0 ){ //LEFT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    g->nb_moves +=1;
    return true;

    int extends_piece = get_width(move);
    if ( d == RIGHT  && get_x(move) + distance + extends_piece < DIMENSION ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    g->nb_moves +=1;
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
    g->nb_moves +=1;
    return true;


    int extends_piece = get_height(move);
    if ( d == UP  && get_y(move) + distance + extends_piece < DIMENSION ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < game_nb_pieces(g); ++i){
	if (intersect(move,g->pieces[i]))
	  return false;
      }
    }
    move_piece(move,d,distance);
    g->nb_moves +=1;
    return true;
  }
}

    
     
 
 
int game_nb_moves(cgame g) {

  return g->nb_moves;

}
