/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** collision_system
*/

#include "entity.h"
#include "system.h"
#include "vector2.h"
#include "utility.h"
#include "components/collision_component.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "systems/collision_system.h"
#include <stddef.h>

void col_update_entity(gc_engine *engine, \
void *system, gc_entity *entity, float dtime __attribute__((unused)))
{
    gc_collision_system *sys = (gc_collision_system *)system;
    struct collision_component *col = GETCMP(collision_component);
    struct transform_component *pos = GETCMP(transform_component);
    qt_object obj = (qt_object) {
        entity->id,
        {pos->position.x, pos->position.y, pos->size.y, pos->size.x},
        col->layer
    };
    qt_update(sys->tree, obj);
    qt_collision qtcol = collision_get_info(sys->tree, entity->id);
    col->distance_down = qtcol.distance_down;
    col->distance_top = qtcol.distance_top;
    col->distance_left = qtcol.distance_left;
    col->distance_right = qtcol.distance_right;
    if (!col->on_collide)
        return;
    for (int i = 0; qtcol.collide_with[i] != -1; i++) {
        for (size_t j = 0; j < col->collide_size / sizeof(void (*)()); j++)
            col->on_collide[j](engine, entity, qtcol.collide_with[i]);
    }
}

static void ctr(void *system, va_list args)
{
    gc_collision_system *col = (gc_collision_system *)system;

    col->tree = qt_create((qt_intrect){-1000, -1000, 2000, 2000}, 25);
    (void)args;
}

static void dtr(void *system)
{
    gc_collision_system *mov = (gc_collision_system *)system;

    qt_destroy(mov->tree);
    (void)system;
}

const gc_collision_system collision_system = {
    base: {
        name: "collision_system",
        component_name: "collision_component",
        size: sizeof(gc_collision_system),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &col_update_entity,
        destroy: &system_destroy
    },
    tree: NULL
};