/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "components/movable_component.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include <stddef.h>

void movable_update_entity(gc_engine *engine, void *system,\
gc_entity *entity, float dtime)
{
    struct movable_component *mov = (struct movable_component *)\
entity->get_component(entity, "MovableComponent");
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");

    if (engine->is_keypressed(mov->left_key))
        pos->position.x -= mov->speed * dtime;
    if (engine->is_keypressed(mov->right_key))
        pos->position.x += mov->speed * dtime;
    (void)system;
}

void movable_destroy(void *system)
{
    (void)system;
}

const gc_system movable_system = {
    name: "MovableSystem",
    component_name: "MovableComponent",
    check_dependencies: &system_check_dependencies,
    update_entity: &movable_update_entity,
    destroy: &movable_destroy
};