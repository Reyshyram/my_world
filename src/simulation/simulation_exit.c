/*
** EPITECH PROJECT, 2026
** simulation_exit.c
** File description:
** Exit the simulation scene
*/

#include <stdlib.h>

#include "graphics/engine.h"

#include "simulation.h"
#include "tilemap.h"

void simulation_exit(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    if (data->tilemap)
        tilemap_destroy(data->tilemap);
    free(data);
}
