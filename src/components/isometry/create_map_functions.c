/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#include "xml.h"
#include <malloc.h>
#include <stdint.h>
#include "create_map_functions.h"

bool get_vertices(struct vertex_component *this, node *n)
{
    int i = 0;
    int j = 0;
    int size[3] = {sizeof(struct vertex), sizeof(struct vertex *), 0};

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

char *get_texture_for_coords(gc_vector2i coords, node *n)
{
    char *texture = NULL;

    for (node *text = n->child; text; text = text->next) {
        if (xml_getintprop(text, "x") != coords.x)
            continue;
        if (xml_getintprop(text, "y") != coords.y)
            continue;
        texture = xml_getproperty(text, "name");
        break;
    }
    return (texture);
}

bool init_tile(struct vertex_component *this, int *inc, void **d, \
gc_vector2i c)
{
    char *t;
    void *tmp;
    gc_vector2i arr[4] = {c, (gc_vector2i){c.x, c.y + 1}, \
(gc_vector2i){c.x + 1, c.y + 1}, (gc_vector2i){c.x + 1, c.y}};

    for (int i = 0; i < 4; i++)
        if (this->vertices[arr[i].x][arr[i].y].z == INT32_MIN)
            return (false);
    for (int i = 0; i < 4; i++)
        this->map[*inc].corners[i] = &this->vertices[arr[i].x][arr[i].y];
    this->map[*inc].data = 0;
    t = get_texture_for_coords(c, d[0]);
    if (t) {
        tmp = ((gc_scene *)d[1])->get_data(d[1], "sprite", t);
        this->map[*inc].texture = tmp;
        free(t);
    }
    else
        this->map[*inc].texture = NULL;
    return (true);
}

bool get_tiles(struct vertex_component *this, gc_scene *scene, node *n)
{
    int inc = 0;
    int v_x = xml_getchildcount(n);
    void *dodge[2] = {n->next, scene};
    int vy = xml_getchildcount(n->child->child);

    for (node *line = n->child; line; line = line->next)
        vy = (xml_getchildcount(line) > vy) ? xml_getchildcount(line) : vy;
    this->map = malloc(sizeof(struct tile) * (v_x * vy + 1));
    if (!this->map)
        return (false);
    for (v_x = 0; this->vertices[v_x + 1]; v_x++) {
        for (vy = 0; this->vertices[v_x][vy].z != INT32_MIN; vy++) {
            if (init_tile(this, &inc, dodge, (gc_vector2i){v_x, vy}))
                inc++;
        }
    }
    this->map[inc].corners[0] = NULL;
    return (true);
}