/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** entity
*/

#pragma once

#include "component.h"
#include "vector2.h"
#include "tags.h"

typedef struct gc_entity
{
    int id;
    char *str;
    gc_component components;
    void (*serialize)();

    struct gc_entity *next;
    struct gc_entity *prev;
} gc_entity;

