/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** renderer_loader
*/

#include "engine.h"
#include "utility.h"
#include "sfml_renderer.h"
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>


sfTexture *get_texture(gc_scene *scene, char *name)
{
    sfTexture *texture;

    if (!scene) {
        my_printf("No scene, can't load textures\n");
        return (NULL);
    }
    if (!name) {
        my_printf("Texture name: null. How should I find a texture ?\n");
        return (NULL);
    }
    texture = scene->get_data(scene, "sprite", name);
    if (texture)
        return (texture);
    my_printf("Gamacon: no texture found for the name \"%s\"\n", name);
    return (NULL);
}

void sfml_texture_destroy(gc_data *data)
{
    sfTexture_destroy(data->custom);
    free(data->name);
}

void sfml_music_destroy(gc_data *data)
{
    sfMusic_destroy(data->custom);
    free(data->name);
}

void sfml_font_destroy(gc_data *data)
{
    sfFont_destroy(data->custom);
    free(data->name);
}