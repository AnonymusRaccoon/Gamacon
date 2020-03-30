/*
** EPITECH PROJECT, 2020
** MUL_my_runner_2019
** File description:
** sfml utilities
*/

#include "vector2.h"
#include "SFML/Graphics.h"

sfVector2f sfvector2f(gc_vector2 vector)
{
    return ((sfVector2f){
            vector.x,
            vector.y
    });
}