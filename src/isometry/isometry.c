/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#include "xml.h"
#include <malloc.h>
#include <stdint.h>
#include <utility.h>
#include "isometry.h"

bool get_vertices(struct vertex_component *this, node *n)
{
    int i = 0;
    int j = 0;
    int size[3] = {sizeof(struct vertex), sizeof(struct vertex *), 0};

    n = xml_getnode(n, "vertex_data");
    this->vertices = malloc(size[1] * (xml_getchildcount(n) + 1));
    if (!this->vertices)
        return (false);
    for (node *line = n->child; line; line = line->next) {
        this->vertices[i] = malloc(size[0] * (xml_getchildcount(line) + 1));
        if (!this->vertices[i])
            return (false);
        for (node *row = line->child; row; row = row->next) {
            size[2] = xml_getintprop(row, "height");
            this->vertices[i][j] = (struct vertex){i, j++, size[2]};
        }
        this->vertices[i++][j] = (struct vertex){0, 0, INT32_MIN};
        j = 0;
    }
    this->vertices[i] = NULL;
    return (true);
}

node *tile_get_data(gc_vector2i coords, node *n)
{
    for (n = n->child; n; n = n->next) {
        if (xml_getintprop(n, "x") != coords.x)
            continue;
        if (xml_getintprop(n, "y") != coords.y)
            continue;
        return n;
    }
    return (NULL);
}

bool init_tile(struct tile *tile, gc_vector2i c, struct vertex **vertices)
{
    gc_vector2i arr[4] = {
        c,
        (gc_vector2i){c.x, c.y + 1}, \
        (gc_vector2i){c.x + 1, c.y + 1},
        (gc_vector2i){c.x + 1, c.y}
    };

    for (int i = 0; i < 4; i++)
        if (vertices[arr[i].x][arr[i].y].z == INT32_MIN)
            return (false);
    for (int i = 0; i < 4; i++)
        tile->corners[i] = &vertices[arr[i].x][arr[i].y];
    tile->data = 0;
    return (true);
}

bool init_data(struct tile *tile, gc_vector2i c, node *n, gc_scene *scene)
{
    char *tmp;

    n = tile_get_data(c, n);
    tmp = xml_gettmpstring(n, "texture", NULL);
    tile->texture = scene->get_data(scene, "sprite", tmp);
    return (true);
}

bool get_tiles(struct vertex_component *this, gc_scene *scene, node *n)
{
    node *vertex_data = xml_getnode(n, "vertex_data");
    node *tiles_data = xml_getnode(n, "tiles_data");
    int w = xml_getchildcount(vertex_data);
    int h = 0;
    int c = 0;

    if (!vertex_data)
        return (false);
    for (node *line = vertex_data->child; line; line = line->next)
        h = MAX(xml_getchildcount(line), h);
    this->map = malloc(sizeof(struct tile) * (w * h + 1));
    if (!this->map)
        return (false);
    for (int x = 0; this->vertices[x + 1]; x++)
        for (int y = 0; this->vertices[x][y].z != INT32_MIN; y++)
            if (init_tile(&this->map[c], (gc_vector2i){x, y}, this->vertices) \
&& init_data(&this->map[c], (struct gc_vector2i){x, y}, tiles_data, scene))
                c++;
    this->map[c].corners[0] = NULL;
    return (true);
}