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
#include "components/camerafollow_component.h"
#include "systems/camerafollow_system.h"
#include "math.h"
#include <stddef.h>

static void update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct camerafollow_system *sys = (struct camerafollow_system *)system;
    struct transform_component *tra = GETCMP(transform_component);

    sys->cam_pos.x = (sys->cam_pos.x + tra->position.x) / 2;
    sys->cam_pos.y = (sys->cam_pos.y + tra->position.y) / 2;
    (void)engine;
    (void)dtime;
}

static void ctr(void *system, va_list args)
{
    struct camerafollow_system *sys = (struct camerafollow_system *)system;

    sys->cam_pos = (gc_vector2){0, 0};
    (void)args;
}

const struct camerafollow_system camerafollow_system = {
    base: {
        name: "camerafollow_system",
        component_name: "camerafollow_component",
        size: sizeof(struct camerafollow_system),
        ctr: &ctr,
        dtr: NULL,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
    cam_pos: (gc_vector2){0, 0}
};