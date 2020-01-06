/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** friction_giver
*/

#pragma once

#include "component.h"

struct friction_giver
{
    gc_component base;
    int value;
};

extern const struct friction_giver friction_giver;