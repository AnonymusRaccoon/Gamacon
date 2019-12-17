/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** vector2
*/

#include "vector2.h"
#include "utility.h"

gc_vector2 gcvector2_normilize(gc_vector2 vec)
{
    int mag = my_sqrt(my_pow(vec.x, 2) + my_pow(vec.y, 2));

    printf("Mag: %d\n", mag);
    vec.x = vec.x / mag;
    vec.y = vec.y / mag;
    return (vec);
}