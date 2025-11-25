#include "../../include/systems/renderer.h"
#include "../../include/ecs.h"
#include "../../include/components/transform2D.h"
#include "../../include/components/sprite.h"
#include "../../include/engine.h"

typedef struct {
    Entity e;
    int layer;
} RenderItem;

void Renderer_Init(void) {}

/*
    Draw all entities in the renderList sorted by layer.
*/
void Renderer_DrawAll(void)
{
    unsigned i, a, b;
    RenderItem renderList[ENTITY_MAX_COUNT];
    int count = 0;

    /* Collect all drawable entities */
    for (i = 0; i < Entity_Max(); i++) {
        if (Entity_IsValid(i) && Transform_Has(i) && Sprite_Has(i)) {
            Sprite* s = Sprite_Get(i);
            if (s->img) {   /* ensure image exists */
                renderList[count].e = i;
                renderList[count].layer = s->layer;
                count++;
            }
        }
    }

    /* Insertion sort by layer */
    for (a = 1; a < (unsigned)count; a++) {
        RenderItem key = renderList[a];
        b = a;
        while (b > 0 && renderList[b - 1].layer > key.layer) {
            renderList[b] = renderList[b - 1];
            b--;
        }
        renderList[b] = key;
    }

    /* Draw all sorted entities */
    for (i = 0; i < (unsigned)count; i++) {
        Entity e = renderList[i].e;
        struct Transform *t = Transform_Get(e);
        Sprite *s = Sprite_Get(e);
        Image *im;

        if (!t || !s)
            continue;

        im = s->img;  /* must be declared at top in C89 */

        if (im && im->pixels) {
            draw_image_256(
                im->pixels,
                im->width,
                im->height,
                (int)t->x,
                (int)t->y
            );
        }
    }
}
