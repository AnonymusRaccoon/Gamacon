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

void clickable_onclick(gc_engine *engine, gc_vector2 position);

struct clickable_component
{
	gc_component base;
	//! @brief On click callback.
	//! @param engine The engine.
	//! @param entity_id The id of the clicked entity.
	//! @return Return true if this callback catch the event (other listeners after this one won't get the event)
	//! @return Return false if you want others listener to receive the event.
	bool (*onclick)(gc_engine *engine, int entity_id);
};


const struct clickable_component clickable_component;
#endif //_CLICKABLE_COMPONENT_H_
