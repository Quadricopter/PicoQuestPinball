#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hid_keyboard_demo.h"

#define MAX_SIMULTANEOUS_KEY    (HID_REPORT_SIZE - 2)
#define TRIM_KEY_LEFT

typedef struct {

    uint8_t pressedKey[MAX_SIMULTANEOUS_KEY];
    bool    changed;

    /* Bluetooth Keytable */
    uint8_t *keytable;
    size_t  keytable_size;
}   t_keyboard;

void    Keyboard_init(t_keyboard *);
void    Keyboard_press(t_keyboard *, uint8_t ascii_key);
void    Keyboard_release(t_keyboard *, uint8_t ascii_key);
void    Keyboard_releaseAll(t_keyboard *);

bool    Keyboard_hasChanged(t_keyboard *);
void    Keyboard_dump(t_keyboard *);

void    Keyboard_setKeyTable(t_keyboard *, const uint8_t *keytable, size_t keytable_size);
void    Keyboard_getHIDReportPayload(t_keyboard *, uint8_t *report);

#endif /*__KEYBOARD_H__*/
