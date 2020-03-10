/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_interactions
*/


#ifndef MY3D_MAP_INTERACTIONS_H
#define MY3D_MAP_INTERACTIONS_H

#include "engine.h"
#include "vertex_component.h"
#include "keybindings.h"

bool tile_interact(gc_engine *engine, gc_entity *entity, gc_vector2 pos, \
enum gc_mousekeys key);

#endif //MY3D_MAP_INTERACTIONS_H
