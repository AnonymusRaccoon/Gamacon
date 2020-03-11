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
		(sin(ANGLE_Y) * x  * 64 + sin(ANGLE_Y) * y * 64 - z)
	};
}

void draw_tile(struct sfml_renderer_system *this, struct vertex_component \
*info, struct tile *tile, bool hovered)
{
	sfVertex *v[4];
	int c[3];
	int vertex_order[4] = {0, 1, 3, 2};

	if (tile->corners[0]->z == INT32_MAX || !tile->corners[2]->y)
		return;
	for (int j = 0; j < tile->data & 3; j++) {
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

void draw_line(struct sfml_renderer_system *this, struct vertex_component \
*info, int x, int y)
{
	sfVertex *vert1 = sfVertexArray_getVertex(this->vertices, 1);

	if (y < 0 || x < 0)
		return;
	if (!info->vertices[y] || info->vertices[y][x].z == INT32_MAX)
		return;
	//printf("Drawing line for vertex at %d, %d\n", x, y);
	vert1->position = get_tile_coords(info->vertices[y][x].x, info->vertices[y][x].y, info->vertices[y][x].z);
	sfRenderWindow_drawVertexArray(this->window, this->vertices, NULL);
}


void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *this, \
struct vertex_component *info)
{
	sfVector2i vec = sfMouse_getPosition((const sfWindow *) this->window);
	sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(this->window, vec, this->view);
	world_pos.y *= -1;
	int i;
	struct tile *tl;

	if (!info || !info->map)
		return;
	tl = get_tile_from_pos(info, (gc_vector2){world_pos.x, world_pos.y});
	for (i = 0; info->map[i].corners[0]; i++);
    for (i--; i >= 0; i--) {
        draw_tile(this, info, &info->map[i], &info->map[i] == tl);
    }
}