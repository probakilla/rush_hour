#include <stdlib.h>
#include <stdio.h>

#include "piece.h"



piece new_piece_rh (int x, int y, bool small, bool horizontal) {
  piece new = malloc(sizeof(struct piece_s));
  new->x = x;
  new->y = y;
  new->small = small;
  new->horizontal = horizontal;
  return new;
}

void delete_piece (piece p) { // pas sûr
    p->x = -1;
    p->y = -1;
    free(p); //libère la mémoire de la pièce
}

void copy_piece (cpiece src, piece dst) {
    dst->x = src->x;
    dst->y = src->y;
    dst->small = src->small;
    //dst->color = src->color;
    dst->horizontal = src->horizontal;
}

void move_piece (piece p, dir d, int distance) {
   
}


bool intersect(cpiece p1, cpiece p2) {
  
    if ( p1->horizontal == p2->horizontal ){  //Verifie si les pieces sont horizontales et ont des ordonnées différentes
        if ( p1->horizontal == true ){
            if ( p1->y != p2->y ){
                return false;
            }
        }
    }
    
if ( p1->horizontal == p2->horizontal ) //Verifie si les pieces sont verticales et ont des abscisses différentes
        if (p1->horizontal == false )
            if ( p1->x != p2->x )
                return false;
        
    
    
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
            if (p1->horizontal == true && p2 ->horizontal == false){
                if (p1->x+i == p2->x && p1->y == p2->y-j)
                    return true;
            }
            else {
                if (p1->x == p2->x+j && p1->y-j == p2->y)
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

