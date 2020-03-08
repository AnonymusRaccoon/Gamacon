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

gc_list *list_remove(gc_list *list, void *obj)
{
	gc_list *listconst = list;

	if (!list)
		return (NULL);
	if (list->data == obj)
		return (list->next);
	while (list->next && list->next->data != obj)
		list = list->next;
	if (!list->next)
		return (listconst);
	list->next = list->next->next;
	return (listconst);
}