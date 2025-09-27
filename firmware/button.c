#include <stdio.h>
#include <string.h>
#include "button.h"

/*
 *
 */

void    Button_init(t_button *ctx, const t_button_map *map, uint8_t count)
{
    memset(ctx, 0, sizeof(t_button));
    ctx->map = (t_button_map*) map;
    ctx->count = count;

    for (uint8_t n = 0; n < ctx->count; n++) {

        gpio_init(ctx->map[n].gpio_in);
        gpio_pull_up(ctx->map[n].gpio_in);
    }
}

void    Button_pool(t_button *ctx, t_keyboard *keyboard)
{
    for (uint8_t n = 0; n < ctx->count; n++) {

        if (!gpio_get(ctx->map[n].gpio_in)) {

            if (!(ctx->pressed_flags & (1 << n))) {

                Keyboard_press(keyboard, ctx->map[n].ascii_out);
                ctx->pressed_flags |= (1 << n);
            }
        }
        else {

            if (ctx->pressed_flags & (1 << n)) {

                Keyboard_release(keyboard, ctx->map[n].ascii_out);
                ctx->pressed_flags &= ~(1 << n);
            }
        }
    }
}