#ifndef __NUDGE_H__
#define __NUDGE_H__

/*
 *
 */

#define TRIGGER_DEG     45      //
#define TRIGGER_G       2.f     //

#define NUDGE_PRESS_MS  100     // Key down duration
#define HOLDOFF_MS      500     // Minimum time between two nudge events

/*
 *
 */

typedef enum {

    NUDGE_ARMED = 0,
    NUDGE_TRIGERGED,
    NUDGE_RELEASED
}   e_nudge_state;

/*
 *
 */

void vTaskNudge(void *pvParameters);


#endif /*__NUDGE_H__*/
