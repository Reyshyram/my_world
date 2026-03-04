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
    sfRenderWindow_drawRectangleShape(engine->window, data->up->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, data->up->text, nullptr);
    sfRenderWindow_drawRectangleShape(engine->window, data->down->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, data->down->text, nullptr);
    sfRenderWindow_drawRectangleShape(engine->window,
        data->change_type->background, nullptr);
    sfRenderWindow_drawText(engine->window, data->change_type->text, nullptr);
    sfRenderWindow_drawRectangleShape(engine->window, data->bomb->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, data->bomb->text, nullptr);
    sfRenderWindow_drawRectangleShape(engine->window, data->random->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, data->random->text, nullptr);
    sfRenderWindow_drawRectangleShape(engine->window, data->reset->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, data->reset->text, nullptr);
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
