/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** list
*/

typedef struct gc_list gc_list;

#pragma once

struct gc_list
{
    void *data;
    gc_list *next;
    gc_list *prev;
};

gc_list *list_add(gc_list *list, void *obj);
gc_list *list_remove(gc_list *list, const void *obj);

#define LISTADD(list, obj) (list = list_add(list, obj))
#define LISTREM(list, obj) (list = list_remove(list, obj))