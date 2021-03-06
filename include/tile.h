/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** tile.h
*/


#ifndef MY_RPG_TILE_H
#define MY_RPG_TILE_H

#include <stdbool.h>
#include "entity.h"


struct tile
{
    struct vertex *corners[4];
    void *texture;
    char data;
    struct gc_entity *entity;
    bool solid;
    char *type;
};

#endif //MY_RPG_TILE_H
