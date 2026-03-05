/*
** EPITECH PROJECT, 2026
** ui_button_set_tooltip
** File description:
** ui button set text but tooltip
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>

#include "graphics/ui.h"

void ui_button_set_tooltip(ui_button_t *button, const char *text,
    int char_size, sfColor *color)
{
    sfFloatRect text_bounds;

    if (!button || !text || !color)
        return;
    sfText_setString(button->tooltip_text, text);
    if (char_size > 0)
        sfText_setCharacterSize(button->tooltip_text,
            (unsigned int) button->scale.x * char_size);
    if (color)
        sfText_setFillColor(button->tooltip_text, *color);
    text_bounds = sfText_getLocalBounds(button->text);
    sfText_setOrigin(button->tooltip_text,
        (sfVector2f) {text_bounds.left + text_bounds.width / 2,
            text_bounds.top + text_bounds.height / 2});
    sfText_setPosition(button->tooltip_text,
        (sfVector2f) {sfRectangleShape_getPosition(button->background).x,
            sfRectangleShape_getPosition(button->background).y
            + (float) (button->char_size * 3)});
}
