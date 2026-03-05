/*
** EPITECH PROJECT, 2026
** simulation_events.c
** File description:
** Handle events during the simulation
*/

#include <SFML/Window/Event.h>

#include "graphics/engine.h"

#include "graphics/ui.h"
#include "stdio.h"
#include "simulation.h"

void simulation_event(engine_t *engine, sfEvent *event)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data || !event)
        return;
    ui_button_events(data->up, event, engine);
    ui_button_events(data->down, event, engine);
    ui_button_events(data->change_type, event, engine);
    ui_button_events(data->bomb, event, engine);
    ui_button_events(data->random, event, engine);
    ui_button_events(data->reset, event, engine);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyL)
            lower_tile_height(data->tilemap);
        if (event->key.code == sfKeyR)
            raise_tile_height(data->tilemap);
        if (event->key.code == sfKeyT)
            select_hovered_tile(data->tilemap);
    }
}
