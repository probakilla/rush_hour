#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "piece.h"

int max (int a, int b) {
  if (a > b)
    return a;
  return b;
}

int min (int a, int b) {
  if (a < b)
    return a;
  return b;
}


struct piece_s { //struct with : coord of the inital point, length, orientation, possibility of move.
  int x, y;
  bool small;
  bool horizontal;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

piece new_piece_rh(int x, int y, bool small, bool horizontal) { //Allocation of the structure and the fields.
  piece new = malloc(sizeof(struct piece_s));
  assert(new != NULL);

  new->x = x;
  new->y = y;
  new->small = small;
  new->horizontal = horizontal;

  // Useless values for RushHour
  if (new->small && new->horizontal){
      new->width = 2;
      new->height = 1;
      new->move_x = true;
      new->move_y = false;
  }
  else if (new->small == false && new->horizontal){
      new->width = 3;
      new->height = 1;
      new->move_x = true;
      new->move_y = false;
  }
  else if (new->small && new->horizontal == false){
      new->width = 1;
      new->height = 2;
      new->move_x = false;
      new->move_y = true;
  }
  else if (new->small == false && new->horizontal == false){
      new->width = 1;
      new->height = 3;
      new->move_x = false;
      new->move_y = true;
  }
  return new;
}

piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y) { //Allocation of the structure and the fields.
  piece new = malloc(sizeof(struct piece_s));
  assert(new != NULL);

  new->x = x;
  new->y = y;
  new->width = width;
  new->height = height;
  new->move_x = move_x;
  new->move_y = move_y;

  if (move_x == true && move_y == false){
      new->small = false;
      new->horizontal = true;
  }
  if (move_x == false && move_y == true){
      new->small = false;
      new->horizontal = false;
  }
  return new;
}

void delete_piece(piece p) { //free the structure.
  free(p);
}

void copy_piece(cpiece src, piece dst) { // Copy each field from the source to the destination.
  dst->x = src->x;
  dst->y = src->y;
  dst->small = src->small;
  dst->horizontal = src->horizontal;
  dst->width = src->width;
  dst->height = src->height;
  dst->move_x = src->move_x;
  dst->move_y = src->move_y;
}

void move_piece(piece p, dir d, int distance) { //The move is supposed correct. Add or substract the distance to the coordinates.
  if (p->move_x == true && p->move_y == true) {
      if (d == LEFT)
	p->x -= distance;
      else if (d == RIGHT)
	p->x += distance;
      if (d == UP)
	p->y += distance;
      else if (d == DOWN)
	p->y -= distance;
  }
  if (p->move_x == true && p->move_y == false) {
      if (d == LEFT)
	p->x -= distance;
      else if (d == RIGHT)
	p->x += distance;
  }
  else if(p->move_x == false && p->move_y == true){
      if (d == UP)
	p->y += distance;
      else if (d == DOWN)
	p->y -= distance;
  }
}



/* --------------------- 

This fonction tests if two pieces intersect. 
The first two if check two dispositions where no intersection is made.
After that the fonction test the bounds of each piece to tell if there is intersection or not.

--------------------- */


bool intersect(cpiece p1, cpiece p2) {

  if ( (p2->x >= p1->x && p2->x <= p1->x + get_width(p1)-1 ) || (p1->x+get_width(p1)-1 >= p2->x &&  p1->x+get_width(p1)-1 <= p2->x + get_width(p2) -1) ){
      if ( (p2-> y >= p1->y && p2->y <= p1->y + get_height(p1)-1 ) || (p1->y+get_height(p1)-1 >= p2->y &&  p1->y+get_height(p1)-1 <= p2->y + get_height(p2) -1) ){
	  return true;
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
  return p->height;
}

int get_width(cpiece p) {
  return p->width;
}

bool is_horizontal(cpiece p) {
  return p->horizontal;
}

bool can_move_x(cpiece p) {
  return p->move_x;
}

bool can_move_y(cpiece p) {
  return p->move_y;
}
