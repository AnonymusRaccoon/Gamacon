/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** position_component
*/

#pragma once

#include "component.h"
#include "vector2.h"

struct position_component
{
    gc_component *base;
    vector2 position;
};

const gc_component position_component;