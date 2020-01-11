/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** tupple
*/

typedef struct gc_tupple gc_tupple;

#pragma once

#include "list.h"
#include "entity.h"

struct gc_tupple
{
    char *name;
    gc_list *entities;
    gc_tupple *next;
};

gc_tupple *tupple_add(gc_tupple *list, const char *name, gc_entity *entity);
void tup_remove(gc_tupple *tup, int id);