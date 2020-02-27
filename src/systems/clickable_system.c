/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** clickable system
*/

#include "entity.h"
#include "components/clickable_component.h"
#include "components/transform_component.h"
#include <stddef.h>

void clickable_onclick(gc_engine *engine, gc_vector2 position)
{
	gc_scene *scene = engine->scene;
	gc_list *entities = NULL;
	struct transform_component *tra;
	struct clickable_component *cl;

	if (!scene)
		return;
	entities = scene->get_entity_by_cmp(scene, "clickable_component");
	for (gc_list *ent = entities; ent; ent = ent->next) {
		tra = GETCMP(((gc_entity *)ent->data), transform_component);
		if ((tra->position.x - tra->size.x / 2) <= position.x
		&& (tra->position.y + tra->size.y / 2) >= position.y
		&& (tra->position.x + tra->size.x / 2) >= position.x
		&& (tra->position.y - tra->size.y / 2) <= position.y) {
			cl = GETCMP(((gc_entity *)ent->data), clickable_component);
			if (cl->onclick)
				cl->onclick(engine, ((gc_entity *)ent->data)->id);
		}
	}
}