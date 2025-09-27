#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "pico/stdlib.h"
#include "keyboard.h"

/*
 *
 */

typedef struct {

    uint        gpio_in;
    uint8_t     ascii_out;
}   t_button_map;

typedef struct {

    t_button_map    *map;
    uint8_t         count;
    uint32_t        pressed_flags;
}   t_button;

/*
 *
 */

void    Button_init(t_button *ctx, const t_button_map *map, uint8_t count);
void    Button_pool(t_button *ctx, t_keyboard *keyboard);


#endif /*__BUTTON_H__*/
