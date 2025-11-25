#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/engine.h"

/* VGA Buffers */
unsigned char far* VGA = (unsigned char far*)MK_FP(VGA_SEGMENT, 0);
unsigned char far *current_buffer = 0;

/*
    function : set_draw_buffer
    args     : unsigned char far *buffer
    purpose  : Allows you to define your own back
    buffer in main.c

    *buffer      :  unsigned char far - backbuffer
*/
void set_draw_buffer(unsigned char far *buffer)
{
    current_buffer = buffer;
}

/*
    function : set_mode13h
    args     : 
    purpose  : Sets the video mode to mode13h
*/
void set_mode13h(void) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = 0x13;
    int86(0x10, &regs, &regs);
}

/*
    function : flip
    args     : backbuffer
    purpose  : Copies information to and from the
    backbuffer, and redraws the screen.
*/
void flip(unsigned char far *buffer)
{
    _fmemcpy(VGA, buffer, SCREEN_SIZE);
}

/*
    function : set_text_mode
    args     : 
    purpose  : Sets the video mode to text mode
*/
void set_text_mode(void) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = 0x03;
    int86(0x10, &regs, &regs);
}

/*
    function : putpixel
    args     : x, y, color
    purpose  : Draws a pixel at (x,y) with a color
    on the backbuffer (if one is available), straight
    to VGA if there is no backbuffer.

      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
    color    :      (unsigned char)    Color (8bpp)

*/
void putpixel(int x, int y, unsigned char color) {
    unsigned char far *buf;

    if (current_buffer)
        buf = current_buffer;
    else
        buf = VGA;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;

    buf[y * SCREEN_WIDTH + x] = color;
}

/*
    function : cls
    args     : color
    purpose  : Clears the screen with a selected color

      color      :     (unsigned char)      Color (8bpp)
*/
void cls(unsigned char color) {
    unsigned char far *buf = current_buffer ? current_buffer : VGA;
    _fmemset(buf, color, SCREEN_WIDTH * SCREEN_HEIGHT);
}

/*
    function : set_palette_256
    args     : palette
    purpose  : Sets the VGA color palette so images or other
    qualities can have the proper colors.

      palette      :     (unsigned char)      Pal[768] (8bpp)
*/
void set_palette_256(unsigned char pal[768]) {
    int i;
    outp(0x3C8, 0);
    for (i = 0; i < 256 * 3; ++i)
        outp(0x3C9, pal[i] >> 2);
}

/*
    function : draw_image_256
    args     : pixels, w, h, x, y
    purpose  : Draws the image at (x,y) with dimensions
    (w,h) using the PCX Pixel Array found in ___.pcx
    
    pixels   :      (unsigned char)    *Pixels (8bpp)
      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
      w      :           (Int)            Width
      h      :           (Int)            Height

*/
void draw_image_256(unsigned char *pixels, int w, int h,
                    int x, int y)
{
    int r;
    unsigned char far *buf = current_buffer ? current_buffer : VGA;

    if (y >= SCREEN_HEIGHT) return;
    if (x >= SCREEN_WIDTH) return;

    for (r = 0; r < h && (y + r) < SCREEN_HEIGHT; ++r) {
        int copy_width = w;
        if (x + w > SCREEN_WIDTH)
            copy_width = SCREEN_WIDTH - x;

        _fmemcpy(buf + (y + r) * SCREEN_WIDTH + x,
                 pixels + r * w,
                 copy_width);
    }
}

/*
    function : wait_key
    args     : 
    purpose  : Keep the window open until you press a key
*/
void wait_key(void) {
    while (!_kbhit());
    getch();
}
