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
*info, struct tile *tile)
{
	sfVertex *vert[4];
	int corners[12];
	int vertex_order[4] = {0, 1, 3, 2};


	if (tile->corners[0]->z == INT32_MAX || !tile->corners[2]->y)
		return;
	for (int j = 0; j < tile->data & 3; j++) {
		int tmp = vertex_order[0];
		for (int i = 0; i < 3; i++) {
			vertex_order[i] = vertex_order[i + 1];
		}
		vertex_order[3] = tmp;
	}
	for (int i = 0; i < 4; i++)
		vert[i] = sfVertexArray_getVertex(this->vertices, vertex_order[i]);

	for (int i = 0; i < 4; i++) {
		corners[i * 3] = tile->corners[i]->x;
		corners[i * 3 + 1] = tile->corners[i]->y;
		corners[i * 3 + 2] = tile->corners[i]->z;
	}
	for (int i = 0; i < 4; i++) {
		vert[i]->position = get_tile_coords(corners[i * 3], corners[i * 3 + 1], corners[i * 3 + 2]);
	}

    sfVector2i vec = sfMouse_getPosition((const sfWindow *) this->window);
	sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(this->window, vec, this->view);
	world_pos.y *= -1;

    if (!is_pos_in_tile((gc_vector2){world_pos.x, world_pos.y}, tile)) {
		this->states->texture = (sfTexture *) tile->texture;
	}
    else {
		this->states->texture = (sfTexture *) tile->texture;
		//this->states->texture = NULL;
	}
    sfVertexArray_setPrimitiveType(this->vertices, sfTrianglesStrip);

    for (int i = 0; i < 4; i++)
    	vert[i]->color = sfWhite;

	sfRenderWindow_drawVertexArray(this->window, this->vertices, this->states);
	world_pos.y *= -1;
	sfVertexArray_setPrimitiveType(this->vertices, sfLinesStrip);
	vert[0]->position = world_pos;
	vert[1]->position = (sfVector2f){world_pos.x, world_pos.y};
	vert[2]->position = (sfVector2f){10000, -10000};
	vert[3]->position = (sfVector2f){10000, -10000};
	//printf("sfml inf is x:%f, y:%f\n", vert2->position.x, vert2->position.y);
	this->states->texture = NULL;

	for (int i = 0; i < 4; i++)
		vert[i]->color = sfRed;
	sfRenderWindow_drawVertexArray(this->window, this->vertices, this->states);
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
	int i;

	if (!info || !info->map)
		return;
	for (i = 0; info->map[i].corners[0]; i++);
    for (i--; i >= 0; i--) {
		//printf("mdr %i %i %i\n", corners[0], corners[1], corners[2]);
        //if (!info->map[i].corners[0]->y)
       //     continue;
        draw_tile(this, info, &info->map[i]);
    }
}