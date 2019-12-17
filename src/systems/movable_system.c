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

void check_collisions(struct movable_component *mov, quadtree *tree, int id)
{

    // if (mov->velocity.x < 0)
    //     mov->velocity.x = MIN(mov->velocity.x, i.distance_left);
    // else
    //     mov->velocity.x = MIN(mov->velocity.x, i.distance_right);
    // if (mov->velocity.y < 0)
    //     mov->velocity.y = MIN(mov->velocity.y, i.distance_down);
    // else
    //     mov->velocity.y = MIN(mov->velocity.y, i.distance_top);
}

void move_entity(gc_entity *entity, struct movable_component *mov, \
quadtree *tree, float dtime)
{
    struct transform_component *pos = GETCMP(transform_component);
    qt_collision i = collision_get_info(tree, entity->id);
    qt_object obj = (qt_object) {entity->id,
        {pos->position.x, pos->position.y, pos->size.y, pos->size.x}
    };

    printf("Acceleration: %f\n Velocity: %f\n", mov->acceleration.x, mov->velocity.x);
    pos->position.x += mov->velocity.x * dtime;
    pos->position.y += mov->velocity.y * dtime;
    obj.rect.x = pos->position.x;
    obj.rect.y = pos->position.y;
    qt_update(tree, obj);
}

void movable_update_entity(gc_engine *engine __attribute__((unused)), \
void *system __attribute__((unused)), gc_entity *entity, float dtime)
{
    struct movable_component *mov = GETCMP(movable_component);
    gc_movable_system *sys = (gc_movable_system *)system;

    mov->velocity.x += mov->acceleration.x * dtime;
    mov->velocity.y += mov->acceleration.y * dtime;
    // if (mov->speed_x != 0 || mov->speed_y != 0) AND IS ALREADY INSIDE THE TREE
    move_entity(entity, mov, sys->tree, dtime);
    mov->acceleration.x = 0;
    mov->acceleration.y = 0;
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
        component_name: "movable_component",
        size: sizeof(gc_movable_system),
        ctr: &movable_ctr,
        dtr: &movable_dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &movable_update_entity,
        destroy: &system_destroy
    },
    tree: NULL
};