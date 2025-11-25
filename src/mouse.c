#include "../include/mouse.h"
#include <i86.h>

/* ------------------------------------------------------------
   Exposed Variables
   ------------------------------------------------------------ */
int mouse_x = 0;
int mouse_y = 0;
unsigned short mouse_b = 0;

/* ------------------------------------------------------------
   Internal state
   ------------------------------------------------------------ */

static int mouse_installed = 0;
static float mouse_sensitivity = 1.0f;

/* Remember last button states for detecting up/down transitions */
static unsigned short prev_buttons = 0;


/*
    function : mouse_init
    args     : 
    purpose  : Setup the mouse to work on DOS
*/
void mouse_init(void)
{
    union REGS regs;

    regs.w.ax = 0;     /* Mouse reset & status */
    int86(0x33, &regs, &regs);

    if (regs.w.ax == 0)
        mouse_installed = 0;
    else
        mouse_installed = 1;
}

/*
    function : mouse_shutdown
    args     : 
    purpose  : Shutdown the mouse pointer to return to text mode
*/
void mouse_shutdown(void)
{
    mouse_installed = 0;
}


/*
    function : get_mouse_state
    args     : 
    purpose  : Checks if the mouse is plugged-in
    and setup properly
*/
void get_mouse_state(void)
{
    union REGS regs;

    if (!mouse_installed)
        return;

    regs.w.ax = 3;
    int86(0x33, &regs, &regs);
}

/*
    function : get_mouse_position
    args     : 
    purpose  : Gets the position of the mouse
    pointer.
*/
void get_mouse_position(void)
{
    union REGS regs;

    if (!mouse_installed)
        return;

    regs.w.ax = 3;
    int86(0x33, &regs, &regs);

    mouse_x = (int)(regs.w.cx * mouse_sensitivity);
    mouse_y = (int)(regs.w.dx * mouse_sensitivity);
    mouse_b = regs.w.bx & 0x0007; 
}


/*
    function : query_buttons
    args     : 
    purpose  : Gets what mouse buttons are currently
    being pressed. (left mouse, middle mouse, right mouse,
    or nothing)
*/
static unsigned short query_buttons(void)
{
    union REGS regs;

    regs.w.ax = 3;
    int86(0x33, &regs, &regs);

    return regs.w.bx & 0x0007;  /* left = bit0, right = bit1, middle = bit2 */
}

/*
    function : get_mouse_down
    args     : 
    purpose  : Checks if the mouse button
    is clicked (left, right, or middle).
*/
void get_mouse_down(void)
{
    unsigned short curr;

    if (!mouse_installed)
        return;

    curr = query_buttons();

    /* Detect transitions (button was 0, now is 1) */
    /* Example: left_down = (!(prev_buttons & 1) && (curr & 1)) */

    prev_buttons = curr;
}

/*
    function : get_mouse_hold
    args     : 
    purpose  : Checks if the mouse
    button is held down (left,
    middle, or right).
*/
void get_mouse_hold(void)
{
    unsigned short curr;

    if (!mouse_installed)
        return;

    curr = query_buttons();

    /* Example: left_hold = (curr & 1); */

    prev_buttons = curr;
}

/*
    function : get_mouse_up
    args     : 
    purpose  : Checks if the mouse
    button is released (left, right,
    or middle).
*/
void get_mouse_up(void)
{
    unsigned short curr;

    if (!mouse_installed)
        return;

    curr = query_buttons();

    /* Detect transitions (button was 1, now is 0) */
    /* Example: left_up = ((prev_buttons & 1) && !(curr & 1)) */

    prev_buttons = curr;
}

/*
    function : set_mouse_sensitivity
    args     : sensitivity
    purpose  : Adjusts the mouse sensitivity
    through software scaling, based on (x,y)
    positions.
*/
void set_mouse_sensitivity(const float sensitivity)
{
    /* We cannot modify INT 33h hardware sensitivity from DOS,
       so we apply software scaling to returned positions.
       Store sensitivity and let get_mouse_position() use it.
    */
    mouse_sensitivity = sensitivity;
}
