/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** data_loader
*/

#include "engine.h"
#include "data.h"
#include "xml.h"
#include "my.h"
#include <malloc.h>

gc_data *tile_texture_array_loader(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_data *data = malloc(sizeof(*data));
	int c;
	char *arr;

	if (!data)
		return (NULL);
	data->type = my_strdup(n->name);
	data->name = data->type;
	if (!data->type || !data->name)
		return (NULL);
	c = xml_getchildcount(n);
	n = n->child;
	arr = malloc(sizeof(void *) * (c + 1));
	if (!arr)
		return (NULL);
	for (int i = 0; i < c; i++)
		arr[i] = xml_getproperty(n, "name");
	arr[c] = '\0';
	data->custom = arr;
	// TODO add a destructor
	data->destroy = NULL;
	return (data);
}