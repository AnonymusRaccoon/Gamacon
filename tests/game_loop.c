/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loop
*/

#include <criterion/criterion.h>
#include "engine.h"
#include "prefab.h"

Test(getentities, filter)
{
    gc_engine *engine = engine_create();
    gc_scene *scene = scene_create((const char **){ NULL });
    gc_list *list;
    int count = 0;

    engine->change_scene(engine, scene);
    prefab_load(engine, "tests/game.gcprefab");
    list = engine->scene->get_entity_by_cmp(engine->scene, "movable_component");
    while (list) {
        count++;
        list = list->next;
    }
    cr_assert_eq(count, 3);
}