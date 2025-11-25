#ifndef TIMER_H
#define TIMER_H

#include <dos.h>

/*---------------------------------------------------------
  Fixed-width integer definitions
  (for compilers that lack <stdint.h>)
---------------------------------------------------------*/
#ifndef __STDINT_H_INCLUDED
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
#endif

/*---------------------------------------------------------
  Timer structure
---------------------------------------------------------*/
typedef struct {
    uint32_t start_ticks;
    uint32_t elapsed_ticks;
} Timer;

/*---------------------------------------------------------
  Function Prototypes
---------------------------------------------------------*/

/**
 * Returns the current BIOS tick count (32-bit value).
 * Each tick occurs ~18.2 times per second.
 */
uint32_t timer_get_ticks(void);

/**
 * Starts a timer.
 */
void timer_start(Timer *timer);

/**
 * Updates the timer’s elapsed tick count.
 */
void timer_update(Timer *timer);

/**
 * Returns the elapsed time since timer_start() in milliseconds.
 */
uint32_t timer_get_elapsed_ms(const Timer *timer);

/**
 * Delays program execution for the specified number of milliseconds.
 * (Blocking delay using busy-wait)
 */
void timer_delay(uint32_t ms);

#endif /* TIMER_H */
