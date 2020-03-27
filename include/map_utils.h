/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include "engine.h"
#include <stdbool.h>
#include "components/vertex_component.h"

#define ANGLE_X 45
#define ANGLE_Y 35
#define ADD_VALUE 10

struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos);
gc_vector2 gc_vector2_from_coords(float x, float y, float z);
bool is_pos_in_tile(gc_vector2 pos, struct tile *tile);