//
// Created by anonymus-raccoon on 3/3/20.
//

#ifndef _TAG_COMPONENT_H_
#define _TAG_COMPONENT_H_

#include "component.h"

struct tag_component
{
	gc_component base;
	char *tag;
};

const struct tag_component tag_component;

#endif //_TAG_COMPONENT_H_
