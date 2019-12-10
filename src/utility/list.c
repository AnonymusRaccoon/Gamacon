/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** list
*/

#include "list.h"
#include <stdlib.h>

gc_list *list_add(gc_list *list, void *obj)
{
    gc_list *listconst = list;

    if (!list) {
        list = malloc(sizeof(gc_list));
        listconst = list;
    } else {
        while (list->next)
            list = list->next;
        list->next = malloc(sizeof(gc_list));
        list = list->next;
    }
    if (!list)
        return (NULL);
    list->data = obj;
    list->next = NULL;
    return (listconst);
}