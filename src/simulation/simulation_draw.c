/*
** EPITECH PROJECT, 2026
** simulation_draw.c
** File description:
** Draw the simulation scene
*/

#include "graphics/engine.h"

#include "simulation.h"
#include "tilemap.h"

void simulation_draw(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    if (data->tilemap)
        tilemap_draw(data->tilemap, engine->window);
}
