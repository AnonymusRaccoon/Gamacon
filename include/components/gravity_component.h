/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** gravity_component
*/

#pragma once

#include "component.h"

struct gravity_component
{
    gc_component base;
    int gravity_speed;
};

extern const struct gravity_component gravity_component;