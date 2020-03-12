/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** friction
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "utility.h"
#include "components/transform_component.h"
#include "components/tooltip_component.h"
#include "systems/camerafollow_system.h"
#include "math.h"
#include <stddef.h>
#include <components/renderer.h>

static void update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct tooltip_component *tt = GETCMP(entity, tooltip_component);
    struct transform_component *tra = tt->parent_transform;
    struct renderer *rend = GETCMP(entity, renderer);
    gc_vector2 pad = tt->padding;
    gc_vector2 position = engine->get_cursor_pos(engine);

    if (!tra)
        return;
    rend->is_visible = (tra->position.x - tra->size.x / 2 - pad.x) <= position.x
        && (tra->position.y + tra->size.y / 2 + pad.y) >= position.y
        && (tra->position.x + tra->size.x / 2 + pad.x) >= position.x
        && (tra->position.y - tra->size.y / 2 - pad.y) <= position.y;
}

static void ctr(void *system, va_list args)
{
}

const gc_system tooltip_system = {
    name: "tooltip_system",
    component_name: "tooltip_component",
    size: sizeof(gc_system),
    ctr: &ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &system_destroy
};