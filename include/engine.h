#ifndef ENGINE_H
#define ENGINE_H

#include <malloc.h>

/* --- Definitions --- */
#define VGA_SEGMENT 0xA000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

/* --- Global drawing buffer pointer --- */
extern unsigned char far *current_buffer;

/* --- Core video functions --- */
void set_draw_buffer(unsigned char far *buffer);
void set_mode13h(void);
void flip(unsigned char far *buffer);
void set_text_mode(void);
void cls(unsigned char color);
void putpixel(int x, int y, unsigned char color);
void wait_key(void);

/* --- Image Rendering --- */
void set_palette_256(unsigned char pal[768]);
void draw_image_256(unsigned char *pixels, int w, int h,
                    int x, int y);
void set_default_palette(void);

#endif
