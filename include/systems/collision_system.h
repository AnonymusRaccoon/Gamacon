/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#pragma once

#include "system.h"
#include "quadtree.h"

typedef struct gc_collision_system
{
    gc_system base;
    quadtree *tree;

} gc_collision_system;

extern const gc_collision_system collision_system;