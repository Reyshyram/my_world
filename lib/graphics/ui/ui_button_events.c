/*
** EPITECH PROJECT, 2026
** ui_buttons_events.c
** File description:
** Handle ui button events
*/

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Mouse.h>

#include "graphics/engine.h"
#include "graphics/ui.h"

void ui_button_events(ui_button_t *button, const sfEvent *event,
    const engine_t *engine)
{
    sfVector2f scale = {1.5F, 1.5F};

    if (!button || !event || !engine)
        return;
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseLeft) {
        if (button->on_click && button->hovered) {
            sfText_setScale(button->text, scale);
            sfRectangleShape_setScale(button->background, scale);
            button->on_click(button->data);
        }
    }
}
