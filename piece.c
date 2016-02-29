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
  
    if (p1->horizontal == p2->horizontal){  //Verifie si les pieces sont horizontales et ont des ordonnées différentes
        if (p1->horizontal == true ){
            if (p1->y != p2->y){
                return false;
            }
        }
    }
    
    if (p1->horizontal == p2->horizontal){ //Verifie si les pieces sont verticales et ont des abscisses différentes
        if (p1->horizontal == false ){
            if (p1->x != p2->x){
                return false;
            }
        }
    }
    
    int tailleP1 = 0;
    int tailleP2 = 0;
    
    if (p1->small == false)
        tailleP1 = 3;
    else 
        tailleP1 = 2;
    
    if (p2->small == false)
        tailleP2 = 3;
    else 
        tailleP2 = 2;
    
    for (int i =0; i<tailleP1; ++i){
        for (int j = 0; j<tailleP2; ++j){
            if (p1->x == p2->x && p1->y == p2->y){
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

