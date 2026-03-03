/*
** EPITECH PROJECT, 2026
** simulation_update.c
** File description:
** Update the simulation
*/

#include <SFML/Graphics/View.h>
#include <SFML/Window/Keyboard.h>

#include "graphics/engine.h"

#include "simulation.h"
#include "tilemap.h"

static void handle_speed_modifiers(float *speed_factor)
{
    if (sfKeyboard_isKeyPressed(sfKeyLControl)
        || sfKeyboard_isKeyPressed(sfKeyRControl))
        *speed_factor = 0.5F;
    if (sfKeyboard_isKeyPressed(sfKeyLShift)
        || sfKeyboard_isKeyPressed(sfKeyRShift))
        *speed_factor = 3;
}

static void handle_camera_movement(engine_t *engine, simulation_data_t *data,
    float speed_factor)
{
    float horizontal = 0;
    float vertical = 0;

    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        horizontal -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        horizontal += 1;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        vertical -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        vertical += 1;
    horizontal *= CAMERA_SPEED * engine->dt * speed_factor;
    vertical *= CAMERA_SPEED * engine->dt * speed_factor;
    sfView_move(data->tilemap->view, (sfVector2f) {horizontal, vertical});
}

static void handle_camera_rotation(engine_t *engine, simulation_data_t *data,
    float speed_factor)
{
    float rotation = 0;

    if (sfKeyboard_isKeyPressed(sfKeyQ))
        rotation -= ROTATION_SPEED * engine->dt * speed_factor;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        rotation += ROTATION_SPEED * engine->dt * speed_factor;
    if (rotation != 0) {
        data->tilemap->rotation_rad += rotation;
        tilemap_calculate_vertices(data->tilemap);
    }
}

static void handle_camera_zoom(engine_t *engine, simulation_data_t *data,
    float speed_factor)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        sfView_zoom(data->tilemap->view,
            1 - ZOOM_SPEED * engine->dt * speed_factor);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        sfView_zoom(data->tilemap->view,
            1 + ZOOM_SPEED * engine->dt * speed_factor);
}

void simulation_update(engine_t *engine)
{
    simulation_data_t *data = (simulation_data_t *) engine->scene->data;
    float speed_factor = 1;

    if (!data)
        return;
    handle_speed_modifiers(&speed_factor);
    handle_camera_movement(engine, data, speed_factor);
    handle_camera_rotation(engine, data, speed_factor);
    handle_camera_zoom(engine, data, speed_factor);
}
