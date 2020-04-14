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

bool vertex_serialize(struct vertex_component *this, const char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
        return (false);
    dprintf(fd, "<gc_map >\n\t<vertex_data>\n");
    for (int x = 0; this->vertices[x]; x++) {
        dprintf(fd, "\t\t<line>\n");
        for (int y = 0; this->vertices[x][y].z != INT32_MIN; y++)
            dprintf(fd, "\t\t\t<row height=\"%d\" />\n", this->vertices[x][y].z);
        dprintf(fd, "\t\t</line>\n");
    }
    dprintf(fd, "\t</vertex_data>\n\t<tiles_data>\n");
    for (int i = 0; this->map[i].corners[0]; i++)
        dprintf(fd, "\t\t<tile x=\"%d\" y=\"%d\" texture=\"%s\" %s/>\n", this->map[i].corners[0]->x, this->map[i].corners[0]->y, NULL, "");
    dprintf(fd, "\t</tiles_data>\n</gc_map>\n");
    return (true);
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