#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "button.h"
#include "board.h"
#include "keyboard.h"

/*
 *
 */

#define BUTTON_MAP_COUNT    4

t_button_map    button_map[BUTTON_MAP_COUNT] = {

    { LEFT_FLIP_BUTTON_PIN,  LEFT_FLIP_BUTTON_ASCII  },
    { RIGHT_FLIP_BUTTON_PIN, RIGHT_FLIP_BUTTON_ASCII },
    { LAUNCH_BUTTON_PIN,     LAUNCH_BUTTON_ASCII     },
    { MENU_BUTTON_PIN,       MENU_BUTTON_ASCII       }
};

/*
 *
 */

void vTaskButton(void *pvParameters)
{
    TickType_t          previousWakeTime = 0;
    t_keyboard_event    event;
    QueueHandle_t       keyInputQueue = (QueueHandle_t) pvParameters;
    uint32_t            pressed_flags;

    /* Init Buttons */
    for (uint8_t n = 0; n < BUTTON_MAP_COUNT; n++) {

        gpio_init(button_map[n].gpio_in);
        gpio_pull_up(button_map[n].gpio_in);
    }

    /* Poll button(s) forever */
    while (true) {

        for (uint8_t n = 0; n < BUTTON_MAP_COUNT; n++) {

            if (!gpio_get(button_map[n].gpio_in)) {

                if (!(pressed_flags & (1 << n))) {

                    /* Send key event in queue */
                    event.type = KEY_PRESS;
                    event.ascii_key = button_map[n].ascii_out;
                    xQueueSendToBack(keyInputQueue, &event, 1);

                    pressed_flags |= (1 << n);
                }
            }
            else {

                if (pressed_flags & (1 << n)) {

                    /* Send key event in queue */
                    event.type = KEY_RELEASE;
                    event.ascii_key = button_map[n].ascii_out;
                    xQueueSendToBack(keyInputQueue, &event, 1);

                    pressed_flags &= ~(1 << n);
                }
            }
        }

        xTaskDelayUntil(&previousWakeTime, pdMS_TO_TICKS(1));
    }

    vTaskDelete(NULL);
}
