/*
** EPITECH PROJECT, 2026
** main
** File description:
** Main file for the program
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/VideoMode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    srand(time(nullptr));
    engine_set_scene(engine, simulation_scene, false);
    engine_main_loop(engine);
    engine_destroy(engine);
}

static int print_help(char *arg)
{
    if (strcmp(arg, "-h") != 0 && strcmp(arg, "--help") != 0) {
        fprintf(stderr, "Invalid argument: %s\n", arg);
        return ERROR;
    }
    puts("Usage: ./my_world [-h|--help]\n");
    puts("How to move the camera:");
    puts("- Arrow keys to move the camera");
    puts("- Q and D to rotate the camera");
    puts("- Z and S to zoom in and out");
    puts("- Shift or Ctrl to change movement speed\n");
    puts("How to modify the world:");
    puts("- Right click to select a block");
    puts("- Click on a button to activate an effect");
    puts("- More informations about the effects/shortcuts in the tooltips");
    return SUCCESS;
}

int main(int ac, UNUSED char **av, char **env)
{
    engine_t engine = {0};
    sfVideoMode video_mode = {WIN_WIDTH, WIN_HEIGHT, 32};

    if (ac == 2)
        return print_help(av[1]);
    if (!is_graphical(env)) {
        fprintf(stderr, "Error: cannot run in a non graphical environment\n");
        return ERROR;
    }
    if (!engine_init(&engine, WIN_TITLE, &video_mode, false)) {
        engine_destroy(&engine);
        fprintf(stderr, "Error: failed to initialize the engine\n");
        return ERROR;
    }
    if (ac == 4 && strcmp(av[1], "-s") == 0) {
        engine.optional_height = atoi(av[2]);
        engine.optional_width = atoi(av[3]);
    }
    printf("%i %i\n", engine.optional_height, engine.optional_width);
    run_game(&engine);
    return SUCCESS;
}
