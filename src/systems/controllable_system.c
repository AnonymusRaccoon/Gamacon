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
#include "components/controllable_component.h"
#include "components/renderer.h"
#include <stddef.h>

void controllable_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct controllable_component *con = (struct controllable_component *)\
entity->get_component(entity, "ControllableComponent");
    struct movable_component *mov = (struct movable_component *)\
entity->get_component(entity, "MovableComponent");

    mov->moving_left = engine->is_keypressed(con->left_key);
    mov->moving_right = engine->is_keypressed(con->right_key);
    (void)system;
    (void)dtime;
}

void controllable_destroy(void *system)
{
    (void)system;
}

const gc_system controllable_system = {
    name: "ControllableSystem",
    component_name: "ControllableComponent",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &controllable_update_entity,
    destroy: &controllable_destroy
};