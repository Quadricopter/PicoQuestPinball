#include "FreeRTOS.h"
#include "queue.h"

#include "keyboard.h"

void vTaskNudge(void *pvParameters)
{
    TickType_t          previousWakeTime = 0;
    QueueHandle_t       keyInputQueue = (QueueHandle_t) pvParameters;
    t_keyboard_event    event;

    // TODO: init accelerometer

    while (true) {

        // TODO: pool accelerometer

        // event.type = KEY_PRESS;
        // event.ascii_key = 's';
        // xQueueSendToBack(keyInputQueue, &event, 1);

        // event.type = KEY_RELEASE;
        // event.ascii_key = 's';
        // xQueueSendToBack(keyInputQueue, &event, 1);

        xTaskDelayUntil(&previousWakeTime, 1000);
    }

    vTaskDelete(NULL);
}
