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

sfVector2f sfvector2f(gc_vector2 vector)
{
	return ((sfVector2f){
		vector.x,
		vector.y
	});
}

static void tile_rotate(struct tile *tile, int **vertex_order)
{
	for (int j = 0; j < (tile->data & 3); j++) {
		int tmp = vertex_order[0];
		for (int i = 0; i < 3; i++)
			vertex_order[i] = vertex_order[i + 1];
		vertex_order[3] = tmp;
	}
}

void sfr_draw_tile(struct sfml_renderer_system *this, gc_vector2 offset, \
struct tile *tile, bool hovered)
{
	sfVertex *v[4];
	int c[3];
	int vertex_order[4] = {0, 1, 3, 2};

	if (tile->corners[0]->z == INT32_MAX || !tile->corners[2]->y)
		return;
	//TODO re integrate tile rotate
	for (int i = 0; i < 4; i++) {
		v[i] = sfVertexArray_getVertex(this->vertices, vertex_order[i]);
		c[0] = tile->corners[i]->x;
		c[1] = tile->corners[i]->y;
		c[2] = tile->corners[i]->z;
		v[i]->position = sfvector2f(gc_vector2_from_coords(c[0], c[1], c[2]));
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

void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *this, \
struct transform_component *pos, struct vertex_component *info)
{
	sfVector2i vec = sfMouse_getPosition((const sfWindow *) this->window);
	sfVector2f wp = sfRenderWindow_mapPixelToCoords(this->window, vec, this->view);
	wp.y *= -1;
	int i;
	struct tile *tl;

	if (!info || !info->map)
		return;
	tl = get_tile_from_pos(info, (gc_vector2){wp.x - pos->position.x, wp.y + pos->position.y});
	for (i = 0; info->map[i].corners[0]; i++);
    for (i--; i >= 0; i--) {
		sfr_draw_tile(this, pos->position, &info->map[i], &info->map[i] == tl);
    }
}