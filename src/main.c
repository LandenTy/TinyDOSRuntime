#include <stdio.h>
#include <conio.h>

/* ECS Specific */
#include "../include/ecs.h"
#include "../include/components/transform2D.h"
#include "../include/components/sprite.h"
#include "../include/systems/renderer.h"

/* Runtime Specific */
#include "../include/engine.h"
#include "../include/stdimglib.h"
#include "../include/keyboard.h"
#include "../include/shape.h"
#include "../include/timer.h"
#include "../include/mouse.h"

int main(void)
{
    Timer frameTimer;
    unsigned char far *backBuffer = NULL;
    Image *img = NULL;
    Image *img2 = NULL;
    Entity player;
    Entity p2;
    struct Transform* t;
    unsigned long frameCount = 0;

    /* ==== Initialize ECS ==== */
    Entity_Init();
    Transform_Init();
    Sprite_Init();
    Renderer_Init();

    /* ==== Load image ==== */
    img = load_pcx_8bit("..\\images\\fall.pcx");
    if (!img) {
        printf("Failed to load PCX image: mypic.pcx\n");
        getch();
        return 1;
    }

    img2 = load_pcx_8bit("..\\images\\mypic.pcx");
    if (!img2) {
        printf("Failed to load PCX image: mypic.pcx\n");
        free_image(img);
        getch();
        return 1;
    }

    /* ==== Initialize systems ==== */
    keyboard_init();
    mouse_init();
    set_mode13h();
    set_palette_256(img->palette);

    backBuffer = _fmalloc(SCREEN_SIZE);
    if (!backBuffer) {
        set_text_mode();
        printf("Out of memory allocating backbuffer!\n");
        free_image(img);
        free_image(img2);
        keyboard_shutdown();
        return 1;
    }

    /* ==== Create Player Entity ==== */
    player = Entity_Create();
    p2 = Entity_Create();

    if (player == ENTITY_INVALID || p2 == ENTITY_INVALID) {
        set_text_mode();
        printf("Failed to create entity!\n");
        _ffree(backBuffer);
        free_image(img);
        free_image(img2);
        keyboard_shutdown();
        return 1;
    }

    /* Player sprite follows mouse */
    Transform_Add(player, 50.0f, 50.0f);
    Sprite_Add(player, img, 10);

    /* Second sprite static */
    Transform_Add(p2, 0.0f, 0.0f);
    Sprite_Add(p2, img2, 5);

    timer_start(&frameTimer);

    /* ==== Main Loop ==== */
    while (!get_key_down(KEY_ESCAPE)) {

        set_draw_buffer(backBuffer);
        _fmemset(backBuffer, 0, SCREEN_SIZE);

        get_mouse_position();
        t = Transform_Get(player);

        if (t) {
            t->x = (float)mouse_x;
            t->y = (float)mouse_y;

            /* Keep sprite inside screen bounds */
            if (t->x < 0) t->x = 0;
            if (t->y < 0) t->y = 0;
            if (t->x > SCREEN_WIDTH - img->width)
                t->x = SCREEN_WIDTH - img->width;
            if (t->y > SCREEN_HEIGHT - img->height)
                t->y = SCREEN_HEIGHT - img->height;
        }

        Renderer_DrawAll();
        flip(backBuffer);

        timer_delay(10);
        timer_update(&frameTimer);
        frameCount++;
    }

    /* ==== Exit screen + FPS ==== */
    {
        uint32_t elapsed_ms = timer_get_elapsed_ms(&frameTimer);
        double elapsed_sec = (elapsed_ms > 0) ? elapsed_ms / 1000.0 : 0.0;
        double avgFPS = (elapsed_sec > 0) ? (frameCount / elapsed_sec) : 0.0;

        keyboard_shutdown();
        mouse_shutdown();
        cls(0);
        set_text_mode();

        printf("Total frames: %lu\n", frameCount);
        printf("Elapsed time: %lu ms\n", elapsed_ms);
        printf("Average FPS: %.2f\n", avgFPS);
    }

    /* ==== Cleanup ==== */
    _ffree(backBuffer);
    free_image(img);
    free_image(img2);

    return 0;
}
