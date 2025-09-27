#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "btstack.h"
#include "hid_keyboard_demo.h"

#include "board.h"
#include "button.h"
#include "keyboard.h"


/*
 * Entry point
 */

int main(void)
{
    t_button    button;
    t_keyboard  keyboard;

    /* Init Pico */
    stdio_init_all();
    if (cyw43_arch_init()) {

        printf("cyw43_arch_init() error\n");
        return 0;
    }

    /* Virtual keyboard */
    const uint8_t *keytable_us_none = NULL;
    size_t keytable_us_none_size = 0;

    keytable_us_none = get_keytable_us_none(&keytable_us_none_size);
    Keyboard_init(&keyboard);
    Keyboard_setKeyTable(&keyboard, keytable_us_none, keytable_us_none_size);

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

            uint8_t     hid_report[HID_REPORT_SIZE];

            Keyboard_dump(&keyboard);
            Keyboard_getHIDReportPayload(&keyboard, hid_report);

            printf("  Report(");
            for (uint8_t n = 0; n < HID_REPORT_SIZE; n++) {
                printf(" 0x%02X", hid_report[n]);
            }
            printf(" )\n");

            send_hid_report(hid_report);
        }

        tight_loop_contents();
    }

    return 0;
}
