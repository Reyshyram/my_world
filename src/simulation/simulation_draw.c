/*
** EPITECH PROJECT, 2026
** simulation_draw.c
** File description:
** Draw the simulation scene
*/

#include <SFML/Graphics/RenderWindow.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

#include "simulation.h"
#include "tilemap.h"

static void draw_buttons(engine_t *engine, simulation_data_t *data)
{
    ui_button_draw(engine, data->up);
    ui_button_draw(engine, data->down);
    ui_button_draw(engine, data->change_type);
    ui_button_draw(engine, data->bomb);
    ui_button_draw(engine, data->random);
    ui_button_draw(engine, data->reset);
}

void simulation_draw(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    if (data->tilemap)
        tilemap_draw(data->tilemap, engine->window);
    draw_buttons(engine, data);
}
