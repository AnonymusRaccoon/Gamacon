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
#include <keybindings.h>

static inline bool collide(struct transform_component *tra, gc_vector2 position)
{
    return (tra->position.x - tra->size.x / 2) <= position.x
        && (tra->position.y + tra->size.y / 2) >= position.y
        && (tra->position.x + tra->size.x / 2) >= position.x
        && (tra->position.y - tra->size.y / 2) <= position.y;
}

void clickable_onclick(gc_engine *engine, va_list list)
{
    enum gc_mousekeys key = va_arg(list, enum gc_mousekeys);
    gc_scene *scene = engine->scene;
    gc_vector2 position = engine->get_cursor_pos(engine);
    gc_list *entities = scene->get_entity_by_cmp(scene, "clickable_component");
    struct transform_component *tra;
    struct clickable_component *cl;

    if (!entities)
        return;
    while (entities->next)
        entities = entities->next;
    for (gc_list *ent = entities; ent; ent = ent->prev) {
        tra = GETCMP(((gc_entity *)ent->data), transform_component);
        if (!collide(tra, position))
            continue;
        cl = GETCMP(((gc_entity *)ent->data), clickable_component);
        if (cl->onclick && cl->onclick(engine, ent->data, position, key))
            return;
    }
}

void clickable_manager_init(struct gc_engine *engine)
{
    engine->add_event_listener(engine, "mouse_click", &clickable_onclick);
}