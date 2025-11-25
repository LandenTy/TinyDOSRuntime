/*=========================================================
    DOS-Compatible Timer Library Implementation
    --------------------------------------------
    Provides simple timing functions using the BIOS
    tick counter at 0x0040:0x006C (~18.2 ticks per second)
=========================================================*/

#include "timer.h"

/*---------------------------------------------------------
  Compiler compatibility for interrupt control
---------------------------------------------------------*/
#ifdef __WATCOMC__
  #include <i86.h>
  #define disable() _disable()
  #define enable()  _enable()
#elif defined(__TURBOC__) || defined(__BORLANDC__)
  #include <dos.h>
#else
  #define disable()
  #define enable()
#endif

/*---------------------------------------------------------
  BIOS tick counter constants
---------------------------------------------------------*/
#define BIOS_TICK_SEGMENT 0x40
#define BIOS_TICK_OFFSET  0x6C
#define TICKS_PER_SECOND  18.2065
#define MS_PER_TICK       (1000.0 / TICKS_PER_SECOND)

/*
    function : timer_get_ticks
    args     : 
    purpose  : Gets the number of CPU ticks based
    on the BIOS.
*/
uint32_t timer_get_ticks(void)
{
    uint32_t ticks;
    disable();
    ticks = *(volatile uint32_t far *)MK_FP(BIOS_TICK_SEGMENT, BIOS_TICK_OFFSET);
    enable();
    return ticks;
}

/*
    function : timer_start
    args     : Timer
    purpose  : Starts the timer for the scene

    Timer    : (Timer) Timer
*/
void timer_start(Timer *timer)
{
    if (!timer) return;
    timer->start_ticks = timer_get_ticks();
    timer->elapsed_ticks = 0;
}

/*
    function : timer_update
    args     : Timer
    purpose  : Updates the timer for the scene per frame
    
    Timer    : (Timer) Timer
*/
void timer_update(Timer *timer)
{
    uint32_t now_ticks;

    if (!timer)
        return;

    now_ticks = timer_get_ticks();
    timer->elapsed_ticks = now_ticks - timer->start_ticks;
}

/*
    function : timer_get_elapsed_ms
    args     : Timer
    purpose  : Returns elapsed time in ms
    
    Timer    : (Timer) Timer
*/
uint32_t timer_get_elapsed_ms(const Timer *timer)
{
    if (!timer) return 0;
    return (uint32_t)(timer->elapsed_ticks * MS_PER_TICK);
}

/*
    function : timer_delay
    args     : ms
    purpose  : Delay everything for x time in ms
    
    ms    : (uint32_t) Time in MS
*/
void timer_delay(uint32_t ms)
{
    uint32_t start_ticks = timer_get_ticks();
    uint32_t delay_ticks = (uint32_t)(ms / MS_PER_TICK);

    while ((timer_get_ticks() - start_ticks) < delay_ticks)
        ;
}
