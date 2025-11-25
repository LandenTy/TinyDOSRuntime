#include <dos.h>
#include <conio.h>
#include "gamepad.h"

#define GAMEPORT 0x201
#define TIMEOUT  30000

/*
    function : Joystick_Init
    args     : 
    purpose  : Initialize the joystick
*/
void joystick_init(void)
{}

/*
    function : Joystick_Read
    args     : js
    purpose  : Get the current state of the joystick
    (buttons pressed, joystick moved).

    js      :  (JoystickState) State of Joystick
*/
void joystick_read(JoystickState* js)
{
    unsigned char v;
    unsigned long countX = 0, countY = 0;
    unsigned long i;

    /* Step 1: Trigger discharge */
    outp(GAMEPORT, 0);

    /* Step 2: Time axis bits */
    for (i = 0; i < TIMEOUT; ++i) {
        v = inp(GAMEPORT);

        if (v & 0x01) countX++; /* X axis */
        if (v & 0x02) countY++; /* Y axis */

        /* Stop when both bits have dropped to 0 */
        if (!(v & 0x03)) break;
    }

    js->x = (int)countX;
    js->y = (int)countY;

    /* Step 3: Buttons (active low) */
    v = inp(GAMEPORT);

    js->button1 = (v & 0x10) ? 0 : 1;
    js->button2 = (v & 0x20) ? 0 : 1;
}
