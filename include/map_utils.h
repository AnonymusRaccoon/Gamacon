/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#pragma once

#include "engine.h"
#include <stdbool.h>
#include "components/vertex_component.h"
#include "systems/sfml_renderer_system.h"

#define ANGLE_X 25
#define ANGLE_Y 35
#define TILE_SIZE 64

struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos);
struct tile *get_tile_at(struct vertex_component *v, gc_vector2i p);
gc_vector2 gc_vector2_from_coords(float x, float y, float z);
struct tile*get_selected_tile(struct sfml_renderer_system *this, \
struct vertex_component *info, gc_vector2 pos);
bool is_pos_in_tile(gc_vector2 pos, struct tile *tile);