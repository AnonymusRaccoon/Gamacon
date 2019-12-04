/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** prefab
*/

#include "engine.h"
#include "entity.h"
#include "prefab.h"
#include <unistd.h>
#include <fcntl.h>

gc_entity *prefab_load(gc_engine *engine, const char *path)
{
    gc_entity *entity;
    int fd = open(path, O_RDONLY);

    if (fd == -1)
        return (NULL);
    entity = deserialize_entity(engine, fd);
    close(fd);
    return (entity);
}
