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

typedef struct {
    tilemap_t *tilemap;
    ui_button_t *up;
    ui_button_t *down;
    ui_button_t *change_type;
    ui_button_t *bomb;
    ui_button_t *random;
    ui_button_t *reset;
} simulation_data_t;

scene_t *simulation_create(void);
void simulation_enter(engine_t *engine);
void simulation_exit(engine_t *engine);
void simulation_draw(engine_t *engine);
void simulation_update(engine_t *engine);
void simulation_event(engine_t *engine, sfEvent *event);

#endif /* !SIMULATION_H_ */
