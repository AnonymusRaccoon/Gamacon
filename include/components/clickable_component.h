/*
** EPITECH PROJECT, 2020
** Gamacon's button
** File description:
** clickable_component
*/

#ifndef _CLICKABLE_COMPONENT_H_
#define _CLICKABLE_COMPONENT_H_

#include "engine.h"
#include "component.h"

struct clickable_component
{
	gc_component base;
	void (*onclick)(gc_engine *engine, int entity_id);
};


const struct clickable_component clickable_component;
#endif //_CLICKABLE_COMPONENT_H_
