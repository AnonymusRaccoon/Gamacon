/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_linker_system.c
*/

#include <components/map_linker.h>
#include "system.h"
#include "map_utils.h"
#include "components/transform_component.h"

void map_linker_update_entity(gc_engine *engine, gc_entity *entity, \
struct tile *tile, gc_vector2 map_offset)
{
    struct map_linker *link = GETCMP(entity, map_linker);
    struct transform_component *tra = GETCMP(entity, transform_component);
    struct vertex *c = tile->corners[0];

    if (!link)
        return;
    link->tile = tile;
    if (!tra)
        return;
    tra->position = gc_vector2_from_coords(c->x, c->y, c->z);
    tra->position.x += map_offset.x;
    tra->position.y += map_offset.y;
}