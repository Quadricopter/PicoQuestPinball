#include <stdio.h>
#include <math.h>
#include "FreeRTOS.h"
#include "queue.h"

#include "nudge.h"
#include "keyboard.h"
#include "board.h"
#include "lis3dh.h"
#include "filter.h"

__inline__ double rad_to_deg(double rad)
{
    return (rad * 180.f) / M_PI;
}

void raw_to_angle(int16_t x, int16_t y, int16_t z, double *pitch, double *roll, double *g)
{
    double p = atan2(y, z);
    double r = atan2(x, z);
    double length = sqrt(x*x + y*y + z*z);

    *pitch = rad_to_deg(p);
    *roll = rad_to_deg(r);
    *g = length / 16384;     // +/- 2G
}

void vTaskNudge(void *pvParameters)
{
    TickType_t          previousWakeTime = 0;
    TickType_t          nudgeTime = 0;
    TickType_t          now = 0;
    uint8_t             keyMem = 0;
    QueueHandle_t       keyInputQueue = (QueueHandle_t) pvParameters;
    t_keyboard_event    event;
    t_lis3dh            accelero;
    e_nudge_state       nudgeState = NUDGE_ARMED;

    /* Init accelerometer */
    lis3dh_init(&accelero, CRTL_REG1_200HZ | CRTL_REG1_XYZ);

    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;

    double  raw_pitch = 0.f;
    double  raw_roll = 0.f;
    double  g = 1.f;

    double  hp_pitch_mem = 0.f;
    double  hp_roll_mem = 0.f;
    double  zero_pitch = 0.f;
    double  zero_roll = 0.f;

    /* Read accel once to init variables with real values */
    lis3dh_read_raw_accel(&accelero, &x, &y, &z);
    raw_to_angle(x, y, z, &raw_pitch, &raw_roll, &g);
    hp_pitch_mem = raw_pitch;
    hp_roll_mem = raw_roll;

    /* Poll accelerometer */
    while (true) {

        /* Read current "raw" values */
        lis3dh_read_raw_accel(&accelero, &x, &y, &z);
        raw_to_angle(x, y, z, &raw_pitch, &raw_roll, &g);

        /* Smooth values for "long time" idle zero */
        high_pass_filter(4, &zero_pitch, raw_pitch, &hp_pitch_mem);
        high_pass_filter(4, &zero_roll,  raw_roll,  &hp_roll_mem);
        printf("UP:%5.1f, LR:%5.1f, G:%.3f\n", zero_pitch, zero_roll, g);

        now = xTaskGetTickCount();

        /* Waiting trigger event */
        if (nudgeState == NUDGE_ARMED) {

            if (g > TRIGGER_G) {

                printf("NUDGE_UP\n");
                keyMem = NUDGE_UP_ASCII;
            }

//            if (fabs(zero_pitch) > TRIGGER_DEG) {
//
//                printf("NUDGE_UP\n");
//                keyMem = NUDGE_UP_ASCII;
//            }
//            else if (zero_roll < -TRIGGER_DEG) {
//
//                printf("NUDGE_LEFT\n");
//                keyMem = NUDGE_LEFT_ASCII;
//            }
//            else if (zero_roll > TRIGGER_DEG) {
//
//                printf("NUDGE_RIGHT\n");
//                keyMem = NUDGE_RIGHT_ASCII;
//            }

            if (keyMem) {

                printf("NUDGE_TRIGGERED\n");

                nudgeTime = xTaskGetTickCount();

                event.type = KEY_PRESS;
                event.ascii_key = keyMem;
                xQueueSendToBack(keyInputQueue, &event, 1);

                nudgeState = NUDGE_TRIGERGED;
            }
        }

        /* Release key after 'NUDGE_PRESS_MS' delay */
        else if (nudgeState == NUDGE_TRIGERGED) {

            if ((now - nudgeTime) > NUDGE_PRESS_MS) {

                printf("NUDGE_RELEASED\n");

                event.type = KEY_RELEASE;
                event.ascii_key = keyMem;
                xQueueSendToBack(keyInputQueue, &event, 1);

                nudgeState = NUDGE_RELEASED;
                keyMem = 0;
            }
        }

        /* Armed again after 'HOLDOFF_MS' delay */
        else if (nudgeState == NUDGE_RELEASED) {

            if ((now - nudgeTime) > HOLDOFF_MS) {

                printf("NUDGE_ARMED\n");
                nudgeState = NUDGE_ARMED;
            }
        }

        xTaskDelayUntil(&previousWakeTime, pdMS_TO_TICKS(5));  // 200 Hz
    }

    vTaskDelete(NULL);
}
