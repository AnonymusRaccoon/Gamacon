/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "utility.h"
#include "components/movable_component.h"
#include "components/collision_component.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "systems/movable_system.h"
#include <stddef.h>

#include "components/controllable_component.h"

void clamp_vel(struct movable_component *mov, struct collision_component *col)
{
    if ((col->distance_left == 0 && mov->velocity.x < 0) ||
        (col->distance_right == 0 && mov->velocity.x > 0))
        mov->velocity.x = 0;
    if ((col->distance_down == 0 && mov->velocity.y < 0) ||
        (col->distance_top == 0 && mov->velocity.y > 0))
        mov->velocity.y = 0;
}

static void update_entity(gc_engine *engine __attribute__((unused)), \
void *system __attribute__((unused)), gc_entity *entity, float dtime)
{
    struct movable_component *mov = GETCMP(movable_component);
    struct transform_component *pos = GETCMP(transform_component);
    struct collision_component *col = GETCMP(collision_component);

    if (mov->velocity.x < 0)
        pos->position.x -= MIN(mov->velocity.x * -dtime, col->distance_left);
    else
        pos->position.x += MIN(mov->velocity.x * dtime, col->distance_right);
    if (mov->velocity.y < 0)
        pos->position.y -= MIN(mov->velocity.y * -dtime, col->distance_down);
    else
        pos->position.y += MIN(mov->velocity.y * dtime, col->distance_top);
    clamp_vel(mov, col);
    mov->velocity.x += mov->acceleration.x * dtime;
    mov->velocity.y += mov->acceleration.y * dtime;
    mov->acceleration.x = 0;
    mov->acceleration.y = 0;
}

static void ctr(void *system, va_list args)
{
    (void)system;
    (void)args;
}

static void dtr(void *system)
{
    (void)system;
}

const gc_system movable_system = {
    name: "movable_system",
    component_name: "movable_component",
    size: sizeof(gc_system),
    ctr: &ctr,
    dtr: &dtr,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &system_destroy
};