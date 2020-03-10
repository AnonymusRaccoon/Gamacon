/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** parallax_component
*/

#pragma once

#include "component.h"
#include "components/transform_component.h"

struct tooltip_component
{
	gc_component base;
	struct transform_component *parent_transform;
	gc_vector2 padding;
};

extern const struct tooltip_component tooltip_component;