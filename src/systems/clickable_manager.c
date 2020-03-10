/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** clickable system
*/

#include "entity.h"
#include "engine.h"
#include "components/clickable_component.h"
#include "components/transform_component.h"
#include "map_interactions.h"
#include <stddef.h>

void clickable_onclick(gc_engine *engine)
{
	gc_scene *scene = engine->scene;
	gc_vector2 position = engine->get_cursor_pos(engine);
	gc_list *entities = NULL;
	struct transform_component *tra;
	struct clickable_component *cl;

	if (!scene)
		return;
	entities = scene->get_entity_by_cmp(scene, "clickable_component");
	if (!entities)
		return;
	while (entities->next)
		entities = entities->next;
	for (gc_list *ent = entities; ent; ent = ent->prev) {
		tra = GETCMP(((gc_entity *)ent->data), transform_component);
		if ((tra->position.x - tra->size.x / 2) <= position.x
		&& (tra->position.y + tra->size.y / 2) >= position.y
		&& (tra->position.x + tra->size.x / 2) >= position.x
		&& (tra->position.y - tra->size.y / 2) <= position.y) {
			cl = GETCMP(((gc_entity *)ent->data), clickable_component);
			if (!cl->onclick)
				continue;
			if (cl->onclick(engine, ((gc_entity *)ent->data)->id, position))
				return;
		}
	}
}

void clickable_manager_init(struct gc_engine *engine)
{
	engine->add_event_listener(engine, "mouse_left_click", &clickable_onclick);
	engine->add_event_listener(engine, "mouse_right_click", &map_manage_right_click);
	engine->add_event_listener(engine, "mouse_left_click", &map_manage_left_click);
}