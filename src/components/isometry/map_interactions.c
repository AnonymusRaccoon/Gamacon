/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_interactions
*/

#include "map_interactions.h"
#include "clickable_component.h"
#include "entity.h"
#include "my.h"
#include <math.h>
#include "components/transform_component.h"
#include "map_managment.h"
#include <stdlib.h>
#include <components/isometry/map_manager_component.h>

bool tile_interact(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
	struct vertex_component *map = GETCMP(entity, vertex_component);
	struct map_manager_component *manager = GETCMP(entity, map_manager_component);
	struct tile *ret = get_tile_from_pos(map, pos);
	int ind;

	if (!map || !manager) {
		my_printf("map not found\n");
		return (false);
	}
	if (!ret)
		return (false);
	if (manager->tile_mode) {
		if (manager->brush == ROTATE)
			ret->data = (ret->data + ((key == GC_LEFT) ? 1 : -1U)) % 4;
		else
			tile_click(engine, ret, ALL_VERTICES | (key == GC_LEFT));
	} else {
		ind = get_index_nearest_vertex(ret, pos);
		tile_click(engine, ret, ((int) pow(2, ind + 1)) | (key == GC_LEFT));
	}
	return (false);
}