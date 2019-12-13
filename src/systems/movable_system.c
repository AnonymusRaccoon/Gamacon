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
#include "utility.h"
#include "components/movable_component.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "systems/movable_system.h"
#include <stddef.h>

void movable_update_entity(gc_engine *engine, void *system, \
gc_entity *entity, float dtime)
{
    struct movable_component *mov = (struct movable_component *)\
entity->get_component(entity, "MovableComponent");
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    gc_movable_system *sys = (gc_movable_system *)system;
    qt_object obj = (qt_object) {
        id: entity->id,
        rect: {pos->position.x, pos->position.y, pos->size.y, pos->size.x}
    };
    qt_collision i = collision_get_info(sys->tree, obj.id);

    if (mov->moving_left)
        pos->position.x -= MIN(mov->speed * dtime, i.distance_left);
    if (mov->moving_right)
        pos->position.x += MIN(mov->speed * dtime, i.distance_right);
    obj.rect.x = pos->position.x;
    qt_update(sys->tree, obj);
    (void)engine;
    (void)system;
}

void movable_ctr(void *system, va_list args)
{
    gc_movable_system *mov = (gc_movable_system *)system;

    mov->tree = qt_create((qt_intrect){0, 0, 100, 100}, 25);
    (void)args;
}

void movable_dtr(void *system)
{
    //SHOULD DESTROY THE QUADTREE HERE
    (void)system;
}

const gc_movable_system movable_system = {
    base: {
        name: "MovableSystem",
        component_name: "MovableComponent",
        size: sizeof(gc_movable_system),
        ctr: &movable_ctr,
        dtr: &movable_dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &movable_update_entity,
        destroy: &system_destroy
    },
    tree: NULL
};