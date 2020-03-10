/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** tile_managment
*/

#ifndef MY3D_TILE_COLLISION_MANAGER_H
#define MY3D_TILE_COLLISION_MANAGER_H

#include <stdbool.h>
#include "vertex_component.h"

//! @brief Checks if a point q is on the segment pr
bool is_on_segment(gc_vector2 p, gc_vector2 q, gc_vector2 r);

//! @brief Checks how the points are beetween each others
//! @return 0 if points are colinear
//! @return 1 if points are clockwise
//! @return 2 if points are counterclockwise
int orientation(gc_vector2 p, gc_vector2 q, gc_vector2 r);

//! @brief Checks if segments p1q1 and p2q2 intersects
bool gc_vector2_do_intersect(gc_vector2 p1, gc_vector2 q1, gc_vector2 p2, gc_vector2 q2);

//! @brief Checks if a point is in a polygon
//! @note The segment created to check is [10000, p.x] so beware when checking with large coordinates
//! @param polygon An array of points creating the polygon
//! @note Beware of the order of the points the polygon ABCD is different from ABDC
//! @param n The number of points of the polygon
//! @note you can't set n less than 3
//! @param p Position of the point to check
bool is_point_in_polygon(gc_vector2 *polygon, int n, gc_vector2 p);

#endif //MY3D_TILE_COLLISION_MANAGER_H
