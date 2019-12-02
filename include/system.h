/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** system
*/

#pragma once

#include "entity.h"

typedef struct System
{
    unsigned size;
    void *(check_dependencies)(const Entity *entity);
    void *(update_entity)(const Entity *entity);
} System;