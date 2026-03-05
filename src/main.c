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

struct args {
    int width;
    int height;
    char *filename;
};

static void run_game(engine_t *engine, int width, int height, char *filename)
{
    scene_t *simulation_scene = simulation_create(width, height, filename);

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

static int print_help(void)
{
    puts("Usage: ./my_world [-h|--help] [-s height width] [-f filename]\n");
    puts("How to move the camera:");
    puts("- Arrow keys to move the camera");
    puts("- Q and D to rotate the camera");
    puts("- Z and S to zoom in and out");
    puts("- Shift or Ctrl to change movement speed\n");
    puts("How to modify the world:");
    puts("- Right click to select a block");
    puts("- Click on a button to activate an effect");
    puts("- More informations about the effects/shortcuts in the tooltips");
    return 1;
}

static int parse_size_args(int ac, char **av, int *i, struct args *args)
{
    if (strcmp(av[*i], "-s") == 0 && *i + 2 < ac) {
        (*i)++;
        args->height = atoi(av[*i]);
        (*i)++;
        args->width = atoi(av[*i]);
        if (args->width < 8 || args->width > 256 || args->height < 8
            || args->height > 256) {
            fprintf(stderr,
                "Error: width and height must be between 8 and 256\n");
            return ERROR;
        }
        return SUCCESS;
    }
    return 1;
}

static int parse_args(int ac, char **av, struct args *args)
{
    int size_success = 0;

    for (int i = 1; i < ac; i++) {
        if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help"))
            return print_help();
        size_success = parse_size_args(ac, av, &i, args);
        if (size_success == ERROR)
            return ERROR;
        if (size_success == SUCCESS)
            continue;
        if (strcmp(av[i], "-f") == 0 && i + 1 < ac) {
            i++;
            args->filename = av[i];
        } else {
            fprintf(stderr, "Invalid argument: %s\n", av[i]);
            return ERROR;
        }
    }
    return SUCCESS;
}

int main(int ac, char **av, char **env)
{
    engine_t engine = {0};
    sfVideoMode video_mode = {WIN_WIDTH, WIN_HEIGHT, 32};
    struct args args = {MAP_DEFAULT_W, MAP_DEFAULT_H, NULL};
    int parse_status = parse_args(ac, av, &args);

    if (parse_status != SUCCESS)
        return (parse_status == 1) ? SUCCESS : ERROR;
    if (!is_graphical(env)) {
        fprintf(stderr, "Error: cannot run in a non graphical environment\n");
        return ERROR;
    }
    if (!engine_init(&engine, WIN_TITLE, &video_mode, false)) {
        engine_destroy(&engine);
        fprintf(stderr, "Error: failed to initialize the engine\n");
        return ERROR;
    }
    run_game(&engine, args.width, args.height, args.filename);
    return SUCCESS;
}
