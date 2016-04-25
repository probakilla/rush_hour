//
// Created by ali on 25/04/16.
//

#ifndef _UTILS_H
#define _UTILS_H

#include "game.h"
#include "piece.h"
/**
 * @brief Compare if two pieces equals by looking at their cooridnates.
 *
 *
 **/
bool pieces_equality(cpiece p, cpiece p2);


/**
 * @brief Compare if two games are equals by looking at their pieces ONLY.
 *
 *
 **/
bool games_equality(game g, game g2);

#endif //RUSH_HOUR_UTILS_H
