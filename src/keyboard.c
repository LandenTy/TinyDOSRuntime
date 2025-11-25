#include <dos.h>
#include <i86.h>
#include <conio.h>

#include "../include/keyboard.h"

static void interrupt (*old_isr)(void) = 0;

static KeyCode scancode_to_keycode[128] = {
    KEY_NONE, KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
    KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUALS, KEY_BACKSPACE,
    KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I,
    KEY_O, KEY_P, KEY_LBRACKET, KEY_RBRACKET, KEY_ENTER, KEY_LCTRL,
    KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
    KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE, KEY_LSHIFT,
    KEY_BACKSLASH, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
    KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RSHIFT, KEY_KP_MULTIPLY,
    KEY_LALT, KEY_SPACE, KEY_CAPSLOCK, KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT
};

static void interrupt keyboard_isr(void)
{
    unsigned char scancode = inp(0x60);
    unsigned char make = !(scancode & 0x80);
    unsigned char code = scancode & 0x7F;
    KeyCode key = KEY_NONE;

    if (code < 128)
        key = scancode_to_keycode[code];

    if (key != KEY_NONE) {
        if (make)
            SET_BIT(key_state, key);
        else
            CLR_BIT(key_state, key);

        if (make)
            SET_BIT(key_pressed, key);
    }
    outp(0x20, 0x20);
}

/*
    function : keyboard_init
    args     : 
    purpose  : Initializes the keyboard functions,
    swaps out old ISR for new ISR using Hardware
    Interrupt 9H (0x9).
*/
void keyboard_init(void)
{
    int i;
    for (i = 0; i < sizeof(key_state); ++i) {
        key_state[i] = 0;
        key_pressed[i] = 0;
    }

    old_isr = _dos_getvect(KEYBOARD_IRQ);
    _dos_setvect(KEYBOARD_IRQ, keyboard_isr);
}

/*
    function : keyboard_shutdown
    args     : 
    purpose  : Shutsdown the keyboard driver and
    sets the old ISR back to the current one.
*/
void keyboard_shutdown(void)
{
    if (old_isr)
        _dos_setvect(KEYBOARD_IRQ, old_isr);
}

/*
    function : get_key_down
    args     : key
    purpose  : Gets the bit for the key pressed
    as denoted by the Keycode, key:

    key         Type: KeyCode
*/
int get_key_down(KeyCode key)
{
    return GET_BIT(key_state, key) != 0;
}

/*
    function : get_key_pressed
    args     : key
    purpose  : Checks the bit if the key
    is being held down.

    key         Type: KeyCode
*/
int get_key_pressed(KeyCode key)
{
    if (GET_BIT(key_pressed, key)) {
        CLR_BIT(key_pressed, key);
        return 1;
    }
    return 0;
}

/*
    function : get_key_up
    args     : key
    purpose  : Checks the bit if the key
    is no longer being held.

    key         Type: KeyCode
*/
int get_key_up(KeyCode key)
{
    return -1;
}
