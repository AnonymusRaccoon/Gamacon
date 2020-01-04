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

float gcvector_magnitude(gc_vector2 vec);
gc_vector2 gcvector2_normilize(gc_vector2 vec);