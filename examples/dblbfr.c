/*
    DOUBLE BUFFERING SAMPLE
*/
#include <dos.h>
#include <stdio.h>
#include <conio.h>

#include "../include/engine.h"
#include "../include/shape.h"
#include "../include/stdimglib.h"
#include "../include/keyboard.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

int main(void) {
    unsigned char far *backBuffer;
    unsigned char *pixels = NULL;
    unsigned char pal[768];
    int x,y,w,h,i;
    int img_x = 50;
    int img_y = 50;
    int speed = 5;

    if (!load_pcx_8bit("..\\images\\fall.pcx", &pixels, pal, &w, &h)) {
        printf("Failed to load image!\n");
        getch();
        return 1;
    }

    keyboard_init();
    set_mode13h();
    set_palette_256(pal);

    backBuffer = _fmalloc(SCREEN_SIZE);
    if (!backBuffer) {
        set_text_mode();
        printf("Out of memory!\n");
        free_image(pixels);
        keyboard_shutdown();
        return 1;
    }

    while (!get_key_down(KEY_ESCAPE)) {
        _fmemset(backBuffer, 0, SCREEN_SIZE); 

        /* Draw image to back buffer */
        draw_image_256_to_buffer(pixels, w, h, img_x, img_y, backBuffer);
        flip(backBuffer);

        /* Movement controls */
        if (get_key_down(KEY_A)) img_x -= speed;
        if (get_key_down(KEY_D)) img_x += speed;
        if (get_key_down(KEY_W)) img_y -= speed;
        if (get_key_down(KEY_S)) img_y += speed;

        /* Keep image in bounds */
        if (img_x < 0) img_x = 0;
        if (img_y < 0) img_y = 0;
        if (img_x > SCREEN_WIDTH - w) img_x = SCREEN_WIDTH - w;
        if (img_y > SCREEN_HEIGHT - h) img_y = SCREEN_HEIGHT - h;

        // KEEP HERE OR ELSE COMPUTER WILL KILL ITSELF
        delay(10);
    }

    _ffree(backBuffer);
    free_image(pixels);
    keyboard_shutdown();
    cls(0);

    return 0;
}
