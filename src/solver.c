#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "queue.h"


// This fucntion reads a game from a text file and create the corresponding game.
game game_from_file(FILE * f){


    int width_game, height_game, nb_pieces;
    int x,y, width_p, height_p;
    int can_move_y;
    int can_move_x;

    fscanf(f,"%d %d", &width_game, &height_game);
    fscanf(f,"%d",&nb_pieces);

    piece *pieces = malloc (sizeof(*pieces) * nb_pieces);


    for (int i = 0; i < nb_pieces; i++){
        fscanf(f,"%d %d %d %d %d %d", &x, &y, &width_p, &height_p, &can_move_x, &can_move_y);
        pieces[i] = new_piece(x,y,width_p,height_p,can_move_x,can_move_y);
    }

    game g = new_game(width_game,height_game,nb_pieces,pieces);

    for (int i = 0; i < nb_pieces; ++i){
        free(pieces[i]);
    }
    free(pieces);
    return g;



}
//This function choose between th right gameover to use.
int choose_gameover(char *game_chosen){
    int gameover_function;
    if (*game_chosen == 'r')
        gameover_function = 0;
    else
        gameover_function = 1;
    return gameover_function;
}

// Usage function to be sure that we have the correct number of parameters
void usage(char *commande){
    fprintf(stderr,"%s <a/r> <file_to_resolve.txt>\n",commande);
    exit(EXIT_FAILURE);
}


bool game_over_ar (cgame g) {
    return (get_x (game_piece(g, 0)) == 1 && get_y (game_piece(g, 0)) == 0);
}

// This function tries to move a piece in a direction and if the move is possible then
// a research is made to find if the game has been seen already. If not the game is added to the heap and the queue.

void new_configuration_horizontal(game g, int i, heap game_heap, queue q){
    game copy = new_game_hr(0,NULL); // Creating a copy for not moving the original game and so not modifiying it.
    copy_game(g,copy);
    if (play_move(copy,i,RIGHT, 1)){
        if(heap_game_search(game_heap, copy) == false){
            push(q,copy);
            game heap_copy = new_game_hr(0,NULL); //A copy of the game is needed beacause of the reference destroyed if given into the heap and the queue.
            copy_game(copy,heap_copy);
            heap_add(game_heap,heap_copy);
        }
    }
    else
        delete_game(copy);
    game copy2 = new_game_hr(0,NULL);
    copy_game(g,copy2);
    if (play_move(copy2,i,LEFT, 1)){
        if(heap_game_search(game_heap, copy2) == false){
            push(q,copy2);
            game heap_copy = new_game_hr(0,NULL); //A copy of the game is needed beacause of the reference destroyed if given into the heap and the queue.
            copy_game(copy2,heap_copy);
            heap_add(game_heap,heap_copy);
        }

    }
    else
        delete_game(copy2);

}

//Same as new_configuration_horizontal but for the vertical pieces.
void new_configuration_vertical(game g, int i, heap game_heap, queue q){
    game copy = new_game_hr(0,NULL);
    copy_game(g,copy);
    if (play_move(copy,i,UP, 1)){
        if(heap_game_search(game_heap, copy) == false){
            push(q,copy);
            game heap_copy = new_game_hr(0,NULL);
            copy_game(copy,heap_copy);
            heap_add(game_heap,heap_copy);
        }


    }
    else
        delete_game(copy);
    game copy2 = new_game_hr(0,NULL);
    copy_game(g,copy2);
    if (play_move(copy2,i,DOWN, 1)){
        if(heap_game_search(game_heap, copy2) == false){
            push(q,copy2);
            game heap_copy = new_game_hr(0,NULL);
            copy_game(copy2,heap_copy);
            heap_add(game_heap,heap_copy);
        }
    }
    else
        delete_game(copy2);
}


int main(int argc, char* argv[]){

    if(argc != 3)
        usage(argv[0]);

    char *chosen_game = argv[1];    //stocking the chosen game in parameters
    char *filename = argv[2];       //stocking the filename to open

    // Initialize an array of functions pointers.
    bool (*gameover_tab[2])(cgame);
    gameover_tab[0] = &game_over_hr;
    gameover_tab[1] = &game_over_ar;

    //This variable will permit the choice between the two game_over functions
    int gameover_function = choose_gameover(chosen_game);

    //Opening the file
    FILE *f = fopen(filename,"r");

    //Loading the game from the file in g
    game g = game_from_file(f);
    fclose(f);

    // Creating the queue for storing all the configurations
    queue q = new_queue();

    //Allocation of the array storing each game encountered
    heap game_heap = new_heap();

    //Creating a copy of the game in order to not push the reference of the orignal game in the queue and erasing it when poping.
    game copy_queue = new_game_hr(0,NULL);
    game copy_heap = new_game_hr(0,NULL);

    copy_game(g,copy_queue);
    copy_game(g,copy_heap);

    push(q,copy_queue);
    heap_add(game_heap,copy_heap);



    // Here we are poping and moving each game until we have a game with a gameover returning true.
    while(! (*gameover_tab[gameover_function])(g)){
        game t = pop(q);  //Storing the reference from the queue
        copy_game(t, g);  //Copying into the current game
        rearrange_queue(q);  //Sort the queue
        delete_game(t);	//Deleting the old reference
        for (int i = 0; i < game_nb_pieces(g); i++){
            if (can_move_x(game_piece(g,i))){
                new_configuration_horizontal(g, i, game_heap, q);
            }
            if (can_move_y(game_piece(g,i))){
                new_configuration_vertical(g, i, game_heap, q);
            }
        }
    }
    printf("%d\n", game_nb_moves(g));
    heap_delete(game_heap);
    delete_queue(q);
    delete_game(g);


}
