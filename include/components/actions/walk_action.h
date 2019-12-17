/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** walk_action
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct walk_action
{
    gc_component base;
    int speed;
    int max_speed;
    int max_acceleration;
};

extern const struct walk_action walk_action;