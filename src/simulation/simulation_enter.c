/*
** EPITECH PROJECT, 2025
** simulation_enter.c
** File description:
** Initialize the simulation scene
*/

#include "graphics/engine.h"

#include "simulation.h"

void simulation_enter(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
}
