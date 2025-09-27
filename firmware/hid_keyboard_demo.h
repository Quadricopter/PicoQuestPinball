#ifndef __HID_KEYBOARD_DEMO_H__
#define __HID_KEYBOARD_DEMO_H__

#include <stdint.h>

/*
 * BTstack sample func
 */

int btstack_main(int argc, const char * argv[]);

/*
 * External access to static func
 */

void send_report_array(int modifier, uint8_t *keycode_array);
const uint8_t *get_keytable_us_none(size_t *size);

#endif /*__HID_KEYBOARD_DEMO_H__*/
