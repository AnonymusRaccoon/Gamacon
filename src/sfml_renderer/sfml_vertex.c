/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** sfml_vertex
*/

#include "sfml_renderer.h"
#include "vector2.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include "components/vertex_component.h"
#include "map_managment.h"
#include <math.h>
#include <stdint.h>
#include <SFML/Graphics.h>

#define ANGLE_X 45
#define ANGLE_Y 35

sfVector2f get_tile_coords(int x, int y, int z)
{
    return (sfVector2f){
        cos(ANGLE_X) * y * 64 - cos(ANGLE_X) * x * 64,
        (sin(ANGLE_Y) * x * 64 + sin(ANGLE_Y) * y * 64 - z)
    };
}

void draw_tile(struct sfml_renderer_system *this, gc_vector2 offset, \
struct tile *tile, bool hovered)
{
    sfVertex *v[4];
    int c[3];
    int vertex_order[4] = {0, 1, 3, 2};

    if (tile->corners[0]->z == INT32_MAX || !tile->corners[2]->y)
        return;
    for (int j = 0; j < (tile->data & 3); j++) {
        int tmp = vertex_order[0];
        for (int i = 0; i < 3; i++)
            vertex_order[i] = vertex_order[i + 1];
        vertex_order[3] = tmp;
    }
    for (int i = 0; i < 4; i++) {
        v[i] = sfVertexArray_getVertex(this->vertices, vertex_order[i]);
        c[0] = tile->corners[i]->x;
        c[1] = tile->corners[i]->y;
        c[2] = tile->corners[i]->z;
        v[i]->position = get_tile_coords(c[0], c[1], c[2]);
        v[i]->position.x += offset.x;
        v[i]->position.y += offset.y;
        if (hovered)
            v[i]->color = (sfColor) {180, 180, 180, 255};
    }
    this->states->texture = (sfTexture *) tile->texture;
    sfRenderWindow_drawVertexArray(this->window, this->vertices, this->states);
    if (hovered)
        for (int i = 0; i < 4; i++)
            v[i]->color = sfWhite;
    this->states->texture = NULL;
}

void sfmlrenderer_draw_tilemap(gc_engine *engine, gc_entity *entity, \
struct vertex_component *info, float dt)
{
    struct sfml_renderer_system *this = GETSYS(engine, sfml_renderer_system);
    struct transform_component *pos = GETCMP(entity, transform_component);
    sfVector2i v = sfMouse_getPosition((const sfWindow *) this->window);
    sfVector2f w = sfRenderWindow_mapPixelToCoords(this->window, v, this->view);
    w.y *= -1;
    int i;
    struct tile *tl;

    if (!info || !info->map)
        return;
    tl = get_tile_from_pos(info, (gc_vector2){w.x, wp.y});
    for (i = 0; info->map[i].corners[0]; i++);
    for (i--; i >= 0; i--) {
        draw_tile(this, pos->position, &info->map[i], &info->map[i] == tl);
    }
}