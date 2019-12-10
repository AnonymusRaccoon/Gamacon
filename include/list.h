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
};

gc_list *list_add(gc_list *list, void *obj);