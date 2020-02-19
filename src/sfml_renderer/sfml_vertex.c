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
#include <stdint.h>

sfVertexArray *sfml_init_verticies(void)
{
    sfVertexArray *arr = sfVertexArray_create();

    sfVertexArray_append(arr, (sfVertex){{0, 0}, sfWhite});
    sfVertexArray_append(arr, (sfVertex){{0, 0}, sfWhite});
    sfVertexArray_setPrimitiveType(arr, sfLinesStrip);
    return (arr);
}

void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *renderer, \
struct vertex_component *info)
{
    sfVertex *vert0 = sfVertexArray_getVertex(renderer->vertices, 0);
    sfVertex *vert1 = sfVertexArray_getVertex(renderer->vertices, 1);

    for (int y = 0; info->vertices[y] != NULL; y++) {
        for (int x = 0; info->vertices[y][x] != INT32_MIN; x++) {
            vert0->position = (sfVector2f){x, y};
        }
    }
}