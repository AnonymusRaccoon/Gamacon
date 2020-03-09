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
#define INF 10000

gc_vector2 get_tile_coords_to_pixels(float x, float y, float z)
{
	return (gc_vector2){
		cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
		-(sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
	};
}

bool is_on_segment(gc_vector2 p, gc_vector2 q, gc_vector2 r)
{
	if (q.x <= fmaxf(p.x, r.x) && q.x >= fminf(p.x, r.x) && \
q.y <= fmaxf(p.y, r.y) && q.y >= fminf(p.y, r.y))
		return (true);
	return (false);
}

int orientation(gc_vector2 p, gc_vector2 q, gc_vector2 r)
{
	int tmp = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (tmp == 0)
		return (0);
	return ((tmp > 0) ? 1 : 2);
}

bool gc_vector2_do_intersect(gc_vector2 p1, gc_vector2 q1, gc_vector2 p2, gc_vector2 q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return (true);
	if (o1 == 0 && is_on_segment(p1, p2, q1))
		return (true);
	if (o2 == 0 && is_on_segment(p1, q2, q1))
		return (true);
	if (o3 == 0 && is_on_segment(p2, p1, q2))
		return (true);
	if (o4 == 0 && is_on_segment(p2, q1, q2))
		return (true);
	return (false);
}

bool is_point_in_polygon(gc_vector2 *polygon, int n, gc_vector2 p)
{
	gc_vector2 segment = {-INF, p.y};
	int count = 0;
	int next = 0;
	int i = 0;

	if (n < 3)
		return (false);
	do {
		next = (i + 1) % n;
		if (gc_vector2_do_intersect(polygon[i], polygon[next], p, segment)) {
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return (is_on_segment(polygon[i], p, polygon[next]));
			count++;
		}
		i = next;
	} while (i != 0);
	return (count & 1);
}

bool is_pos_in_tile(gc_vector2 pos, struct tile *tile)
{
	struct vertex **c = tile->corners;
	gc_vector2 corners[4];

	for (int i = 0; i < 4; i++)
		corners[i] = get_tile_coords_to_pixels(c[i]->x, c[i]->y, c[i]->z);
	if (is_point_in_polygon(corners, 4, pos)) {
		//for (int i = 0; i < 4; i ++)
		//	printf("%i :(x:%f, y:%f)\n", i + 1, corners[i].x, corners[i].y);
	//	printf("\n");
		return (true);
	}
	return (false);
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
	struct tile *ret = NULL;

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
	return (false);
}