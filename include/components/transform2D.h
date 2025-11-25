#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "../ecs.h"

typedef struct Transform {
    float x;
    float y;
} Transform;

/* Public API */
void        Transform_Init(void);
void        Transform_Add(Entity e, float x, float y);
void        Transform_Remove(Entity e);
int         Transform_Has(Entity e);
Transform*  Transform_Get(Entity e);

#endif
