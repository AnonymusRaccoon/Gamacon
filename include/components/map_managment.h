/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include "engine.h"
#include <stdbool.h>
#include "vertex_component.h"

bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos);
gc_vector2 get_tile_coords_to_pixels(float x, float y, float z);
bool is_pos_in_tile(gc_vector2 pos, struct tile *tile);