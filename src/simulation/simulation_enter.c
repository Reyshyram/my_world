/*
** EPITECH PROJECT, 2026
** simulation_enter.c
** File description:
** Initialize the simulation scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <stddef.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

#include "my_world.h"
#include "simulation.h"
#include "tilemap.h"

static void set_up_top_buttons_functions(simulation_data_t *data)
{
    data->up->data = data->tilemap;
    data->down->data = data->tilemap;
    data->bomb->data = data->tilemap;
    data->change_type->data = data->tilemap;
    data->up->on_click = (void *) raise_tile_height;
    data->down->on_click = (void *) lower_tile_height;
    data->bomb->on_click = (void *) bomb_tile;
}

static void set_up_top_buttons(engine_t *engine, simulation_data_t *data)
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
    set_up_top_buttons_functions(data);
}

static void reset_tilemap(tilemap_t *map)
{
    for (size_t i = 0; i < map->height * map->width; i++) {
        map->heights[i] = MAX_HEIGHT / 2;
        map->types[i] = TILE_TYPE_GRASS;
    }
    tilemap_calculate_vertices(map);
}

static void set_up_bottom_buttons(engine_t *engine, simulation_data_t *data)
{
    data->random = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {85, 685}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->random, "RANDOM", 24, &sfWhite);
    data->random->data = data->tilemap;
    data->random->on_click = (void *) randomize_tile_map;
    data->reset = ui_button_create(engine, UI_BUTTON_TEXTURE,
        &(sfVector2f) {225, 685}, &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->reset, "RESET", 24, &sfWhite);
    data->reset->data = data->tilemap;
    data->reset->on_click = (void *) reset_tilemap;
}

static void set_up_buttons(engine_t *engine, simulation_data_t *data)
{
    set_up_top_buttons(engine, data);
    set_up_bottom_buttons(engine, data);
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
