#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "btstack.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "hid_keyboard_demo.h"
#include "board.h"
#include "button.h"
#include "nudge.h"
#include "keyboard.h"

/*
 * Main task
 * Receives button/nudge events and send reports
 */

void vTaskMain(void *pvParameters)
{
    TickType_t          previousWakeTime = 0;
    QueueHandle_t       keyInputQueue = NULL;
    t_keyboard          keyboard;
    t_keyboard_event    event;

    /* Virtual keyboard */
    const uint8_t *keytable_us_none = NULL;
    size_t keytable_us_none_size = 0;

    keytable_us_none = get_keytable_us_none(&keytable_us_none_size);
    Keyboard_init(&keyboard);
    Keyboard_setKeyTable(&keyboard, keytable_us_none, keytable_us_none_size);

    /* Init Bluetooth */
    btstack_main(0, NULL);
    gap_set_local_name("PicoQuestPinball");

    /* Start button and nudge task */
    keyInputQueue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(t_keyboard_event));
    xTaskCreate(vTaskButton, "button", configMINIMAL_STACK_SIZE, keyInputQueue, 0, NULL);
    xTaskCreate(vTaskNudge,  "nudge",  configMINIMAL_STACK_SIZE, keyInputQueue, 0, NULL);

    /* Infinite loop */
    while (1) {

        /* Wait event(s) from button/nudge tasks.. */
        while (xQueueReceive(keyInputQueue, &event, 1)) {

            printf("event: %d, %d\n", event.type, event.ascii_key);
            switch (event.type) {

                case KEY_RELEASE:
                    Keyboard_release(&keyboard, event.ascii_key);
                    break;

                case KEY_PRESS:
                    Keyboard_press(&keyboard, event.ascii_key);
                    break;
            }
        }

        /* ..and generate related HID report */
        if (Keyboard_hasChanged(&keyboard)) {

            uint8_t     hid_report[HID_REPORT_SIZE];

            Keyboard_dump(&keyboard);
            Keyboard_getHIDReportPayload(&keyboard, hid_report);
            send_hid_report(hid_report);
        }

        tight_loop_contents();

        xTaskDelayUntil(&previousWakeTime, pdMS_TO_TICKS(1));
    }

    vTaskDelete(NULL);
}

/*
 * Entry point
 */

int main(void)
{
    TaskHandle_t    xTask;

    /* Init Pico */
    stdio_init_all();
    if (cyw43_arch_init()) {

        printf("cyw43_arch_init() error\n");
        return 0;
    }

    /* FreeRTOS main task */
    xTaskCreate(vTaskMain, "main", configMINIMAL_STACK_SIZE, NULL, 0, &xTask);
    vTaskCoreAffinitySet(xTask, 1);     // assertion "get_core_num() == async_context_core_num(cyw43_async_context)" failed

    /* Run FreeRTOS scheduler */
    vTaskStartScheduler();
    printf("[%s] vTaskStartScheduler stopped!\n", __FUNCTION__);
    while (true) {        
    }

    return 0;
}
