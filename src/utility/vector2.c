/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** vector2
*/

#include <SFML/Audio.h>
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

gc_vector2 gc_vector2_add(gc_vector2 first, gc_vector2 second)
{
    return ((gc_vector2){first.x + second.x, first.y + second.y});
}

gc_vector2i gc_vector2i_add(gc_vector2i first, gc_vector2i second)
{
    return ((gc_vector2i){first.x + second.x, first.y + second.y});
}

gc_vector2 gc_vector2_from_sf(sfVector2f sf_vector)
{
    return (gc_vector2){sf_vector.x, sf_vector.y};
}