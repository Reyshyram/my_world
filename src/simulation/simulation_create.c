/*
** EPITECH PROJECT, 2026
** simulation_create.c
** File description:
** Create simulation scene
*/

#include <stdlib.h>
#include <string.h>

#include "graphics/engine.h"

#include "simulation.h"

scene_t *simulation_create(void)
{
    scene_t *scene = malloc(sizeof(*scene));

    if (!scene)
        return nullptr;
    scene->on_enter = simulation_enter;
    scene->on_exit = simulation_exit;
    scene->draw = simulation_draw;
    scene->update = simulation_update;
    scene->handle_events = simulation_event;
    scene->data = malloc(sizeof(simulation_data_t));
    memset(scene->data, 0, sizeof(simulation_data_t));
    if (!scene->data) {
        free(scene);
        return nullptr;
    }
    return scene;
}
