/*
    Mouse Sample
*/
#include <stdio.h>
#include <conio.h>
#include "../include/engine.h"
#include "../include/stdimglib.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/mouse.h"

int main(void) {
    Timer frameTimer;
    unsigned char far *backBuffer;
    unsigned char *pixels = NULL;
    unsigned char pal[768];
    int w, h;

    int img_x = 50;
    int img_y = 50;

    /* Initialize image */
    if (!load_pcx_8bit("..\\images\\fall.pcx", &pixels, pal, &w, &h)) {
        printf("Failed to load image!\n");
        getch();
        return 1;
    }

    /* Initialize systems */
    keyboard_init();
    mouse_init();
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

    timer_start(&frameTimer);

    while (!get_key_down(KEY_ESCAPE)) {
        timer_start(&frameTimer);
        get_mouse_position();
        img_x = mouse_x;
        img_y = mouse_y;

        /* Keep in bounds */
        if (img_x < 0) img_x = 0;
        if (img_y < 0) img_y = 0;
        if (img_x > SCREEN_WIDTH - w) img_x = SCREEN_WIDTH - w;
        if (img_y > SCREEN_HEIGHT - h) img_y = SCREEN_HEIGHT - h;

        /* Draw frame */
        _fmemset(backBuffer, 0, SCREEN_SIZE);
        draw_image_256(pixels, w, h, img_x, img_y, backBuffer);
        flip(backBuffer);

        timer_delay(100);
        timer_update(&frameTimer);
    }

    /* Cleanup */
    _ffree(backBuffer);
    free_image(pixels);
    keyboard_shutdown();
    mouse_shutdown();
    cls(0);

    return 0;
}
