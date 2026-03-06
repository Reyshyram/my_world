/*
** EPITECH PROJECT, 2026
** my_world.h
** File description:
** Main header
*/

#ifndef MY_WORLD_H
// clang-format off
    #define MY_WORLD_H

    #include "graphics/engine.h"

    #define UNUSED [[maybe_unused]]

    #define PROGRAM_NAME "my_world"
    #define WIN_TITLE "My World"
    #define WIN_HEIGHT 720
    #define WIN_WIDTH 1280
    #define FPS 60

    #define BUTTON_WITDH 125
    #define BUTTON_HEIGHT 56
    #define UI_BUTTON_TEXTURE "assets/sprites/ui/button.png"

    #define BACKGROUND_PATH SPRITES_PATH "background.png"

    #define BOMB_SOUND SFXS_PATHS "bomb.wav"
    #define LOWER_SOUND SFXS_PATHS "lower.mp3"
    #define RAISE_SOUND SFXS_PATHS "raise.mp3"
    #define RANDOM_SOUND SFXS_PATHS "random.wav"
    #define RESET_SOUND SFXS_PATHS "reset.wav"
    #define SAVE_SOUND SFXS_PATHS "save.wav"
    #define TYPE_SOUND SFXS_PATHS "type.wav"
// clang-format on

#endif /* !MY_WORLD_H */
