#ifndef __HID_KEYBOARD_DEMO_H__
#define __HID_KEYBOARD_DEMO_H__

#include <stdint.h>

#define HID_REPORT_SIZE  8

/*
 * BTstack sample func
 */

int btstack_main(int argc, const char * argv[]);

/*
 * External access to static members
 */

void            send_hid_report(uint8_t *hid_report);
const uint8_t   *get_keytable_us_none(size_t *size);

#endif /*__HID_KEYBOARD_DEMO_H__*/
