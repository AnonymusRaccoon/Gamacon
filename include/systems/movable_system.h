/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** movable_system
*/

#pragma once

#include "system.h"
#include "quadtree.h"

typedef struct gc_movable_system
{
    gc_system base;
    quadtree *tree;

} gc_movable_system;

extern const gc_movable_system movable_system;