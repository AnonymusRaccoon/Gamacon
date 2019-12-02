/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#pragma once

#include <stdarg.h>

typedef struct gc_component
{
    char *name;
    unsigned size;
    struct gc_component *dependencies;
    void (*ctr)(void *component, va_list);
    void (*dtr)(void *component);
    char *(*serialize)(void *component);
    void (*destroy)(void *component);

    struct gc_component *next;
    struct gc_component *prev;

    char *tostr;
} gc_component;