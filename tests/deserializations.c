/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** deserializations
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "engine.h"
#include "prefab.h"

Test(deserialization, deserialize_entity)
{
    gc_engine *engine = engine_create();
    gc_scene *scene = scene_create((const char **){ NULL });
    int ret;

    engine->change_scene(engine, scene);
    ret = prefab_load(engine, "tests/player.gcprefab");
    cr_assert_eq(ret, 0);
    cr_assert_neq(engine->scene, NULL);
    cr_assert_eq(((gc_entity *)engine->scene->entities->data)->id, 0);
    cr_assert_str_eq(((gc_entity *)engine->scene->entities->data)->components->name, "transform_component");
    cr_assert_str_eq(((gc_entity *)engine->scene->entities->data)->components->next->name, "renderer");
    cr_assert_str_eq(((gc_entity *)engine->scene->entities->data)->components->next->next->name, "movable_component");
    cr_assert_str_eq(((gc_entity *)engine->scene->entities->data)->components->next->next->next->name, "controllable_component");
}