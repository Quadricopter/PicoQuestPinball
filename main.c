#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hid_keyboard_demo.c"  // FIXME: .c/.h

#include "board.h"
#include "button.h"
#include "keyboard.h"

//#include "btstack.h"
//#define REPORT_ID 0x01
//extern uint16_t hid_cid;
//int btstack_main(int argc, const char *argv[]);


void send_report_array(int modifier, uint8_t *keycode_array)
{
    uint8_t message[] = {0xa1, REPORT_ID, modifier, 0, keycode_array[0],
                                                       keycode_array[1],
                                                       keycode_array[2],
                                                       keycode_array[3],
                                                       keycode_array[4],
                                                       keycode_array[5]};

    hid_device_send_interrupt_message(hid_cid, &message[0], sizeof(message));
}

/*
 * Entry point
 */

int main(void)
{
    t_button    button;
    t_keyboard  keyboard;
    uint8_t     report[BLUETOOTH_REPORT_LEN];

    /* Init Pico */
    stdio_init_all();
    if (cyw43_arch_init()) {

        printf("cyw43_arch_init() error\n");
        return 0;
    }

    /* Virtual keyboard */
    Keyboard_init(&keyboard);
    Keyboard_setKeyTable(&keyboard, keytable_us_none, sizeof(keytable_us_none));

    /* Init Buttons */
    t_button_map    button_map[] = {

        { LEFT_FLIP_BUTTON_PIN,  LEFT_FLIP_BUTTON_ASCII  },
        { RIGHT_FLIP_BUTTON_PIN, RIGHT_FLIP_BUTTON_ASCII },
        { LAUNCH_BUTTON_PIN,     LAUNCH_BUTTON_ASCII     },
        { MENU_BUTTON_PIN,       MENU_BUTTON_ASCII       }
    };
    Button_init(&button, button_map, 4);

    /* Init Bluetooth */
    btstack_main(0, NULL);
    gap_set_local_name("PicoQuestPinball");

    /* Infinite loop */
    while (1) {

        Button_pool(&button, &keyboard);
        if (Keyboard_hasChanged(&keyboard)) {

            uint8_t     report[BLUETOOTH_REPORT_LEN];

            Keyboard_dump(&keyboard);
            Keyboard_getHIDReportPayload(&keyboard, report, BLUETOOTH_REPORT_LEN);

            printf("  Report(");
            for (uint8_t n = 0; n < BLUETOOTH_REPORT_LEN; n++) {
                printf(" 0x%02X", report[n]);
            }
            printf(" )\n");

            send_report_array(0, report);
        }

        tight_loop_contents();
    }

    return 0;
}
