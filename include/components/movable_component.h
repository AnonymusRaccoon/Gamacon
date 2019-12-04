/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"

struct movable_component
{
    gc_component base;
    int left_key;
    int right_key;
    int jump_key;
};

extern const struct movable_component movable_component;