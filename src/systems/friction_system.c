/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** friction
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "utility.h"
#include "components/movable_component.h"
#include "components/friction_component.h"
#include "components/collision_component.h"
#include "math.h"
#include <stddef.h>

void fric_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct friction_component *fric = GETCMP(friction_component);
    struct movable_component *mov = GETCMP(movable_component);
    struct collision_component *col = GETCMP(collision_component);

    if (!col || collision_is_in_contact(col)) {
        mov->acceleration.x -= fric->value * mov->velocity.x;
        mov->acceleration.y -= fric->value * mov->velocity.y;
    }
    (void)system;
    (void)engine;
    (void)dtime;
}

void fric_destroy(void *system)
{
    (void)system;
}

const gc_system friction_system = {
    name: "FrictionSystem",
    component_name: "friction_component",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &fric_update_entity,
    destroy: &fric_destroy
};