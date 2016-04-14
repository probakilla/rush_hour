#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"


#define ALLOC 10000

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

bool is_array_full(game *t, int *pk, int iR){
    return iR == *pk * ALLOC - 1;
}

game* extend_array(game *t, int *pk, int iR){
    if (is_array_full(t, pk, iR)){
        t = realloc(t, sizeof(game) * (ALLOC * (*pk+1)));
        (*pk) += 1 ;
    }
    return t;
}

bool pieces_equality(cpiece p, cpiece p2){  // Regarde si deux meme pieces sont egales dans deux jeux differents
    return get_x(p) != get_x(p2) || get_y(p) != get_y (p2);
}


bool games_equality(game g, game g2){ // regarde si deux jeux sont egaux en ne comparant que leurs pieces
    for (int i = 0 ; i < game_nb_pieces(g); ++i){
        if (pieces_equality(game_piece(g, i), game_piece(g2, i)) == true){
            return false;
        }
    }
    return true;
}

bool array_search(game *t, game g, int IndiceTableauRempli){ // Regarde si le jeu passé en parametre correspond a un des jeux du tableau
    for (int i = 0; i < IndiceTableauRempli; ++i){
        if (games_equality(g, t[i]) == true)
            return true;
    }
    return false;
}

int choose_gameover(char *game_chosen){
    int gameover_function;
    if (*game_chosen == 'r')
        gameover_function = 0;
    else
        gameover_function = 1;
    return gameover_function;
}


bool game_over_ar (cgame g) {
    return (get_x (game_piece(g, 0)) == 1 && get_y (game_piece(g, 0)) == 0);
}



int main(int argc, char* argv[]){

	//FONCTION USAGE

	char *chosen_game = argv[1];    //stocking the chosen game in parameters
	char *filename = argv[2];       //stocking the filename to open

    // Initialize an array of functions pointers.
    bool (*gameover_tab[2])(cgame);
    gameover_tab[0] = &game_over_hr;
    gameover_tab[1] = &game_over_ar;

    int gameover_function = choose_gameover(chosen_game);  //This variable will permit the choice between the two game_over functions

    clock_t t1,t2;

    //Opening the file
    FILE *f = fopen(filename,"r");

    //Loading the game from the file in g
    game g = game_from_file(f);


    t1 = clock();

    queue q = new_queue();

    //Allocation of the array storing each game encountered
    game *game_array = malloc (ALLOC * sizeof(game));

    //Creating a temporary game in order to not push the reference of the orignal game in the queue.
    game tmp = new_game_hr(0,NULL);

    int k = 1; //multiple de la taille ALLOC./a
    int* pK = &k;
    int index_fill = 0;
    int nbjeuxfile = 0;

    copy_game(g,tmp);
    push(q,tmp);
    nbjeuxfile ++ ;
    game_array[index_fill] = tmp;
    index_fill ++;  //indice remplissage tableau

    while(! (*gameover_tab[gameover_function])(g)){

        copy_game(pop(q), g);
        printf("nb moves : %d x0:%d y0 : %d\n", game_nb_moves(g),get_x(game_piece(g,0)),get_y(game_piece(g,0)));
        for (int i = 0; i < game_nb_pieces(g); i++){
            if (can_move_x(game_piece(g,i))){
            	game tmp = new_game_hr(0,NULL);
            	copy_game(g,tmp);
                if (play_move(tmp,i,RIGHT, 1)){
                    if(array_search(game_array, tmp, index_fill) == false){
                        push(q,tmp);
                        nbjeuxfile ++ ;
                        game_array = extend_array(game_array, pK, index_fill);
                        game tmpTableau = new_game_hr(0,NULL); //Copie le jeu car passage de réferencee t donc destruction de la reference pendant le pop
                        copy_game(tmp,tmpTableau);
                        game_array[index_fill] = tmpTableau;
                        index_fill++;
                    }


                }
                game tmp2 = new_game_hr(0,NULL);
                copy_game(g,tmp2);
                if (play_move(tmp2,i,LEFT, 1)){
                    if(array_search(game_array, tmp2, index_fill) == false){
                        push(q,tmp2);
                        nbjeuxfile ++ ;
                        game_array = extend_array(game_array, pK, index_fill);
                        game tmpTableau = new_game_hr(0,NULL); //Copie le jeu car passage de réferencee t donc destruction de la reference pendant le pop
                        copy_game(tmp2,tmpTableau);
                        game_array[index_fill] = tmpTableau;
                        index_fill++;
                    }

                }
            }
            if (can_move_y(game_piece(g,i))){
            	game tmp = new_game_hr(0,NULL);
            	copy_game(g,tmp);
                if (play_move(tmp,i,UP, 1)){
                    if(array_search(game_array, tmp, index_fill) == false){
                        push(q,tmp);
                        nbjeuxfile ++ ;
                        game_array = extend_array(game_array, pK, index_fill);
                        game tmpTableau = new_game_hr(0,NULL); //Copie le jeu car passage de réferencee t donc destruction de la reference pendant le pop
                        copy_game(tmp,tmpTableau);
                        game_array[index_fill] = tmpTableau;
                        index_fill++;
                    }


                }
                game tmp2 = new_game_hr(0,NULL);
                copy_game(g,tmp2);
                if (play_move(tmp2,i,DOWN, 1)){
                    if(array_search(game_array, tmp2, index_fill) == false){
                        push(q,tmp2);
                        nbjeuxfile ++ ;
                        game_array = extend_array(game_array, pK, index_fill);
                        game tmpTableau = new_game_hr(0,NULL); //Copie le jeu car passage de réferencee t donc destruction de la reference pendant le pop
                        copy_game(tmp2,tmpTableau);
                        game_array[index_fill] = tmpTableau;
                        index_fill++;
                    }
                }

            }
        }
    }
    t2 = clock();
    float tps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("terminé en %d mouvements et %f secondes. %d jeux ont été push\n", game_nb_moves(g),tps,nbjeuxfile);
}
