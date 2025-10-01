#include <string.h>
#include "keyboard.h"

void    Keyboard_init(t_keyboard *ctx)
{
    memset(ctx, 0, sizeof(t_keyboard));
}

void    Keyboard_press(t_keyboard *ctx, uint8_t ascii_key)
{
    /* Already pressed? */
    for (uint8_t n = 0; n < MAX_SIMULTANEOUS_KEY; n++) {

        if (ctx->pressedKey[n] == ascii_key) {

            return;
        }
    }

    for (uint8_t n = 0; n < MAX_SIMULTANEOUS_KEY; n++) {

        if (ctx->pressedKey[n] == 0) {

            ctx->pressedKey[n] = ascii_key;
            break;
        }
    }

    ctx->changed = true;
}

void    Keyboard_release(t_keyboard *ctx, uint8_t ascii_key)
{
#ifdef TRIM_KEY_LEFT
    uint8_t n = 0;

    while (true) {

        if (ctx->pressedKey[n] == ascii_key) {

            ctx->pressedKey[n] = 0;

            // Trim left
            for (uint8_t z = n; z < MAX_SIMULTANEOUS_KEY - 1; z++)
                ctx->pressedKey[z] = ctx->pressedKey[z+1];
            ctx->pressedKey[MAX_SIMULTANEOUS_KEY] = 0;
        }
        else
            n++;

        if (n >= MAX_SIMULTANEOUS_KEY)
            break;
    }
#else
    for (uint8_t n = 0; n < MAX_SIMULTANEOUS_KEY; n++) {

        if (ctx->pressedKey[n] == ascii_key) {

            ctx->pressedKey[n] = 0;
        }
    }
#endif /*TRIM_KEY_LEFT*/

    ctx->changed = true;
}

void    Keyboard_releaseAll(t_keyboard *ctx)
{
    memset(ctx->pressedKey, 0, sizeof(uint8_t) * MAX_SIMULTANEOUS_KEY);
    ctx->changed = true;
}

bool    Keyboard_hasChanged(t_keyboard *ctx)
{
    return ctx->changed;
}

void    Keyboard_dump(t_keyboard *ctx)
{
    printf("Keyboard(");
    for (uint8_t n = 0; n < MAX_SIMULTANEOUS_KEY; n++) {

        printf(" 0x%02X", ctx->pressedKey[n]);
    }
    printf(" )\n");
}

void    Keyboard_setKeyTable(t_keyboard *ctx, const uint8_t *keytable, size_t keytable_size)
{
    ctx->keytable = (uint8_t*) keytable;
    ctx->keytable_size = keytable_size;
}

static bool my_lookup_keycode(uint8_t character, const uint8_t *table, int size, uint8_t *keycode)
{
    for (int i = 0; i < size; i++) {

        if (table[i] != character)
            continue;
        *keycode = i;

        return true;
    }

    return false;
}

/*
 * HID report
 * 8 bytes: [MODIFIER] [RESERVED] [KEY1] [KEY2] [KEY3] [KEY4] [KEY5] [KEY6]
 */

 void    Keyboard_getHIDReportPayload(t_keyboard *ctx, uint8_t *hid_report)
{
    uint8_t input_idx = 0;
    uint8_t report_idx = 0;

    memset(hid_report, 0, sizeof(uint8_t) * HID_REPORT_SIZE);

    for (input_idx = 0; input_idx < MAX_SIMULTANEOUS_KEY; input_idx++) {

        if (ctx->pressedKey[input_idx] != 0) {

            uint8_t keycode = 0;

            if (my_lookup_keycode(ctx->pressedKey[input_idx], ctx->keytable, ctx->keytable_size, &keycode)) {

                hid_report[report_idx+2] = keycode;
                report_idx++;
            }
        }
    }

//    printf("  Report(");
//    for (uint8_t n = 0; n < HID_REPORT_SIZE; n++) {
//        printf(" 0x%02X", hid_report[n]);
//    }
//    printf(" )\n");

    ctx->changed = false;
}
