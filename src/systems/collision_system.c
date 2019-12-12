/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** collision_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "components/collision_component.h"
#include "components/transform_component.h"
#include <stddef.h>

void parallax_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct transform_component *text = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    struct collision_component *parallax = (struct collision_component *)\
entity->get_component(entity, "CollisionComponent");

    
    (void)system;
    (void)engine;
}

void parallax_destroy(void *system)
{
    (void)system;
}

const gc_system parallax_system = {
    name: "CollisionSystem",
    component_name: "CollisionComponent",
    check_dependencies: &system_check_dependencies,
    update_entity: &parallax_update_entity,
    destroy: &parallax_destroy
};