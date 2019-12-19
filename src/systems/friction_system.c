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
#include <stddef.h>

void fric_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct friction_component *fric = GETCMP(friction_component);
    struct movable_component *mov = GETCMP(movable_component);
    gc_vector2 dir = gcvector2_normilize(mov->acceleration);

    if (isnan(dir.x) || isnan(dir.y))
        return;
    if (-fric->threshold < mov->velocity.x && mov->velocity.x < fric->threshold)
        mov->velocity.x = 0;
    else if (mov->acceleration.x * dir.x > -fric->value) {
        mov->acceleration.x -= fric->value * dir.x * .8f;
        mov->acceleration.x -= MAX(fric->value * .02f * mov->velocity.x * dir.x, 0) / dir.x;
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