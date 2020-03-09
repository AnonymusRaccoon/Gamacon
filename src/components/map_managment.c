/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include <SFML/Audio.h>
#include <systems/sfml_renderer_system.h>
#include "engine.h"
#include "map_managment.h"
#include <math.h>
#include "vertex_component.h"
#include "stdint.h"

#define ANGLE_X 45
#define ANGLE_Y 35
#define ADD_VALUE 10

enum modes_on_tile {
	VERTEX_0 = 2,
	VERTEX_1 = 4,
	VERTEX_2 = 8,
	VERTEX_3 = 16,
	ALL_VERTICES = 30,
	INVERT_ADD_VALUE = 1
};

gc_vector2 get_tile_coords_to_pixels(float x, float y, float z)
{
	return (gc_vector2){
		cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
		-(sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
	};
}

struct tile *get_tile_from_pos(gc_engine *engine, struct vertex_component *map, gc_vector2 pos)
{
	for (int i = 0; map->map[i + 1].corners[0]->z != INT32_MIN; i++) {
		//printf("map fresh x: %i y: %i z: %i\n", map->map[i].corners[0]->x, map->map[i].corners[0]->y, map->map[i].corners[0]->z);
		if (is_pos_in_tile(pos, &map->map[i])) {
			//printf("found \n");
			return (&map->map[i]);
		}
	}
	return (NULL);
}

void action_click_on_tile(gc_engine *engine, gc_scene *scene, struct tile *ret, char mode)
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

bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos)
{
	gc_scene *scene = engine->scene;
	gc_entity *entity = scene->get_entity(scene, id);
	struct vertex_component *map = entity->get_component(entity, "vertex_component");
	struct tile *ret = NULL;

	//printf("map_manage_click called id: %i coords x: %f y:%f\n", id, pos.x, pos.y);
	if (!map) {
		my_printf("map not found\n");
		return (false);
	}
	ret = get_tile_from_pos(engine, map, pos);
	if (ret) {
		action_click_on_tile(engine, scene, ret, ALL_VERTICES | INVERT_ADD_VALUE);
	}
	return (false);
}