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

gc_vector2 get_tile_coords_to_pixels(float x, float y, float z)
{
	return (gc_vector2){
		cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
		-(sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
	};
}

int nb_intersection_between_vectors(gc_vector2 x1, gc_vector2 x2, gc_vector2 polygon[4])
{
	int nb_intersects = 0;

	//printf("pos x : %f y : %f\n", x1.x, x1.y);
	//printf("x2 x : %f y : %f\n", x2.x, x2.y);
	//printf("c1 x : %f y : %f\n", polygon[0].x, polygon[0].y);
	if (gc_vector2_is_intersect(x1, x2, polygon[0], polygon[1])) {
		nb_intersects++;
		printf("1 p0 : x:%f f:%f\n", polygon[0].x, polygon[0].y);
		printf("1 p1 : x:%f f:%f\n", polygon[1].x, polygon[1].y);
	}
	if (gc_vector2_is_intersect(x1, x2, polygon[1], polygon[3])) {
		nb_intersects++;
		printf("2 p1 : x:%f f:%f\n", polygon[1].x, polygon[1].y);
		printf("2 p2 : x:%f f:%f\n", polygon[3].x, polygon[3].y);
	}
	if (gc_vector2_is_intersect(x1, x2, polygon[3], polygon[2])) {
		nb_intersects++;
		printf("3 p2 : x:%f f:%f\n", polygon[2].x, polygon[2].y);
		printf("3 p3 : x:%f f:%f\n", polygon[3].x, polygon[3].y);
	}
	if (gc_vector2_is_intersect(x1, x2, polygon[2], polygon[0])) {
		nb_intersects++;
		printf("4 p2 : x:%f f:%f\n", polygon[2].x, polygon[2].y);
		printf("4 p0 : x:%f f:%f\n", polygon[0].x, polygon[0].y);
	}
	return  (nb_intersects);
}

bool is_pos_in_tile(gc_vector2 pos, struct tile *tile)
{
	struct vertex **c = tile->corners;
	gc_vector2 inf = {INFINITY, INFINITY};
	gc_vector2 corners[4];
	int ret;

	for (int i = 0; i < 4; i++) {
		corners[i] = get_tile_coords_to_pixels(c[i]->x, c[i]->y, c[i]->z);
	}

	ret = nb_intersection_between_vectors(pos, inf, corners);
	//my_printf("nb int : %i\n", ret);
	if (!ret || ret % 2 != 0)
		return (false);
	printf("The polygon true\n");
	for (int i = 0; i < 4; i++)
		printf("%i :(x:%f, y:%f)\n", i + 1, corners[i].x, corners[i].y);
	return (true);
}

struct tile *get_tile_from_pos(gc_engine *engine, struct vertex_component *map, gc_vector2 pos)
{
	for (int i = 0; map->map[i + 1].corners[0]->z != INT32_MIN; i++) {
		//printf("map fresh x: %i y: %i z: %i\n", map->map[i].corners[0]->x, map->map[i].corners[0]->y, map->map[i].corners[0]->z);
		if (is_pos_in_tile(pos, &map->map[i])) {
			printf("found \n");
			return (&map->map[i]);
		}
	}
	return (NULL);
}

bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos)
{
	gc_scene *scene = engine->scene;
	gc_entity *entity = scene->get_entity(scene, id);
	struct vertex_component *map = entity->get_component(entity, "vertex_component");
	struct tile *ret;

	printf("map_manage_click called id: %i coords x: %f y:%f\n", id, pos.x, pos.y);
	if (!map) {
		my_printf("aie\n");
		return (true);
	}
	ret = get_tile_from_pos(engine, map, pos);
	if (ret) {
		ret->corners[0]->z += 10;
		ret->corners[1]->z += 10;
		ret->corners[2]->z += 10;
		ret->corners[3]->z += 10;
		ret->texture = engine->scene->get_data(scene, "sprite", "command_block");
	}
	return (true);
}