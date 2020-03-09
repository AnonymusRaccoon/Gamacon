//
// Created by cbihan on 3/9/20.
//

#ifndef MY3D_EVENT_MANAGER_H
#define MY3D_EVENT_MANAGER_H

typedef struct gc_event_manager gc_event_manager;

#include "list.h"

struct gc_event_listener
{
	void (*func)(gc_engine *);
	const char *name;
};

void engine_trigger_event(gc_engine *engine, const char *name);
bool engine_add_event_listener(gc_engine *engine, const char *name, void *func);

#endif //MY3D_EVENT_MANAGER_H