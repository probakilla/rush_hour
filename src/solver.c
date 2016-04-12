#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"


#define ALLOC 300
#define NB_PIECES 3

game game_from_file(FILE * f){

    game g;

    int width_game, height_game, nb_pieces;
    int x,y, width_p, height_p;
    int can_move_x, can_move_y;

    fscanf(f,"%d %d", &width_game, &height_game);
    fscanf(f,"%d",&nb_pieces);

    piece *pieces = malloc (sizeof(*pieces) * nb_pieces);


    for (int i = 0; i < nb_pieces; i++){
        fscanf(f,"%d %d %d %d %d %d", &x, &y, &width_p, &height_p, &can_move_x, &can_move_y);
        pieces[i] = new_piece(x,y,width_p,height_p,can_move_x,can_move_y);
    }

    g = new_game(width_game,height_game,nb_pieces,pieces);
    return g;



}

bool tableauPlein(game *t, int *pk,int iR){
    return iR == *pk * ALLOC - 1;
}

game* agrandirTableau(game *t, int *pk, int iR){
    if (tableauPlein(t,pk,iR)){
        t = realloc(t, sizeof(game) * (ALLOC * (*pk+1)));
        (*pk) += 1 ;
    }
    return t;
}

bool egalitePiece(cpiece p, cpiece p2){  // Regarde si deux meme pieces sont egales dans deux jeux differents
    return get_x(p) == get_x(p2) && get_y(p) == get_y (p2);
}


bool egaliteJeux(game g, game g2){ // regarde si deux jeux sont egaux en ne comparant que leurs pieces
    for (int i = 0 ; i < game_nb_pieces(g); ++i){
        if (egalitePiece(game_piece(g,i),game_piece(g2,i)) == false){
            return false;
        }
    }
    return true;
}

bool rechercheTableau(game *t, game g, int IndiceTableauRempli){ // Regarde si le jeu passé en parametre correspond a un des jeux du tableau
    for (int i = 0; i < IndiceTableauRempli; ++i){
        if (egaliteJeux(g,t[i]) == true)
            return true;
    }
    return false;
}






int main(){

    clock_t t1,t2;

    t1 = clock();
    // Resolvable en 13 coups
    piece *pieces1 = malloc (sizeof(*pieces1) * NB_PIECES);

    pieces1[0] = new_piece_rh (3, 3, true,  true);   // x, y , small , horizontal
    pieces1[1] = new_piece_rh (3, 0, true, false);
    pieces1[2] = new_piece_rh (4, 1, true , true);
    pieces1[3] = new_piece_rh (5, 3, false , false);
    //pieces1[4] = new_piece_rh (2, 0, true , true);
    //pieces1[5] = new_piece_rh (4, 0, false , false);

    game g = new_game_hr(NB_PIECES,pieces1);
    game tmp = new_game_hr(NB_PIECES,pieces1);
    queue q = new_queue();
    game *tabGame = malloc (ALLOC * sizeof(game));

    int k = 1; //multiple de la taille ALLOC
    int* pK = &k;
    int indice_r = 0;

    push(q,tmp);
    copy_game(g,tmp);
    tabGame[indice_r] = tmp;
    indice_r ++;  //indice remplissage tableau

    while(!game_over_hr(g)){

        copy_game(pop(q), g);
        for (int i = 0; i < game_nb_pieces(g); i++){
            if (can_move_x(game_piece(g,i))){
            	game tmp = new_game_hr(NB_PIECES,pieces1);
            	copy_game(g,tmp);
                if (play_move(tmp,i,RIGHT, 1)){
                    if(rechercheTableau(tabGame, g, indice_r) == false){
                        push(q,tmp);
                        tabGame = agrandirTableau(tabGame,pK,indice_r);
                        tabGame[indice_r] = tmp;
                        indice_r++;
                    }
                    //play_move(g,i,LEFT,1);   //Remet la piece a l'etat initial

                }
                game tmp2 = new_game_hr(NB_PIECES,pieces1);
                copy_game(g,tmp2);
                if (play_move(tmp2,i,LEFT, 1)){
                    if(rechercheTableau(tabGame, g,indice_r) == false){
                        push(q,tmp2);
                        tabGame = agrandirTableau(tabGame,pK,indice_r);
                        tabGame[indice_r] = tmp2;
                        indice_r++;
                    }
                    //play_move(g,i,RIGHT,1);   //Remet la piece a l'etat initial
                }
            }
            if (can_move_y(game_piece(g,i))){
            	game tmp = new_game_hr(NB_PIECES,pieces1);
            	copy_game(g,tmp);
                if (play_move(tmp,i,UP, 1)){
                    if(rechercheTableau(tabGame, g,indice_r) == false){
                        push(q,tmp);
                        tabGame = agrandirTableau(tabGame,pK,indice_r);
                        tabGame[indice_r] = tmp;
                        indice_r++;
                    }
                    //play_move(g,i,DOWN,1);   //Remet la piece a l'etat initial

                }
                game tmp2 = new_game_hr(NB_PIECES,pieces1);
                copy_game(g,tmp2);
                if (play_move(tmp2,i,DOWN, 1)){
                    if(rechercheTableau(tabGame, g,indice_r) == false){
                        push(q,tmp2);
                        tabGame = agrandirTableau(tabGame,pK,indice_r);
                        tabGame[indice_r] = tmp2;
                        indice_r++;
                    }
                }
            }
        }
    }
    t2 = clock();
    float tps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("terminé en %d mouvements et %f secondes\n", game_nb_moves(g),tps);
}
