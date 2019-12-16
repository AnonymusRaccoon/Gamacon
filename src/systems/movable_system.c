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

void move_entity(gc_entity *entity, struct movable_component *mov, \
quadtree *tree, float dtime)
{
    struct transform_component *pos = (struct transform_component *)\
entity->get_component(entity, "TransformComponent");
    qt_object obj = (qt_object) {entity->id,
        {pos->position.x, pos->position.y, pos->size.y, pos->size.x}
    };
    qt_collision i = collision_get_info(tree, obj.id);

    printf("Speed: (%d, %d) Left: %d, Right: %d\n", mov->speed_x, mov->speed_y, i.distance_left, i.distance_right);
    if (mov->speed_x < 0)
        pos->position.x -= MIN(mov->speed_x * -dtime, i.distance_left);
    else
        pos->position.x += MIN(mov->speed_x * dtime, i.distance_right);
    if (mov->speed_y < 0)
        pos->position.y -= MIN(mov->speed_y * -dtime, i.distance_down);
    else
        pos->position.y += MIN(mov->speed_y * dtime, i.distance_top);
    obj.rect.x = pos->position.x;
    obj.rect.y = pos->position.y;
    qt_update(tree, obj);
}

void movable_update_entity(gc_engine *engine __attribute__((unused)), \
void *system __attribute__((unused)), gc_entity *entity, float dtime)
{
    struct movable_component *mov = (struct movable_component *)\
entity->get_component(entity, "MovableComponent");
    gc_movable_system *sys = (gc_movable_system *)system;

    // if (mov->speed_x != 0 || mov->speed_y != 0) AND IS ALREADY INSIDE THE TREE
    move_entity(entity, mov, sys->tree, dtime);
}

void movable_ctr(void *system, va_list args)
{
    gc_movable_system *mov = (gc_movable_system *)system;

    mov->tree = qt_create((qt_intrect){-1000, -1000, 2000, 2000}, 25);
    (void)args;
}

void movable_dtr(void *system)
{
    gc_movable_system *mov = (gc_movable_system *)system;

    qt_destroy(mov->tree);
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