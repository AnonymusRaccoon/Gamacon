/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** tupple
*/

#include "tupple.h"
#include "entity.h"
#include "utility.h"
#include <stdlib.h>

static int tupple_add_existing(gc_tupple *li, const char *name, gc_entity *ent)
{
    while (li && my_strcmp(li->name, name))
        li = li->next;
    if (!li)
        return (-1);
    li->entities = list_add(li->entities, ent);
    return (0);
}

gc_tupple *tupple_add(gc_tupple *list, const char *name, gc_entity *entity)
{
    gc_tupple *listconst = list;

    if (!list) {
        list = malloc(sizeof(gc_tupple));
        listconst = list;
    } else {
        if (!tupple_add_existing(list, name, entity))
            return (listconst);
        while (list->next)
            list = list->next;
        list->next = malloc(sizeof(gc_tupple));
        list = list->next;
    }
    if (!list)
        return (NULL);
    list->name = my_strdup(name);
    list->entities = list_add(NULL, entity);
    list->next = NULL;
    return (listconst);
}