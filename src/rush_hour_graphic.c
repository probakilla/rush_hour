#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "game.h"

#define HEIGHT_VIDEO 600
#define WIDTH_VIDEO 600
#define NB_PIECES 7
#define NB_BOX 6
#define COLOR_BITS 32
#define SIZE_COLOR 8

SDL_Surface* screen;

//Init screen
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

//set a color to a pixel
void setPixel(int x, int y, Uint32 coul){
    *((Uint32*)(screen->pixels) + x + y * screen->w) = coul;
}

void refresh_screen(void){
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

//make a black screen to erase the older screen
void clear(void){
    for (int y = 0; y < HEIGHT_VIDEO ; ++y){
        for (int x = 0; x < WIDTH_VIDEO ; ++x)
            setPixel(x,y,SDL_MapRGB(screen->format,0,0,0));
    }
    refresh_screen();
}

dir choice_dir(cpiece p, int new_x, int new_y,int x, int y){
    dir res = -1;

    if(can_move_x(p)){
        if (new_x > x && new_y == y)
            res = RIGHT;
        if (new_x < x && new_y == y)
            res = LEFT;
    }
    if(can_move_y(p)){
        if (new_y > y && new_x == x)
            res = UP;
        if (new_y < y && new_x == x)
            res = DOWN;
    }
    return res;
}

//take a game and draw the different car on the screen
void drawcar(game game,float h_box, float w_box){

    // initialization of different colors
  int color[SIZE_COLOR][3] = {{255,0,0},{0,255,0},{0,0,255},{51,0,51},{255,255,0},{102,51,0}, {51,204,255}, {255,102,0}};

    for(int nb = 0; nb<NB_PIECES; nb ++){
        for (int y = h_box; y > 0; y--){
            for(int x = 0; x < w_box; x++){
	      if(!can_move_x(game_piece(game,nb)) && !can_move_y(game_piece(game,nb))){
		 setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,50,50,50));
                if(get_width(game_piece(game,nb))==2){
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,50,50,50));
                }
                if(get_width(game_piece(game,nb))==3){
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,50,50,50));
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box*2,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,50,50,50));
                }
                if(get_height(game_piece(game,nb))==2){
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box,SDL_MapRGB(screen->format,50,50,50));
                }
                if(get_height(game_piece(game,nb))==3){
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box,SDL_MapRGB(screen->format,50,50,50));
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box*2,SDL_MapRGB(screen->format,50,50,50));
                }
	      }
	      else{
                setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                if(get_width(game_piece(game,nb))==2){
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                }
                if(get_width(game_piece(game,nb))==3){
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                    setPixel(get_x(game_piece(game,nb))*w_box+x+w_box*2,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                }
                if(get_height(game_piece(game,nb))==2){
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                }
                if(get_height(game_piece(game,nb))==3){
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                    setPixel(get_x(game_piece(game,nb))*w_box+x,HEIGHT_VIDEO-get_y(game_piece(game,nb))*h_box-y-h_box*2,SDL_MapRGB(screen->format,color[nb][0], color[nb][1],color[nb][2]));
                }
	     }
            }
        }
    }
}


int main(int argc, char** argv){

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
    pieces1[6] = new_piece (5, 5, 1, 1, false, false);
    game game = new_game_hr(NB_PIECES, pieces1);

    float h_box = HEIGHT_VIDEO/NB_BOX;
    float w_box = WIDTH_VIDEO/NB_BOX;

    int clic_cpt = 0;

    SDL_Event event;

    int x = 0;
    int y = 0;

    int new_x = 0;
    int new_y = 0;

    int nb_piece = -1;

    initSDL();
    drawcar(game, h_box, w_box);
    refresh_screen();

    while(1){

      while (SDL_PollEvent(&event)){ //wait for an event
            switch(event.type) {

                case SDL_QUIT:
                    return EXIT_SUCCESS;
                    break;

                case SDL_MOUSEBUTTONDOWN:
		  if (event.button.button == SDL_BUTTON_LEFT && clic_cpt == 0){//when you choose a car

                        x = (int)(event.button.x/w_box);
                        y = (int)(event.button.y/h_box);
                        y = (NB_BOX -1 -y);

                        nb_piece = game_square_piece(game,x,y);
                        if (nb_piece != -1){
                            clic_cpt +=1;
                        }
                        break;
                    }

		  if (event.button.button == SDL_BUTTON_LEFT && clic_cpt == 1){//when the user click in a black box for move
                        new_x = (int)(event.button.x/w_box);
                        new_y = (int)(event.button.y/h_box);
                        new_y = (NB_BOX -1 -new_y);
                        if( new_y <= get_y(game_piece(game,game_square_piece(game,x,y)))+get_height(game_piece(game,game_square_piece(game,x,y)))-1 && new_y>=get_y(game_piece(game,game_square_piece(game,x,y))))
                            new_y=y;
                        if(new_x <= get_x(game_piece(game,game_square_piece(game,x,y)))+get_width(game_piece(game,game_square_piece(game,x,y)))-1 && new_x>=get_x(game_piece(game,game_square_piece(game,x,y))))
                            new_x=x;
                        play_move(game,nb_piece,choice_dir(game_piece(game,game_square_piece(game,x,y)),new_x,new_y,x,y),1);
                        if (game_over_hr(game)){
                            for (int i = 0 ; i < NB_PIECES; i++){
                                free(pieces1[i]);
                            }
                            free(pieces1);
                            fprintf(stdout," You win ! You finished this in %d moves.",game_nb_moves(game));
                            delete_game(game);
                            SDL_Quit();
                            exit(EXIT_SUCCESS);
                        }
                        clic_cpt = 0;
                        clear();
                        drawcar(game, h_box, w_box);
                        refresh_screen();
                    }
            }
        }
    }
}
  


