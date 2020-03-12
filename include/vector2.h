/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vector2
*/

#pragma once

typedef struct gc_vector2
{
    float x;
    float y;
} gc_vector2;

typedef struct gc_vector2i
{
    int x;
    int y;
} gc_vector2i;

float gcvector_magnitude(gc_vector2 vec);
gc_vector2 gcvector2_normilize(gc_vector2 vec);

gc_vector2 gc_vector2_add(gc_vector2 first, gc_vector2 second);