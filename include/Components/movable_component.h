/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"

struct MovableComponent
{
    gc_component *base;
    int left_key;
    int right_key;
    int jump_key;
};