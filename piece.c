#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "piece.h"


struct piece_s {
  int x, y;
  bool small;
  bool horizontal;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

piece new_piece_rh (int x, int y, bool small, bool horizontal) { //Allocation of the structure and the fields.
  piece new = malloc(sizeof(new));
  assert(new != NULL);

  new->x = x;
  new->y = y;
  new->small = small;
  new->horizontal = horizontal;

  // Useless values for RushHour
  int width = 0;
  int height = 0;
  bool move_x = false;
  bool move_y = false;

  return new;
}

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
  piece new = malloc(sizeof(new));
  assert(new != NULL);

  new->x = x;
  new->y = y;
  new->width = width;
  new->height = height;
  new->move_x = move_x;
  new->move_y = move_y;

  return new;
}

void delete_piece (piece p) { //Resetting coordinates and freeing structure.
  p->x = -1;
  p->y = -1;
  free(p);
}

void copy_piece (cpiece src, piece dst) { // Copy each field from the source to the destination.
  dst->x = src->x;
  dst->y = src->y;
  dst->small = src->small;
  dst->horizontal = src->horizontal;
}

void move_piece (piece p, dir d, int distance) { //The move is supposed correct. Add or substract the distance to the coordinates.
  if (p->horizontal == true){
    if (d == LEFT)
      p->x -= distance;
    else if (d == RIGHT)
      p->x += distance;
  }
  else{
    if (d == UP)
      p->y += distance;
    else if (d == DOWN)
      p->y -= distance;
  }     
}


bool intersect(cpiece p1, cpiece p2) {
  if ( p1->horizontal == p2->horizontal ){  //Check if pieces are horizontal and have differents y so don't intersect.
    if ( p1->horizontal == true ){
      if ( p1->y != p2->y ){
	return false;
      }
    }
  }
    
  if ( p1->horizontal == p2->horizontal ) //Check if pieces are vertical and have differents x so don't intersect.
    if (p1->horizontal == false )
      if ( p1->x != p2->x )
	return false;
       
  int piece1_extends = 0;  
  int piece2_extends= 0;
  
  if (p1->small == false) // Add the "extension" to the piece.
    piece1_extends = 2;
  else 
   piece1_extends = 1;
    
  if (p2->small == false)
    piece2_extends= 2;
  else 
    piece2_extends= 1;
    
  if (p1->horizontal == true && p2 ->horizontal == false){ 
    if (p2->x >= p1->x && p2->x <= p1->x + piece1_extends){ // Test if abscissa of p2 is between the abscissa of p1.
      if (p1->y >= p2->y && p1->y <= p2->y +piece2_extends) {// Same test for the y of p1.
	return true;
      }
    }
  }
  else {
    if (p1->x >= p2->x && p1->x <= p2->x + piece2_extends){ // Test if abscissa of p1 is between the abscissa of p2.
      if (p2->y >= p1->y && p2->y <= p1->y + piece1_extends){// Same test for the y of p2.
	return true;
      }
    }
  }   
  return false;
}

int get_x(cpiece p) {
  return p->x;
}

int get_y(cpiece p) {
  return p->y;
}


int get_height(cpiece p) {
  if (p->horizontal == true)
    return 1;
  if(p->small==true && p->horizontal==false)
    return 2;
  if(p->small==false && p->horizontal==false)
    return 3;
}

int get_width(cpiece p) {
  if (!p->horizontal)
    return 1;
  if(p->small==true && p->horizontal==true)
    return 2;
  if(p->small==false && p->horizontal==true)
    return 3;
}

bool is_horizontal(cpiece p) {
  return p->horizontal;
}

bool can_move_x(cpiece p){
  return p->move_x;
}
bool can_move_y(cpiece p){
  return p->move_y;
}

