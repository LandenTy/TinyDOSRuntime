#include "../../include/components/sprite.h"

static Sprite sprite_data[ENTITY_MAX_COUNT];
static int sprite_alive[ENTITY_MAX_COUNT];

void Sprite_Init(void)
{
    unsigned i;
    for (i = 0; i < ENTITY_MAX_COUNT; i++) {
        sprite_alive[i] = 0;
        sprite_data[i].img = NULL;
        sprite_data[i].layer = 0;
    }
}

void Sprite_Add(Entity e, Image *img, int layer)
{
    if (e >= ENTITY_MAX_COUNT) return;

    sprite_alive[e] = 1;
    sprite_data[e].img   = img;
    sprite_data[e].layer = layer;
}

void Sprite_Remove(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) return;
    sprite_alive[e] = 0;
}

int Sprite_Has(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) return 0;
    return sprite_alive[e];
}

Sprite* Sprite_Get(Entity e)
{
    if (!Sprite_Has(e)) return NULL;
    return &sprite_data[e];
}
