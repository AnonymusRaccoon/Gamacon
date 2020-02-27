//
// Created by anonymus-raccoon on 2/21/20.
//

#ifndef _UI_H_
#define _UI_H_

#include "engine.h"

gc_data *button_make(gc_engine *engine, gc_scene *scene, node *n);

gc_entity *new_text(gc_engine *engine, gc_scene *scene, node *n);

gc_entity *new_sprite(gc_engine *engine, gc_scene *scene, node *n);

void ui_setup(gc_engine *engine);

#endif //_UI_H_
