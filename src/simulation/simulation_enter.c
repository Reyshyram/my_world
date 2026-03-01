/*
** EPITECH PROJECT, 2026
** simulation_enter.c
** File description:
** Initialize the simulation scene
*/

#include "graphics/engine.h"

#include "simulation.h"
#include "tilemap.h"

void simulation_enter(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    data->tilemap =
        tilemap_create(MAP_DEFAULT_W, MAP_DEFAULT_H, &engine->window_size);
}
