/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

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
    int fd = open(path, O_RDONLY);
    char *object_type = NULL;

    if (fd == -1)
        return (NULL);
    while ((object_type = read_line(fd))) {
        if (!my_strcmp(object_type, "Entity"))
            entity = entity_add(entity, deserialize_entity(engine, fd));
    }
    close(fd);
    return (entity);
}
