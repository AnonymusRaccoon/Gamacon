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

typedef struct Entity
{
    int id;
    char *str;
    tag tag;
    Component *components;
    void (*serialize)();
    Vector2 position;

    struct Entity *next;
    struct Entity *prev;
} Entity;