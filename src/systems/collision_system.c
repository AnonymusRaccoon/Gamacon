/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** collision_system
*/

#include "entity.h"
#include "system.h"
#include "texture.h"
#include "vector2.h"
#include "utility.h"
#include "components/collision_component.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "systems/collision_system.h"
#include <stddef.h>

static void update_entity(gc_engine *engine __attribute__((unused)), \
void *system, gc_entity *entity, float dtime __attribute__((unused)))
{
    gc_collision_system *sys = (gc_collision_system *)system;
    struct collision_component *col = GETCMP(collision_component);
    struct transform_component *pos = GETCMP(transform_component);
    qt_object obj = (qt_object) {entity->id,
        {pos->position.x, pos->position.y, pos->size.y, pos->size.x}
    };
    // if (GETCMP(movable_component) != NULL)
        qt_update(sys->tree, obj);
    qt_collision i = collision_get_info(sys->tree, entity->id);
    col->distance_down = i.distance_down;
    col->distance_top = i.distance_top;
    col->distance_left = i.distance_left;
    col->distance_right = i.distance_right;
}

static void ctr(void *system, va_list args)
{
    gc_collision_system *col = (gc_collision_system *)system;
    // gc_scene *scene = va_arg(args, gc_scene *);
    // struct transform_component *pos;
    // gc_entity *entity;
    // qt_object obj;

    col->tree = qt_create((qt_intrect){-1000, -1000, 2000, 2000}, 25);
    // for (gc_list *ent = scene->entities; ent; ent = ent->next) {
    //     entity = (gc_entity *)ent->data;
    //     pos = GETCMP(transform_component);
    //     obj.id = entity->id;
    //     obj.rect.x = pos->position.x;
    //     obj.rect.y = pos->position.y;
    //     obj.rect.w = pos->size.x;
    //     obj.rect.h = pos->size.y;
    //     qt_add(col->tree, obj);
    // }
}

static void dtr(void *system)
{
    gc_collision_system *mov = (gc_collision_system *)system;

    qt_destroy(mov->tree);
    (void)system;
}

const gc_collision_system collision_system = {
    base: {
        name: "CollisionSystem",
        component_name: "collision_component",
        size: sizeof(gc_collision_system),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
    tree: NULL
};