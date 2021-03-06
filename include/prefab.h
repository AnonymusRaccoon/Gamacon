/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

#pragma once

#include "entity.h"

int prefab_load(gc_engine *engine, const char *path);
int prefab_loadentities(node *n, gc_engine *engine, gc_scene *scene);
gc_entity *deserialize_entity(gc_engine *engine, gc_scene *scene, node *n);
gc_component *deserialize_component(gc_engine *engine, gc_entity *entity, \
gc_scene *scene, node *n);
void prefab_destroy(gc_scene *scene, int prefab_id);
