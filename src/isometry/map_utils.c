/*
** EPITECH PROJECT, 2020
** Gamacon
** File description:
** map_managment
*/

#include "engine.h"
#include "map_utils.h"
#include <math.h>
#include "components/vertex_component.h"
#include "stdint.h"
#include "systems/sfml_renderer_system.h"

gc_vector2 gc_vector2_from_coords(float x, float y, float z)
{
    return ((gc_vector2){
        cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
        (sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
    });
}

struct tile *get_tile_from_pos(struct vertex_component *map, gc_vector2 pos)
{
    int end = INT32_MAX;

    if (!map || !map->map)
        return (NULL);
    for (int i = 0; map->map[i].corners[0]; i++) {
        if (map->map[i].corners[0]->z == end || !map->map[i].corners[2]->y)
            continue;
        if (is_pos_in_tile(pos, &map->map[i])) {
            return (&map->map[i]);
        }
    }
    return (NULL);
}

struct tile *get_tile_at(struct vertex_component *v, gc_vector2i p)
{
    if (!v || !v->map)
        return (NULL);
    for (int i = 0; v->map[i].corners[0]; i++) {
        if (v->map[i].corners[0]->x == p.x && v->map[i].corners[0]->y == p.y)
            return (&v->map[i]);
    }
    return (NULL);
}

int get_index_nearest_vertex(struct tile *sel, gc_vector2 pos)
{
    float spacing = INFINITY;
    gc_vector2 coords;
    double tmp;
    int i_stock = 0;

    pos.y *= -1;
    for (int i = 0; i < 4; i++) {
        coords = gc_vector2_from_coords(sel->corners[i]->x, \
sel->corners[i]->y, sel->corners[i]->z);
        tmp = pow(coords.x - pos.x, 2) + pow(coords.y - pos.y, 2);
        if (tmp < spacing) {
            spacing = tmp;
            i_stock = i;
        }
    }
    return (i_stock);
}

struct tile*get_selected_tile(struct sfml_renderer_system *this, \
struct vertex_component *info, gc_vector2 pos)
{
    sfVector2i v = sfMouse_getPosition((const sfWindow *) this->window);
    sfVector2f w = sfRenderWindow_mapPixelToCoords(this->window, \
v, this->view);

    w.y *= -1;
    return (get_tile_from_pos(info, gc_vector2_add(pos, *(gc_vector2 *)&w)));
}