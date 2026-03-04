/*
** EPITECH PROJECT, 2026
** simulation_enter.c
** File description:
** Initialize the simulation scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

#include "my_world.h"
#include "simulation.h"
#include "tilemap.h"

static void set_up_buttons(engine_t *engine, simulation_data_t *data)
{
    data->up = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {85, 45}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->up, "UP", 24, &sfWhite);
    data->down = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {225, 45}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->down, "DOWN", 24, &sfWhite);
    data->change_type = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {365, 45}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->change_type, "TYPE", 24, &sfWhite);
    data->bomb = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {505, 45}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->bomb, "BOMB", 24, &sfWhite);
    data->random = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {85, 685}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->random, "RANDOM", 24, &sfWhite);
    data->random->data = data->tilemap;
    data->random->on_click = (void *) randomize_tile_map;
}

void simulation_enter(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;

    if (!data)
        return;
    data->tilemap =
        tilemap_create(MAP_DEFAULT_W, MAP_DEFAULT_H, &engine->window_size);
    set_up_buttons(engine, data);
}
