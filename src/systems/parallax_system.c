/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** parallax_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "components/parallax_component.h"
#include "components/renderer.h"
#include <stddef.h>

void parallax_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct renderer *text = \
(struct renderer *)entity->get_component(entity, "Renderer");
    struct parallax_component *parallax = \
(struct parallax_component *)entity->get_component(entity, "ParallaxComponent");

    if (!text->sprite)
        return;
    text->sprite->rect.left += parallax->speed * dtime;
    (void)system;
    (void)engine;
}

void parallax_destroy(void *system)
{
    (void)system;
}

const gc_system parallax_system = {
    name: "ParallaxSystem",
    component_name: "ParallaxComponent",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &parallax_update_entity,
    destroy: &parallax_destroy
};