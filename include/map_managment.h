/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include "engine.h"
#include <stdbool.h>
#include "vertex_component.h"

enum modes_on_tile {
	VERTEX_0 = 2,
	VERTEX_1 = 4,
	VERTEX_2 = 8,
	VERTEX_3 = 16,
	ALL_VERTICES = 30,
	INVERT_ADD_VALUE = 1
};

#define ANGLE_X 45
#define ANGLE_Y 35
#define ADD_VALUE 10

void move_tile(gc_engine *engine, struct tile *ret, char mode, bool r);
int get_index_nearest_vertex(struct tile *sel, gc_vector2 pos);
struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos);
bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos);
gc_vector2 get_tile_coords_to_pixels(float x, float y, float z);
bool is_pos_in_tile(gc_vector2 pos, struct tile *tile);