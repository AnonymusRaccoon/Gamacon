/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"

struct camerafollow_system
{
    gc_system base;
    gc_vector2 cam_pos;
};

extern const struct camerafollow_system camerafollow_system;