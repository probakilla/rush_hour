#include <stdlib.h>
#include <stdio.h>

#include "piece.h"



piece new_piece_rh (int x, int y, bool small, bool horizontal) {
  piece p;
  return p;
}

void delete_piece (piece p) {
}

void copy_piece (cpiece src, piece dst) {

}

void move_piece (piece p, dir d, int distance) {

}


bool intersect(cpiece p1, cpiece p2) {
  return 0;
}

int get_x(cpiece p) {
  return p->x;
}

int get_y(cpiece p) {
  return p->y;
}


int get_height(cpiece p) {
  	if(p->horizontal==true)
		return 1;
	if(p->small==true && p->horizontal==false)
		return 2;
	if(p->small==false && p->horizontal==false)
		return 3;
}

int get_width(cpiece p) {
	if(p->horizontal==false)
		return 1;
	if(p->small==true && p->horizontal==true)
		return 2;
	if(p->small==false && p->horizontal==true)
		return 3;
}

bool is_horizontal(cpiece p) {
  return p->horizontal;
}

