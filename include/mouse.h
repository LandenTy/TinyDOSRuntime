#ifndef MOUSE_H
#define MOUSE_H

#include "../include/stdimglib.h"

extern int mouse_x;
extern int mouse_y;
extern unsigned short mouse_b; 

void mouse_init(void);
void mouse_shutdown(void);

void get_mouse_state(void); // Get whatever option is happening on the mouse (i.e left-click, right-click, middle-click, scroll, etc.)
void get_mouse_down(void); // Get mouse button down, will take in mouse button type (Left, Right, Middle)
void get_mouse_hold(void); // Get mouse button hold, will take in mouse button type (Left, Right, Middle)
void get_mouse_up(void);   // Get mouse button up, will take in mouse button type (Left, Right, Middle)
void get_mouse_position(void); // Returns (x,y) position of mouse cursor

void set_mouse_position(const float x, const float y); // Takes in floats for x, y and sets the cursor position
void set_mouse_cursor(const char *path); // Set Cursor to custom PCX image
void set_mouse_sensitivity(const float sensitivity); // Takes in float, and sets how sensitive the mouse is when moved

#endif
