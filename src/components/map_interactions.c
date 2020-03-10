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

#define TILE_MODE false
#define ROTATION false

gc_entity *get_map_entity(gc_engine *engine)
{
	gc_scene *scene = engine->scene;
	gc_list *entities = NULL;
	gc_vector2 position = engine->get_cursor_pos(engine);
	struct transform_component *tra;
	struct vertex_component *vc;

	if (!scene)
		return (NULL);
	entities = scene->get_entity_by_cmp(scene, "vertex_component");
	if (!entities)
		return (NULL);
	while (entities->next)
		entities = entities->next;
	for (gc_list *ent = entities; ent; ent = ent->prev) {
		tra = GETCMP(((gc_entity *)ent->data), transform_component);
		if ((tra->position.x - tra->size.x / 2) <= position.x
			&& (tra->position.y + tra->size.y / 2) >= position.y
			&& (tra->position.x + tra->size.x / 2) >= position.x
			&& (tra->position.y - tra->size.y / 2) <= position.y) {
			vc = GETCMP(((gc_entity *)ent->data), vertex_component);
			if (!vc->vertices || !vc->map)
				continue;
			return ((gc_entity *)ent->data);
		}
	}
	return (NULL);
}

void apply_interaction_to_map(gc_engine *engine, struct tile *ret, bool left_click, gc_vector2 pos)
{
	int ind;

	if (TILE_MODE) {
		if (ROTATION) {
			ret->data = (ret->data + 1) % 4;
			printf("new tile data %i\n", (int)ret->data);
			return;
		}
		action_click_on_tile(engine, ret, ALL_VERTICES | left_click);
		return;
	}
	ind = get_index_nearest_vertex(ret, pos);
	action_click_on_tile(engine, ret, ((int)pow(2, ind + 1)) | left_click);
}

void tile_interact(gc_engine *engine, bool left_click)
{
	gc_entity *entity = get_map_entity(engine);
	gc_vector2 pos = engine->get_cursor_pos(engine);
	struct vertex_component *map;
	struct tile *ret = NULL;

	if (!entity)
		return;
	map = entity->get_component(entity, "vertex_component");
	if (!map) {
		my_printf("map not found\n");
		return;
	}
	ret = get_tile_from_pos(engine, map, pos);
	if (ret) {
		apply_interaction_to_map(engine, ret, left_click, pos);
	}
}