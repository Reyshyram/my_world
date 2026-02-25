/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main file for the program
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/VideoMode.h>
#include <stdio.h>

#include "graphics/engine.h"

#include "my_world.h"
#include "simulation.h"

static void run_game(engine_t *engine)
{
    scene_t *simulation_scene = simulation_create();

    if (!simulation_scene) {
        fprintf(stderr, "Error: failed to create the simulation scene\n");
        return;
    }
    sfRenderWindow_setFramerateLimit(engine->window, FPS);
    engine_set_scene(engine, simulation_scene, false);
    engine_main_loop(engine);
    engine_destroy(engine);
}

int main(int ac, UNUSED char **av, char **env)
{
    engine_t engine = {0};
    sfVideoMode video_mode = {WIN_WIDTH, WIN_HEIGHT, 32};

    if (!is_graphical(env)) {
        fprintf(stderr, "Error: cannot run in a non graphical environment\n");
        return ERROR;
    }
    if (ac != 1) {
        fprintf(stderr, "Too many arguments.\n");
        return ERROR;
    }
    if (!engine_init(&engine, WIN_TITLE, &video_mode, false)) {
        engine_destroy(&engine);
        fprintf(stderr, "Error: failed to initialize the engine\n");
        return ERROR;
    }
    run_game(&engine);
    return SUCCESS;
}
