/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parallax_system
*/

#include "entity.h"
#include "system.h"
#include "sprite.h"
#include "vector2.h"
#include "components/parallax_component.h"
#include "components/renderer.h"
#include "components/transform_component.h"
#include <stddef.h>

void parallax_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct renderer *text = GETCMP(renderer);
    struct parallax_component *par = GETCMP(parallax_component);
    struct transform_component *tra = GETCMP(transform_component);
    gc_sprite *sprite;

    if (text->type != GC_TEXTUREREND || !text->data)
        return;
    sprite = ((gc_sprite *)text->data);
    sprite->rect.left += (tra->position.x - par->old_pos.x) * par->speed;
    par->old_pos = tra->position;
    (void)system;
    (void)engine;
    (void)dtime;
}

void parallax_destroy(void *system)
{
    (void)system;
}

const gc_system parallax_system = {
    name: "parallax_system",
    component_name: "parallax_component",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &parallax_update_entity,
    destroy: &parallax_destroy
};