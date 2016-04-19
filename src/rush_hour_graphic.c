#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "game.h"
#include "piece.h"

#define HEIGHT_VIDEO 600
#define WIDTH_VIDEO 800
#define NB_PIECES 6
#define NB_BOX 6
#define COLOR_BITS 32

SDL_Surface* screen;
  
///////////////////////INIT SDL///////////////////////////

void initSDL(void){

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "ERROR INIT SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(WIDTH_VIDEO, HEIGHT_VIDEO, COLOR_BITS, SDL_SWSURFACE);
 
  if (screen == NULL) {
    fprintf(stderr, "ERROR GRAPHIC MODE: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  SDL_WM_SetCaption("Rush Hour", NULL);

}

///////////////////////////////Attendre Evenement////////////////////////////

void attendreTouche(void){

  SDL_Event event;
 
  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);

  /*  
      int continuer = 1;
    
      while (continuer) {

      SDL_WaitEvent(&event);

      switch(event.type) {

      case SDL_QUIT:
      continuer = 0;
      break;

      case SDL_MOUSEBUTTONDOWN:
	 
      if (event.button.button==SDL_BUTTON_LEFT)
      setPixel(12,15,couleurs[C_VERT_FONCE]);
      actualiser();
      break;

      default :

      break;
      }*/

}

/////////////////////////////SetPixel////////////////////////////////////////

void setPixel(int x, int y, Uint32 coul){
  *((Uint32*)(screen->pixels) + x + y * screen->w) = coul;
}

///////////////////////////Actualisation Ecran//////////////////////////////

void actualiser(void){
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

//////////////////////////Dessiner Grille//////////////////////////////////

void drawgrid(void){

  for (int i = 0; i < HEIGHT_VIDEO; i++){
    for(int y = 0; y< WIDTH_VIDEO; y++){
      setPixel(i,y,SDL_MapRGB(screen->format,0, 0x80,0));
    }
  }

}

//////////////////////////Dessiner Voiture//////////////////////////////////

void drawcar(void){

  // initialization of different game configurations
  piece *pieces1 = malloc (sizeof(*pieces1) * NB_PIECES);
  if (pieces1 == NULL){
    fprintf(stderr,"Error : bad allocation of pieces1, please restart the game.\n");
    exit(EXIT_FAILURE);
  }
  // FIRST GAME
  pieces1[0] = new_piece_rh (0, 3, true,  true);   // x, y , small , horizontal
  pieces1[1] = new_piece_rh (2, 3, false , false);
  pieces1[2] = new_piece_rh (0, 0, true , false); 
  pieces1[3] = new_piece_rh (1, 1, true , true);
  pieces1[4] = new_piece_rh (2, 0, true , true);
  pieces1[5] = new_piece_rh (4, 0, false , false);

  // initialization of different colors
  int color[NB_PIECES][3] = {{255,0,0},{0,255,0},{0,0,255},{51,0,51},{255,255,0},{102,51,0}};
  float h_box = HEIGHT_VIDEO/NB_BOX;
  float w_box = WIDTH_VIDEO/NB_BOX;

  for(int nb = 0; nb<NB_PIECES; nb ++){
    for (int y = h_box; y > 0; y--){
      for(int x = 0; x < w_box; x++){
	setPixel(get_x(pieces1[nb])*w_box+x,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	if(get_width(pieces1[nb])==2){
	  setPixel(get_x(pieces1[nb])*w_box+x+w_box,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	}
	if(get_width(pieces1[nb])==3){
	  setPixel(get_x(pieces1[nb])*w_box+x+w_box,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	  setPixel(get_x(pieces1[nb])*w_box+x+w_box*2,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	}
	if(get_height(pieces1[nb])==2){
	  setPixel(get_x(pieces1[nb])*w_box+x,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y-h_box,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	}
	if(get_height(pieces1[nb])==3){
	  setPixel(get_x(pieces1[nb])*w_box+x,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y-h_box,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	  setPixel(get_x(pieces1[nb])*w_box+x,HEIGHT_VIDEO-get_y(pieces1[nb])*h_box-y-h_box*2,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
	}
      }
    }
  }
}

/////////////////////MAIN////////////////////////////////////////////////////

int main(int argc, char** argv){

  initSDL();
  drawcar();
  actualiser();
  attendreTouche();
  return EXIT_SUCCESS;
}

