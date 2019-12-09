/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

#include "xml.h"
#include "engine.h"
#include "entity.h"
#include "prefab.h"
#include "read_line.h"
#include "utility.h"
#include <unistd.h>
#include <fcntl.h>

gc_entity *prefab_load(gc_engine *engine, const char *path)
{
    gc_entity *entity = NULL;
    node *n = xml_parse(path);

    if (!n)
        return (NULL);
    n = xml_getnode(n, "gc_scene");
    for (node *ent_n = n->child; n; n = n->next)
        entity = entity_add(entity, deserialize_entity(engine, ent_n));
    xml_destroy(n);
    return (entity);
}
