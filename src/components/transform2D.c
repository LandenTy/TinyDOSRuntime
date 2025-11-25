#include "../../include/components/transform2D.h"

/* Component storage */
static Transform transform_data[ENTITY_MAX_COUNT];
static int transform_alive[ENTITY_MAX_COUNT];

/*
    function : Transform_Init
    args     : 
    purpose  : Initialize Transform Component   
*/
void Transform_Init(void)
{
    unsigned i;
    for (i = 0; i < ENTITY_MAX_COUNT; ++i) {
        transform_alive[i] = 0;
        transform_data[i].x = 0.0f;
        transform_data[i].y = 0.0f;
    }
}

/*
    function : Transform_Add
    args     : e, x, y
    purpose  : Adds a transform to an entity at (x,y)

      e    :     (Entity)             Entity    
      x    :     (floats)               x
      y    :     (floats)               y
*/
void Transform_Add(Entity e, float x, float y)
{
    if (e >= ENTITY_MAX_COUNT) {
        return;
    }

    transform_alive[e] = 1;
    transform_data[e].x = x;
    transform_data[e].y = y;
}

/*
    function : Transform_Remove
    args     : e
    purpose  : Removes the transform from the entity

      e    :     (Entity)             Entity    
*/
void Transform_Remove(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) {
        return;
    }
    transform_alive[e] = 0;
}

/*
    function : Transform_Has
    args     : e
    purpose  : Checks if the component is still active
    in the scene.

      e    :     (Entity)             Entity
*/
int Transform_Has(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) {
        return 0;
    }
    return transform_alive[e];
}

/*
    function : Transform_Get
    args     : e
    purpose  : Gets the component data for the entity
    (if-active).

      e    :     (Entity)             Entity
*/
Transform* Transform_Get(Entity e)
{
    if (!Transform_Has(e)) {
        return 0;
    }
    return &transform_data[e];
}
