/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** system
*/

#pragma once

#include "entity.h"

typedef struct gc_system
{
    unsigned size;
    void *(check_dependencies)(const gc_entity *entity);
    void *(update_entity)(const gc_entity *entity);
} gc_system;