#ifndef ENTITY_H
#define ENTITY_H

/* Use 16-bit IDs. */
typedef unsigned short Entity;

#define ENTITY_MAX_COUNT 2048 /* How many on/off-screen entities can be instantiated at any given time */
#define ENTITY_INVALID 0xFFFF /* Const. Defines an invalid or unused entity (and when to exclude it from runtime). */

/* Public interface */
void        Entity_Init(void);
Entity      Entity_Create(void);
void        Entity_Destroy(Entity e);
int         Entity_IsValid(Entity e);
unsigned    Entity_Count(void);
unsigned    Entity_Max(void);

#endif
