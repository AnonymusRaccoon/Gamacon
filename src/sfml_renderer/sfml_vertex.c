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
#include <math.h>
#include <stdint.h>
#include <SFML/Graphics.h>

sfVertexArray *sfml_init_verticies(void)
{
    sfVertexArray *arr = sfVertexArray_create();

    sfVertexArray_append(arr, (sfVertex){{0, 0}, sfWhite});
    sfVertexArray_append(arr, (sfVertex){{0, 0}, sfWhite});
    sfVertexArray_setPrimitiveType(arr, sfLinesStrip);
    return (arr);
}

#define ANGLE_X 45
#define ANGLE_Y 35

sfVector2f get_tile_coords(int x, int y, int z)
{
//	return (sfVector2f) {x * 64, y * 64};
	return (sfVector2f){
		cos(ANGLE_X) * x * 64 - cos (ANGLE_X) * y * 64,
		sin(ANGLE_Y) * y  * 64 + sin (ANGLE_Y) * x * 64 - z
	};
}

void draw_line(struct sfml_renderer_system *this, struct vertex_component \
*info, int x, int y)
{
	sfVertex *vert1 = sfVertexArray_getVertex(this->vertices, 1);

	if (y < 0 || x < 0)
		return;
	if (!info->vertices[y] || info->vertices[y][x] == INT32_MAX)
		return;
//	printf("Drawing line for vertex at %d, %d\n", x, y);
	vert1->position = get_tile_coords(x, y, info->vertices[y][x]);
	sfRenderWindow_drawVertexArray(this->window, this->vertices, NULL);
}


void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *this, \
struct vertex_component *info)
{
	sfVertex *vert0 = sfVertexArray_getVertex(this->vertices, 0);

    for (int y = 0; info->vertices[y]; y++) {
        for (int x = 0; info->vertices[y][x] != INT32_MIN; x++) {
            vert0->position = get_tile_coords(x, y, info->vertices[y][x]);
            draw_line(this, info, x, y - 1);
            draw_line(this, info, x - 1, y);
        }
    }
}