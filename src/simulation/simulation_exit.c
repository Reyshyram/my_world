/*
** EPITECH PROJECT, 2025
** simulation_exit.c
** File description:
** Exit the simulation scene
*/

#include <stdlib.h>

#include "graphics/engine.h"

#include "simulation.h"

void simulation_exit(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    free(data);
}
