#ifndef __BUTTON_H__
#define __BUTTON_H__

/*
 *
 */

typedef struct {

    uint        gpio_in;
    uint8_t     ascii_out;
}   t_button_map;

/*
 *
 */

void    vTaskButton(void *pvParameters);


#endif /*__BUTTON_H__*/
