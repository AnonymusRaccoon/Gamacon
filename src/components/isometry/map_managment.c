/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include <SFML/Audio.h>
#include "systems/sfml_renderer_system.h"
#include "engine.h"
#include "map_managment.h"
#include <math.h>
#include "my.h"
#include "vertex_component.h"
#include "stdint.h"

#define ANGLE_X 45
#define ANGLE_Y 35
#define ADD_VALUE 10

gc_vector2 get_tile_coords_to_pixels(float x, float y, float z)
{
	return (gc_vector2){
		cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
		-(sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
	};
}

struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos)
{
	if (!map)
		return (NULL);
	for (int i = 0; map->map[i].corners[0]; i++) {
		if (map->map[i].corners[0]->z == INT32_MAX || !map->map[i].corners[2]->y)
			continue;
		if (is_pos_in_tile(pos, &map->map[i])) {
			return (&map->map[i]);
		}
	}
	return (NULL);
}

int get_index_nearest_vertex(struct tile *sel, gc_vector2 pos)
{
	float spacing = INFINITY;
	gc_vector2 coords;
	double tmp;
	int i_stock = 0;

	for (int i = 0; i < 4; i++) {
		coords = get_tile_coords_to_pixels(sel->corners[i]->x, sel->corners[i]->y, sel->corners[i]->z);
		tmp = pow(coords.x - pos.x, 2) + pow(coords.y - pos.y, 2);
		if (tmp < spacing) {
			spacing = tmp;
			i_stock = i;
		}
	}
	return (i_stock);
}

void tile_click(gc_engine *engine, struct tile *ret, char mode)
{
	int val = (mode & 1) ? ADD_VALUE : -ADD_VALUE;

	if (mode & 2)
		ret->corners[0]->z += val;
	if (mode & 4)
		ret->corners[1]->z += val;
	if (mode & 8)
		ret->corners[2]->z += val;
	if (mode & 16)
		ret->corners[3]->z += val;
	ret->texture = engine->scene->get_data(engine->scene, "sprite", "command_block");
}