/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** text
*/

#pragma once

#include <stdbool.h>

typedef struct gc_text
{
    char *text;
    void *font;
    int size;
    int color;
    bool resize;
} gc_text;