/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_interactions
*/


#ifndef MY3D_MAP_INTERACTIONS_H
#define MY3D_MAP_INTERACTIONS_H

#include "map_managment.h"
#include "engine.h"
#include "vertex_component.h"

void tile_interact(gc_engine *engine, bool left_click);

static inline void map_manage_right_click(gc_engine *engine)
{
	tile_interact(engine, false);
}

static inline void map_manage_left_click(gc_engine *engine)
{
	tile_interact(engine, true);
}
#endif //MY3D_MAP_INTERACTIONS_H
