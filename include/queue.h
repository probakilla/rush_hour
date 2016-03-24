#ifndef _FILE_H_
#define _FILE_H_

/**
 * @file file.h
 *
 * @brief A file will be used in our game solver.
 *
 **/

/**
 * @struct file_s
 * @brief This file will use an array on games.
 *
 **/

typedef struct file_s* file;


/**
 * @brief Create a new file.
 * @param to initialize a file, we only need the size of the array the initialize it.
 **/

void new_file (int array_size);

/**
 * @brief push a game in the file. If the file is full, the size of the array will double.
 * @param The game you want to stock in the file.
 **/

void push (game g);

/**
 * @brief returns the first game of the array. All others games will be shifted.
 **/

game pop ();


#endif
