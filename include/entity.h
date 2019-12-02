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
    char *tostr;
    gc_component *components;
    char *(*serialize)(struct gc_entity *entity);

    struct gc_entity *next;
    struct gc_entity *prev;
} gc_entity;

char *entity_serialize(gc_entity *entity);

gc_entity *entity_create();
gc_entity *entity_add_component(gc_entity *entity, void *component);