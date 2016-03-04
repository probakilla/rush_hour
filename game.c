#include <stdio.h>
#include <stdlib.h>
 
#include "game.h"
#include "piece.h"
#include "game_texte.h"
 
#define DIMENSION 6

struct game_s{
  int nb_moves;
  int nb_pieces;
  piece *pieces;
};

game new_game_hr (int nb_pieces, piece *pieces){ //We suppose that the piece i = 0 is the "red one", the one we have to lead to exit).
  game  current = malloc(sizeof(struct game_s)); //Allocation of the structure
  current->nb_pieces = nb_pieces;
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
  dst->nb_moves = src->nb_moves;
  dst->nb_pieces = src->nb_pieces;
  for (int i = 0; i<game_nb_pieces(src);i++){
    copy_piece(src->pieces[i],dst->pieces[i]);
  }
}
  
  
 
 
int game_nb_pieces(cgame g) {
  return g->nb_pieces;
}
 
cpiece game_piece(cgame g, int piece_num) {
  return g->pieces[piece_num];
    
}
 
bool game_over_hr(cgame g) {
  return get_y(g->pieces[0]) == 4 && get_x(g->pieces[0]) == 3;
}
 
bool play_move(game g, int piece_num, dir d, int distance) {
  

  if (distance < 0){
    return false;
  }

  if (piece_num <= 0 && piece_num >= game_nb_pieces(g) ){
    return false; 
  }

  if (is_horizontal((piece)game_piece(g,piece_num))){ //LEFT or RIGHT
    if ( d == LEFT && get_x((piece)game_piece(g,piece_num)) - distance >= 0 ){ //LEFT and check if the piece is still in the grid
      for (int i = 0; i < piece_num; ++i){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      for (int i = piece_num + 1; i<game_nb_pieces(g); i++){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      move_piece((piece)game_piece(g,piece_num),d,distance);
      g->nb_moves +=1;
      return true;
    }

    int extends_piece = get_width((piece)game_piece(g,piece_num)) - 1;
    if ( d == RIGHT  && get_x((piece)game_piece(g,piece_num)) + distance + extends_piece < DIMENSION - 1 ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < piece_num; ++i){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      for (int i = piece_num + 1; i<game_nb_pieces(g); i++){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      move_piece((piece)game_piece(g,piece_num),d,distance);
      g->nb_moves +=1;
      return true;
    }
  }

  if (!is_horizontal((piece)game_piece(g,piece_num))){ //UP or DOWN
    if ( d == DOWN && get_y((piece)game_piece(g,piece_num)) - distance >= 0 ){//DOWN and check if the piece is still in the grid
      for (int i = 0; i < piece_num; ++i){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      for (int i = piece_num + 1; i<game_nb_pieces(g); i++){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      move_piece((piece)game_piece(g,piece_num),d,distance);
      g->nb_moves +=1;
      return true;
    }

    move_piece((piece)game_piece(g,piece_num),d,distance);
    g->nb_moves +=1;
    return true;



    int extends_piece = get_height((piece)game_piece(g,piece_num)) -1 ;
    if ( d == UP  && get_y((piece)game_piece(g,piece_num)) + distance + extends_piece < DIMENSION - 1 ){ //RIGHT and check if the piece is still in the grid
      for (int i = 0; i < piece_num; ++i){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      for (int i = piece_num + 1; i<game_nb_pieces(g); i++){
	if(intersect((piece)game_piece(g,piece_num),g->pieces[i]))
	  return false;
      }
      move_piece((piece)game_piece(g,piece_num),d,distance);
      g->nb_moves +=1;
      return true;
    }
  }
}
   
    
int game_nb_moves(cgame g) {
  return g->nb_moves;
}
