/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "components/movable_component.h"
#include "components/controllable_component.h"
#include "components/controllers/keyboard_controller.h"
#include "components/renderer.h"
#include <stddef.h>

void keyboard_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct controllable_component *con = GETCMP(controllable_component);
    struct keyboard_controller *key = GETCMP(keyboard_controller);

    con->moving_left = engine->is_keypressed(key->left_key);
    con->moving_right = engine->is_keypressed(key->right_key);
    con->jumping = engine->is_keypressed(key->jump_key);
    (void)system;
    (void)dtime;
}

void keyboard_destroy(void *system)
{
    (void)system;
}

const gc_system keyboard_controller_system = {
    name: "keyboard_controller_system",
    component_name: "keyboard_controller",
    size: sizeof(gc_system),
    ctr: NULL,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &keyboard_update_entity,
    destroy: &keyboard_destroy
};