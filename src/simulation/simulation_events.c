/*
** EPITECH PROJECT, 2026
** simulation_events.c
** File description:
** Handle events during the simulation
*/

#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

#include "simulation.h"
#include "tilemap.h"

static void handle_tilemap_functions(simulation_data_t *data, sfEvent *event)
{
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseRight)
        select_hovered_tile(data->tilemap);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyL)
            lower_tile_height(data->tilemap);
        if (event->key.code == sfKeyR)
            raise_tile_height(data->tilemap);
        if (event->key.code == sfKeyT)
            change_tile_type(data->tilemap);
        if (event->key.code == sfKeyB)
            bomb_tile(data->tilemap);
    }
}

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
    handle_tilemap_functions(data, event);
}
