/*
** EPITECH PROJECT, 2025
** simulation_events.c
** File description:
** Handle events during the simulation
*/

#include <SFML/Window/Event.h>

#include "graphics/engine.h"

#include "simulation.h"

void simulation_event(engine_t *engine, sfEvent *event)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data || !event)
        return;
}
