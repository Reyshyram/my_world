/*
** EPITECH PROJECT, 2026
** ui_button_draw
** File description:
** ui_button but it draws
*/

#include <SFML/Graphics/RenderWindow.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

void button_draw_tooltip(engine_t *engine, ui_button_t *button)
{
    sfRenderWindow_drawText(engine->window, button->text, nullptr);
    sfRenderWindow_drawText(engine->window, button->tooltip_text, nullptr);
}

void ui_button_draw(engine_t *engine, ui_button_t *button)
{
    sfRenderWindow_drawRectangleShape(engine->window, button->background,
        nullptr);
    sfRenderWindow_drawText(engine->window, button->text, nullptr);
    if (button->hovered && button->tooltip_text)
        button_draw_tooltip(engine, button);
}
