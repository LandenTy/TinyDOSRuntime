#include "../include/ecs.h"

/* Entity state arrays */
static int entity_alive[ENTITY_MAX_COUNT];
static Entity free_stack[ENTITY_MAX_COUNT];
static unsigned free_top;
static unsigned active_count;

/*
    function : Entity_Init
    args     : 
    purpose  : As long as the stack is NOT full, allocate the list of entities,
    so you can just add them as you go.
*/
void Entity_Init(void)
{
    unsigned i;
    for (i = 0; i < ENTITY_MAX_COUNT; ++i) {
        entity_alive[i] = 0;
        free_stack[i] = (Entity)i;
    }
    free_top = ENTITY_MAX_COUNT;
    active_count = 0;
}

/*
    function : Entity_Create
    args     : 
    purpose  : Create a new Entity IF there is enough room on the stack
*/
Entity Entity_Create(void)
{
    Entity id;
    if (free_top == 0) {
        return ENTITY_INVALID;
    }
    free_top--;
    id = free_stack[free_top];
    entity_alive[id] = 1;
    active_count++;

    return id;
}

/*
    function : Entity_Destroy
    args     : Entity e
    purpose  : Destroy the entity as long as it's valid (Not in non-existent memory)

       e     :    Entity
*/
void Entity_Destroy(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) {
        return;
    }
    if (!entity_alive[e]) {
        return;
    }

    entity_alive[e] = 0;
    free_stack[free_top++] = e;
    active_count--;
}

/*
    function : Entity_IsValid
    args     : Entity e
    purpose  : Check if an Entity is valid 
    (is alive and under the max entity count)
    
       e     :    Entity
*/
int Entity_IsValid(Entity e)
{
    if (e >= ENTITY_MAX_COUNT) {
        return 0;
    }
    return entity_alive[e];
}

/*
    function : Entity_IsValid
    args     : 
    purpose  : Get the number of entities currently active
*/
unsigned Entity_Count(void)
{
    return active_count;
}

/*
    function : Entity_IsValid
    args     : 
    purpose  : Get the max number of entities which can be
    instantiated on/off of the screen.
*/
unsigned Entity_Max(void)
{
    return ENTITY_MAX_COUNT;
}
