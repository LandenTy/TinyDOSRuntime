#include <conio.h>
#include <dos.h>
#include <stdio.h>

#include "../include/engine.h"
#include "../include/shape.h"
#include "../include/stdimglib.h"
#include "../include/keyboard.h"

int main(void) {
    unsigned char *pixels = NULL;
    unsigned char pal[768];
    int w, h;

    int poly_x[5] = {50, 80, 100, 60, 30};
    int poly_y[5] = {30, 20, 60, 90, 70};

    if (!load_pcx_8bit("..\\images\\fall.pcx", &pixels, pal, &w, &h)) {
        printf("Failed to load image!\n");
        getch();
        return 1;
    }

    keyboard_init();
    set_mode13h();
    set_palette_256(pal);
    draw_image_256(pixels, w, h, 0, 0);
    
    // Wait until ESC is pressed
    while (!get_key_down(KEY_ESCAPE)) {
        delay(10);
    }

    free_image(pixels);
    keyboard_shutdown();
    cls(0);

    return 0;
}
