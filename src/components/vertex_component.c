/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#include "xml.h"
#include "component.h"
#include "components/vertex_component.h"
#include "isometry.h"
#include "utility.h"
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

static void ctr(void *component, va_list args)
{
    (void)component;
    (void)args;
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    struct vertex_component *this = (struct vertex_component *)component;
    char *tilemap = xml_gettempprop(n, "tilemap");
    char *name = n->name;

    this->vertices = NULL;
    this->map = NULL;
    if (!tilemap) {
        my_printf("gamacon: unable to find property 'tilemap' on %s\n", name);
        return;
    }
    n = xml_parse(tilemap);
    if (!n) {
        my_printf("gamacon: unable to find a valid tilemap at %s\n", tilemap);
        return;
    }
    if (!get_vertices(this, n) || !get_tiles(this, scene, n)) {
        my_printf("Unable to malloc during verticies/tile parsing\n");
        return;
    }
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

bool vertex_serialize(struct vertex_component *ve, gc_scene *scene, \
const char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    gc_data *texture;

    if (fd < 0)
        return (false);
    dprintf(fd, "<gc_map >\n\t<vertex_data>\n");
    for (int x = 0; ve->vertices[x]; x++) {
        dprintf(fd, "\t\t<line>\n");
        for (int y = 0; ve->vertices[x][y].z != INT32_MIN; y++)
            dprintf(fd, "\t\t\t<row height=\"%d\" />\n", ve->vertices[x][y].z);
        dprintf(fd, "\t\t</line>\n");
    }
    dprintf(fd, "\t</vertex_data>\n\t<tiles_data>\n");
    for (int i = 0; ve->map[i].corners[0]; i++) {
        texture = scene->get_data_ptr(scene, ve->map[i].texture);
        dprintf(fd, "\t\t<tile x=\"%d\" y=\"%d\" texture=\"%s\" %s/>\n", \
ve->map[i].corners[0]->x, ve->map[i].corners[0]->y, \
texture ? texture->name : "", ve->map[i].solid ? "solid=\"true\"" : "");
    }
    dprintf(fd, "\t</tiles_data>\n</gc_map>\n");
    return (!close(fd));
}

const struct vertex_component vertex_component = {
    base: {
        name: "vertex_component",
        size: sizeof(struct vertex_component),
        dependencies: (char *[]){
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};