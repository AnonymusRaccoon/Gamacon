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

#define TILE_MODE true
#define ROTATION false

void apply_interaction_to_map(gc_engine *engine, struct tile *ret, \
bool left_click, gc_vector2 pos)
{
	int ind;

	if (TILE_MODE) {
		if (ROTATION) {
			ret->data = (ret->data + ((left_click) ? 1 : -1U)) % 4;
			return;
		}
		action_click_on_tile(engine, ret, ALL_VERTICES | left_click);
		return;
	}
	ind = get_index_nearest_vertex(ret, pos);
	action_click_on_tile(engine, ret, ((int)pow(2, ind + 1)) | left_click);
}

bool tile_interact(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key)
{
	struct vertex_component *map;
	struct tile *ret = NULL;

	if (!entity)
		return (false);
	map = entity->get_component(entity, "vertex_component");
	if (!map) {
		my_printf("map not found\n");
		return (false);
	}
	ret = get_tile_from_pos(engine, map, pos);
	if (ret) {
		apply_interaction_to_map(engine, ret, key == GC_LEFT, pos);
	}
	return (false);
}