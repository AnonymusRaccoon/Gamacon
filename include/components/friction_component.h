/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** gravity_component
*/

#pragma once

#include "component.h"

struct friction_component
{
    gc_component base;
    int value;
    int default_value;
};

extern const struct friction_component friction_component;