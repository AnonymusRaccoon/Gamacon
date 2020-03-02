/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include "engine.h"
#include <stdbool.h>

static inline bool gc_vector2_is_ccw(gc_vector2 a, gc_vector2 b,gc_vector2 c)
{
	return ((c.y - a.y) * (b.x - a.x) > (b.y - a.x) * (c.x - a.x));
}

static inline bool gc_vector2_is_intersect(gc_vector2 a, gc_vector2 b, \
gc_vector2 c, gc_vector2 d)
{
	return (gc_vector2_is_ccw(a, c, d) != gc_vector2_is_ccw(b, c, d) &&\
gc_vector2_is_ccw(a, b, c) != gc_vector2_is_ccw(a, b, d));
}

bool map_manage_click(gc_engine *engine, int id, gc_vector2 pos);