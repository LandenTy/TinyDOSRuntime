#ifndef SPRITE_H
#define SPRITE_H

#include "../ecs.h"
#include "../stdimglib.h"

/* Sprite component */
typedef struct Sprite {
    Image *img;   /* image object */
    int layer;    /* Z-index */
} Sprite;

/* Public API */
void    Sprite_Init(void);
void    Sprite_Add(Entity e, Image *img, int layer);
void    Sprite_Remove(Entity e);
int     Sprite_Has(Entity e);
Sprite* Sprite_Get(Entity e);

#endif
