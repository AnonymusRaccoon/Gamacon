/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** vector2
*/

#include "vector2.h"
#include "utility.h"
#include "math.h"

float gcvector_magnitude(gc_vector2 vec)
{
    return (sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
}

gc_vector2 gcvector2_normilize(gc_vector2 vec)
{
    float mag = gcvector_magnitude(vec);

    vec.x = vec.x / mag;
    vec.y = vec.y / mag;
    return (vec);
}