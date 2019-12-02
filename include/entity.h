/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** entity
*/

typedef struct gc_entity gc_entity;

#pragma once

#include "component.h"
#include "vector2.h"
#include "tags.h"

struct gc_entity
{
    int id;
    char *tostr;
    gc_component *components;
    char *(*serialize)(gc_entity *entity);
    void (*destroy)(gc_entity *entity);

    gc_entity *next;
    gc_entity *prev;
};

char *entity_serialize(gc_entity *entity);

gc_entity *entity_create(void);
gc_entity *entity_add_component(gc_entity *entity, void *component);