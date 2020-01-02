/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** walk_action
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "component.h"
#include "components/movable_component.h"
#include "components/controllable_component.h"
#include "components/actions/jump_action.h"
#include "utility.h"
#include <stddef.h>

void update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct controllable_component *con = GETCMP(controllable_component);
    struct movable_component *mov = GETCMP(movable_component);
    struct jump_action *jump = GETCMP(jump_action);

    mov->acceleration.y += con->jumping * jump->acceleration;
    (void)system;
    (void)dtime;
    (void)engine;
}

void destroy(void *system)
{
    (void)system;
}

const gc_system jump_system = {
    name: "JumpSystem",
    component_name: "jump_action",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &destroy
};