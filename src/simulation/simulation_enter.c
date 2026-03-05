/*
** EPITECH PROJECT, 2026
** simulation_enter.c
** File description:
** Initialize the simulation scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Text.h>
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
    data->change_type->on_click = (void *) change_tile_type;
    ui_button_set_tooltip(data->up,
        "Raises the height of selected tile by one.\n(Shortcut: R)",
        data->up->char_size, &sfWhite);
    ui_button_set_tooltip(data->down,
        "Lowers the height of selected tile by one.\n(Shortcut: L)",
        data->up->char_size, &sfWhite);
    ui_button_set_tooltip(data->change_type,
        "Changes the type of selected tile.", data->up->char_size, &sfWhite);
    ui_button_set_tooltip(data->bomb, "Lowers an area like a bomb would.",
        data->up->char_size, &sfWhite);
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

static void set_up_strength_ui(engine_t *engine, simulation_data_t *data)
{
    data->strength_minus =
        ui_button_create(engine, UI_BUTTON_TEXTURE, &(sfVector2f) {1050, 685},
        &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->strength_minus, "-", 24, &sfWhite);
    data->strength_minus->data = data->tilemap;
    data->strength_minus->on_click = (void *) decrease_tool_strength;
    data->strength_plus =
        ui_button_create(engine, UI_BUTTON_TEXTURE, &(sfVector2f) {1190, 685},
        &(sfVector2f) {BUTTON_WITDH, BUTTON_HEIGHT});
    ui_button_set_text(data->strength_plus, "+", 24, &sfWhite);
    data->strength_plus->data = data->tilemap;
    data->strength_plus->on_click = (void *) increase_tool_strength;
    data->strength_txt = sfText_create();
    sfText_setFont(data->strength_txt, engine->default_font);
    sfText_setCharacterSize(data->strength_txt, 20);
    sfText_setFillColor(data->strength_txt, sfWhite);
    sfText_setString(data->strength_txt, "Strength: 2");
    sfText_setPosition(data->strength_txt, (sfVector2f) {1120, 635});
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
    set_up_strength_ui(engine, data);
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
