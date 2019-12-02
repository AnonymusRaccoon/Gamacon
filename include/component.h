/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#pragma once

#include <stdarg.h>

typedef struct Component
{
    char *name;
    unsigned size;
    struct Component *dependencies;
    void (*ctr)(void *component, va_list);
    void (*dtr)(void *component);
    char *(*serialize)(void *component);
// privates:
    char *tostr;
} Component;