/*
** EPITECH PROJECT, 2025
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
// clang-format on

typedef struct {

} simulation_data_t;

scene_t *simulation_create(void);
void simulation_enter(engine_t *engine);
void simulation_exit(engine_t *engine);
void simulation_draw(engine_t *engine);
void simulation_update(engine_t *engine);
void simulation_event(engine_t *engine, sfEvent *event);

#endif /* !SIMULATION_H_ */
