/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** input_component
*/

#ifndef _INPUT_COMPONENT_H_
#define _INPUT_COMPONENT_H_

#include "component.h"

struct input_component
{
    gc_component base;
    int value;
};

extern const struct input_component input_component;

#endif //_INPUT_COMPONENT_H_
