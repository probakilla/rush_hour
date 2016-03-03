#include <stdlib.h>
#include <stdio.h>

#include "piece.h"


struct piece_s {
  int x, y;
  bool small;
  const int color; //later
  bool horizontal;
};

<<<<<<< HEAD
=======




>>>>>>> 004a85afcdfbe420e0ae6d400d3230c2f4a497c9
piece new_piece_rh (int x, int y, bool small, bool horizontal) {
  piece new = malloc(sizeof(struct piece_s));
  new->x = x;
  new->y = y;
  new->small = small;
  new->horizontal = horizontal;
  return new;
}

void delete_piece (piece p) { 
  p->x = -1;
  p->y = -1;
  free(p);
}

void copy_piece (cpiece src, piece dst) {
  dst->x = src->x;
  dst->y = src->y;
  dst->small = src->small;
  dst->horizontal = src->horizontal;
}

void move_piece (piece p, dir d, int distance) {
  if (p->horizontal == true){
    if (d == 1)
      p->x -= distance;
    else if (d == 3)
      p->x += distance;
  }
  else{
    if (d == 0)
      p->y += distance;
    else if (d == 2)
      p->y -= distance;
  }     
}


bool intersect(cpiece p1, cpiece p2) {
  
  if ( p1->horizontal == p2->horizontal ){  //Check if pieces are horizontal and have differents y
    if ( p1->horizontal == true ){
      if ( p1->y != p2->y ){
	return false;
      }
    }
  }
    
  if ( p1->horizontal == p2->horizontal ) //Check if pieces are vertical and have differents x
    if (p1->horizontal == false )
      if ( p1->x != p2->x )
	return false;
        
    
    
  int piece1_extends = 0;
  int piece2_extends= 0;
    
  if (p1->small == false)
    piece1_extends = 2;
  else 
   piece1_extends = 1;
    
  if (p2->small == false)
    piece2_extends= 2;
  else 
    piece2_extends= 1;
    
  if (p1->horizontal == true && p2 ->horizontal == false){ 
    if (p2->x >= p1->x && p2->x <= p1->x + piece1_extends) // Test if abscissa of p2 is between the abscissa of p1
      if (p1->y >= p2->y && p1->y <= p2->y +piece2_extends) // Same test for the y of p1
	return true;
  }
  else {
    if (p1->x >= p2->x && p1->x <= p2->x + piece2_extends) // Test if abscissa of p1 is between the abscissa of p2 
      if (p2->y >= p1->y && p2->y <= p1->y + piece1_extends)// Same test for the y of p2 
	return true;
     
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
  if(p->small==true && p->horizontal==false)
    return 1;
  if(p->small==false && p->horizontal==false)
    return 2;
}

int get_width(cpiece p) {
  if(p->small==true && p->horizontal==true)
    return 1;
  if(p->small==false && p->horizontal==true)
    return 2;
}

bool is_horizontal(cpiece p) {
  return p->horizontal;
}

