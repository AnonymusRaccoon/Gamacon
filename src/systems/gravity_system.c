/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** gravity_system
*/


#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "utility.h"
#include "components/movable_component.h"
#include "components/gravity_component.h"
#include "components/renderer.h"
#include <stddef.h>

void gravity_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct gravity_component *grav = (struct gravity_component *)\
entity->get_component(entity, "GravityComponent");
    struct movable_component *mov = (struct movable_component *)\
entity->get_component(entity, "MovableComponent");

    mov->speed_y = MAX(mov->speed_y - grav->gravity_speed, -grav->max_speed);
    (void)system;
    (void)dtime;
    (void)engine;
}

void gravity_destroy(void *system)
{
    (void)system;
}

const gc_system gravity_system = {
    name: "GravitySystem",
    component_name: "GravityComponent",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &gravity_update_entity,
    destroy: &gravity_destroy
};