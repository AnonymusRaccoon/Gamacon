/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** sfml_init
*/

#include "components/transform_component.h"
#include <malloc.h>
#include <SFML/Graphics.h>
#include "sfml_init.h"

sfRenderStates *sfml_init_render_state(void)
{
    sfRenderStates *states = malloc(sizeof(sfRenderStates));

    if (!states)
        return (NULL);
    states->texture = NULL;
    states->blendMode = sfBlendAlpha;
    states->shader = NULL;
    states->transform = sfTransform_Identity;
    return (states);
}

sfVertexArray *sfml_init_verticies(void)
{
    sfVertexArray *arr = sfVertexArray_create();
    sfVertex v[4] = {
        {.position = {0, 0}, .texCoords = {0, 0}, .color = sfWhite},
        {.position = {0, 0}, .texCoords = {TEXTURE_WIDTH, 0}, .color = sfWhite},
        {.position = {0, 0}, .texCoords = {0, TEXTURE_HEIGHT}, .color = sfWhite},
        {.position = {0, 0}, .texCoords = {TEXTURE_WIDTH, \
TEXTURE_HEIGHT}, .color = sfWhite}
    };

    for (int i = 0; i < 4; i++)
        sfVertexArray_append(arr, v[i]);
    sfVertexArray_setPrimitiveType(arr, sfTrianglesStrip);
    return (arr);
}