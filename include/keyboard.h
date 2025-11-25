#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keycode.h"

/* Definitions */
#define KEYBOARD_IRQ 0x09
#define SET_BIT(arr, k)   ((arr)[(k)/8] |=  (1 << ((k)%8)))
#define CLR_BIT(arr, k)   ((arr)[(k)/8] &= ~(1 << ((k)%8)))
#define GET_BIT(arr, k)   ((arr)[(k)/8] &   (1 << ((k)%8)))

static unsigned char key_state[(KEY_COUNT + 7) / 8];
static unsigned char key_pressed[(KEY_COUNT + 7) / 8];

/* Initialize keyboard driver and install ISR */
void keyboard_init(void);
void keyboard_shutdown(void);

/* Check key state */
int get_key_down(KeyCode key);
int get_key_pressed(KeyCode key);
int get_key_up(KeyCode key);

#endif
