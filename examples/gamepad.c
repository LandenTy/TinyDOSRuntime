/*
    Gamepad Sample with Image Manipulation
*/
#include <stdio.h>
#include <conio.h>

#include "../include/engine.h"
#include "../include/stdimglib.h"
#include "../include/keyboard.h"
#include "../include/timer.h"
#include "../include/gamepad.h"

int main(void) {
    Timer frameTimer;
    unsigned char far *backBuffer;
    unsigned char *pixels = NULL;
    unsigned char pal[768];
    int w, h;

    int img_x = 50;
    int img_y = 50;

    JoystickState js;

    /* Load image */
    if (!load_pcx_8bit("..\\images\\fall.pcx", &pixels, pal, &w, &h)) {
        printf("Failed to load image!\n");
        getch();
        return 1;
    }

    /* Initialize systems */
    keyboard_init();
    joystick_init();

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

        /* ----- Joystick movement ----- */
        joystick_read(&js);

        /*
            Adjust the axis thresholds to match your device.
            Typical raw readings for analog sticks ~0..15000+
        */

        if (js.x < 2000)     img_x -= 2;  /* Left  */
        if (js.x > 8000)     img_x += 2;  /* Right */
        if (js.y < 2000)     img_y -= 2;  /* Up    */
        if (js.y > 8000)     img_y += 2;  /* Down  */

        /* Optional: joystick button 1 recenters the image */
        if (js.button1) {
            img_x = (SCREEN_WIDTH  - w) / 2;
            img_y = (SCREEN_HEIGHT - h) / 2;
        }

        /* Keep image inside screen bounds */
        if (img_x < 0) img_x = 0;
        if (img_y < 0) img_y = 0;
        if (img_x > SCREEN_WIDTH - w)  img_x = SCREEN_WIDTH - w;
        if (img_y > SCREEN_HEIGHT - h) img_y = SCREEN_HEIGHT - h;

        /* ----- Draw frame ----- */
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

    cls(0);
    return 0;
}
