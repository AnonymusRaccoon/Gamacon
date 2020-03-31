/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_linker.h
*/


#ifndef MY_RPG_MAP_LINKER_H
#define MY_RPG_MAP_LINKER_H

#include "component.h"

struct map_linker
{
    gc_component base;
    struct tile *tile;
};

const struct map_linker map_linker;

void map_linker_update_entity(gc_engine *engine, gc_entity *entity, \
struct tile *tile, gc_vector2 map_offset);

#endif //MY_RPG_MAP_LINKER_H
