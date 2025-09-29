#ifndef __BOARD_H__
#define __BOARD_H__

#include "hardware/i2c.h"

/*
 * Raspberry Pi Pico W
 */

#define LEFT_FLIP_BUTTON_PIN    2
#define RIGHT_FLIP_BUTTON_PIN   3
#define LAUNCH_BUTTON_PIN       4
#define MENU_BUTTON_PIN         5

#define I2C_DEVICE              i2c0
#define I2C_SPEED               400000
#define I2C_SDA_PIN             20
#define I2C_SCL_PIN             21

/*
 * Pinball FX VR
 */

#define LEFT_FLIP_BUTTON_ASCII  'u'
#define RIGHT_FLIP_BUTTON_ASCII '6'
#define LAUNCH_BUTTON_ASCII     '8'
#define MENU_BUTTON_ASCII       'i'

#define NUDGE_UP_ASCII          's'
#define NUDGE_LEFT_ASCII        'd'
#define NUDGE_RIGHT_ASCII       'f'

/*
 * FreeRTOS
 */

#define EVENT_QUEUE_LENGTH      8


#endif /*__BOARD_H__*/