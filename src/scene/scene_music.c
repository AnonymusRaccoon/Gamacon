/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** scene_music
*/

#include "scene.h"
#include "xml.h"
#include <SFML/Audio.h>
#include <malloc.h>

int scene_load_musics(gc_scene *scene, node *n)
{
    char *path;

    scene->music = malloc(sizeof(gc_music));
    if (!scene->music)
        return (-1);
    n = xml_getnode(n, "music");
    if (!n)
        return (0);
    path = xml_getproperty(n, "src");
    scene->music->music = sfMusic_createFromFile(path);
    if (!scene->music->music)
        return (-1);
    return (0);
}