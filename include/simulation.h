/*
** EPITECH PROJECT, 2026
** simulation.h
** File description:
** Simulation scene
*/

#ifndef SIMULATION_H_
// clang-format off
    #define SIMULATION_H_

    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>

    #include "graphics/engine.h"
    #include "graphics/ui.h"
    #include "tilemap.h"
// clang-format on

typedef struct simulation_s {
    tilemap_t *tilemap;
    unsigned int map_width;
    unsigned int map_height;
    char *filename;
    sfSprite *background;
    ui_button_t *up;
    ui_button_t *down;
    ui_button_t *change_type;
    ui_button_t *bomb;
    ui_button_t *random;
    ui_button_t *reset;
    ui_button_t *save;
    ui_button_t *strength_plus;
    ui_button_t *strength_minus;
    sfText *strength_txt;
} simulation_data_t;

scene_t *simulation_create(int width, int height, char *filename);
void simulation_enter(engine_t *engine);
void simulation_exit(engine_t *engine);
void simulation_draw(engine_t *engine);
void simulation_update(engine_t *engine);
void simulation_event(engine_t *engine, sfEvent *event);

#endif /* !SIMULATION_H_ */
