/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** sfml_vertex
*/

#include "vector2.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include "components/vertex_component.h"
#include "map_utils.h"
#include <stdint.h>
#include <SFML/Graphics.h>
#include "isometry.h"
#include "components/map_linker.h"
#include "components/renderer.h"

static void tile_rotate(struct tile *tile, int *vertex_order)
{
    for (int j = 0; j < (tile->data & ROTATION_INFO); j++) {
        int tmp = vertex_order[0];
        for (int i = 0; i < 3; i++)
            vertex_order[i] = vertex_order[i + 1];
        vertex_order[3] = tmp;
    }
}

static void tile_prepare_for_draw(struct sfml_renderer_system *this, \
struct tile *tile, gc_vector2 offset, sfVertex **v)
{
    int c[3];
    int vertex_order[4] = {0, 1, 3, 2};

    tile_rotate(tile, vertex_order);
    for (int i = 0; i < 4; i ++) {
        v[i] = sfVertexArray_getVertex(this->vertices, vertex_order[i]);
        c[0] = tile->corners[i]->x;
        c[1] = tile->corners[i]->y;
        c[2] = tile->corners[i]->z;
        v[i]->position = sfvector2f(gc_vector2_from_coords(c[0], c[1], c[2]));
        v[i]->position.x += offset.x;
        v[i]->position.y += offset.y;
    }
}

void sfmlrenderer_draw_tile(gc_engine *engine, \
gc_vector2 offset, struct tile *tile, float dt)
{
    struct renderer *renderer;
    struct sfml_renderer_system *this = GETSYS(engine, sfml_renderer_system);
    sfVertex *v[4];

    if (tile->corners[0]->z == INT32_MAX || !tile->corners[2]->y)
        return;
    tile_prepare_for_draw(this, tile, offset, v);
    this->states->texture = (sfTexture *) tile->texture;
    sfRenderWindow_drawVertexArray(this->window, this->vertices, this->states);
    this->states->texture = NULL;
    if (tile->entity) {
        map_linker_update_entity(engine, tile->entity, tile, offset);
        renderer = GETCMP(tile->entity, renderer);
        if (!this->system.check_dependencies(&this->system, tile->entity))
            return;
        renderer->is_visible = true;
        this->system.update_entity(engine, this, tile->entity, dt);
        renderer->is_visible = false;
    }
}

void sfmlrenderer_manage_hovered_tile(struct sfml_renderer_system *this, \
bool hovered)
{
    sfColor colors[2] = {sfWhite, {180, 180, 180, 255}};
    int sel = 0;

    if (hovered)
        sel = 1;
    for (int j = 0; j < 4; j++)
        sfVertexArray_getVertex(this->vertices, j)->color = colors[sel];
}



void sfmlrenderer_draw_tilemap(gc_engine *engine, gc_entity *entity, \
struct vertex_component *info, float dt)
{
    struct sfml_renderer_system *this = GETSYS(engine, sfml_renderer_system);
    struct transform_component *tra = GETCMP(entity, transform_component);
    struct tile *tl;
    int width = 0;
    int length = 0;
    int end_diagonal = 0;

    if (!info || !info->map)
        return;
    tl = get_selected_tile(this, info, tra->position);
	for (width = 0; info->vertices[0][width].z != INT32_MIN; width++);
	for (length = 0; info->map[length].corners[0]; length++);
	width--;
	end_diagonal = length + width - 1;
	for (int i = length - 1; i >= 0; i -= (i > length - width) ? 1 : width) {
		end_diagonal -= (end_diagonal <= width) ? 1 : width;
		for (int j = i; j >= end_diagonal; j -= width - 1) {
			sfmlrenderer_manage_hovered_tile(this, &info->map[j] == tl);
			sfmlrenderer_draw_tile(engine, tra->position, &info->map[j], dt);
		}
	}
}