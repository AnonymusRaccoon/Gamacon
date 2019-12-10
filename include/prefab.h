/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

#pragma once

#include "entity.h"

int prefab_load(gc_engine *engine, const char *path);

gc_entity *deserialize_entity(gc_engine *engine, node *n);