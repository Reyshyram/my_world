/*
** EPITECH PROJECT, 2026
** interpolation.c
** File description:
** Interpolation function for the engine
*/

float interpolatef(float a, float b, float t)
{
    return a + t * (b - a);
}
